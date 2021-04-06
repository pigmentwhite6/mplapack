/*
 * Copyright (c) 2008-2021
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

void Ctpqrt(INTEGER const m, INTEGER const n, INTEGER const l, INTEGER const nb, COMPLEX *a, INTEGER const lda, COMPLEX *b, INTEGER const ldb, COMPLEX *t, INTEGER const ldt, COMPLEX *work, INTEGER &info) {
    //
    //  -- LAPACK computational routine --
    //  -- LAPACK is a software package provided by Univ. of Tennessee,    --
    //  -- Univ. of California Berkeley, Univ. of Colorado Denver and NAG Ltd..--
    //
    //     .. Scalar Arguments ..
    //     ..
    //     .. Array Arguments ..
    //     ..
    //
    // =====================================================================
    //
    //     ..
    //     .. Local Scalars ..
    //     ..
    //     .. External Subroutines ..
    //     ..
    //     .. Executable Statements ..
    //
    //     Test the input arguments
    //
    info = 0;
    if (m < 0) {
        info = -1;
    } else if (n < 0) {
        info = -2;
    } else if (l < 0 || (l > min(m, n) && min(m, n) >= 0)) {
        info = -3;
    } else if (nb < 1 || (nb > n && n > 0)) {
        info = -4;
    } else if (lda < max((INTEGER)1, n)) {
        info = -6;
    } else if (ldb < max((INTEGER)1, m)) {
        info = -8;
    } else if (ldt < nb) {
        info = -10;
    }
    if (info != 0) {
        Mxerbla("Ctpqrt", -info);
        return;
    }
    //
    //     Quick return if possible
    //
    if (m == 0 || n == 0) {
        return;
    }
    //
    INTEGER i = 0;
    INTEGER ib = 0;
    INTEGER mb = 0;
    INTEGER lb = 0;
    INTEGER iinfo = 0;
    for (i = 1; i <= n; i = i + nb) {
        //
        //     Compute the QR factorization of the current block
        //
        ib = min(n - i + 1, nb);
        mb = min(m - l + i + ib - 1, m);
        if (i >= l) {
            lb = 0;
        } else {
            lb = mb - m + l - i + 1;
        }
        //
        Ctpqrt2(mb, ib, lb, &a[(i - 1) + (i - 1) * lda], lda, &b[(i - 1) * ldb], ldb, &t[(i - 1) * ldt], ldt, iinfo);
        //
        //     Update by applying H**H to B(:,I+IB:N) from the left
        //
        if (i + ib <= n) {
            Ctprfb("L", "C", "F", "C", mb, n - i - ib + 1, ib, lb, &b[(i - 1) * ldb], ldb, &t[(i - 1) * ldt], ldt, &a[(i - 1) + ((i + ib) - 1) * lda], lda, &b[((i + ib) - 1) * ldb], ldb, work, ib);
        }
    }
    //
    //     End of Ctpqrt
    //
}
