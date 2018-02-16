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
#include "Implementation_Core/Tensor_Core.h"
#include "../BC_MathLibraries/Mathematics_CPU.h"
#include "../BC_MathLibraries/Mathematics_GPU.cu"


namespace BC {

template<bool var, class a, class b>
using ifte = typename std::conditional<var, a, b>::type; //ifte -- if than, else

template<class T>
static constexpr bool prim = MTF::isPrimitive<T>::conditional;


template<class T, class derived, class Mathlib, class voider = void>
class TensorBase :
				public Tensor_Operations <T, ifte<prim<T>, Tensor_Core<T, Mathlib>, T>, derived, Mathlib>,
				public Tensor_Utility    <T, derived, Mathlib, prim<T>>

{

protected:
	using math_parent  = Tensor_Operations<T, ifte<prim<T>, Tensor_Core<T, Mathlib>, T>, derived, Mathlib>;
	using functor_type 			=  ifte<prim<T>, Tensor_Core<T, Mathlib>, T>;
	functor_type black_cat_array;

public:
	template<class... params>
	TensorBase(const params&... p) : black_cat_array(p...) {}
	TensorBase(		 derived&& tensor) : black_cat_array(tensor.black_cat_array){}
	TensorBase(const derived&  tensor) : black_cat_array(tensor.black_cat_array){}

	using math_parent::operator=;

	operator  const derived&() const { return static_cast<const derived&>(*this); }
	operator  		derived&() 		 { return static_cast<	    derived&>(*this); }

	int rank() const { return black_cat_array.rank(); }
	int size() const { return black_cat_array.size(); }
	int rows() const { return black_cat_array.rows(); }
	int cols() const { return black_cat_array.cols(); }
	int LD_rows() const { return black_cat_array.LD_rows(); }
	int LD_cols() const { return black_cat_array.LD_cols(); }

	int dimension(int i)		const { return black_cat_array.dimension(i); }
	void printDimensions() 		const { black_cat_array.printDimensions();   }
	void printLDDimensions()	const { black_cat_array.printLDDimensions(); }

	const int* InnerShape() const 			{ return black_cat_array.InnerShape(); }
	auto accessor_packet(int index) const   { return black_cat_array.accessor_packet(index); }
	auto transpose_packet() 		const   { return black_cat_array.transpose_packet();}

	auto dotproduct_packet(int eval_order, const Tensor_Core<T, Mathlib>& sh) const
											{ return black_cat_array.dotproduct_packet(eval_order, sh.black_cat_array); }

	const functor_type& _data() const { return black_cat_array;  }
		  functor_type& _data()		  { return black_cat_array; }
};

}


#endif /* TENSOR_BASE_H_ */
