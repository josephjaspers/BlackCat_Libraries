/*
 * BC_MetaTemplate_EssentialMethods.h
 *
 *  Created on: Dec 11, 2017
 *      Author: joseph
 */

#ifndef ADHOC_H_
#define ADHOC_H_

#include "Simple.h"
#include <type_traits>

namespace BC {
	namespace MTF {

		//EXPRESSION_TYPE----------------------------------------------------------------------------------------------
		template<class, class>  struct expression_substitution;

		template<class sub, template<class, class> class derived, class scalar_type, class ml>
		struct expression_substitution<sub, derived<scalar_type, ml>>{
				using type = derived<sub, ml>;
		};
		//SCALAR_TYPE----------------------------------------------------------------------------------------------
		template<class T>
		struct determine_scalar {
				using type = T;
		};
		template<template<class...> class tensor, class T, class... set>
		struct determine_scalar<tensor<T, set...>> {
				using type = typename determine_scalar<T>::type;
		};
		template<class front, class... T> struct determine_mathlib_impl {
			using type = typename determine_mathlib_impl<T...>::type;
		};
		template<class front> struct determine_mathlib_impl<front> {
			using type = front;
		};
		template<class> struct determine_mathlib;
		template<template<class...> class tensor, class... traits> struct determine_mathlib<tensor<traits...>> {
			using type = typename determine_mathlib_impl<traits...>::type;
		};


		//DETERMINE IF ITS A CORE_TYPE (DETERMINE IF THE METHOD SHOULD GAIN ACCESS TO UTILITY METHODS)-------------------------------------

		template<class, class> struct Scalar;
		template<class, class> struct Vector;
		template<class, class> struct Matrix;
		template<class, class> struct Cube;

		template<class> struct isRoot { static constexpr bool conditional = false; };
		template<class t, class m> struct isRoot<Scalar<t, m>> { static constexpr bool conditional = true; };
		template<class t, class m> struct isRoot<Vector<t, m>> { static constexpr bool conditional = true; };
		template<class t, class m> struct isRoot<Matrix<t, m>> { static constexpr bool conditional = true; };
		template<class t, class m> struct isRoot<Cube<t, m>> { static constexpr bool conditional = true; };

		template<class> struct Tensor_Core;
		template<class> struct Tensor_Slice;
		template<class> struct Tensor_Scalar;

		template<class T> struct isCore 				{ static constexpr bool conditional = MTF::isPrimitive<T>::conditional; };
		template<class a> struct isCore<Tensor_Core<a>> { static constexpr bool conditional = true;  };
		template<class a> struct isCore<Tensor_Slice<a>> { static constexpr bool conditional = true;  };
		template<class a> struct isCore<Tensor_Scalar<a>> { static constexpr bool conditional = true;  };

		template<class T, class M, template<class,class> class tensor> struct isCore<tensor<T, M>> {
			static constexpr bool conditional = isRoot<tensor<T, M>>::conditional ? isCore<T>::conditional : false;
		};

		template<class T> struct isCorePure {
			static  constexpr bool conditional = MTF::isPrimitive<T>::conditional; };
		template<class T> struct isCorePure<Tensor_Core<T>> { static  constexpr bool conditional = true; };

	}
}
#endif /* ADHOC_H_ */
