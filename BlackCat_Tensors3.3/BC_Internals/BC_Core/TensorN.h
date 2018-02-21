/*
 * TensorN.h
 *
 *  Created on: Feb 20, 2018
 *      Author: joseph
 */

#ifndef TENSORN_H_
#define TENSORN_H_

namespace BC {

template<class T, int rank, class Mathlib>
class Tensor : public TensorBase<T, Matrix<T, Mathlib>, Mathlib, Rank<2>> {

	template<class,class>
	friend class Vector;

	using parent_class = TensorBase<T, Matrix<T, Mathlib>, Mathlib, Rank<2>>;

	template<bool if_, class then, class else_> using ifte = std::conditional_t<if_, then, else_>;
	struct DISABLED;

	static constexpr int acc_rank = rank - 1;

	template<class t, int r, class ml>
	using accessor_shell = ifte<rank == 0, DISABLED,
								ifte<rank == 1, Scalar<t, ml>,
									ifte<rank == 2, Vector<t, ml>,
										ifte<rank == 3, Matrix<t, ml>,
											Tensor<T, rank - 1, Mathlib>>>>>;

public:
	using scalar = T;
	using parent_class::operator=;
	using accessor = typename parent_class::accessor;
	static constexpr int RANK() { return 2; }

	Tensor() {}
	Tensor(const Tensor&  v) : parent_class(v) {}
	Tensor(		 Tensor&& v) : parent_class(v) {}
	Tensor(const Tensor&& v) : parent_class(v) {}

	template<class... dims>
	Tensor(dims... d) : parent_class(std::vector<int> {d...}) {}

	template<class U, int r>  Tensor(const Tensor<U, r, Mathlib>&  t) : parent_class(t) {}
	template<class U, int r>  Tensor(	   Tensor<U, r, Mathlib>&& t) : parent_class(t) {}
	template<class... params> Tensor(const params&... p) : parent_class(p...) {}

	Tensor& operator =(const Tensor& t)  { return parent_class::operator=(t); }
	Tensor& operator =(const Tensor&& t) { return parent_class::operator=(t); }
	Tensor& operator =(	     Tensor&& t) { return parent_class::operator=(t); }
	template<class U, int r>
	Tensor& operator = (const Tensor<U, r, Mathlib>& t) { return parent_class::operator=(t); }

	Tensor(std::vector<T> sh) : parent_class(sh) {}
	accessor_shell<accessor, acc_rank, Mathlib> operator [] (int index) { return accessor_shell<accessor, acc_rank, Mathlib>(this->accessor_packet(index)); }
	const accessor_shell<accessor, acc_rank, Mathlib> operator [] (int index) const { return accessor_shell<accessor, acc_rank, Mathlib>(this->accessor_packet(index)); }
};


}




#endif /* TENSORN_H_ */