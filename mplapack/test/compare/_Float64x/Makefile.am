check_PROGRAMS = $(mplapack__Float64x_test_PROGRAMS)
TESTS = $(check_PROGRAMS)
mplapack__Float64x_test_PROGRAMS = \
Cgelq2.test__Float64x \
Cgeqr2.test__Float64x \
Cgeqrf.test__Float64x \
Cgesv.test__Float64x \
Cgetf2.test__Float64x \
Cgetrf.test__Float64x \
Cgetri.test__Float64x \
Cgetrs.test__Float64x \
Cheev.test__Float64x \
Chetd2.test__Float64x \
Chetrd.test__Float64x \
Clacgv.test__Float64x \
Clacrm.test__Float64x \
Clacrt.test__Float64x \
Cladiv.test__Float64x \
Claesy.test__Float64x \
Claev2.test__Float64x \
Clahef.test__Float64x \
Clanhe.test__Float64x \
Clanht.test__Float64x \
Clansy.test__Float64x \
Clarfb.test__Float64x \
Clarfg.test__Float64x \
Clarf.test__Float64x \
Clarft.test__Float64x \
Clartg.test__Float64x \
Clascl.test__Float64x \
Claset.test__Float64x \
Clasr.test__Float64x \
Classq.test__Float64x \
Claswp.test__Float64x \
Clasyf.test__Float64x \
Clatrd.test__Float64x \
Cpotf2.test__Float64x \
Crot.test__Float64x \
Cspmv.test__Float64x \
Cspr.test__Float64x \
Csteqr.test__Float64x \
Csymv.test__Float64x \
Csyr.test__Float64x \
Ctrti2.test__Float64x \
Ctrtri.test__Float64x \
Ctrtrs.test__Float64x \
Cung2l.test__Float64x \
Cung2r.test__Float64x \
Cungql.test__Float64x \
Cungqr.test__Float64x \
Cungtr.test__Float64x \
Cunmqr.test__Float64x \
iCmax1.test__Float64x \
iMlaenv.test__Float64x \
Mlsamen.test__Float64x \
Mutils.test__Float64x \
RCsum1.test__Float64x \
Rgecon.test__Float64x \
Rgeequ.test__Float64x \
Rgeqlf.test__Float64x \
Rgesv.test__Float64x \
Rgetf2.test__Float64x \
Rgetrf.test__Float64x \
Rgetri.test__Float64x \
Rgetrs.test__Float64x \
Rladiv.test__Float64x \
Rlae2.test__Float64x \
Rlaev2.test__Float64x \
Rlamch.test__Float64x \
Rlange.test__Float64x \
Rlanst.test__Float64x \
Rlansy.test__Float64x \
Rlapy2.test__Float64x \
Rlapy3.test__Float64x \
Rlarfb.test__Float64x \
Rlarfg.test__Float64x \
Rlarf.test__Float64x \
Rlarft.test__Float64x \
Rlartg.test__Float64x \
Rlaruv.test__Float64x \
Rlascl.test__Float64x \
Rlaset.test__Float64x \
Rlasr.test__Float64x \
Rlasrt.test__Float64x \
Rlassq.test__Float64x \
Rlaswp.test__Float64x \
Rlasyf.test__Float64x \
Rlatrd.test__Float64x \
Rlatrs.test__Float64x \
Rlauu2.test__Float64x \
Rlauum.test__Float64x \
Rorg2l.test__Float64x \
Rorg2r.test__Float64x \
Rorgql.test__Float64x \
Rorgqr.test__Float64x \
Rorgtr.test__Float64x \
Rpocon.test__Float64x \
Rposv.test__Float64x \
Rpotf2.test__Float64x \
Rpotri.test__Float64x \
Rpotrs.test__Float64x \
Rsteqr.test__Float64x \
Rsterf.test__Float64x \
Rsyev.test__Float64x \
Rsytd2.test__Float64x \
Rsytrd.test__Float64x \
Rtrti2.test__Float64x \
Rtrtri.test__Float64x \
Rtrtrs.test__Float64x 


