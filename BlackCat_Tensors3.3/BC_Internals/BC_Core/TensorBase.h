/*
 * Tensor_Base.h
 *
 *  Created on: Jan 6, 2018
 *      Author: joseph
 */

#ifndef TENSOR_BASE_H_
#define TENSOR_BASE_H_

#include "Implementation_Core/Tensor_Operations.h"
#include "Implementation_Core/Tensor_Utility.h"
#include "Implementation_Core/Tensor_Core.cu"

namespace BC {

using MTF::ifte;		//if then else
using MTF::isPrim;
using MTF::shell_of;
using MTF::isCore;

template<class,class> class DISABLED;
template<class,class> class Scalar;
template<class,class> class Vector;
template<class,class> class Matrix;
template<class,class> class Cube;

template<int> struct base;

template<> struct base<0> { template<class t, class m> using type = Scalar<t,m>;  template<class t, class m> using slice = DISABLED<t, m>; };
template<> struct base<1> { template<class t, class m> using type = Vector<t, m>; template<class t,class m> using slice = Scalar<t, m>; };
template<> struct base<2> { template<class t, class m> using type = Matrix<t, m>; template<class t,class m> using slice = Vector<t, m>; };
template<> struct base<3> { template<class t, class m> using type = Cube<t, m>;   template<class t,class m> using slice = Matrix<t, m>; };

template<int,int, class> struct Rank;
template<class> struct ranker;
template<class a, class b> struct ranker<Scalar<a,b>> { static constexpr int value = 0; using type = Rank<value, value>; };
template<class a, class b> struct ranker<Vector<a,b>> { static constexpr int value = 1; using type = Rank<value, value>;  };
template<class a, class b> struct ranker<Matrix<a,b>> { static constexpr int value = 2; using type = Rank<value, value>;  };
template<class a, class b> struct ranker<Cube<a,b>>   { static constexpr int value = 3; using type = Rank<value, value>;  };

template<class T> using _scalar = typename MTF::determine_scalar<T>::type;
template<class T> using _mathlib = typename MTF::determine_mathlibrary<T>::type;
template<class T> using _ranker  = typename ranker<T>::type;

template<class> struct determine_functor;
template<template<class...> class tensor, class functor, class... set>
struct determine_functor<tensor<functor, set...>>{

	using derived = tensor<functor,set...>;
	using fscal = functor;
	using type = ifte<MTF::isPrimitive<functor>::conditional, Tensor_Core<_scalar<derived>, _mathlib<derived>, _ranker<derived>>, functor>;
};

template<class T>
using _functor = typename determine_functor<T>::type;
template<class T> using _fscal = typename determine_functor<T>::fscal;

template<class derived>
class TensorBase :
				public Tensor_Operations <_scalar<derived>, _functor<derived>, derived,  _mathlib<derived>>,
				public Tensor_Utility    <_scalar<derived>, derived, _mathlib<derived>, isPrim<_fscal<derived>> || isCore<_functor<derived>>::conditional>

{

protected:

	static constexpr int RANK = ranker<derived>::type::inner_rank;
	static constexpr int LD_RANK = ranker<derived>::type::outer_rank;
	using Mathlib =  _mathlib<derived>;

	using self = TensorBase<derived>;
	using math_parent  = Tensor_Operations <_scalar<derived>, _functor<derived>, derived,  _mathlib<derived>>;
	using functor_type = _functor<derived>;

	template<class> struct DISABLED;
	static constexpr bool GENUINE_TENSOR =isPrim<_fscal<derived>> || isCore<_functor<derived>>::conditional;
	functor_type black_cat_array;

public:
	using math_parent::operator=;
	operator  const derived&() const { return static_cast<const derived&>(*this); }
	operator  		derived&() 		 { return static_cast<	    derived&>(*this); }


	template<class atLeastOneParam, class... params> TensorBase(const atLeastOneParam& alop, const params&... p) : black_cat_array(alop, p...) { }

	template<class    U> using deriv   = typename shell_of<derived>::type<U, Mathlib>;
	template<class... U> using functor = typename shell_of<functor_type>::type<U...>;

	template<class var>
	static std::vector<int> shapeOf(const var& v) {
		std::vector<int> sh(v.rank());
		for (int i = 0; i < v.rank(); ++i){
			sh[i] = v.dimension(i);
		}
		return sh;
	}
	template<class U>
	TensorBase(const deriv<U>& tensor) : black_cat_array(shapeOf(tensor)) {
		this->assert_same_size(tensor);
		Mathlib::copy(this->black_cat_array, tensor.data(), this->size());
	}
	template<class... U> TensorBase(const deriv<functor<U...>>& tensor) : black_cat_array(tensor.black_cat_array) {}

	TensorBase(		 derived&& tensor) : black_cat_array(tensor.black_cat_array){}
	TensorBase(const derived&  tensor) : black_cat_array(tensor.black_cat_array){}

	int rank() const { return black_cat_array.rank(); }
	int size() const { return black_cat_array.size(); }
	int rows() const { return black_cat_array.rows(); }
	int cols() const { return black_cat_array.cols(); }
	int LD_rows() const { return black_cat_array.LD_rows(); }
	int LD_cols() const { return black_cat_array.LD_cols(); }
	void resetShape(std::vector<int> sh) { black_cat_array.resetShape(sh); }

	int dimension(int i)		const { return black_cat_array.dimension(i); }
	void printDimensions() 		const { black_cat_array.printDimensions();   }
	void printLDDimensions()	const { black_cat_array.printLDDimensions(); }

	const auto InnerShape() const 			{ return black_cat_array.InnerShape(); }
	const auto OuterShape() const 			{ return black_cat_array.OuterShape(); }


	const functor_type& _data() const { return black_cat_array; }
		  functor_type& _data()		  { return black_cat_array; }

	derived& operator =(const derived& tensor) {
		this->assert_same_size(tensor);
		Mathlib::copy(this->data(), tensor.data(), this->size());
		return *this;
	}


	const auto slice(int i) const { return black_cat_array.slice(i); }
		  auto slice(int i) 	  { return black_cat_array.slice(i); }

		  auto operator [] (int i) 		 { return typename base<RANK>::slice<decltype(slice(0)), Mathlib>(slice(i)); }
	const auto operator [] (int i) const { return typename base<RANK>::slice<decltype(slice(0)), Mathlib>(slice(i)); }

	const auto& operator() (int i) const { return this->data()[i]; }
		  auto& operator() (int i) 	     { return this->data()[i]; }

};

}


#endif /* TENSOR_BASE_H_ */

