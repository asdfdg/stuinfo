#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "cgic.h"

int cgiMain()
{

fprintf(cgiOut, "Content-type:text/html;charset=utf-8\n\n");

  char Cno [4] = "\0";
	char Cname[20] = "\0";
	char Ccredit[5] = "\0";

	int status = 0;

	status = cgiFormString("Cno", Cno , 20);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get Cno error!\n");
		return 1;
	}


	status = cgiFormString("Cname",  Cname, 20);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get Cname error!\n");
		return 1;
	}

	status = cgiFormString("Ccredit",  Ccredit, 8);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get Ccredit error!\n");
		return 1;
	}




	//fprintf(cgiOut, "name = %s, age = %s, stuId = %s\n", name, age, stuId);

	int ret;
	char sql[128] = "\0";
	MYSQL *db;

	//初始化
	db = mysql_init(NULL);
	mysql_options(db,MYSQL_SET_CHARSET_NAME,"utf8");
	if (db == NULL)
	{
		fprintf(cgiOut,"mysql_init fail:%s\n", mysql_error(db));
		return -1;
	}

	//连接数据库
	db = mysql_real_connect(db, "127.0.0.1", "root", "123456", "stu",  3306, NULL, 0);
	if (db == NULL)
	{
		fprintf(cgiOut,"mysql_real_connect fail:%s\n", mysql_error(db));
		mysql_close(db);
		return -1;
	}



	strcpy(sql, "CREATE TABLE course(Cno CHAR(4) PRIMARY KEY,Cname CHAR(20)UNIQUE NOT NULL,Ccredit SMALLINT  check(Ccredit>=0  and Ccredit<=10))character set=utf8");
	if ((ret = mysql_real_query(db, sql, strlen(sql) + 1)) != 0)
	{
		if (ret != 1)
		{
			fprintf(cgiOut,"mysql_real_query fail:%s\n", mysql_error(db));
			mysql_close(db);
			return -1;
		}
	}



	sprintf(sql, "insert into course values('%s', '%s', %d)", Cno,  Cname, atoi(Ccredit));
	if (mysql_real_query(db, sql, strlen(sql) + 1) != 0)
	{
		fprintf(cgiOut, "%s\n", mysql_error(db));
		mysql_close(db);
		return -1;
	}

	fprintf(cgiOut, "add student ok!\n");
	mysql_close(db);
	return 0;
}