mplapack__Float64x_testdir = $(prefix)/lib/$(target)/mplapack/test/compare/_Float64x

install-data-hook:
if IS_MACOS
	bash $(top_builddir)/misc/fix_dylib_macOS.sh $(mplapack__Float64x_testdir) $(prefix)
endif

mplibs=-L$(MPC_LIBDIR) -L$(MPFR_LIBDIR) -lmpc -lmpfr -lgmpxx -lgmp
refblas=-L$(top_builddir)/external/i/LAPACK/lib -lblas $(FCLIBS)
reflapack=-L$(top_builddir)/external/i/LAPACK/lib -llapack $(FCLIBS)

test_cxxflags = $(OPENMP_CXXFLAGS) -I$(top_srcdir)/include -I$(GMP_INCLUDEDIR) -I$(MPFR_INCLUDEDIR) -I$(MPC_INCLUDEDIR) -I$(top_srcdir)/mpfrc++ -D___MPLAPACK_BUILD_WITH__FLOAT64X___ -D___MPLAPACK_INTERNAL___
AM_FFLAGS = -x f77-cpp-input -g

if IS_MINGW
test_libdepends = $(mplibs) $(reflapack) $(refblas) -Wl,--allow-multiple-definition
else
test_libdepends = $(mplibs) $(reflapack) $(refblas)
endif

if !IS_MACOS
test_srcdepends = ../../../../mpblas/test/common/xerbla.cpp ../../../../mpblas/test/common/mplapack.test.cpp ../../../../mpblas/test/common/Mxerbla.override.cpp
endif

if IS_MACOS
lib_LTLIBRARIES = libmxerbla_override.la
libmxerbla_override_la_CPPFLAGS = -I$(top_srcdir)/include -D___MPLAPACK_BUILD_WITH__FLOAT64X___
libmxerbla_override_la_SOURCES =  ../../../../mpblas/test/common/Mxerbla.override.cpp
libmxerbla_override_la_LDFLAGS= -Wl,-flat_namespace,-undefined,dynamic_lookup
test_srcdepends = ../../../../mpblas/test/common/xerbla.cpp ../../../../mpblas/test/common/mplapack.test.cpp
mplibs+=-Wl,-flat_namespace,-undefined,dynamic_lookup
TESTS_ENVIRONMENT=DYLD_INSERT_LIBRARIES=.libs/libmxerbla_override.0.dylib
endif

if IS_MINGW
$(check_PROGRAMS): libmxerbla_override.la
lib_LTLIBRARIES = libmxerbla_override.la
libmxerbla_override_la_CPPFLAGS = -I$(top_srcdir)/include -D___MPLAPACK_BUILD_WITH__FLOAT64X___
libmxerbla_override_la_SOURCES =  ../../../../mpblas/test/common/Mxerbla.override.cpp
test_srcdepends = ../../../../mpblas/test/common/xerbla.cpp ../../../../mpblas/test/common/mplapack.test.cpp
libmxerbla_override_la_LDFLAGS = -no-undefined
endif

if IS_MINGW
libdepends = -Wl,--allow-multiple-definition -Wl,--whole-archive,.libs/libmxerbla_override.a,$(top_builddir)/mpblas/reference/.libs/libmpblas__Float64x.a,$(top_builddir)/mplapack/reference/.libs/libmplapack__Float64x.a,$(top_builddir)/mplapack/reference/.libs/libmplapack_mpfr.a,$(top_builddir)/mpblas/reference/.libs/libmpblas_mpfr.a,--no-whole-archive
else
libdepends = -L$(top_builddir)/mplapack/reference -lmplapack__Float64x -lmplapack_mpfr -L$(top_builddir)/mpblas/reference -lmpblas__Float64x -lmpblas_mpfr
endif

