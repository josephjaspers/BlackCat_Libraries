/*  Project: BlackCat_Tensors
 *  Author: JosephJaspers
 *  Copyright 2018
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BC_INTERNAL_BASE_H_
#define BC_INTERNAL_BASE_H_

#include "Expression_Template_Traits.h"

namespace BC {
namespace tensors {
namespace exprs {


template<class Derived>
struct Expression_Template_Base: BC_Type {

	BCINLINE
	const Derived& internal() const {
		return BC::traits::derived_cast(*this);
	}

	BCINLINE
	Derived& internal() {
		return BC::traits::derived_cast(*this);
	}


	BCINLINE Expression_Template_Base() {

		using BC::traits::true_v;
		using BC::traits::Integer;

#ifndef _MSC_VER
		static_assert(std::is_trivially_copy_constructible<Derived>::value,
				"ExpressionTemplates must be trivially constructible");

		static_assert(std::is_trivially_copyable<Derived>::value,
				"ExpressionTemplates must be tricially copyable");
#endif
		static_assert(true_v<typename Derived::value_type>,
				"ExpressionTemplates must define: 'using value_type = <T>;'");

		static_assert(true_v<decltype(std::declval<Derived>().inner_shape())>,
				"ExpressionTemplates must define: inner_shape()");

		static_assert(true_v<decltype(std::declval<Derived>().rows())>,
				"ExpressionTemplates must define: rows()");

		static_assert(true_v<decltype(std::declval<Derived>().cols())>,
				"ExpressionTemplates must define: cols()");

		static_assert(true_v<decltype(std::declval<Derived>().dimension(0))>,
				"ExpressionTemplates must define: dimension(int)");

		static_assert(true_v<Integer<Derived::tensor_dimension>>,
				"ExpressionTemplates must define: "
				"static constexpr int tensor_dimension");

		static_assert(true_v<Integer<Derived::tensor_iterator_dimension>>,
				"ExpressionTemplates must define: "
				"static constexpr int tensor_iterator_dimension");
	}

	void deallocate() const {}
};


template<class Derived>
struct Expression_Base:
		Expression_Template_Base<Derived>,
		BC_Expr {

	using copy_constructible = std::false_type;
	using move_constructible = std::false_type;
	using copy_assignable    = std::false_type;
	using move_assignable    = std::false_type;

	BCINLINE const auto inner_shape() const {
		BC::Dim<Derived::tensor_dimension> dim;
		for (BC::size_t i = 0; i < Derived::tensor_dimension; ++i) {
			dim[i] = static_cast<const Derived&>(*this).dimension(i);
		}
		return dim;
	}

	BCINLINE const auto get_shape() const {
		return BC::Shape<Derived::tensor_dimension>(
				static_cast<const Derived&>(*this).inner_shape());
	}
};


template<class Derived>
struct Kernel_Array_Base : Expression_Template_Base<Derived>, BC_Array {

	BCINLINE
	Kernel_Array_Base() {
		using value_type = typename Derived::value_type;
		using memptr_type = decltype(std::declval<Derived>().memptr());
		using memptr_value_type =
				std::remove_const_t<std::remove_pointer_t<memptr_type>>;

		static_assert(std::is_same<value_type, memptr_value_type>::value,
			"Array_Types must define: memptr() \n"
			"which returns a pointer of the ExpressionTemplate's value_type");
	}
};


} //ns BC
} //ns exprs
} //ns tensors


#endif /* BC_INTERNAL_BASE_H_ */
