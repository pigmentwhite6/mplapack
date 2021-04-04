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

void Rtpqrt2(INTEGER const &m, INTEGER const &n, INTEGER const &l, REAL *a, INTEGER const &lda, REAL *b, INTEGER const &ldb, REAL *t, INTEGER const &ldt, INTEGER &info) {
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
    //  =====================================================================
    //
    //     .. Parameters ..
    //     ..
    //     .. Local Scalars ..
    //     ..
    //     .. External Subroutines ..
    //     ..
    //     .. Intrinsic Functions ..
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
    } else if (l < 0 || l > min(m, n)) {
        info = -3;
    } else if (lda < max((INTEGER)1, n)) {
        info = -5;
    } else if (ldb < max((INTEGER)1, m)) {
        info = -7;
    } else if (ldt < max((INTEGER)1, n)) {
        info = -9;
    }
    if (info != 0) {
        Mxerbla("Rtpqrt2", -info);
        return;
    }
    //
    //     Quick return if possible
    //
    if (n == 0 || m == 0) {
        return;
    }
    //
    INTEGER i = 0;
    INTEGER p = 0;
    INTEGER j = 0;
    const REAL one = 1.0f;
    REAL alpha = 0.0;
    for (i = 1; i <= n; i = i + 1) {
        //
        //        Generate elementary reflector H(I) to annihilate B(:,I)
        //
        p = m - l + min(l, i);
        Rlarfg(p + 1, a[(i - 1) + (i - 1) * lda], b[(i - 1) * ldb], 1, t[(i - 1)]);
        if (i < n) {
            //
            //           W(1:N-I) := C(I:M,I+1:N)^H * C(I:M,I) [use W = T(:,N)]
            //
            for (j = 1; j <= n - i; j = j + 1) {
                t[(j - 1) + (n - 1) * ldt] = (a[(i - 1) + ((i + j) - 1) * lda]);
            }
            Rgemv("T", p, n - i, one, b[((i + 1) - 1) * ldb], ldb, b[(i - 1) * ldb], 1, one, t[(n - 1) * ldt], 1);
            //
            //           C(I:M,I+1:N) = C(I:m,I+1:N) + alpha*C(I:M,I)*W(1:N-1)^H
            //
            alpha = -(t[(i - 1)]);
            for (j = 1; j <= n - i; j = j + 1) {
                a[(i - 1) + ((i + j) - 1) * lda] += alpha * (t[(j - 1) + (n - 1) * ldt]);
            }
            Rger(p, n - i, alpha, b[(i - 1) * ldb], 1, t[(n - 1) * ldt], 1, b[((i + 1) - 1) * ldb], ldb);
        }
    }
    //
    const REAL zero = 0.0f;
    INTEGER mp = 0;
    INTEGER np = 0;
    for (i = 2; i <= n; i = i + 1) {
        //
        //        T(1:I-1,I) := C(I:M,1:I-1)^H * (alpha * C(I:M,I))
        //
        alpha = -t[(i - 1)];
        //
        for (j = 1; j <= i - 1; j = j + 1) {
            t[(j - 1) + (i - 1) * ldt] = zero;
        }
        p = min(i - 1, l);
        mp = min(m - l + 1, m);
        np = min(p + 1, n);
        //
        //        Triangular part of B2
        //
        for (j = 1; j <= p; j = j + 1) {
            t[(j - 1) + (i - 1) * ldt] = alpha * b[((m - l + j) - 1) + (i - 1) * ldb];
        }
        Rtrmv("U", "T", "N", p, b[(mp - 1)], ldb, t[(i - 1) * ldt], 1);
        //
        //        Rectangular part of B2
        //
        Rgemv("T", l, i - 1 - p, alpha, b[(mp - 1) + (np - 1) * ldb], ldb, b[(mp - 1) + (i - 1) * ldb], 1, zero, t[(np - 1) + (i - 1) * ldt], 1);
        //
        //        B1
        //
        Rgemv("T", m - l, i - 1, alpha, b, ldb, b[(i - 1) * ldb], 1, one, t[(i - 1) * ldt], 1);
        //
        //        T(1:I-1,I) := T(1:I-1,1:I-1) * T(1:I-1,I)
        //
        Rtrmv("U", "N", "N", i - 1, t, ldt, t[(i - 1) * ldt], 1);
        //
        //        T(I,I) = tau(I)
        //
        t[(i - 1) + (i - 1) * ldt] = t[(i - 1)];
        t[(i - 1)] = zero;
    }
    //
    //     End of Rtpqrt2
    //
}