Mutils_test__Float64x_SOURCES  = ../common/Mutils.test.cpp $(test_srcdepends) ../common/ilaenv.cpp
Mutils_test__Float64x_LDFLAGS    = $(libdepends) $(test_libdepends)
Mutils_test__Float64x_CXXFLAGS = $(test_cxxflags)

Cgelq2_test__Float64x_SOURCES  = ../common/Cgelq2.test.cpp $(test_srcdepends)
Cgelq2_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Cgelq2_test__Float64x_CXXFLAGS = $(test_cxxflags)

Cgeqr2_test__Float64x_SOURCES  = ../common/Cgeqr2.test.cpp $(test_srcdepends)
Cgeqr2_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Cgeqr2_test__Float64x_CXXFLAGS = $(test_cxxflags)

Cgeqrf_test__Float64x_SOURCES  = ../common/Cgeqrf.test.cpp $(test_srcdepends)
Cgeqrf_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Cgeqrf_test__Float64x_CXXFLAGS = $(test_cxxflags)

Cgesv_test__Float64x_SOURCES  = ../common/Cgesv.test.cpp $(test_srcdepends)
Cgesv_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Cgesv_test__Float64x_CXXFLAGS = $(test_cxxflags)

Cgetf2_test__Float64x_SOURCES  = ../common/Cgetf2.test.cpp $(test_srcdepends)
Cgetf2_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Cgetf2_test__Float64x_CXXFLAGS = $(test_cxxflags)

Cgetrf_test__Float64x_SOURCES  = ../common/Cgetrf.test.cpp $(test_srcdepends)
Cgetrf_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Cgetrf_test__Float64x_CXXFLAGS = $(test_cxxflags)

Cgetri_test__Float64x_SOURCES  = ../common/Cgetri.test.cpp $(test_srcdepends)
Cgetri_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Cgetri_test__Float64x_CXXFLAGS = $(test_cxxflags)

Cgetrs_test__Float64x_SOURCES  = ../common/Cgetrs.test.cpp $(test_srcdepends)
Cgetrs_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Cgetrs_test__Float64x_CXXFLAGS = $(test_cxxflags)

Cheev_test__Float64x_SOURCES  = ../common/Cheev.test.cpp $(test_srcdepends)
Cheev_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Cheev_test__Float64x_CXXFLAGS = $(test_cxxflags)

Chetd2_test__Float64x_SOURCES  = ../common/Chetd2.test.cpp $(test_srcdepends)
Chetd2_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Chetd2_test__Float64x_CXXFLAGS = $(test_cxxflags)

Chetrd_test__Float64x_SOURCES  = ../common/Chetrd.test.cpp $(test_srcdepends)
Chetrd_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Chetrd_test__Float64x_CXXFLAGS = $(test_cxxflags)

Clacgv_test__Float64x_SOURCES  = ../common/Clacgv.test.cpp $(test_srcdepends)
Clacgv_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Clacgv_test__Float64x_CXXFLAGS = $(test_cxxflags)

Clacrm_test__Float64x_SOURCES  = ../common/Clacrm.test.cpp $(test_srcdepends)
Clacrm_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Clacrm_test__Float64x_CXXFLAGS = $(test_cxxflags)

Clacrt_test__Float64x_SOURCES  = ../common/Clacrt.test.cpp $(test_srcdepends)
Clacrt_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Clacrt_test__Float64x_CXXFLAGS = $(test_cxxflags)

Cladiv_test__Float64x_SOURCES  = ../common/Cladiv.test.cpp $(test_srcdepends)
Cladiv_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Cladiv_test__Float64x_CXXFLAGS = $(test_cxxflags)

Claesy_test__Float64x_SOURCES  = ../common/Claesy.test.cpp $(test_srcdepends)
Claesy_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Claesy_test__Float64x_CXXFLAGS = $(test_cxxflags)

