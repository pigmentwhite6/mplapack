//public domain
#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
#include <algorithm>

#include <mpblas_mpfr.h>
#include <mplapack_mpfr.h>

#define MPFR_FORMAT "%+68.64Re"
#define MPFR_SHORT_FORMAT "%+20.16Re"

inline void printnum(mpreal rtmp) { mpfr_printf(MPFR_FORMAT, mpfr_ptr(rtmp)); }
inline void printnum_short(mpreal rtmp) { mpfr_printf(MPFR_SHORT_FORMAT, mpfr_ptr(rtmp)); }
inline void printnum(mpcomplex ctmp) {
    mpreal cre, cim;
    cre = ctmp.real();
    cim = ctmp.imag();
    mpfr_printf(MPFR_SHORT_FORMAT MPFR_SHORT_FORMAT "i", mpfr_ptr(cre), mpfr_ptr(cim));
    return;
}

//Matlab/Octave format
template <class X> void printvec(X *a, int len) {
    X tmp;
    printf("[ ");
    for (int i = 0; i < len; i++) {
        tmp = a[i];
        printnum(tmp);
        if (i < len - 1)
            printf(", ");
    }
    printf("]");
}

template <class X> void printmat(int n, int m, X *a, int lda)
{
    X mtmp;

    printf("[ ");
    for (int i = 0; i < n; i++) {
        printf("[ ");
        for (int j = 0; j < m; j++) {
            mtmp = a[i + j * lda];
            printnum(mtmp);
            if (j < m - 1)
                printf(", ");
        }
        if (i < n - 1)
            printf("]; ");
        else
            printf("] ");
    }
    printf("]");
}
int main()
{
    mplapackint n = 3;
    mplapackint lwork, info;

    mpcomplex *A = new mpcomplex[n * n];
    mpreal *w = new mpreal[n];
    mpreal *rwork = new mpreal[3 * n - 1];

//setting A matrix
    A[0 + 0 * n] = 2.0;               A[0 + 1 * n] = mpcomplex(0.0, -1.0);    A[0 + 2 * n] = 0.0;
    A[1 + 0 * n] = mpcomplex(0.0, 1.0); A[1 + 1 * n] = 2.0;                   A[1 + 2 * n] = 0.0;
    A[2 + 0 * n] = 0.0;               A[2 + 1 * n] = 0.0;                   A[2 + 2 * n] = 3.0;

    printf("A ="); printmat(n, n, A, n); printf("\n");
//work space query
    lwork = -1;
    mpcomplex *work = new mpcomplex[1];

    Cheev("V", "U", n, A, n, w, work, lwork, rwork, info);
    lwork = (int) cast2double (work[0].real());
    delete[]work;
    work = new mpcomplex[std::max((mplapackint) 1, lwork)];
//inverse matrix
    Cheev("V", "U", n, A, n, w, work, lwork, rwork, info);
//print out some results.
    printf("#eigenvalues \n");
    printf("w ="); printmat(n, 1, w, 1); printf("\n");

    printf("#eigenvecs \n");
    printf("U ="); printmat(n, n, A, n); printf("\n");
    printf("#you can check eigenvalues using octave/Matlab by:\n");
    printf("eig(A)\n");
    printf("#you can check eigenvectors using octave/Matlab by:\n");
    printf("U'*A*U\n");

    delete[]work;
    delete[]w;
    delete[]A;
}
