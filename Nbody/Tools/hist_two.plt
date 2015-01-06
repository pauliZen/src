reset

#set term png #output terminal and file
#set output "histogram.png"
set term postscript landscape enhanced color "Text" 16
set output 'bin_0.ps'

#set term x11

set macro

hist(x,width)=width*floor(x/width)+width/2.0
hstyle="smooth freq with boxes "

two_hist = "plot [@xr][@yr] file1 every ::igl u (hist(@col,binwidth)):(scale) @hstyle t 'Old', \
     file2 every ::igl u (hist(@col,binwidth)):(scale) @hstyle t 'New'"

file1 = "bdat.old"  #filename
file2 = "bdat.new"
igl  = 4       #ignore lines
n    = 100     #number of intervals
scale = 1.0    #scaling of data
binwidth = 0.1 #bin size
xr = ""        #xrange
yr = ""        #yrange
#rscale=206205.*10.0  #AU

#------------------ECC-----------------#
col = "$6"
set xlabel "Ecc"
set ylabel "Frequency"
binwidth = 0.02 #bin size

@two_hist

#------------------MASS1-----------------#
col = "log10($3)"
set xlabel "log(M1)"
set ylabel "Frequency"

@two_hist

#------------------MASS2-----------------#
col  = "log10($4)"        #column number

set xlabel "log(M2)"
set ylabel "Frequency"

@two_hist

#--------------M1/M2-------------------#
col = "($4/$3)"
set xlabel 'M1/M2'
set ylabel 'Frequency'
xr = "0:1"

@two_hist

#-------------SEMI----------------#
col  = "log10($8)"        #column number

set xlabel "Log(Semi[AU])"
set ylabel "Frequency"
binwidth = 0.1 #bin size
xr = ""

@two_hist

#-------------Period----------------#
col  = "log10($7)"        #column number

set xlabel "Log(Period[days])"
set ylabel "Frequency"


@two_hist