Claev2_test__Float64x_SOURCES  = ../common/Claev2.test.cpp $(test_srcdepends)
Claev2_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Claev2_test__Float64x_CXXFLAGS = $(test_cxxflags)

Clahef_test__Float64x_SOURCES  = ../common/Clahef.test.cpp $(test_srcdepends)
Clahef_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Clahef_test__Float64x_CXXFLAGS = $(test_cxxflags)

Clanhe_test__Float64x_SOURCES  = ../common/Clanhe.test.cpp $(test_srcdepends)
Clanhe_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Clanhe_test__Float64x_CXXFLAGS = $(test_cxxflags)

Clanht_test__Float64x_SOURCES  = ../common/Clanht.test.cpp $(test_srcdepends)
Clanht_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Clanht_test__Float64x_CXXFLAGS = $(test_cxxflags)

Clansy_test__Float64x_SOURCES  = ../common/Clansy.test.cpp $(test_srcdepends)
Clansy_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Clansy_test__Float64x_CXXFLAGS = $(test_cxxflags)

Clarfb_test__Float64x_SOURCES  = ../common/Clarfb.test.cpp $(test_srcdepends)
Clarfb_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Clarfb_test__Float64x_CXXFLAGS = $(test_cxxflags)

Clarfg_test__Float64x_SOURCES  = ../common/Clarfg.test.cpp $(test_srcdepends)
Clarfg_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Clarfg_test__Float64x_CXXFLAGS = $(test_cxxflags)

Clarf_test__Float64x_SOURCES  = ../common/Clarf.test.cpp $(test_srcdepends)
Clarf_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Clarf_test__Float64x_CXXFLAGS = $(test_cxxflags)

Clarft_test__Float64x_SOURCES  = ../common/Clarft.test.cpp $(test_srcdepends)
Clarft_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Clarft_test__Float64x_CXXFLAGS = $(test_cxxflags)

Clartg_test__Float64x_SOURCES  = ../common/Clartg.test.cpp $(test_srcdepends)
Clartg_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Clartg_test__Float64x_CXXFLAGS = $(test_cxxflags)

Clascl_test__Float64x_SOURCES  = ../common/Clascl.test.cpp $(test_srcdepends)
Clascl_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Clascl_test__Float64x_CXXFLAGS = $(test_cxxflags)

Claset_test__Float64x_SOURCES  = ../common/Claset.test.cpp $(test_srcdepends)
Claset_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Claset_test__Float64x_CXXFLAGS = $(test_cxxflags)

Clasr_test__Float64x_SOURCES  = ../common/Clasr.test.cpp $(test_srcdepends)
Clasr_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Clasr_test__Float64x_CXXFLAGS = $(test_cxxflags)

Classq_test__Float64x_SOURCES  = ../common/Classq.test.cpp $(test_srcdepends)
Classq_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Classq_test__Float64x_CXXFLAGS = $(test_cxxflags)

Claswp_test__Float64x_SOURCES  = ../common/Claswp.test.cpp $(test_srcdepends)
Claswp_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Claswp_test__Float64x_CXXFLAGS = $(test_cxxflags)

Clasyf_test__Float64x_SOURCES  = ../common/Clasyf.test.cpp $(test_srcdepends)
Clasyf_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Clasyf_test__Float64x_CXXFLAGS = $(test_cxxflags)

Clatrd_test__Float64x_SOURCES  = ../common/Clatrd.test.cpp $(test_srcdepends)
Clatrd_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Clatrd_test__Float64x_CXXFLAGS = $(test_cxxflags)

Cpotf2_test__Float64x_SOURCES  = ../common/Cpotf2.test.cpp $(test_srcdepends)
Cpotf2_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Cpotf2_test__Float64x_CXXFLAGS = $(test_cxxflags)

Crot_test__Float64x_SOURCES  = ../common/Crot.test.cpp $(test_srcdepends)
Crot_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Crot_test__Float64x_CXXFLAGS = $(test_cxxflags)

