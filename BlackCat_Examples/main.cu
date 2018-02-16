#include <iostream>
#include "BlackCat_Tensors.h"
using BC::Vector;
using BC::Matrix;
using BC::Scalar;

template<class T>
T copy(const T& t) { return t; }


int VectorPointwise() {

std::cout << "Vector test " <<std::endl;

	Vector<double> a = {5};
	Vector<double> b = {5};
	Vector<double> c = {5};

	std::cout << " getting size" <<std::endl;


	std::cout << b.size() << " getting size" <<std::endl;
//	a.printDimensions();
//	a.printDetails();


//	b.print();
	std::cout << "Randomizing " << std::endl;
	b.randomize(-3, 5);
	c.randomize(0, 5);

	std::cout << " B " << std::endl;
	b.print();
	std::cout << " C" << std::endl;
	c.print();

	std::cout << " B + C" << std::endl;
	a = b + c;
	a.print();

	std::cout << " B - C" << std::endl;
	a = b - c;


	std::cout << " B ** C" << std::endl;
	b.print();
	c.print();

	a = b ** c;
	a.print();


	std::cout << "b[0]" << std::endl;
	b[0].print();


	std::cout << "a" << std::endl;
	a.print();


	std::cout << "a += b[0]" << std::endl;
	a += b[0];
	a.print();


	std::cout << " success " << std::endl;
	return 0;


}

int MatrixPointwise() {

std::cout << "Matrix test " <<std::endl;

	Matrix<double> a(4,3);
	Matrix<double> b(4,3);
	Matrix<double> c(4,3);


	Matrix<double> z(5,5 );
	Vector<double> d(3);


	*d;
	Vector<double> e(4);

	b.randomize(0, 10);
	c.randomize(0, 10);

	b.print();
	c.print();

	std::cout << "A = b + c" << std::endl;
	a = b + c;

	a.print();



	a[0][1].print();

	std::cout << " adding array " << std::endl;
b.print();
b += a[0][1];
b.print();
c.printDetails();
d.printDetails();
	e = (c * d);


	e.print();
	e[1] = 2;
	z.randomize(1,2);

	e[1].print();

	z = z.t() * e[1] * z;

	z.print();
	std::cout << " success " << std::endl;

	return 0;
}

int gpu() {

	Vector<float, BC::GPU> a(10);
	Vector<float, BC::GPU> b(10);
	Vector<float, BC::GPU> c(10);

	Matrix<float, BC::GPU> d(10, 10);


	a = d * b + c;

	a.randomize(0, 3);
	b.randomize(0, 3);

	a.print();
	b.print();

	c = (a + b);// + (b % B);
	c.print();

   std::cout << " success " << std::endl;
	return 0;
}

struct sigmoid {
	template<class T>
	T operator ()(T val) const {
		std::cout << " g func  " << std::endl;

		return 1/ (1 + std::pow(2.71828, -val));
	}
};

template<class T, class ml>
auto g(const Matrix<T, ml>& v) {
	return v.unExpr(sigmoid());
}
template<class T, class ml>
auto g(const Matrix<T, ml>&& v) {
	return v.unExpr(sigmoid());
}

