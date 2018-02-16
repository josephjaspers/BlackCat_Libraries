


/*
 * Shape.h
 *
 *  Created on: Jan 18, 2018
 *      Author: joseph
 */

#ifndef SHAPE_H_
#define SHAPE_H_

#include <vector>

namespace BC {

template<class T, class Mathlib>
struct Tensor_Core {

	using _shape = std::vector<int>;
	using scalar = typename MTF::determine_scalar<T>::type;

	int sz;
	int order;
	bool array_ownership;
	scalar* array;
	_shape is;
	_shape os;

		  scalar* ary() { return array; }
	const scalar* ary() const { return array; }

	operator scalar*()             { return array; }
	operator const scalar*() const { return array; }
	operator scalar*&()             { return array; }
	operator const scalar*&() const { return array; }

		  scalar& operator [] (int index) { return array[index]; };
	const scalar& operator [] (int index) const { return array[index]; };

	Tensor_Core(const Tensor_Core& param) : is(param.is), os(param.os), sz(param.sz), order(param.order), array_ownership(true) {
		Mathlib::initialize(array, sz);
	}


	Tensor_Core(_shape param) : is(param), order(param.size()), array_ownership(true) {
		os = _shape(order);
		if (order > 0) {
			os = _shape(order);
			sz = is[0];
			os[0] = is[0];
			for (int i = 1; i < order; ++i) {
				sz *= is[i];
				os[i] = os[i - 1] * is[i];
			}
		}
		Mathlib::initialize(array, sz);
	}
	Tensor_Core(scalar* ary, _shape is, _shape os, int order, int size, bool ownership) : array(ary), is(is), os(os), order(order), sz(size), array_ownership(ownership) {}
	Tensor_Core(scalar* ary) : array(ary), array_ownership(false), order(0), sz(1), is(0), os(0) {}

	int rank() const { return order; }
	int size() const { return sz;    }
	int rows() const { return order > 0 ? is[0] : 1; }
	int cols() const { return order > 1 ? is[1] : 1; }
	int dimension(int i) const { return order > i ? is[i] : 1; }
	void printDimensions() const { for (int i = 0; i < order; ++i) { std::cout << "["<< is[i] << "]"; } std::cout << std::endl; }
	void printLDDimensions() const { for (int i = 0; i < order; ++i) { std::cout << "["<< os[i] << "]"; } std::cout << std::endl; }

	int LD_rows() const { return order > 0 ? os[0] : 1; }
	int LD_cols() const { return order > 1 ? os[1] : 1; }
	int LDdimension(int i) const { return order > i + 1 ? os[i] : 1; }

	const int* InnerShape() const { return &is[0]; }
	const int* OuterShape() const { return &os[0]; }
	void print() const { Mathlib::print(array, InnerShape(),rank(), 4); }

	void resetShape(_shape sh)  {
		is = sh;
		os = _shape(order);
		sz = is[0];
		os[0] = is[0];
		for (int i = 1; i < order; ++i) {
			sz *= is[i];
			os[i] = os[i - 1] * is[i];
		}

	}
	const Tensor_Core& expression_packet() const  { return *this; }
	auto accessor_packet(int index) const    { return Tensor_Core(&array[index * is[order - 1]], is, os, order - 1, sz/is[order - 1], false); }
	auto transpose_packet() const   { return Tensor_Core(this->array, {this->cols(), this->rows()}, os, 2, sz, false); }
	auto dotproduct_packet(int eval_order, const Tensor_Core& sh) const {

		return eval_order == 1 ?
				Tensor_Core({this->rows()}) :
				Tensor_Core({this->rows(), sh.cols()});
	}
	auto subAccessor_packet(_shape is_) const  { return Tensor_Core(is_, os, order, sz, false); }
	void ChangeShapeOwnership(bool swap = false) {
		array_ownership = swap;
	}
};



}

#endif /* SHAPE_H_ */


