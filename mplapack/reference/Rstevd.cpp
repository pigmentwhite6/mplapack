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

void Rstevd(const char *jobz, INTEGER const n, REAL *d, REAL *e, REAL *z, INTEGER const ldz, REAL *work, INTEGER const lwork, INTEGER *iwork, INTEGER const liwork, INTEGER &info) {
    //
    //  -- LAPACK driver routine --
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
    bool wantz = Mlsame(jobz, "V");
    bool lquery = (lwork == -1 || liwork == -1);
    //
    info = 0;
    INTEGER liwmin = 1;
    INTEGER lwmin = 1;
    if (n > 1 && wantz) {
        lwmin = 1 + 4 * n + pow2(n);
        liwmin = 3 + 5 * n;
    }
    //
    if (!(wantz || Mlsame(jobz, "N"))) {
        info = -1;
    } else if (n < 0) {
        info = -2;
    } else if (ldz < 1 || (wantz && ldz < n)) {
        info = -6;
    }
    //
    if (info == 0) {
        work[1 - 1] = lwmin;
        iwork[1 - 1] = liwmin;
        //
        if (lwork < lwmin && !lquery) {
            info = -8;
        } else if (liwork < liwmin && !lquery) {
            info = -10;
        }
    }
    //
    if (info != 0) {
        Mxerbla("Rstevd", -info);
        return;
    } else if (lquery) {
        return;
    }
    //
    //     Quick return if possible
    //
    if (n == 0) {
        return;
    }
    //
    const REAL one = 1.0;
    if (n == 1) {
        if (wantz) {
            z[(1 - 1)] = one;
        }
        return;
    }
    //
    //     Get machine constants.
    //
    REAL safmin = Rlamch("Safe minimum");
    REAL eps = Rlamch("Precision");
    REAL smlnum = safmin / eps;
    REAL bignum = one / smlnum;
    REAL rmin = sqrt(smlnum);
    REAL rmax = sqrt(bignum);
    //
    //     Scale matrix to allowable range, if necessary.
    //
    INTEGER iscale = 0;
    REAL tnrm = Rlanst("M", n, d, e);
    const REAL zero = 0.0;
    REAL sigma = 0.0;
    if (tnrm > zero && tnrm < rmin) {
        iscale = 1;
        sigma = rmin / tnrm;
    } else if (tnrm > rmax) {
        iscale = 1;
        sigma = rmax / tnrm;
    }
    if (iscale == 1) {
        Rscal(n, sigma, d, 1);
        Rscal(n - 1, sigma, &e[1 - 1], 1);
    }
    //
    //     For eigenvalues only, call Rsterf.  For eigenvalues and
    //     eigenvectors, call Rstedc.
    //
    if (!wantz) {
        Rsterf(n, d, e, info);
    } else {
        Rstedc("I", n, d, e, z, ldz, work, lwork, iwork, liwork, info);
    }
    //
    //     If matrix was scaled, then rescale eigenvalues appropriately.
    //
    if (iscale == 1) {
        Rscal(n, one / sigma, d, 1);
    }
    //
    work[1 - 1] = lwmin;
    iwork[1 - 1] = liwmin;
    //
    //     End of Rstevd
    //
}