auto dp_test () {

	Matrix<double> a(3, 2);
	Matrix<double> b(2 ,3);

	for (int i = 0; i < 6; ++i)  {
		b.data()[i] = i + 7;
		a.data()[i] = i + 1;
	}

	std::cout << std::endl;

	Matrix<double> d(2, 3);
	Matrix<double> e(3, 2);



	d = a.t();
	e = b.t();

	d.print();
	e.print();

	std::cout << " post print  " << std::endl;

	Matrix<double> c(2, 2);

	Scalar<double> C(2);
//
	c = d * e;
	Scalar<double> A(2);
	Scalar<double> B(2);
//
//
	A.print();
////
	std::cout << " dot product " << std::endl;
//
	c = a.t() * A * (b.t() * B);
//
//
	c = a.t() * A * (b.t() * Scalar<double>(2));
//
	c.print();

	std::cout << " copy " << std::endl;
	a.print();
	b.print();

	auto tmp = a + b;
	Vector<double> c_copy = copy(tmp);
//	(a + b).printExpression();
	std::cout << "done  copy " << std::endl;
//	c_copy.print();


//	c.print();
//	c = g(c);
//	c.print();
////
//	c_copy.print();

	std::cout << "successsasd " << std::endl;
//	return 0;
//	return c_copy;
}
//
//auto dp_test_GPU () {
//
//	Matrix<float> COPY(2 ,3);
//	Matrix<float> COPY2(3, 2);
//
//	for (int i = 0; i < 6; ++i)  {
//		COPY.data()[i] = i + 1;
//		COPY2.data()[i] = i + 7;
//
//	}
//
//
//	Matrix<float, BC::GPU> a(3, 2);
//	Matrix<float, BC::GPU> b(2 ,3);
//
//	Matrix<float, BC::GPU> d(2, 3);
//	Matrix<float, BC::GPU> e(3, 2);
//
//
//	BC::GPU::HostToDevice(a.data(), COPY.data(), 6);
//	BC::GPU::HostToDevice(b.data(), COPY2.data(), 6);
//
//
//	a.print();
//	b.print();
//
//
//
//
//	d = a.t();
//	e = b.t();
//
//	d.print();
//	e.print();
//
//	std::cout << " post print  " << std::endl;
//
//	Matrix<float,BC::GPU> c(2, 2);
//	std::cout << "dotproduct of d and e " << std::endl;
//	c = d * e;
//	c.print();
//
//
//	//DOES NOT WORK
//	Scalar<float,BC::GPU> A(2);
//	Scalar<float,BC::GPU> B(2);
//
//	A.print();
//	B.print();
//
//	c = a.t() * A * (b.t() * A);
//	c = a.t() * A * (b.t() * Scalar<float,BC::GPU>(2)); //causes crash on gpu
//
//	c.print();
//
//	std::cout << " copy " << std::endl;
//	a.print();
//	b.print();
//
//	auto tmp = a + b;
//	Vector<float,BC::GPU> c_copy = copy(tmp);
////	(a + b).printExpression();
//	std::cout << "done  copy " << std::endl;
////	c_copy.print();
//
//
////	c.print();
////	c = g(c);
////	c.print();
//////
////	c_copy.print();
//
//	std::cout << "successsasd " << std::endl;
////	return 0;
////	return c_copy;
//}
//

int readWrite() {

	std::ofstream os("input.txt");

	Matrix<double> a(3, 2);
	Matrix<double> b(2 ,3);

	for (int i = 0; i < 6; ++i)  {
		a.data()[i] = i + 7;
		b.data()[i] = i + 1;
	}

	a.print();
	b.print();

	a.write(os);
	b.write(os);
//	std::cout << std::endl;

	os.close();

	std::ifstream is("input.txt");

	Matrix<double> d(3, 2);
	Matrix<double> e(2, 3);


	d.read(is);
	e.read(is);

	is.close();
	std::cout << " read "<< std::endl;

	d.print();
	e.print();
	std::cout << " success "<< std::endl;
	return 0;
}

void AND_example() {

	std::cout <<" and example" << std::endl;

	Matrix<double> a(2, 2);
	Matrix<double> b(2 ,2);

	Matrix<double> c(2, 2);
	c.fill(100);
	for (int i = 0; i < 4; ++i)  {
		a.data()[i] = i + 7;
		b.data()[i] = i + 1;
	}
	c.print();
	a.print();
	b.print();


	//Combines both of these statements into a single for loop (must still be the same size)
	(a = a + c) && (b += c);

	a.print();
	b.print();


}


#include "SpeedTests.h"
int main() {
	gpu();

	speedTests<100000, 100000>();
	speedTests<10000,  100000>();
	speedTests<1000,   100000>();
	speedTests<100,    100000>();
	speedTests<10,     100000>();

//	c.printDimensions();
//	c.print();
//	readWrite();
//	VectorPointwise();
//	MatrixPointwise();
//	AND_example();
//	dp_test_GPU();
//	dp_test();

	std::cout << " success  main"<< std::endl;


	return 0;
}