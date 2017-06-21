#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "cgic.h"

int cgiMain()
{

	fprintf(cgiOut, "Content-type:text/html;charset=utf-8\n\n");

  char Ino [20] = "\0";
	char Iname[20] = "\0";
	char Isex[8] = "\0";
	char Iage[16] = "\0";
	char Iphone[16] = "\0";
  char Sdept[16] = "\0";
	int status = 0;

	status = cgiFormString("Ino", Ino , 20);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get Ino error!\n");
		return 1;
	}


	status = cgiFormString("Iname",  Iname, 20);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get Iname error!\n");
		return 1;
	}

	status = cgiFormString("Isex",  Isex, 8);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get Isex error!\n");
		return 1;
	}

	status = cgiFormString("Iage",  Iage, 16);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get Iage error!\n");
		return 1;
	}

	status = cgiFormString("Iphone",  Iphone, 16);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get Iphone error!\n");
		return 1;
	}

	status = cgiFormString("Sdept",  Sdept, 16);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get Sdept error!\n");
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



	/*strcpy(sql, "CREATE TABLE information
	/*(Ino CHAR(20) PRIMARY KEY,Iname CHAR(20) NOT NULL,Isex CHAR(8) CHECK (sex in ('男' ,'女')), Iage SMALLINT NOT NULL,
   Iphone INT(11) UNIQUE NOT NULL,Sdept INT, FOREIGN KEY (Sdept) REFERENCES school(Sdept)
 )");*
	if ((ret = mysql_real_query(db, sql, strlen(sql) + 1)) != 0)
	{
		if (ret != 1)
		{
			fprintf(cgiOut,"mysql_real_query fail:%s\n", mysql_error(db));
			mysql_close(db);
			return -1;
		}
	}*/



	sprintf(sql, "insert into information values('%s', '%s', '%s', %d, %d ,%d)", Ino,  Iname, Isex ,atoi(Iage), atoi(Iphone) ,atoi(Sdept));
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
