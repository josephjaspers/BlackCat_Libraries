/*
 * test_accessors.h
 *
 *  Created on: Dec 16, 2018
 *      Author: joseph
 */

#ifndef TEST_ACCESSORS_H_
#define TEST_ACCESSORS_H_

#include "test_common.h"

namespace bc {
namespace tests {

template<class value_type, template<class> class allocator>
int test_accessors(int sz=128) {

	BC_TEST_BODY_HEAD

	using mat = bc::Matrix<value_type, allocator<value_type>>;
	using vec = bc::Vector<value_type, allocator<value_type>>;
	using scalar = bc::Scalar<value_type, allocator<value_type>>;

	mat a(sz,sz);

	BC_TEST_ON_STARTUP {
		value_type val= 0;
		for (auto col : a) {
			col = val++;
		}
	};

	BC_TEST_DEF(
		mat x(3,3);
		vec y(3);
		scalar s;

		auto print_compilation_test = [&]() {
			x.print();
			y.print();
			s.print();

			//test expression_templates print functions
			(x+x).print();
			(x*x).print();
			(x*x).print_sparse();
		};

		//Get rid of unused variable warning
		if (false) {
			print_compilation_test();
		}

		return true;
	)

	//test slice
	BC_TEST_DEF(
		vec a0(a[0]);
		vec a1(a[1]);

		vec validation = a[0].approx_equal(a0) && a[1].approx_equal(a1);
		return bc::tensors::all(validation[0]);
	)

	BC_TEST_DEF(
		vec a3(a.diagnol());
		vec b3(a3.size());
		b3 = a.diagnol();

		return bc::tensors::all(a3.approx_equal(a.diagnol())) &&
				bc::tensors::all(a.diagnol().approx_equal(b3)) &&
				a3.size() == sz;
	)

	//test ranged slice
	BC_TEST_DEF(
		vec a0(a[0]);
		vec a1(a[1]);
		vec a2(a[2]);

		auto slice_range = a.slice(0, 3);

		bool ensure_correct_size = slice_range.size() == sz * 3;
		bool ensure_correct_cols = slice_range.cols() == 3;
		bool ensure_correct_rows = a.rows() == sz;

		vec validation = slice_range[0].approx_equal(a0) &&
				slice_range[1].approx_equal(a1) &&
				slice_range[2].approx_equal(a2);

		return bc::tensors::all(validation) &&
				ensure_correct_size &&
				ensure_correct_cols &&
				ensure_correct_rows;
	)

	//test ranged slice
	BC_TEST_DEF(
		vec a0(a[1]);
		vec a1(a[2]);
		vec a2(a[3]);

		auto slice_range = a.slice(1, 4);

		bool ensure_correct_size = slice_range.size() == sz * 3;
		bool ensure_correct_cols = slice_range.cols() == 3;
		bool ensure_correct_rows = a.rows() == sz;

		vec validation = slice_range[0].approx_equal(a0) &&
				slice_range[1].approx_equal(a1) &&
				slice_range[2].approx_equal(a2);

		return bc::tensors::all(validation) &&
				ensure_correct_size &&
				ensure_correct_cols &&
				ensure_correct_rows;
	)

	//test chunk
	BC_TEST_DEF(

		vec a1(a[1]);
		vec a2(a[2]);
		vec a3(a[3]);

		auto block_of_a = a[{bc::dim(1,1), bc::dim(4,3)}];

		bool ensure_correct_size = block_of_a.size() == 4 * 3;
		bool ensure_correct_rows = block_of_a.rows() == 4;
		bool ensure_correct_cols = block_of_a.cols() == 3;

		vec validation =
				block_of_a[0].approx_equal(a1.slice(1, 5)) &&
				block_of_a[1].approx_equal(a2.slice(1, 5)) &&
				block_of_a[2].approx_equal(a3.slice(1, 5));

		return bc::tensors::all(validation) &&
				ensure_correct_size &&
				ensure_correct_cols &&
				ensure_correct_rows;
	)

	//same as test_block but with subblock method
	BC_TEST_DEF(

		vec a1(a[1]);
		vec a2(a[2]);
		vec a3(a[3]);

		auto block_of_a = a.subblock(bc::dim(1,1), bc::dim(4,3));

		bool ensure_correct_size = block_of_a.size() == 4 * 3;
		bool ensure_correct_rows = block_of_a.rows() == 4;
		bool ensure_correct_cols = block_of_a.cols() == 3;

		vec validation =
				block_of_a[0].approx_equal(a1.slice(1, 5)) &&
				block_of_a[1].approx_equal(a2.slice(1, 5)) &&
				block_of_a[2].approx_equal(a3.slice(1, 5));

		return bc::tensors::all(validation) &&
				ensure_correct_size &&
				ensure_correct_cols &&
				ensure_correct_rows;
	)

	BC_TEST_DEF(
			return a.flattened().size() == a.size() &&
					bc::all(a.flattened().slice(0,sz) == a[0]) &&
					bc::all(a.flattened().slice(sz, sz*2) == a[1]);
	)

	//test chunk of chunk
	BC_TEST_DEF(

		vec a1(a[1]);
		vec a2(a[2]);
		vec a3(a[3]);

		auto primary_block_of_a = a[{bc::dim(0, 0), bc::dim(5,5)}];
		auto block_of_a = primary_block_of_a[{bc::dim(1,1), bc::dim(4,3)}];

		bool ensure_correct_size = block_of_a.size() == 4 * 3;
		bool ensure_correct_rows = block_of_a.rows() == 4;
		bool ensure_correct_cols = block_of_a.cols() == 3;

		vec validation =
				block_of_a[0].approx_equal(a1.slice(1, 5)) &&
				block_of_a[1].approx_equal(a2.slice(1, 5)) &&
				block_of_a[2].approx_equal(a3.slice(1, 5));

		return bc::tensors::all(validation) &&
				ensure_correct_size &&
				ensure_correct_cols &&
				ensure_correct_rows;
	)


	//----------------------- test valid ranges ---------------------------//
	std::ostream* curr_error_stream = get_error_stream();
	set_error_stream(nullptr);

	//assert invalid scalar exception
	BC_TEST_DEF(
		try {
			a.scalar(-1);
		} catch(...) {
			return true;
		}
		return false;
	)

	//assert invalid range check
	BC_TEST_DEF(
		try {
			a.slice(-1);
		} catch(...) {
			return true;
		}
		return false;
	)

	BC_TEST_DEF(
		try {
			a.diagnol(-(a.rows()+1));
		} catch(...) {
			return true;
		}
		return false;
	)
	BC_TEST_DEF(
		try {
			a.diagnol((a.rows()+1));
		} catch(...) {
			return true;
		}
		return false;
	)

	BC_TEST_DEF(
		try {
			a.row(a.rows());
		} catch(...) {
			return true;
		}
		return false;
	)

	BC_TEST_DEF(
		try {
			a.row(-a.rows());
		} catch(...) {
			return true;
		}
		return false;
	)

	set_error_stream(curr_error_stream);
	BC_TEST_BODY_TAIL
}
}
}



#endif /* TEST_ACCESSORS_H_ */
