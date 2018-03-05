/*
 * Determiners.h
 *
 *  Created on: Feb 25, 2018
 *      Author: joseph
 */

#ifndef DETERMINERS_H_
#define DETERMINERS_H_

#include "../../BC_MetaTemplateFunctions/Adhoc.h"
#include "../../BC_MetaTemplateFunctions/Simple.h"

namespace BC {

using MTF::ifte;		//if then else
using MTF::isPrim;		//is a primitive type
using MTF::shell_of;	//get template type shell IE tensor<stuff...> -> tensor<//use your types here//>
using MTF::isCore;		//is a Core or one of its derivatives
using MTF::isCorePure;	//is a TensorCore<T> type (more restrictive than isCore)

template<class,class> class DISABLED;
template<class,class> class Scalar;
template<class,class> class Vector;
template<class,class> class Matrix;
template<class,class> class Cube;
template<class> struct Tensor_Core;

template<int> struct base;

template<> struct base<0> { template<class t, class m> using type = Scalar<t,m>;  template<class t, class m> using slice = DISABLED<t, m>; };
template<> struct base<1> { template<class t, class m> using type = Vector<t, m>; template<class t,class m> using slice = Scalar<t, m>; };
template<> struct base<2> { template<class t, class m> using type = Matrix<t, m>; template<class t,class m> using slice = Vector<t, m>; };
template<> struct base<3> { template<class t, class m> using type = Cube<t, m>;   template<class t,class m> using slice = Matrix<t, m>; };

template<int a ,int b = a, class = void> struct Rank;
template<class> struct ranker;
template<class a, class b> struct ranker<Scalar<a,b>> { static constexpr int value = 0; using type = Rank<value, value>;  };
template<class a, class b> struct ranker<Vector<a,b>> { static constexpr int value = 1; using type = Rank<value, value>;  };
template<class a, class b> struct ranker<Matrix<a,b>> { static constexpr int value = 2; using type = Rank<value, value>;  };
template<class a, class b> struct ranker<Cube<a,b>>   { static constexpr int value = 3; using type = Rank<value, value>;  };

template<class T> using _scalar = typename MTF::determine_scalar<T>::type;
template<class T> using _mathlib = typename MTF::determine_mathlib<T>::type;
template<class T> using _ranker  = typename ranker<T>::type;
template<class T> static constexpr int _rankOf  = ranker<T>::value;

template<class> struct determine_functor;
template<template<class...> class tensor, class functor, class... set>
struct determine_functor<tensor<functor, set...>>{

	using derived = tensor<functor,set...>;
	using fscal = functor;
	using type = ifte<MTF::isPrimitive<functor>::conditional, Tensor_Core<derived>, functor>;
};

template<class T>
using _functor = typename determine_functor<T>::type;
template<class T> using _fscal = typename determine_functor<T>::fscal;

template<class> struct determine_evaluation;
template<template<class...> class tensor, class functor, class... set>
struct determine_evaluation<tensor<functor, set...>>{
	using derived = tensor<functor,set...>;

	using type = ifte<MTF::isPrimitive<functor>::conditional || isCore<functor>::conditional,
			derived&,
			tensor<Tensor_Core<derived>>>;
};
template<class T> using _evaluation = typename determine_evaluation<T>::type;


}



#endif /* DETERMINERS_H_ */
