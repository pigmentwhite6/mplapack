set xlabel font "Helvetica,20"
set ylabel font "Helvetica,20"
set key font "Helvetica,20"
set title font "Helvetica,24"
set title "Rsyrk %%MODELNAME%%"
set xlabel "Dimension"
set ylabel "MFLOPS"
#set terminal postscript eps color enhanced
set terminal pdf

plot \
"log.Rsyrk.mpfr"            using 1:3 title 'MPFR 512bit'            with lines linewidth 6, \
"log.Rsyrk.mpfr_opt"        using 1:3 title 'MPFR 512bit(OpenMP)'    with lines linewidth 6, \
"log.Rsyrk.gmp"             using 1:3 title 'GMP  512bit'            with lines linewidth 6, \
"log.Rsyrk.gmp_opt"         using 1:3 title 'GMP  512bit(OpenMP)'    with lines linewidth 6, \
"log.Rsyrk.qd"              using 1:3 title 'quad-double'            with lines linewidth 6, \
"log.Rsyrk.qd_opt"	    using 1:3 title 'quad-double(OpenMP)'    with lines linewidth 6