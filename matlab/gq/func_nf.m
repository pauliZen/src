%²ÄÁÏ¸´ÕÛÉäÂÊ
function nf=func_nf(S,gamma,gamma1)
k=datax;
omiga=3*10^10*k;
e=5.35+313600*S./(313600-k.*k-i*gamma1*k)-2.86*10^24./(omiga.*omiga+i*gamma*omiga);
nf=sqrt(e);