Cspmv_test__Float64x_SOURCES  = ../common/Cspmv.test.cpp $(test_srcdepends)
Cspmv_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Cspmv_test__Float64x_CXXFLAGS = $(test_cxxflags)

Cspr_test__Float64x_SOURCES  = ../common/Cspr.test.cpp $(test_srcdepends)
Cspr_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Cspr_test__Float64x_CXXFLAGS = $(test_cxxflags)

Csteqr_test__Float64x_SOURCES  = ../common/Csteqr.test.cpp $(test_srcdepends)
Csteqr_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Csteqr_test__Float64x_CXXFLAGS = $(test_cxxflags)

Csymv_test__Float64x_SOURCES  = ../common/Csymv.test.cpp $(test_srcdepends)
Csymv_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Csymv_test__Float64x_CXXFLAGS = $(test_cxxflags)

Csyr_test__Float64x_SOURCES  = ../common/Csyr.test.cpp $(test_srcdepends)
Csyr_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Csyr_test__Float64x_CXXFLAGS = $(test_cxxflags)

Ctrti2_test__Float64x_SOURCES  = ../common/Ctrti2.test.cpp $(test_srcdepends)
Ctrti2_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Ctrti2_test__Float64x_CXXFLAGS = $(test_cxxflags)

Ctrtri_test__Float64x_SOURCES  = ../common/Ctrtri.test.cpp $(test_srcdepends)
Ctrtri_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Ctrtri_test__Float64x_CXXFLAGS = $(test_cxxflags)

Ctrtrs_test__Float64x_SOURCES  = ../common/Ctrtrs.test.cpp $(test_srcdepends)
Ctrtrs_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Ctrtrs_test__Float64x_CXXFLAGS = $(test_cxxflags)

Cung2l_test__Float64x_SOURCES  = ../common/Cung2l.test.cpp $(test_srcdepends)
Cung2l_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Cung2l_test__Float64x_CXXFLAGS = $(test_cxxflags)

Cung2r_test__Float64x_SOURCES  = ../common/Cung2r.test.cpp $(test_srcdepends)
Cung2r_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Cung2r_test__Float64x_CXXFLAGS = $(test_cxxflags)

Cungql_test__Float64x_SOURCES  = ../common/Cungql.test.cpp $(test_srcdepends)
Cungql_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Cungql_test__Float64x_CXXFLAGS = $(test_cxxflags)

Cungqr_test__Float64x_SOURCES  = ../common/Cungqr.test.cpp $(test_srcdepends)
Cungqr_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Cungqr_test__Float64x_CXXFLAGS = $(test_cxxflags)

Cungtr_test__Float64x_SOURCES  = ../common/Cungtr.test.cpp $(test_srcdepends)
Cungtr_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Cungtr_test__Float64x_CXXFLAGS = $(test_cxxflags)

Cunmqr_test__Float64x_SOURCES  = ../common/Cunmqr.test.cpp $(test_srcdepends)
Cunmqr_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Cunmqr_test__Float64x_CXXFLAGS = $(test_cxxflags)

iCmax1_test__Float64x_SOURCES  = ../common/iCmax1.test.cpp $(test_srcdepends)
iCmax1_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
iCmax1_test__Float64x_CXXFLAGS = $(test_cxxflags)

iMlaenv_test__Float64x_SOURCES  = ../common/iMlaenv.test.cpp $(test_srcdepends)
iMlaenv_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
iMlaenv_test__Float64x_CXXFLAGS = $(test_cxxflags)

Mlsamen_test__Float64x_SOURCES  = ../common/Mlsamen.test.cpp $(test_srcdepends)
Mlsamen_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Mlsamen_test__Float64x_CXXFLAGS = $(test_cxxflags)

RCsum1_test__Float64x_SOURCES  = ../common/RCsum1.test.cpp $(test_srcdepends)
RCsum1_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
RCsum1_test__Float64x_CXXFLAGS = $(test_cxxflags)

