#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>
#include <iostream>
#include <string>
using namespace std;

#define _HOST_ "172.16.21.142"
#define _USER_ "root"
#define _PASSWD_ ""
#define _DBNAME_ "mysql"

bool Query(MYSQL* mysql,const string& strSql)
{    
    if(0 != mysql_query(mysql,strSql.c_str()))
    {
     cout << strSql <<" (error)" << endl;
     exit(0);  
    }
    cout << strSql <<" (OK)" << endl;
    return true;
}

int main()
{
	MYSQL* mysql = mysql_init(NULL);
	if(!mysql)
    {
     printf("init fail\n");
     exit(0);   
    }
	mysql = mysql_real_connect(mysql, _HOST_,
					   _USER_,
					   _PASSWD_,
					   _DBNAME_,
					   0,
					   NULL,
					   0);
	if(!mysql)
    {
     printf("connect fail\n");
     exit(0);   
    }
    mysql_set_character_set(mysql,"utf8");//设置字符集
    printf("hello mysql\n");
  
    string strSql = "drop database if exists mysql_api_test";
    Query(mysql,strSql);
    
    strSql = "create database mysql_api_test";
    Query(mysql,strSql);
    
    strSql = "use mysql_api_test";
    Query(mysql,strSql);
    
    strSql = "create table user(id smallint unsigned auto_increment primary key,username varchar(20) not null)";
    Query(mysql,strSql);
    
    strSql = "insert into user (username) value ('Nick')";
    Query(mysql,strSql);
    
    strSql = "insert into user (username) value ('Bob')";
    Query(mysql,strSql);
    
    strSql = "insert into user (username) value ('Alice')";
    Query(mysql,strSql);
    
    //查询数据-开始
    strSql = "select * from user";
    Query(mysql,strSql);
    MYSQL_RES* result = mysql_store_result(mysql);
    if(NULL == result)
    {
        cout << "get result fail" << endl;
    }
    
    
    int num_fields = mysql_num_fields(result);//字段个数
    //print fields
    MYSQL_FIELD* fields = mysql_fetch_fields(result);
    for (int i = 0;i < num_fields;i++) 
    {
         cout << fields[i].name << "\t";
    }
    cout << endl;
    
    //打印数据
    MYSQL_ROW row;
    while(NULL != (row = mysql_fetch_row(result)))
    {
        //cout << row[0] << "\t" << row[1] << endl;
        for (int i = 0;i < num_fields;i++) 
        {
             cout << row[i] << "\t";
        }
        cout << endl;
    }   
    
    mysql_free_result(result);
    //查询数据-结束
    
    mysql_close(mysql);
	return 0;

}

