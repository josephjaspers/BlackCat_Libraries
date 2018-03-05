/*
 * Expression_Binary_Dotproduct_impl2.h
 *
 *  Created on: Jan 23, 2018
 *      Author: joseph
 */
#ifdef  __CUDACC__
#ifndef EXPRESSION_BINARY_DOTPRODUCT_IMPL2_H_
#define EXPRESSION_BINARY_DOTPRODUCT_IMPL2_H_

#include "../BC_MetaTemplateFunctions/Simple.h"
#include "../BC_MetaTemplateFunctions/Adhoc.h"
#include "../BC_Core/Implementation_Core/Determiners.h"
#include <iostream>
#include <type_traits>

namespace BC {

template<class, class, class, class> 	class binary_expression_scalar_R;
template<class, class, class, class> 	class binary_expression_scalar_L;
template<class, class 			   > 	class unary_expression_transpose;
template<class, class, class, class> 	class binary_expression;
template<class>						 	class Tensor_Core;
										class mul;

template<class T> T&  cc(const T&  param) { return const_cast<T&> (param); }
template<class T> T&& cc(const T&& param) { return const_cast<T&&>(param); }
template<class T> T*  cc(const T*  param) { return const_cast<T*> (param); }

//DEFAULT TYPE
template<class> struct det_eval {
	static constexpr bool evaluate = true;
	static constexpr bool transposed = false;
	static constexpr bool scalar = false;
	template<class param> static auto getScalar(const param& p)-> typename MTF::determine_scalar<param>::type* { return nullptr; }
	template<class param> static auto getArray(const param& p) -> typename MTF::determine_scalar<param>::type*  { throw std::invalid_argument("Attempting to use an array from an unevaluated context"); }
};

//IF TENSOR CORE (NON EXPRESSION)
template<class deriv> struct det_eval<Tensor_Core<deriv>> {
	static constexpr bool evaluate = false;
	static constexpr bool transposed = false;
	static constexpr bool scalar = false;

	template<class param> static _scalar<deriv>* getScalar(const param& p) { return nullptr; }
	template<class param> static _scalar<deriv>* getArray(const param& p) { return cc(p); }
};
////IF TRANSPOSE
template<class T, class deriv>
struct det_eval<unary_expression_transpose<T, Tensor_Core<deriv>>> {
	static constexpr bool evaluate = false;
	static constexpr bool transposed = true;
	static constexpr bool scalar = false;

	template<class param> static T* getScalar(const param& p) { return nullptr; }
	template<class param> static T* getArray(const param& p) { return cc(p.array); }
};


//IF A SCALAR BY TENSOR MUL OPERATION R
template<class T, class d1, class d2>
struct det_eval<binary_expression_scalar_R<T, mul, Tensor_Core<d1>, Tensor_Core<d2>>> {
	static constexpr bool evaluate = false;
	static constexpr bool transposed = false;
	static constexpr bool scalar = true;

	template<class param> static T* getScalar(const param& p) { return cc(p.right); }
	template<class param> static T* getArray(const param& p) { return cc(p.left); }
};

//IF A SCALAR BY TENSOR MUL OPERATION L
template<class T, class d1, class d2>
struct det_eval<binary_expression_scalar_L<T, mul, Tensor_Core<d1>, Tensor_Core<d2>>> {
	static constexpr bool evaluate = false;
	static constexpr bool transposed = false;
	static constexpr bool scalar = true;
	template<class param> static T* getScalar(const param& p) { return cc(p.left); }
	template<class param> static T* getArray(const param& p) { return cc(p.right); }
};

//IF A SCALAR BY TENSOR MUL OPERATION R + TRANSPOSED
template<class T, class d1, class d2>
struct det_eval<binary_expression_scalar_R<T, mul, unary_expression_transpose<T, Tensor_Core<d1>>, Tensor_Core<d2>>> {
	static constexpr bool evaluate = false;
	static constexpr bool transposed = true;
	static constexpr bool scalar = true;

	template<class param> static T* getScalar(const param& p) { return cc(p.right); }
	template<class param> static T* getArray(const param& p) { return cc(p.left.array); }
};

//IF A SCALAR BY TENSOR MUL OPERATION L + TRANSPOSED
template<class T, class d1, class d2>
struct det_eval<binary_expression_scalar_L<T, mul, Tensor_Core<d1>, unary_expression_transpose<T, Tensor_Core<d2>>>> {
	static constexpr bool evaluate = false;
	static constexpr bool transposed = true;
	static constexpr bool scalar = true;

	template<class param> static T* getScalar(const param& p) { return p.left.data(); }
	template<class param> static T* getArray(const param& p) { return p.right.array; }
};
template<class value, class... list>
struct is_one_of {
	static constexpr bool conditional = false;
};
template<class value, class head, class... list>
struct is_one_of<value, head, list...> {
	static constexpr bool conditional = MTF::same<value, head>::conditional || is_one_of<value, list...>::conditional;
};

}

#endif /* EXPRESSION_BINARY_DOTPRODUCT_IMPL2_H_ */
#endif