Rgecon_test__Float64x_SOURCES  = ../common/Rgecon.test.cpp $(test_srcdepends)
Rgecon_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Rgecon_test__Float64x_CXXFLAGS = $(test_cxxflags)

Rgeequ_test__Float64x_SOURCES  = ../common/Rgeequ.test.cpp $(test_srcdepends)
Rgeequ_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Rgeequ_test__Float64x_CXXFLAGS = $(test_cxxflags)

Rgeqlf_test__Float64x_SOURCES  = ../common/Rgeqlf.test.cpp $(test_srcdepends)
Rgeqlf_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Rgeqlf_test__Float64x_CXXFLAGS = $(test_cxxflags)

Rgesv_test__Float64x_SOURCES  = ../common/Rgesv.test.cpp $(test_srcdepends)
Rgesv_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Rgesv_test__Float64x_CXXFLAGS = $(test_cxxflags)

Rgetf2_test__Float64x_SOURCES  = ../common/Rgetf2.test.cpp $(test_srcdepends)
Rgetf2_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Rgetf2_test__Float64x_CXXFLAGS = $(test_cxxflags)

Rgetrf_test__Float64x_SOURCES  = ../common/Rgetrf.test.cpp $(test_srcdepends)
Rgetrf_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Rgetrf_test__Float64x_CXXFLAGS = $(test_cxxflags)

Rgetri_test__Float64x_SOURCES  = ../common/Rgetri.test.cpp $(test_srcdepends)
Rgetri_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Rgetri_test__Float64x_CXXFLAGS = $(test_cxxflags)

Rgetrs_test__Float64x_SOURCES  = ../common/Rgetrs.test.cpp $(test_srcdepends)
Rgetrs_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Rgetrs_test__Float64x_CXXFLAGS = $(test_cxxflags)

Rladiv_test__Float64x_SOURCES  = ../common/Rladiv.test.cpp $(test_srcdepends)
Rladiv_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Rladiv_test__Float64x_CXXFLAGS = $(test_cxxflags)

Rlae2_test__Float64x_SOURCES  = ../common/Rlae2.test.cpp $(test_srcdepends)
Rlae2_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Rlae2_test__Float64x_CXXFLAGS = $(test_cxxflags)

Rlaev2_test__Float64x_SOURCES  = ../common/Rlaev2.test.cpp $(test_srcdepends)
Rlaev2_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Rlaev2_test__Float64x_CXXFLAGS = $(test_cxxflags)

Rlamch_test__Float64x_SOURCES  = ../common/Rlamch.test.cpp $(test_srcdepends)
Rlamch_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Rlamch_test__Float64x_CXXFLAGS = $(test_cxxflags)

Rlange_test__Float64x_SOURCES  = ../common/Rlange.test.cpp $(test_srcdepends)
Rlange_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Rlange_test__Float64x_CXXFLAGS = $(test_cxxflags)

Rlanst_test__Float64x_SOURCES  = ../common/Rlanst.test.cpp $(test_srcdepends)
Rlanst_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Rlanst_test__Float64x_CXXFLAGS = $(test_cxxflags)

Rlansy_test__Float64x_SOURCES  = ../common/Rlansy.test.cpp $(test_srcdepends)
Rlansy_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Rlansy_test__Float64x_CXXFLAGS = $(test_cxxflags)

Rlapy2_test__Float64x_SOURCES  = ../common/Rlapy2.test.cpp $(test_srcdepends)
Rlapy2_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Rlapy2_test__Float64x_CXXFLAGS = $(test_cxxflags)

Rlapy3_test__Float64x_SOURCES  = ../common/Rlapy3.test.cpp $(test_srcdepends)
Rlapy3_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Rlapy3_test__Float64x_CXXFLAGS = $(test_cxxflags)

