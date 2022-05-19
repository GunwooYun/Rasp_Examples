#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h> // mysql library (compact)

static char *host = "localhost";
static char *user = "root";
static char *pass = "kcci";
static char *dbname = "test";

int main()
{
	MYSQL *conn;
	MYSQL_RES *res_ptr;
	MYSQL_ROW sqlrow;

	conn = mysql_init(NULL);

	if(!(mysql_real_connect(conn, host, user, pass, dbname, 0, NULL, 0))){

		fprintf(stderr, "ERROR : %s[%d]\n", mysql_error(conn), mysql_errno(conn));
		exit(1);
	}
	printf("Connection Successful!!\n");

	//int res = mysql_query(conn, "insert into states(id, state, number)values(null, 'jeju', '064')");
	int res = mysql_query(conn, "select * from states");
	
	if(!res){
		//printf("inserted %lu rows\n", (unsigned long)mysql_affected_rows(conn));
		res_ptr = mysql_store_result(conn);
		if(res_ptr){
			printf("Retrived %lu rows\n", (unsigned long)mysql_num_rows(res_ptr));
			sqlrow = mysql_fetch_row(res_ptr);
			//if(sqlrow != NULL) printf("sqlrow is NULL\n");
			//printf("%10S %10s %10s\n", sqlrow[0], sqlrow[1], sqlrow[2]);
			while((sqlrow = mysql_fetch_row(res_ptr))) printf("%10S %10s %10s\n", sqlrow[0], sqlrow[1], sqlrow[2]);
		}
	}else{
		//fprintf(stderr, "insert error %d : %s\n", mysql_errno(conn), mysql_error(conn));
		fprintf(stderr, "select error %d : %s\n", mysql_errno(conn), mysql_error(conn));
	}
	mysql_free_result(res_ptr);
	mysql_close(conn);


	return EXIT_SUCCESS;
}
