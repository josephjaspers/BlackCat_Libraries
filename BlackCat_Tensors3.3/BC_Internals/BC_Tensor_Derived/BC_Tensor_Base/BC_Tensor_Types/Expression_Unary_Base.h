/*
 * Expression_Unary_Base.cu
 *
 *  Created on: Jan 25, 2018
 *      Author: joseph
 */
#ifndef EXPRESSION_UNARY_POINTWISE_CU_
#define EXPRESSION_UNARY_POINTWISE_CU_

#include "Expression_Base.h"

namespace BC {
namespace internal {
template<class value, class operation>
class unary_expression : public expression_base<unary_expression<value, operation>> {
public:

	operation oper;
	value array;

	__BCinline__ static constexpr int DIMS() { return value::DIMS(); }
	__BCinline__ static constexpr int ITERATOR() { return value::ITERATOR(); }
	__BCinline__ static constexpr bool INJECTABLE() { return value::INJECTABLE(); }

	__BCinline__  unary_expression(value v, operation op = operation()) : array(v), oper(op) {}
	template<class V, class core> //CONVERSION CONSTRUCTOR FOR BLAS ROTATION
	__BCinline__  unary_expression(unary_expression<V, operation> ue, core tensor) : array(ue.array, tensor), oper(ue.oper) {}

	template<class BLAS_expr> //CONVERSION CONSTRUCTOR FOR BLAS ROTATION
		__BCinline__  unary_expression(unary_expression<BLAS_expr, operation> ue, value tensor) : array(tensor), oper(ue.oper) {
		ue.array.eval(tensor);
	}

	__BCinline__  const auto inner_shape() const 			{ return array.inner_shape(); }
	__BCinline__  const auto outer_shape() const 			{ return array.outer_shape(); }

	__BCinline__ auto operator [](int index) const -> decltype(oper(array[index])) {
		return oper(array[index]);
	}
	__BCinline__ auto operator [](int index) -> decltype(oper(array[index])) {
		return oper(array[index]);
	}
	template<class... integers>__BCinline__ auto operator ()(integers... index) const -> decltype(oper(array(index...))) {
		return oper(array(index...));
	}
	template<class... integers>	__BCinline__ auto operator ()(integers... index) -> decltype(oper(array(index...))) {
		return oper(array(index...));
	}
	__BCinline__ const auto slice(int i) const {
		return unary_expression<decltype(array.slice(0)), operation>(array.slice(i)); }
	__BCinline__ const auto row(int i) const {
		return unary_expression<decltype(array.row(0)),operation>(array.row(i)); }
	__BCinline__ const auto col(int i) const {
		return unary_expression<decltype(array.col(0)),operation>(array.col(i)); }
	__BCinline__ const auto scalar(int i) const {
		return unary_expression<decltype(array.scalar(0)),operation>(array.scalar(i)); }

	__BCinline__ void eval() const {
		array.eval();
	}
};
}
}
#endif /* EXPRESSION_UNARY_POINTWISE_CU_ */
