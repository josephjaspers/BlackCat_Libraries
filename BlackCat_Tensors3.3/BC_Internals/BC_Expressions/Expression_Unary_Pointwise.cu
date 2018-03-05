/*
 * Expression_Unary_Pointwise.cu
 *
 *  Created on: Jan 25, 2018
 *      Author: joseph
 */
#ifdef  __CUDACC__
#ifndef EXPRESSION_UNARY_POINTWISE_CU_
#define EXPRESSION_UNARY_POINTWISE_CU_

#include "Expression_Base.cu"
namespace BC {
template<class T, class operation, class value>
class unary_expression : public expression<T, unary_expression<T, operation, value>> {
public:

	operation oper;
	value array;

	int rank() const { return array.rank(); }
	int size() const { return array.size(); }
	int rows() const { return array.rows(); }
	int cols() const { return array.cols(); }
	int LD_rows() const { return array.LD_rows(); }
	int LD_cols() const { return array.LD_cols(); }
	int dimension(int i)		const { return array.dimension(i); }
	void printDimensions() 		const { array.printDimensions();   }
	void printLDDimensions()	const { array.printLDDimensions(); }
	const auto innerShape() const 			{ return array.innerShape(); }
	const auto outerShape() const 			{ return array.outerShape(); }

	inline __attribute__((always_inline)) __BC_gcpu__ unary_expression(value v) :
		array(v) {
	}

	inline __attribute__((always_inline)) __BC_gcpu__
	auto operator [](int index) const -> decltype(oper(array[index])) {
		return oper(array[index]);
	}
	inline __attribute__((always_inline)) __BC_gcpu__
	auto operator [](int index) -> decltype(oper(array[index])) {
		return oper(array[index]);
	}
};
}
#endif /* EXPRESSION_UNARY_POINTWISE_CU_ */
#endif
