#include <iostream>
#include "sqlite3.h"

#define _DEBUG_ 1

using namespace std;

int main(int argc, char* argv[])
{
	
	sqlite3 *db = NULL;
	char *zErrMsg = 0;

	int rc;
	rc = sqlite3_open("mydemo.db", &db); //��ָ�������ݿ��ļ�,��������ڽ�����һ��ͬ�������ݿ��ļ�
	if (rc)
	{
		
		cout << stderr << "Can't open database: " << sqlite3_errmsg(db) << endl;
		sqlite3_close(db);
		return (1);
	}
	else 
		cout<<"create or open Sqlite3 sucess" <<endl;
	
	//������  TABLE ���ֶ���:ID,SensorID ,SiteNum ,Time, SensorParameter
	char *sql = " CREATE TABLE SensorData(ID INTEGER PRIMARY KEY,SensorID INTEGER,SiteNum INTEGER,Time VARCHAR(12),SensorParameter REAL);";
	sqlite3_exec(db, sql, 0, 0, &zErrMsg);


	//�������� 
	sql = "INSERT INTO SensorData VALUES(NULL , 4 , 1 , '201602011203', 18.9 );";
	sqlite3_exec(db, sql, 0, 0, &zErrMsg);

	sql = "INSERT INTO SensorData VALUES(NULL , 24 , 40 , '201602011303', 16.4 );";
	sqlite3_exec(db, sql, 0, 0, &zErrMsg);

	sql = "INSERT INTO SensorData VALUES(NULL , 34 , 15 , '201602011308', 15.4 );";
	sqlite3_exec(db, sql, 0, 0, &zErrMsg);


	int nrow = 0, ncolumn = 0;
	char **azResult; //��ά�����Ž��

	//��ѯ����
	sql = "SELECT * FROM SensorData ";
	sqlite3_get_table(db, sql, &azResult, &nrow, &ncolumn, &zErrMsg);
	int i = 0;
	printf("row:%d column=%d  ", nrow, ncolumn);
	printf(" The result of querying is :  \r\n");
	for (i = 0; i < (nrow + 1) * ncolumn; i++)
		printf("azResult[%d] = %s  \r\n", i, azResult[i]);

	//ɾ������
	sql = "DELETE FROM SensorData WHERE SensorID =0 ;";
	sqlite3_exec(db, sql, 0, 0, &zErrMsg);


#ifdef _DEBUG_
	printf("zErrMsg = %s  ", zErrMsg);
#endif
	sql = "SELECT * FROM SensorData ";
	sqlite3_get_table(db, sql, &azResult, &nrow, &ncolumn, &zErrMsg);
	printf(" row:%d column=%d ", nrow, ncolumn);
	printf(" After deleting , the result of querying is :  ");
	for (i = 0; i < (nrow + 1) * ncolumn; i++)
		printf("azResult[%d] = %s \r\n", i, azResult[i]);


	//�ͷŵ� azResult ���ڴ�ռ�
	sqlite3_free_table(azResult);

#ifdef _DEBUG_
	printf("zErrMsg = %s  ", zErrMsg);
#endif

	sqlite3_close(db); //�ر����ݿ�



	system("pause");
	return 0;
}