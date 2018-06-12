/*
 * GPU_BLAS.h
 *
 *  Created on: May 6, 2018
 *      Author: joseph
 */

#ifndef GPU_BLAS_H_
#define GPU_BLAS_H_

namespace BC{

template<class core_lib>
struct GPU_BLAS {

	static void gemm(bool transA, bool transB, const float *A, const float *B, float *C, const int m, const int n, const int k, const float* scalarA = nullptr, const float* scalarB = nullptr, int lda = 0, int ldb = 0, int ldc = 0) {
		auto TRANS_A = transA ? CUBLAS_OP_T : CUBLAS_OP_N;
		auto TRANS_B = transB ? CUBLAS_OP_T : CUBLAS_OP_N;

		if (lda == 0 ) lda = m;
		if (ldb == 0 ) ldb = n;
		if (ldc == 0 ) ldc = m;

		cublasHandle_t handle;
		cublasCreate(&handle);
		cublasSetPointerMode(handle, CUBLAS_POINTER_MODE_DEVICE);

		const float *const alpha = scalarA ? const_cast<float*>(scalarA) : core_lib::BC_ONE;
		const float *const beta = scalarB ? const_cast<float*>(scalarB) : core_lib::BC_ZERO;

		cublasSgemm(handle, TRANS_A, TRANS_B, m, n, k, alpha, A, lda, B, ldb, beta, C, ldc);
		cudaDeviceSynchronize();
		cublasDestroy(handle);
	}
};


}



#endif /* GPU_BLAS_H_ */