Rlarfb_test__Float64x_SOURCES  = ../common/Rlarfb.test.cpp $(test_srcdepends)
Rlarfb_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Rlarfb_test__Float64x_CXXFLAGS = $(test_cxxflags)

Rlarfg_test__Float64x_SOURCES  = ../common/Rlarfg.test.cpp $(test_srcdepends)
Rlarfg_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Rlarfg_test__Float64x_CXXFLAGS = $(test_cxxflags)

Rlarf_test__Float64x_SOURCES  = ../common/Rlarf.test.cpp $(test_srcdepends)
Rlarf_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Rlarf_test__Float64x_CXXFLAGS = $(test_cxxflags)

Rlarft_test__Float64x_SOURCES  = ../common/Rlarft.test.cpp $(test_srcdepends)
Rlarft_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Rlarft_test__Float64x_CXXFLAGS = $(test_cxxflags)

Rlartg_test__Float64x_SOURCES  = ../common/Rlartg.test.cpp $(test_srcdepends)
Rlartg_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Rlartg_test__Float64x_CXXFLAGS = $(test_cxxflags)

Rlaruv_test__Float64x_SOURCES  = ../common/Rlaruv.test.cpp $(test_srcdepends)
Rlaruv_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Rlaruv_test__Float64x_CXXFLAGS = $(test_cxxflags)

Rlascl_test__Float64x_SOURCES  = ../common/Rlascl.test.cpp $(test_srcdepends)
Rlascl_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Rlascl_test__Float64x_CXXFLAGS = $(test_cxxflags)

Rlaset_test__Float64x_SOURCES  = ../common/Rlaset.test.cpp $(test_srcdepends)
Rlaset_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Rlaset_test__Float64x_CXXFLAGS = $(test_cxxflags)

Rlasr_test__Float64x_SOURCES  = ../common/Rlasr.test.cpp $(test_srcdepends)
Rlasr_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Rlasr_test__Float64x_CXXFLAGS = $(test_cxxflags)

Rlasrt_test__Float64x_SOURCES  = ../common/Rlasrt.test.cpp $(test_srcdepends)
Rlasrt_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Rlasrt_test__Float64x_CXXFLAGS = $(test_cxxflags)

Rlassq_test__Float64x_SOURCES  = ../common/Rlassq.test.cpp $(test_srcdepends)
Rlassq_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Rlassq_test__Float64x_CXXFLAGS = $(test_cxxflags)

Rlaswp_test__Float64x_SOURCES  = ../common/Rlaswp.test.cpp $(test_srcdepends)
Rlaswp_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Rlaswp_test__Float64x_CXXFLAGS = $(test_cxxflags)

Rlasyf_test__Float64x_SOURCES  = ../common/Rlasyf.test.cpp $(test_srcdepends)
Rlasyf_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Rlasyf_test__Float64x_CXXFLAGS = $(test_cxxflags)

Rlatrd_test__Float64x_SOURCES  = ../common/Rlatrd.test.cpp $(test_srcdepends)
Rlatrd_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Rlatrd_test__Float64x_CXXFLAGS = $(test_cxxflags)

Rlatrs_test__Float64x_SOURCES  = ../common/Rlatrs.test.cpp $(test_srcdepends)
Rlatrs_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Rlatrs_test__Float64x_CXXFLAGS = $(test_cxxflags)

Rlauu2_test__Float64x_SOURCES  = ../common/Rlauu2.test.cpp $(test_srcdepends)
Rlauu2_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Rlauu2_test__Float64x_CXXFLAGS = $(test_cxxflags)

Rlauum_test__Float64x_SOURCES  = ../common/Rlauum.test.cpp $(test_srcdepends)
Rlauum_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Rlauum_test__Float64x_CXXFLAGS = $(test_cxxflags)

Rorg2l_test__Float64x_SOURCES  = ../common/Rorg2l.test.cpp $(test_srcdepends)
Rorg2l_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Rorg2l_test__Float64x_CXXFLAGS = $(test_cxxflags)

