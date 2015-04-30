reset

#set term png #output terminal and file
#set output "histogram.png"
set term postscript landscape enhanced color "Text" 16
set output 'bin.ps'

#set term x11

set macro

hist(x,width)=width*floor(x/width)+width/2.0

#hist_plot= " set boxwidth binwidth; \
#	plot file every ::igl using (hist(column(col),binwidth)):(scale) smooth freq with boxes notitle"

#log_hist_plot= " set boxwidth binwidth; \
#	plot file every ::igl using (hist(log10(column(col)*scale),binwidth)):(1.0) smooth freq with boxes notitle"

# hist_plot = "width=(max-min)/n; \
#              set xrange [min:max]; \
#              set yrange [0:]; \
#              set offset graph 0.05,0.05,0.05,0.0; \
#              set xtics min,(max-min)/5,max; \
#              set boxwidth width*0.9; \
#              set style fill solid 0.5; \
#              set tics out nomirror; \
#              plot file every ::igl u (hist(column(col)*scale,width)):(1.0) smooth freq w boxes lc rgb\"green\" notitle "

# log_hist_plot = "width=(max-min)/n; \
#              set xrange [min:max]; \
#              set yrange [0:]; \
#              set offset graph 0.05,0.05,0.05,0.0; \
#              set xtics min,(max-min)/5,max; \
#              set boxwidth width*0.9; \
#              set style fill solid 0.5; \
#              set tics out nomirror; \
#              plot file every ::igl u (hist(log10(column(col)*scale),width)):(1.0) smooth freq w boxes lc rgb\"green\" notitle "

file = "bdat"  #filename
igl  = 4       #ignore lines
#scale = 1.0    #scaling of data
#n    = 100     #number of intervals
#rscale=206205.*10.0  #AU

#------------------ECC-----------------#
#col  = 6        #column number
#max  = 1.0      #max value8
#min  = 0.       #min value
#binwidth = 0.01  #bin size

set grid
set xlabel "Ecc"
set ylabel "Number"
plot file every ::igl u (hist($6,0.01)):(1.0) smooth freq with boxes t ''

#----------------M2/M1------------------#

reset
#set grid
#set xlabel 'Log10(M1[M_{sun}])'
#set ylabel 'M2/M1'
#plot file every ::igl u ($4>$3?log10($4):log10($3)):($4>$3?$3/$4:$4/$3) t ''
#set ylabel 'Log10(M2(M_{sun}])'
#set logscale x
#set logscale y
#plot file every ::igl u ($4>$3?$4:$3):($4>$3?$3:$4) t ''
set xlabel 'M2/M1 (M2<=M1)'
set ylabel 'Number'
plot file every ::igl u (hist($4>$3?$3/$4:$4/$3,0.1)):(1.0) smooth freq with boxes t 'All' lt 1 lc 1, \
       '' every ::igl u ($4>=5||$3>=5?(hist($4>$3?$3/$4:$4/$3,0.1)):1/0):(1.0) smooth freq with boxes t 'M>=5 M_sun' lt 1 lc 2, \
       '' every ::igl u ($4<5&&$3<5?(hist($4>$3?$3/$4:$4/$3,0.1)):1/0):(1.0) smooth freq with boxes t 'M<5 M_sun' lt 1 lc 3

#------------------MASS1-----------------#
# col  = 3        #column number
# max  = 5.       #max value
# min  = 0.1      #min value

# set xlabel "M1"
# set ylabel "Frequency"

# @log_hist_plot

#------------------MASS2-----------------#
# col  = 4        #column number
# max  = 5.       #max value
# min  = 0.1      #min value

# set xlabel "M2"
# set ylabel "Frequency"

# @log_hist_plot

#-------------SEMI----------------#
#col  = 8        #column number
#max  = 3.       #max value
#min  = -3.      #min value
reset
set grid
set xlabel "Log10(Semi[AU])"
set ylabel "Number"

plot file every ::igl u (hist(log10($8),0.1)):(1.0) smooth freq with boxes t 'All' lt 1 lc 1, \
       '' every ::igl u ($4>=5||$3>=5?hist(log10($8),0.1):1/0):(1.0) smooth freq with boxes t 'M>=5 M_sun' lt 1 lc 2, \
       '' every ::igl u (($4<5&&$3<5)?hist(log10($8),0.1):1/0):(1.0) smooth freq with boxes t 'M<5 M_sun' lt 1 lc 3

#-------------Period----------------#
#col  = 7        #column number
#max  = 3.
#min  = -3.

set xlabel "Log10(Period[days])"
set ylabel "Number"

plot file every ::igl u (hist(log10($7),0.1)):(1.0) smooth freq with boxes t 'All' lt 1 lc 1, \
       '' every ::igl u ($4>=5||$3>=5?hist(log10($7),0.1):1/0):(1.0) smooth freq with boxes t 'M>=5 M_sun' lt 1 lc 2, \
       '' every ::igl u ($4<5&&$3<5?hist(log10($7),0.1):1/0):(1.0) smooth freq with boxes t 'M<5 M_sun' lt 1 lc 3

#--------------M1/M2------------------#
# file = "bdat.9" #filename

# set xlabel "M1"
# set ylabel "M2"
# unset logscale x
# unset logscale y
# set autoscale
# min = 0.08
# max = 100.

# set xrange [min:max]
# set yrange [min:max]

# plot file u 5:6 w p

# set autoscale
