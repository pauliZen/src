      subroutine gopu_SpinTerms(X,V,r,M1,m2,c,alpha,dv3,dalpha)
      implicit real*8 (a-h,m,n,o-z)
      real*8 x(3),v(3),dv3(3),n(3)
      real*8 dalpha(3),w(3),alpha(3)
      real*8 nxa(3),vxa(3),J(3)
      real*8 dv_q(3)!,trh(3) ! TEST 
      save
      ! This routine assumes: The BH mass M1>>m2. Spin of
                            ! m2 is neglected.
       do k=1,3
       n(k)=x(k)/r 
       end do
       m=m1+m2
       eta=m1*m2/m**2
       SQ=sqrt(1-4*eta)
       Aq=-12/(1+sq)
       Bq= -6/(1+sq)-3
       Cq=1+6/(1+sq)
       rdot=cdot(n,v)
       call cross(n,v,w)
       anxv=cdot(alpha,w)
       call cross(n,alpha,nxa)
       call cross(v,alpha,vxa)
       do k=1,3
       dv3(k)=-m1**2/(c*r)**3*
     & (Aq*anxv*n(k)+rdot*Bq*nxa(k)+Cq*vxa(k))
       end do
       coeff=eta*m/(c*r)**2*(3/(1+sq)+.5d0)
       call cross(w,alpha,dalpha)
        do k=1,3
        dalpha(k)=coeff*dalpha(k)
        end do
c       C.Will Q2-terms
        sjj=0
        do k=1,3
        j(k)=M1**2/c*alpha(k)
        sjj=sjj+j(k)**2
        end do
        sj=sqrt(sjj)
        if(sj.ne.0.0)then  ! if sj=0, then J(k)=0 and Q-term =0 anyway
        do k=1,3
        j(k)=j(k)/sj
        end do
        end if
        Q2=-sjj/M1/c**2!  X=X_j-X_i in this code
c        do k=1,3
c       trh(k)=dv3(k)  ! add Quadrupole terms
c     &  +1.5*Q2/r**4*(n(k)*(5*cdot(n,j)**2-1)-2*cdot(n,j)*j(k))
c        end do
        Q2=-Q2 ! earlier Q2 was grad Q-Potential, now grad
               ! Q-ForceFunction => different sign 
        call Q2term(m,r,x,v,c,Q2,j,dv_q)
        do k=1,3
        dv3(k)=dv3(k)+dv_q(k) ! add quadrupole terms (these are more correct)
        end do
       return
       end

       subroutine Q2term(m,r,x,v,c,Q2,e,dvq)
       implicit real*8 (a-h,m,o-z)
       real*8 x(3),v(3),dvq(3),Rx(3),Ux(3),e(3)
       ! m=m1+m2 (?),vv=v**2
       ! e=spin direction;  Q2=m**3/c**4*xi**2, xi=|spin|=Kerr parameter
       vv=cdot(v,v)
       er=cdot(e,x)
       RQ2=(-1+3*(er/r)**2)/(2*r**3) ! the quadrupole pot (exept 4 factor Q2)
       U2b=m/r
       oc=1/c 
       do k=1,3
       Ux(k)=-x(k)*m/r**3 ! two-body acceleration
       Rx(k)=(3*e(k)*er)/r**5+
     & (x(k)*(-3*er**2/r**6-(3*(-1+(3*(er)**2)/r**2))/(2*r**4)))/r
       ! quadrupole potential gradient
       end do
       vRx=cdot(v,Rx) 
       do k=1,3 ! complete quadrupole term in \dot v
       dvq(k) = Q2*(Rx(k)*(1 + oc**2*(-4*(Q2*RQ2 + U2b) + vv))
     & -4*oc**2*(RQ2*Ux(k)+vRx*v(k)))
       end do
       return
       end

       function cdot(a,b)
       real*8  a(3),b(3),cdot
       cdot=a(1)*b(1)+a(2)*b(2)+a(3)*b(3)
       return
       end

       subroutine cross(a,b,c)
       real*8 a(3),b(3),c(3)
       c(1)=a(2)*b(3)-a(3)*b(2)
       c(2)=a(3)*b(1)-a(1)*b(3)
       c(3)=a(1)*b(2)-a(2)*b(1)
       return
       end
