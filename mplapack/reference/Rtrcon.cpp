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

void Rtrcon(const char *norm, const char *uplo, const char *diag, INTEGER const &n, REAL *a, INTEGER const &lda, REAL &rcond, REAL *work, INTEGER *iwork, INTEGER &info) {
    bool upper = false;
    bool onenrm = false;
    bool nounit = false;
    const REAL one = 1.0;
    const REAL zero = 0.0;
    REAL smlnum = 0.0;
    REAL anorm = 0.0;
    REAL ainvnm = 0.0;
    str<1> normin = char0;
    INTEGER kase1 = 0;
    INTEGER kase = 0;
    arr_1d<3, INTEGER> isave(fill0);
    REAL scale = 0.0;
    INTEGER ix = 0;
    REAL xnorm = 0.0;
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
    //     .. Local Arrays ..
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
    upper = Mlsame(uplo, "U");
    onenrm = norm == "1" || Mlsame(norm, "O");
    nounit = Mlsame(diag, "N");
    //
    if (!onenrm && !Mlsame(norm, "I")) {
        info = -1;
    } else if (!upper && !Mlsame(uplo, "L")) {
        info = -2;
    } else if (!nounit && !Mlsame(diag, "U")) {
        info = -3;
    } else if (n < 0) {
        info = -4;
    } else if (lda < max((INTEGER)1, n)) {
        info = -6;
    }
    if (info != 0) {
        Mxerbla("Rtrcon", -info);
        return;
    }
    //
    //     Quick return if possible
    //
    if (n == 0) {
        rcond = one;
        return;
    }
    //
    rcond = zero;
    smlnum = dlamch("Safe minimum") * (max((INTEGER)1, n)).real();
    //
    //     Compute the norm of the triangular matrix A.
    //
    anorm = Rlantr[(norm - 1) + (uplo - 1) * ldRlantr];
    //
    //     Continue only if ANORM > 0.
    //
    if (anorm > zero) {
        //
        //        Estimate the norm of the inverse of A.
        //
        ainvnm = zero;
        normin = "N";
        if (onenrm) {
            kase1 = 1;
        } else {
            kase1 = 2;
        }
        kase = 0;
    statement_10:
        Rlacn2(n, work[(n + 1) - 1], work, iwork, ainvnm, kase, isave);
        if (kase != 0) {
            if (kase == kase1) {
                //
                //              Multiply by inv(A).
                //
                Rlatrs(uplo, "No transpose", diag, normin, n, a, lda, work, scale, work[(2 * n + 1) - 1], info);
            } else {
                //
                //              Multiply by inv(A**T).
                //
                Rlatrs(uplo, "Transpose", diag, normin, n, a, lda, work, scale, work[(2 * n + 1) - 1], info);
            }
            normin = "Y";
            //
            //           Multiply by 1/SCALE if doing so will not cause overflow.
            //
            if (scale != one) {
                ix = iRamax[(n - 1) + (work - 1) * ldiRamax];
                xnorm = abs(work[ix - 1]);
                if (scale < xnorm * smlnum || scale == zero) {
                    goto statement_20;
                }
                Rrscl(n, scale, work, 1);
            }
            goto statement_10;
        }
        //
        //        Compute the estimate of the reciprocal condition number.
        //
        if (ainvnm != zero) {
            rcond = (one / anorm) / ainvnm;
        }
    }
//
statement_20:;
    //
    //     End of Rtrcon
    //
}
