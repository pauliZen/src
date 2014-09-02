%∑¥…‰¬ º∆À„
function R=reflection1(S,gamma,c,gammato)
k=datax;
omiga=3*10^10*k;
nf=func_nf(S,gamma,gammato);
ns=func_ns(S,gamma);
rvf=(1-nf)./(1+nf);
rfs=(nf-ns)./(nf+ns);
a=sqrt(exp(i*2*nf*3.8*10^(-4).*omiga/(3*10^10)));
R=c*abs(((rvf+a.*rfs)./(1+a.*rvf.*rfs)).*((rvf+a.*rfs)./(1+a.*rvf.*rfs)));