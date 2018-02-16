/*
 * TensorBase.h
 *
 *  Created on: Feb 15, 2018
 *      Author: joseph
 */

#ifndef TENSORBASE_H_
#define TENSORBASE_H_

#include "Expression.h"
#include "Expression_Binary_Functors.cu"
#include "Simple.h"
namespace BC {

template<int order>
struct Shape {

};
template<>
struct Shape<0> {

};
template<>
struct Shape<1> {
	int m;
};
//int m;
//int n;
//int sz;
//
//scalar* array;
template<class derived, class scalar>
struct TensorBase {

	operator const derived&() {
		return static_cast<const derived&>(*this);
	}
	operator derived&() {
		return static_cast<derived&>(*this);
	}

	template<class d, class s> auto operator +(const TensorBase<d, s>& tens) const {
		bp_expr<add, derived&, TensorBase<d, s>::derived>(*this, tens);
	}
	template<class d, class s> auto operator -(const TensorBase<d, s>& tens) const {
		bp_expr<sub, derived&, TensorBase<d, s>::derived>(*this, tens);
	}
	template<class d, class s> auto operator /(const TensorBase<d, s>& tens) const {
		bp_expr<div, derived&, TensorBase<d, s>::derived>(*this, tens);
	}
	template<class d, class s> auto operator &(const TensorBase<d, s>& tens) const {
		bp_expr<div, derived&, TensorBase<d, s>::derived>(*this, tens);
	}
};

template<bool var, class A, class B>
using elif = std::conditional<var, A, B>::type;


template<class > struct derived_shell;
template<template<class ...> class T, class... set> struct derived_shell<T<set...>>
{	template<class... p> using type = T<p...>;};


template<class T, bool ownership = true>
struct ScalarCore{
	T array;
	int size() { return 0; }
	auto operator [] (int index) const -> decltype(array[0]) { return array[0]; }
	auto operator [] (int index)  -> decltype(array[0])  { return array[0]; }

};
template<class T,class ml, bool ownership = true>
struct VectorCore {
	T array;
	int m;
	int size() { return m; }
	auto operator [] (int index) const -> decltype(array[index]) { return array[index]; }
	auto operator [] (int index)  	   -> decltype(array[index]) { return array[index]; }

};
template<class T, class ml, bool ownership = true>
struct MatrixCore {
	T array;
	int m, n;
	int sz = m * n;
	int size() const { return m * n; }
	auto operator [] (int index) const -> decltype(array[index]) { return array[index]; }
	auto operator [] (int index)  	   -> decltype(array[index]) { return array[index]; }
};

template<class T, class ml, bool ownership = true>
struct TensorCore {
	T array;
	int m, n;
	int sz = m * n;
	int size() const { return m * n; }
	auto operator [] (int index) const -> decltype(array[index]) { return array[index]; }
	auto operator [] (int index)  	   -> decltype(array[index]) { return array[index]; }
};


template<class derived, class scalar, int order, class ml>
struct TensorBase {

	static constexpr int ORDER = order;
	template<class sub> using derived_body = derived_shell<sub, ml>;

	//short hand ensures matching ml
	template<class d, class s, int o> using tensorParam = TensorBase<d, s, o, ml>;

	using default_functor = elif<order == 0, ScalarCore<scalar, ml>,
								elif<order == 1, VectorCore<scalar, ml>,
									elif<order == 2, MatrixCore<scalar, ml>, TensorCore<scalar, ml>>>>;
	using functor = elif<MTF::isPrimitive<scalar>::conditional, default_functor, scalar>;

	operator const functor& () const { return array; }
	operator functor& () { return array; }

	functor array;

	int size() const { return array.size(); }

	//The return type for pointwise functions
	template<class tensor, class sub> using ret_type = elif<order == 0, tensor::derived_body<sub>, derived_body<sub>>;

	template<class d, class s, int o>
	auto operator +(const tensorParam<d, s, o>& tc) const {
		return ret_type<add, functor, tensorParam<d, s, o>::functor>(*this, tc);
	}
	template<class d, class s, int o>
	auto operator -(const tensorParam<d, s, o>& tc) const {
		return ret_type<sub, functor, tensorParam<d, s, o>::functor>(*this, tc);
	}
	template<class d, class s, int o>
	auto operator /(const tensorParam<d, s, o>& tc) const {
		return ret_type<div, functor, tensorParam<d, s, o>::functor>(*this, tc);
	}
	template<class d, class s, int o>
	auto operator %(const tensorParam<d, s, o>& tc) const {
		return ret_type<mul, functor, tensorParam<d, s, o>::functor>(*this, tc);
	}

};

}
#endif /* TENSORBASE_H_ */