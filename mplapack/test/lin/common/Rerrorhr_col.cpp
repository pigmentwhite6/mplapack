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

#include <fem.hpp> // Fortran EMulation library of fable module
using namespace fem::major_types;
using fem::common;

#include <mplapack_matgen.h>
#include <mplapack_lin.h>

void Rerrorhr_col(const char *path, INTEGER const nunit) {
    common cmn;
    common_write write(cmn);
    INTEGER infot;
    INTEGER nout;
    bool ok;
    bool lerr;
    //
    //
    //  -- LAPACK test routine --
    //  -- LAPACK is a software package provided by Univ. of Tennessee,    --
    //  -- Univ. of California Berkeley, Univ. of Colorado Denver and NAG Ltd..--
    //
    //     .. Scalar Arguments ..
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
    //     .. External Subroutines ..
    //     ..
    //     .. Scalars in Common ..
    //     ..
    //     .. Common blocks ..
    //     ..
    //     .. Intrinsic Functions ..
    //     ..
    //     .. Executable Statements ..
    //
    nout = nunit;
    write(nout, star);
    //
    //     Set the variables to innocuous values.
    //
    INTEGER j = 0;
    const INTEGER nmax = 2;
    INTEGER i = 0;
    REAL a[nmax * nmax];
    REAL t[nmax * nmax];
    REAL d[nmax];
    INTEGER lda = nmax;
    INTEGER ldt = nmax;
    for (j = 1; j <= nmax; j = j + 1) {
        for (i = 1; i <= nmax; i = i + 1) {
            a[(i - 1) + (j - 1) * lda] = 1.e+0 / castREAL(i + j);
            t[(i - 1) + (j - 1) * ldt] = 1.e+0 / castREAL(i + j);
        }
        d[j - 1] = 0.e+0;
    }
    ok = true;
    //
    //     Error exits for Householder reconstruction
    //
    //     Rorhr_col
    //
    //
    infot = 1;
    INTEGER info = 0;
    Rorhr_col(-1, 0, 1, a, 1, t, 1, d, info);
    chkxer("Rorhr_col", infot, nout, lerr, ok);
    //
    infot = 2;
    Rorhr_col(0, -1, 1, a, 1, t, 1, d, info);
    chkxer("Rorhr_col", infot, nout, lerr, ok);
    Rorhr_col(1, 2, 1, a, 1, t, 1, d, info);
    chkxer("Rorhr_col", infot, nout, lerr, ok);
    //
    infot = 3;
    Rorhr_col(0, 0, -1, a, 1, t, 1, d, info);
    chkxer("Rorhr_col", infot, nout, lerr, ok);
    //
    Rorhr_col(0, 0, 0, a, 1, t, 1, d, info);
    chkxer("Rorhr_col", infot, nout, lerr, ok);
    //
    infot = 5;
    Rorhr_col(0, 0, 1, a, -1, t, 1, d, info);
    chkxer("Rorhr_col", infot, nout, lerr, ok);
    //
    Rorhr_col(0, 0, 1, a, 0, t, 1, d, info);
    chkxer("Rorhr_col", infot, nout, lerr, ok);
    //
    Rorhr_col(2, 0, 1, a, 1, t, 1, d, info);
    chkxer("Rorhr_col", infot, nout, lerr, ok);
    //
    infot = 7;
    Rorhr_col(0, 0, 1, a, 1, t, -1, d, info);
    chkxer("Rorhr_col", infot, nout, lerr, ok);
    //
    Rorhr_col(0, 0, 1, a, 1, t, 0, d, info);
    chkxer("Rorhr_col", infot, nout, lerr, ok);
    //
    Rorhr_col(4, 3, 2, a, 4, t, 1, d, info);
    chkxer("Rorhr_col", infot, nout, lerr, ok);
    //
    //     Print a summary line.
    //
    Alaesm(path, ok, nout);
    //
    //     End of Rerrorhr_col
    //
}
