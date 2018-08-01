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
class unary_expression : public expression_base<unary_expression<value, operation>>, public operation {
public:

	value array;

	__BCinline__ static constexpr int DIMS() { return value::DIMS(); }
	__BCinline__ static constexpr int ITERATOR() { return value::ITERATOR(); }

	template<class... args> __BCinline__
	unary_expression(value v, const args&... args_) : array(v), operation(args_...) {}

	__BCinline__  const auto inner_shape() const 			{ return array.inner_shape(); }
	__BCinline__  const auto outer_shape() const 			{ return array.outer_shape(); }

	__BCinline__ auto operator [](int index) const {
		return static_cast<const operation&>(*this)(array[index]);
	}
	template<class... integers>__BCinline__
	auto operator ()(integers... index) const {
		return static_cast<const operation&>(*this)(array(index...));
	}
	__BCinline__ int size() const { return array.size(); }
	__BCinline__ int rows() const { return array.rows(); }
	__BCinline__ int cols() const { return array.cols(); }
	__BCinline__ int dimension(int i) const { return array.dimension(i); }
	__BCinline__ int outer_dimension() const { return array.outer_dimension(); }


};
}
}
#endif /* EXPRESSION_UNARY_POINTWISE_CU_ */

//__BCinline__ const auto slice(int i) const {
//	using slice_t = decltype(array.slice(i));
//	return unary_expression<slice_t, operation>(array.slice(i), oper);
//}
//__BCinline__ const auto scalar(int i) const {
//	using scalar_t = decltype(array.scalar(i));
//	return unary_expression<scalar_t, operation>(array.scalar(i), oper);
//}
//
//__BCinline__ const auto col(int i) const {
//	static_assert(DIMS() == 2, "COLUMN ACCESS ONLY AVAILABLE TO MATRICEDS");
//	return slice(i);
//}
