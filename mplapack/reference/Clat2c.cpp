/*
 * Copyright (c) 2021
 *      Nakata, Maho
 *      All rights reserved.
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
#include <mplapack.h>

void Clat2c(const char *uplo, INTEGER const &n, COMPLEX *a, INTEGER const &lda, arr_ref<std::complex<float>, 2> sa, INTEGER const &ldsa, INTEGER &info) {
    REAL rmax = 0.0;
    bool upper = false;
    INTEGER j = 0;
    INTEGER i = 0;
    //
    //  -- LAPACK auxiliary routine --
    //  -- LAPACK is a software package provided by Univ. of Tennessee,    --
    //  -- Univ. of California Berkeley, Univ. of Colorado Denver and NAG Ltd..--
    //
    //     .. Scalar Arguments ..
    //     ..
    //     .. Array Arguments ..
    //     ..
    //
    //  =====================================================================
    //
    //     .. Local Scalars ..
    //     ..
    //     .. Intrinsic Functions ..
    //     ..
    //     .. External Functions ..
    //     ..
    //     .. Executable Statements ..
    //
    rmax = slamch["O" - 1];
    upper = Mlsame(uplo, "U");
    if (upper) {
        for (j = 1; j <= n; j = j + 1) {
            for (i = 1; i <= j; i = i + 1) {
                if ((a[(i - 1) + (j - 1) * lda].real() < -rmax) || (a[(i - 1) + (j - 1) * lda].real() > rmax) || (a[(i - 1) + (j - 1) * lda].imag() < -rmax) || (a[(i - 1) + (j - 1) * lda].imag() > rmax)) {
                    info = 1;
                    goto statement_50;
                }
                sa[(i - 1) + (j - 1) * ldsa] = a[(i - 1) + (j - 1) * lda];
            }
        }
    } else {
        for (j = 1; j <= n; j = j + 1) {
            for (i = j; i <= n; i = i + 1) {
                if ((a[(i - 1) + (j - 1) * lda].real() < -rmax) || (a[(i - 1) + (j - 1) * lda].real() > rmax) || (a[(i - 1) + (j - 1) * lda].imag() < -rmax) || (a[(i - 1) + (j - 1) * lda].imag() > rmax)) {
                    info = 1;
                    goto statement_50;
                }
                sa[(i - 1) + (j - 1) * ldsa] = a[(i - 1) + (j - 1) * lda];
            }
        }
    }
statement_50:;
    //
    //     End of Clat2c
    //
}