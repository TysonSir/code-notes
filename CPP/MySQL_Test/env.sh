#!/bin/bash
yum remove mysql mysql-server mysql-libs compat-mysql51
rpm -qa | grep mariadb
rpm -qa | grep mysql
yum install mysql-server
yum install mysql-client
yum install mariadb-devel
service mysql start
ps aux | grep mysql
ps aux | grep mariadb
echo "password is null"
