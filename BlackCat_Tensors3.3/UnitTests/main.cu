#include <iostream>
#include "../BlackCat_Tensors.h"
#include "SpeedTests.h"
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
	b.printDimensions();
	a.printDimensions();

//	a.printDetails();


////	b.print();
	std::cout << "Randomizing " << std::endl;
	b.randomize(-3, 5);
	c.randomize(0, 5);
//

	a.data()[0] = 123123;
	std::cout << " B " << std::endl;
	b.print();
	std::cout << " C" << std::endl;
	c.print();
//
//
	std::cout << " c= b.t" << std::endl;
//
	c = b.t();
	c.print();
//
	std::cout << " B + C" << std::endl;
	a = b + c;
	a.print();

	a.data().array[0] = 3243;
	a.print();
//
	std::cout << " a + a + a" << std::endl;
	a = a + a + a;

	a.print();

	std::cout << " B ** C" << std::endl;
	b.print();
	c.print();

	a = b ** c;
	a.print();

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

	std::cout << " c= b.t" << std::endl;

//	c = b.t();

	std::cout << "A = b + c" << std::endl;
	a = b + c;

	Scalar<double> sc(10000);

	a.print();

	a = a + sc;
	a.print();




	std::cout << " adding array " << std::endl;

//c.printDetails();
//d.printDetails();
	e = (c * d);



	z.print();
	std::cout << " success " << std::endl;

	return 0;
}


int main() {

	MatrixPointwise();
//	VectorPointwise();

	//	dp_test();



	std::cout << " success  main"<< std::endl;


	return 0;
}