Rorg2r_test__Float64x_SOURCES  = ../common/Rorg2r.test.cpp $(test_srcdepends)
Rorg2r_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Rorg2r_test__Float64x_CXXFLAGS = $(test_cxxflags)

Rorgql_test__Float64x_SOURCES  = ../common/Rorgql.test.cpp $(test_srcdepends)
Rorgql_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Rorgql_test__Float64x_CXXFLAGS = $(test_cxxflags)

Rorgqr_test__Float64x_SOURCES  = ../common/Rorgqr.test.cpp $(test_srcdepends)
Rorgqr_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Rorgqr_test__Float64x_CXXFLAGS = $(test_cxxflags)

Rorgtr_test__Float64x_SOURCES  = ../common/Rorgtr.test.cpp $(test_srcdepends)
Rorgtr_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Rorgtr_test__Float64x_CXXFLAGS = $(test_cxxflags)

Rpocon_test__Float64x_SOURCES  = ../common/Rpocon.test.cpp $(test_srcdepends)
Rpocon_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Rpocon_test__Float64x_CXXFLAGS = $(test_cxxflags)

Rposv_test__Float64x_SOURCES  = ../common/Rposv.test.cpp $(test_srcdepends)
Rposv_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Rposv_test__Float64x_CXXFLAGS = $(test_cxxflags)

Rpotf2_test__Float64x_SOURCES  = ../common/Rpotf2.test.cpp $(test_srcdepends)
Rpotf2_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Rpotf2_test__Float64x_CXXFLAGS = $(test_cxxflags)

Rpotri_test__Float64x_SOURCES  = ../common/Rpotri.test.cpp $(test_srcdepends)
Rpotri_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Rpotri_test__Float64x_CXXFLAGS = $(test_cxxflags)

Rpotrs_test__Float64x_SOURCES  = ../common/Rpotrs.test.cpp $(test_srcdepends)
Rpotrs_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Rpotrs_test__Float64x_CXXFLAGS = $(test_cxxflags)

Rsteqr_test__Float64x_SOURCES  = ../common/Rsteqr.test.cpp $(test_srcdepends)
Rsteqr_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Rsteqr_test__Float64x_CXXFLAGS = $(test_cxxflags)

Rsterf_test__Float64x_SOURCES  = ../common/Rsterf.test.cpp $(test_srcdepends)
Rsterf_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Rsterf_test__Float64x_CXXFLAGS = $(test_cxxflags)

Rsyev_test__Float64x_SOURCES  = ../common/Rsyev.test.cpp $(test_srcdepends)
Rsyev_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Rsyev_test__Float64x_CXXFLAGS = $(test_cxxflags)

Rsytd2_test__Float64x_SOURCES  = ../common/Rsytd2.test.cpp $(test_srcdepends)
Rsytd2_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Rsytd2_test__Float64x_CXXFLAGS = $(test_cxxflags)

Rsytrd_test__Float64x_SOURCES  = ../common/Rsytrd.test.cpp $(test_srcdepends)
Rsytrd_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Rsytrd_test__Float64x_CXXFLAGS = $(test_cxxflags)

Rtrti2_test__Float64x_SOURCES  = ../common/Rtrti2.test.cpp $(test_srcdepends)
Rtrti2_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Rtrti2_test__Float64x_CXXFLAGS = $(test_cxxflags)

Rtrtri_test__Float64x_SOURCES  = ../common/Rtrtri.test.cpp $(test_srcdepends)
Rtrtri_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Rtrtri_test__Float64x_CXXFLAGS = $(test_cxxflags)

Rtrtrs_test__Float64x_SOURCES  = ../common/Rtrtrs.test.cpp $(test_srcdepends)
Rtrtrs_test__Float64x_LDFLAGS  = $(libdepends) $(test_libdepends)
Rtrtrs_test__Float64x_CXXFLAGS = $(test_cxxflags)



