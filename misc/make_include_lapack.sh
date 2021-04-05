cd ~/mplapack/mplapack/reference

#!/bin/bash

if [ `uname` = "Linux" ]; then
    SED=sed
else
    SED=gsed
fi

MPLIBS="gmp mpfr _Float128 dd qd double _Float64x"

cat *hpp ~/mplapack/misc/special.hpp > header_all

for mplib in $MPLIBS; do
    if [ x"$mplib" = x"gmp" ]; then
        cp header_all mplapack_${mplib}.h 
        sed -i -e 's/INTEGER/mplapackint/g' mplapack_${mplib}.h 
        sed -i -e 's/COMPLEX/mpc_class/g' mplapack_${mplib}.h 
        sed -i -e 's/REAL/mpf_class/g' mplapack_${mplib}.h 
        sed -i -e "s/Rlamch/Rlamch_${mplib}/g" mplapack_${mplib}.h 
        sed -i -e "s/iMlaenv/iMlaenv_${mplib}/g" mplapack_${mplib}.h 
    fi

    if [ x"$mplib" = x"mpfr" ]; then
        cp header_all mplapack_${mplib}.h 
        sed -i -e 's/INTEGER/mplapackint/g' mplapack_${mplib}.h 
        sed -i -e 's/COMPLEX/mpcomplex/g' mplapack_${mplib}.h 
        sed -i -e 's/REAL/mpreal/g' mplapack_${mplib}.h 
        sed -i -e "s/Rlamch/Rlamch_${mplib}/g" mplapack_${mplib}.h 
        sed -i -e "s/iMlaenv/iMlaenv_${mplib}/g" mplapack_${mplib}.h 
    fi

    if [ x"$mplib" = x"double" ]; then
        cp header_all mplapack_${mplib}.h 
        sed -i -e 's/INTEGER/mplapackint/g' mplapack_${mplib}.h 
        sed -i -e 's/COMPLEX/std::complex<double>/g' mplapack_${mplib}.h 
        sed -i -e 's/REAL/double/g' mplapack_${mplib}.h 
        sed -i -e "s/Rlamch/Rlamch_${mplib}/g" mplapack_${mplib}.h 
        sed -i -e "s/iMlaenv/iMlaenv_${mplib}/g" mplapack_${mplib}.h 
    fi

    if [ x"$mplib" = x"dd" ]; then
        cp header_all mplapack_${mplib}.h 
        sed -i -e 's/INTEGER/mplapackint/g' mplapack_${mplib}.h 
        sed -i -e 's/COMPLEX/dd_complex/g' mplapack_${mplib}.h 
        sed -i -e 's/REAL/dd_real/g' mplapack_${mplib}.h 
        sed -i -e "s/Rlamch/Rlamch_${mplib}/g" mplapack_${mplib}.h 
        sed -i -e "s/iMlaenv/iMlaenv_${mplib}/g" mplapack_${mplib}.h 
    fi

    if [ x"$mplib" = x"qd" ]; then
        cp header_all mplapack_${mplib}.h 
        sed -i -e 's/INTEGER/mplapackint/g' mplapack_${mplib}.h 
        sed -i -e 's/COMPLEX/qd_complex/g' mplapack_${mplib}.h 
        sed -i -e 's/REAL/qd_real/g' mplapack_${mplib}.h 
        sed -i -e "s/Rlamch/Rlamch_${mplib}/g" mplapack_${mplib}.h 
        sed -i -e "s/iMlaenv/iMlaenv_${mplib}/g" mplapack_${mplib}.h 
    fi

    if [ x"$mplib" = x"_Float128" ]; then
        cp header_all mplapack_${mplib}.h 
        sed -i -e 's/INTEGER/mplapackint/g' mplapack_${mplib}.h 
        sed -i -e 's/COMPLEX/std::complex<_Float128>/g' mplapack_${mplib}.h 
        sed -i -e 's/REAL/_Float128/g' mplapack_${mplib}.h 
        sed -i -e "s/Rlamch/Rlamch_${mplib}/g" mplapack_${mplib}.h 
        sed -i -e "s/iMlaenv/iMlaenv_${mplib}/g" mplapack_${mplib}.h 
    fi

    if [ x"$mplib" = x"_Float64x" ]; then
        cp header_all mplapack_${mplib}.h 
        sed -i -e 's/INTEGER/mplapackint/g' mplapack_${mplib}.h 
        sed -i -e 's/COMPLEX/std::complex<_Float64x>/g' mplapack_${mplib}.h 
        sed -i -e 's/REAL/_Float64x/g' mplapack_${mplib}.h 
        sed -i -e "s/Rlamch/Rlamch_${mplib}/g" mplapack_${mplib}.h 
        sed -i -e "s/iMlaenv/iMlaenv_${mplib}/g" mplapack_${mplib}.h 
    fi

    clang-format -style="{BasedOnStyle: llvm, IndentWidth: 4, ColumnLimit: 10000 }" mplapack_${mplib}.h | sort > l ; mv l mplapack_${mplib}.h 
    cat ~/mplapack/misc/mplapack_${mplib}.h.in mplapack_${mplib}.h > ~/mplapack/include/mplapack_${mplib}.h
    rm mplapack_${mplib}.h
    echo "#endif" >> ~/mplapack/include/mplapack_${mplib}.h

done
rm header_all mplapack.h *hpp
