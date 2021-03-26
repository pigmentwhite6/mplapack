/*
 * Copyright (c) 2008-2010
 *	Nakata, Maho
 * 	All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 */
#include <mpblas.h>
#include <blas.h>
#include <mplapack_debug.h>

#if defined VERBOSE_TEST
#include <iostream>
#endif

#define MIN_N -3
#define MAX_N 20
#define MIN_INCX -3
#define MAX_INCX 10
#define MAX_ITER 3

REAL_REF maxdiff = 0.0;

void Rtpmv_test2(const char *uplo, const char *trans, const char *diag)
{
    int errorflag = FALSE;
    int mplapack_errno1, mplapack_errno2;
    for (int incx = MIN_INCX; incx <= MAX_INCX; incx++) {
	for (int n = MIN_N; n < MAX_N; n++) {
#if defined VERBOSE_TEST
	    printf("#n is %d, incx is %d ", n, incx);
	    printf("uplo is %s trans is %s, diag is %s \n", uplo, trans, diag);
#endif
	    REAL_REF *AP_ref = new REAL_REF[vecplen(n)];
	    REAL_REF *x_ref = new REAL_REF[veclen(n, incx)];
	    REAL *AP = new REAL[vecplen(n)];
	    REAL *x = new REAL[veclen(n, incx)];

	    for (int iter = 0; iter < MAX_ITER; iter++) {
		set_random_vector(AP_ref, AP, vecplen(n));
		set_random_vector(x_ref, x, veclen(n, incx));

		mplapack_errno = 0; blas_errno = 0;
#if defined ___MPLAPACK_BUILD_WITH_MPFR___
		dtpmv_f77(uplo, trans, diag, &n, AP_ref, x_ref, &incx);
		mplapack_errno1 = blas_errno;
#else
		Rtpmv(uplo, trans, diag, n, AP_ref, x_ref, incx);
		mplapack_errno1 = mplapack_errno;
#endif
		Rtpmv(uplo, trans, diag, n, AP, x, incx);
		mplapack_errno2 = mplapack_errno;

#if defined VERBOSE_TEST
		printf("errno: mplapack %d, ref %d\n", mplapack_errno1, mplapack_errno2);
#endif
		if (mplapack_errno1 != mplapack_errno2) {
#if defined VERBOSE_TEST
		    printf("error in Mxerbla!!\n");
#endif
		    errorflag = TRUE;
		}
		REAL_REF diff = infnorm(x_ref, x, veclen(n, incx), 1);
		if (diff > EPSILON) {
#if defined VERBOSE_TEST
		    printf("error: "); printnum(diff); printf("\n");
#endif
		    errorflag = TRUE;
		}
		if (maxdiff < diff)
		    maxdiff = diff;
	    }
	    delete[]AP_ref;
	    delete[]AP;
	    delete[]x_ref;
	    delete[]x;
	}
    }
    if (errorflag == TRUE) {
	printf("error: "); printnum(maxdiff); printf("\n");
        printf("*** Testing Rtpmv failed ***\n");
	exit(1);
    }
}

void Rtpmv_test()
{
    Rtpmv_test2("U", "N", "U");
    Rtpmv_test2("U", "N", "N");
    Rtpmv_test2("U", "T", "U");
    Rtpmv_test2("U", "T", "N");
    Rtpmv_test2("U", "C", "U");
    Rtpmv_test2("U", "C", "N");
    Rtpmv_test2("L", "N", "U");
    Rtpmv_test2("L", "N", "N");
    Rtpmv_test2("L", "T", "U");
    Rtpmv_test2("L", "T", "N");
    Rtpmv_test2("L", "C", "U");
    Rtpmv_test2("L", "C", "N");
}

int main(int argc, char *argv[])
{
    printf("*** Testing Rtpmv start ***\n");
    Rtpmv_test();
    printf("*** Testing Rtpmv successful ***\n");
    return (0);
}