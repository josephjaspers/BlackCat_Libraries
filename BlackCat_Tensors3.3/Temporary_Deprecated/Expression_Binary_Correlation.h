/*
 * Expressions_Binary_Correlation.h
 *
 *  Created on: Mar 22, 2018
 *      Author: joseph
 */

#ifndef EXPRESSIONS_BINARY_CORRELATION_H_
#define EXPRESSIONS_BINARY_CORRELATION_H_

#include "Expression_Base.h"
#include "Expression_Binary_Base.h"

namespace BC {

struct inner;
template<int,class> struct _x_corr {};

template<class lv, class rv, int corr_dimension>
struct binary_expression<lv, rv, _x_corr<corr_dimension,inner>> : expression_base<binary_expression<lv, rv, _x_corr<corr_dimension,inner>>> {

	__BCinline__ static constexpr int DIMS() { return corr_dimension; }
	__BCinline__ static constexpr int ITERATOR() { return corr_dimension; }

	using scalar = _scalar<lv>;
//	scalar* rv_cache = new scalar[right.size()];

	static_assert(lv::DIMS() == rv::DIMS(), "CORRELATION CURRENTLY ONLY SUPPORTED FOR SAME ORDER TENSORS");
	static_assert(DIMS() <= 3, "CORRELATION MOST MOVEMENT IS LIMITED TO 3D");


	lv left;  //krnl
	rv right; //img

	binary_expression(lv l_, rv r_) :left(l_), right(r_) {}

	__BCinline__ const auto inner_shape() const { return l_array([&](int i) {return right.dimension(i) - left.dimension(i) + 1;} ); }
	__BCinline__ const auto outer_shape() const { return l_array([&](int i) {return i == 0 ? this->rows() : this->dimension(i) * this->dimension(i - 1);} );}

	template<int x> using conditional_int = std::conditional_t<x == corr_dimension, int, DISABLED>;

	template<class... ints> __BCinline__
	scalar axpy (conditional_int<1> x, ints... location) const {
		scalar sum = 0;
		for (int i = 0 ; i < left.rows(); ++i) {
			sum += left(i) * right(i + x, location...);
		}
		return sum;
	}

	template<class... ints> __BCinline__
	scalar axpy (conditional_int<2> x, int y, ints... indexes) const {
		scalar sum = 0;
		for (int n = 0; n < left.cols(); ++n) {
			for (int m = 0 ; m < left.rows(); ++m) {
				sum += left(m, n) * right(m + x, n + y, indexes...);
			}
		}
		return sum;
	}

	template<class... ints> __BCinline__
	scalar axpy (conditional_int<3> x, int y, int z, ints... indexes) const {
		scalar sum = 0;
		for (int k = 0; k < left.dimension(2); ++k) {
			for (int n = 0; n < left.cols(); ++n) {
				for (int m = 0 ; m < left.rows(); ++m) {
					sum += left(m, n, k) * right(m + x, n + y, k + z, indexes...);
				}
			}
		}
		return sum;
	}

	template<class... integers> __BCinline__  scalar operator ()(integers... ints) const {
		return axpy(ints...);
	}
	__BCinline__  scalar operator [](int x) const {
		return axpy(x);
	}
};
}


#endif /* EXPRESSIONS_BINARY_CORRELATION_H_ */