%拟合程序，对四个参数调整拟合，最终得到折射率R
function R=fitting(z)
x=datax;
temp=datay;
y=temp(1,:);
beta0=z;
beta=nlinfit(x,y,@func,beta0);
R(1,:)=reflection1(beta(1),beta(2),beta(3),beta(4));
beta(1)
beta(2)
beta(3)
beta(4)

y=temp(2,:);
beta=nlinfit(x,y,@func,beta0);
R(2,:)=reflection1(beta(1),beta(2),beta(3),beta(4));

y=temp(3,:);
beta=nlinfit(x,y,@func,beta0);
R(3,:)=reflection1(beta(1),beta(2),beta(3),beta(4));
R=R';