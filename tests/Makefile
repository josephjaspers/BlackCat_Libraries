CXXVERSION = -std=c++14 
CXXFLAGS = -O3 -o blackcat_tests -Wall
CUFLAGS = -O3 -o blackcat_tests_cu 
CXXDFLAGS = -g  -o blackcat_tests_debug

CXXFILES = run.cpp
CUFILES  = run.cu

LIBS = -lblas

ATLAS_BLAS_LINKAGE = -D BC_BLAS_USE_C_LINKAGE=1
ATLASLIBS =  -lf77blas -lcblas -latlas
CULIBS = -lcublas

INCLUDE = ../include/  -I /usr/include/
LIBINCLUDE = /usr/lib/

default:
	$(CXX) $(CXXVERSION) $(CXXFILES) $(LIBS) $(CXXFLAGS) -I $(INCLUDE) -L $(LIBINCLUDE)

debug:
	$(CXX) $(CXXVERSION) $(CXXFILES) $(LIBS) $(CXXDFLAGS) -I $(INCLUDE) -L $(LIBINCLUDE)

TRAVIS_LIBS = -lblas
travis:
	$(CXX) $(CXXVERSION) $(CXXFILES) $(TRAVIS_LIBS) $(CXXFLAGS) -I $(INCLUDE) -L $(LIBINCLUDE)

atlas:
	 $(CXX) $(CXXVERSION) $(ATLAS_BLAS_LINKAGE) $(CXXFILES)  $(CXXFLAGS) -I $(INCLUDE) -L $(LIBINCLUDE) $(ATLASLIBS)

cuda:
	nvcc $(CUFILES) $(CXXVERSION) $(CULIBS) $(LIBS) $(CUFLAGS) -I $(INCLUDE) -L $(LIBINCLUDE)

cuda_atlas:
	nvcc $(CUFILES) $(CXXVERSION) $(ATLAS_BLAS_LINKAGE) $(CULIBS) $(CUFLAGS) -I $(INCLUDE) -L $(LIBINCLUDE) $(ATLASLIBS)
	
clang:
	 clang $(CXXFILES) -std=c++17 -lblas  $(CXXFLAGS) -I $(INCLUDE) -L $(LIBINCLUDE)
clean:
	rm -i mnist_test_exec; rm -i mnist_test_exec_cu;


