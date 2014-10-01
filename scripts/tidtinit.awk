
BEGIN {
    tunit=14.91;
    t2=tunit*tunit;
}
NR>1 {
    f=4.0/3.0*$2/($3^3);
    print $1/tunit, ($4-f)/t2, $5/t2, $6/t2, ($7-f)/t2, $8/t2, $9/t2, ($10-f)/t2, $11/t2, $12/t2
}

