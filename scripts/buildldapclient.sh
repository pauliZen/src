yum -y install openldap-clients nss-pam-ldapd
scp root@10.0.1.3:/etc/pam.d/password-auth-ac /etc/pam.d/
scp root@10.0.1.3:/etc/pam.d/system-auth-ac /etc/pam.d/
scp root@10.0.1.3:/etc/openldap/ldap.conf /etc/openldap/
scp root@10.0.1.3:/etc/pam_ldap.conf /etc/
scp root@10.0.1.3:/etc/nslcd.conf /etc/
scp root@10.0.1.3:/etc/nsswitch.conf /etc/
scp root@10.0.1.3:/etc/sysconfig/iptables /etc/sysconfig/
chkconfig oddjobd on
chkconfig nscd on
