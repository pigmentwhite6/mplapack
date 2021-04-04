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

void Csysv_aa_2stage(const char *uplo, INTEGER const &n, INTEGER const &nrhs, COMPLEX *a, INTEGER const &lda, COMPLEX *tb, INTEGER const &ltb, INTEGER *ipiv, INTEGER *ipiv2, COMPLEX *b, INTEGER const &ldb, COMPLEX *work, INTEGER const &lwork, INTEGER &info) {
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
    //     .. Local Scalars ..
    //     ..
    //     .. External Functions ..
    //     ..
    //     .. External Subroutines ..
    //     ..
    //     .. Intrinsic Functions ..
    //     ..
    //     .. Executable Statements ..
    //
    //     Test the input parameters.
    //
    info = 0;
    bool upper = Mlsame(uplo, "U");
    bool wquery = (lwork == -1);
    bool tquery = (ltb == -1);
    if (!upper && !Mlsame(uplo, "L")) {
        info = -1;
    } else if (n < 0) {
        info = -2;
    } else if (nrhs < 0) {
        info = -3;
    } else if (lda < max((INTEGER)1, n)) {
        info = -5;
    } else if (ltb < (4 * n) && !tquery) {
        info = -7;
    } else if (ldb < max((INTEGER)1, n)) {
        info = -11;
    } else if (lwork < n && !wquery) {
        info = -13;
    }
    //
    INTEGER lwkopt = 0;
    if (info == 0) {
        Csytrf_aa_2stage(uplo, n, a, lda, tb, -1, ipiv, ipiv2, work, -1, info);
        lwkopt = INTEGER(work[1 - 1]);
    }
    //
    if (info != 0) {
        Mxerbla("Csysv_aa_2stage", -info);
        return;
    } else if (wquery || tquery) {
        return;
    }
    //
    //     Compute the factorization A = U**T*T*U or A = L*T*L**T.
    //
    Csytrf_aa_2stage(uplo, n, a, lda, tb, ltb, ipiv, ipiv2, work, lwork, info);
    if (info == 0) {
        //
        //        Solve the system A*X = B, overwriting B with X.
        //
        Csytrs_aa_2stage(uplo, n, nrhs, a, lda, tb, ltb, ipiv, ipiv2, b, ldb, info);
        //
    }
    //
    work[1 - 1] = lwkopt;
    //
    //     End of Csysv_aa_2stage
    //
}
