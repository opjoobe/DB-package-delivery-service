#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "mysql.h"
#include <iostream>       // std::cout
#include <typeinfo>       // operator typeid


#pragma comment(lib, "libmysql.lib")

const char* host = "localhost";
const char* user = "joobe24"; //joobe24
const char* pw = "rhawnql88@"; //rhawnql88@
const char* db = "2ndproject";

/*mysql에 연결하기 위한 전초작업임*/

int main(void) {

	MYSQL* connection = NULL;
	MYSQL conn;
	MYSQL_RES* sql_result;
	MYSQL_ROW sql_row;
	const char* query;
	int type; // 프로그램에서 어떤 타입의 쿼리를 수행할지 고르기 위한 변수

	if (mysql_init(&conn) == NULL)
		printf("mysql_init() error!");

	connection = mysql_real_connect(&conn, host, user, pw, db, 3306, (const char*)NULL, 0);
	if (connection == NULL)
	{
		printf("%d ERROR : %s\n", mysql_errno(&conn), mysql_error(&conn));
		return 1;
	}
	//뭔가 연결이 잘못되었다면 이 위에서 끝날것임.
	else
	{
		//printf("Connection Succeed\n\n\n");

		if (mysql_select_db(&conn, db))
		{
			printf("%d ERROR : %s\n", mysql_errno(&conn), mysql_error(&conn));
			return 1;
		}
		/*여기 위까지는 조교님이 주신 CPP와 동일. mysql과 연결하는 작업.*/
		FILE* pFile = NULL;

		pFile = fopen("20120968_1.txt", "r"); //"CRUD를 위한 텍스트 파일 1 읽어오기"
		if (pFile != NULL)
		{
			char strTemp[255];
			while (!feof(pFile))
			{
				query = fgets(strTemp, sizeof(strTemp), pFile);
				mysql_query(connection, query); //mysql에 txt의 줄마다 있는 query를 보내 처리
			}
			fclose(pFile);
		}// txt 파일을 통한 Create와 Insert 완료
		else
		{
			printf("file open error");
			return 1;
		}// file open error인 경우 처리
		
		 /*다 읽었으니 본격적으로 프로그램 수행 받기 시작*/
		printf("************************************************************\n");
		printf("******* SG Company Package Delivery Management System ******\n");
		printf("*******        Designed by joobe24@sogang.ac.kr       ******\n");
		printf("************************************************************\n\n\n");
		while (1) 
		{		
			printf("\n------- SELECT QUERY TYPES -------\n\n");
			printf("\t1. TYPE I\n");
			printf("\t2. TYPE II\n");
			printf("\t3. TYPE III\n");
			printf("\t4. TYPE IV\n");
			printf("\t5. TYPE V\n");
			printf("\t0. QUIT\n");
			printf("Which type of query? ");
			scanf("%d", &type);
			printf("\n");
		
			if (type == 0) {
				printf("\n---- QUIT ----\n"); // choice가 0에 해당하는 경우, 프로그램을 종료시킴
				printf("Have a nice day!!!\n\n");
				break;
			}
			else if (type == 1)
			{
				while (1) {
					int t_number; //트럭번호를 받기 위한 변수
					printf("---- TYPE I ----\n"); // choice가 1에 해당하는 경우, subtype을 제시함. 
					printf("Input the number of truck : ");
					scanf("%d", &t_number);
					//char query1[200] = "select location_contact from location where location_id='t_";
					if (t_number != 1721) 
					{
						printf("Truck %d is not destroyed.\n\n", t_number); 
						continue;
					}
					while (1)
					{
						int type1;
						printf("\n---- Subtypes in TYPE I----\n");
						printf("\t1. TYPE I-1\n");
						printf("\t2. TYPE I-2\n");
						printf("\t3. TYPE I-3\n");
						printf("Which type of query? ");
						scanf("%d", &type1);
						if (type1 == 0)
							break;
						if (type1 == 1)
								{
									printf("\n---- TYPE I-1 ----\n");
									printf("** Find all customers who had a package on the truck at the time of the crash. **\n");
									printf("Customer ID: ");
 									char query1_1[255] = "select S.customer_id from shipment S, tracking T where S.shipment_id = T.shipment_id and location_id = 't_1721' and date_format(date_time, '%Y-%m-%d') = '2019-04-01'";
									int state1_1 = 0;
									state1_1 = mysql_query(connection, query1_1);
									if (state1_1 == 0)
									{
										sql_result = mysql_store_result(connection);
										while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
										{
											printf("%s | ", sql_row[0]);
										}
										mysql_free_result(sql_result);
									}
									printf("\n\n");
									continue;
								}
						if (type1 == 2)
								{
									printf("\n---- TYPE I-2 ----\n");
									printf("** Find all recipients who had a package on the truck at the time of the crash. **\n");
									printf("Customer name: ");
									char query1_2[200] = "select r_name from shipment S, tracking T where S.shipment_id = T.shipment_id and date_format(date_time,'%Y-%m-%d')= '2019-04-01' and location_id ='t_1721'";
									int state1_2 = 0;
									state1_2 = mysql_query(connection, query1_2);
									if (state1_2 == 0)
									{
										sql_result = mysql_store_result(connection);
										while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
										{
											printf("%s | ", sql_row[0]);
										}
										mysql_free_result(sql_result);
									}
									printf("\n\n");
								}
						if (type1 == 3)
								{
									printf("\n---- TYPE I-3 ----\n");
									printf("** Find the last successful delivery by that truck prior to the crash. **\n");
									printf("Last Successful Delivery on: ");
									char query1_3[200] = "select max(date_time) from tracking where date_time < '2019-04-01' and location_id = 't_1721'";
									int state1_3 = 0;
									state1_3 = mysql_query(connection, query1_3);
									if (state1_3 == 0)
									{
										sql_result = mysql_store_result(connection);
										while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
										{
											printf("%s ", sql_row[0]);
										}
										mysql_free_result(sql_result);
									}
									printf("\n\n");
								}
					}
					break;
				}
			}
			else if (type == 2)
			{
				int ans, year;
				char s1[10];
				char s2[10];
				printf("---- TYPE II ----\n");
				while (1) {
					printf("** Find the customer who has shipped the most packages in certain year **\n");
					printf("Which Year? : ");
					scanf("%d", &ans);
					if (ans == 0) break;
					year = ans - 2000;
					sprintf(s1, "%d", year);

					/*query 처리*/
					char query2[255] = "with temp(c,v) as (select customer_id, count(customer_id) from shipment S where shipment_id like 'S";
					strcat(query2, s1);
					strcat(query2, "%' group by customer_id) select c from temp where v = (select max(v) from temp)");

					printf("Customer ID: ");
					int state2 = 0;
					state2 = mysql_query(connection, query2);
					if (state2 == 0)
					{
						sql_result = mysql_store_result(connection);
						while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
						{
							printf("%s ", sql_row[0]);
						}

						mysql_free_result(sql_result);
					}
					printf("shipped most in %d\n", ans);
				}
				printf("\n\n");
			}
			else if (type == 3)
			{
				int ans;
				char s3[10];
				printf("---- TYPE III ----\n");
				while (1) {
					printf("** Find the customer who has spent the most money on shipping in the past certian year **\n");
					printf("Which Year? : ");
					scanf("%d", &ans);
					if (ans == 0) break;
					sprintf(s3, "%d", ans);
					char query3[255] = "with temp(c,v) as (select customer_id,sum(charge) from bill B, pays P where B.bill_id = P.bill_id and year(payment_date)='";
					strcat(query3, s3);
					strcat(query3,"'group by customer_id) select c from temp where v=(select max(v) from temp)");
					printf("Customer ID: ");
					int state3 = 0;
					state3 = mysql_query(connection, query3);
					if (state3 == 0)
					{
						sql_result = mysql_store_result(connection);
						while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
						{
							printf("%s ", sql_row[0]);
						}
						mysql_free_result(sql_result);
					}
					printf("spent most in %d\n", ans);
				}
				printf("\n\n");
			}
			else if (type == 4)
			{
				printf("---- TYPE IV ----\n\n");
				printf("** Find those packages that were not delivered within the promised time**\n");
				char query4[255] = "select package_id from shipment where promised_date<delivery_date";
				int state4 = 0;
				state4 = mysql_query(connection, query4);
				if (state4 == 0)
				{
					sql_result = mysql_store_result(connection);
					while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
					{
						printf("%s | ", sql_row[0]);
					}
					mysql_free_result(sql_result);
				}
				printf("\n\n");
			}
			else if (type == 5)
			{
				fflush(stdin);
				char customer[30];
				char yrmth[20];
				printf("---- TYPE V ----\n");
				printf("** Generate the bill for each customer for the past certain month **\n");
				printf("Customer Name : ");
				scanf(" %[^\n]s", customer);
				fflush(stdin);
				printf("Which month(YYYY-MM)? ");
				fflush(stdin);
				scanf(" %[^\n]s", &yrmth);
				char filename[30] = "bill-";
				strcat(filename, yrmth);
				strcat(filename, "-");
				strcat(filename, customer);
				strcat(filename, ".txt");
	
				FILE* bill = fopen(filename, "w");
				printf("Generating Bill..\n");
				char query5_tmp[255] = "select customer_id from customer where name='";
				strcat(query5_tmp, customer);
				strcat(query5_tmp, "'");
				char c_id[8];
				int state5_0 = 0;
				state5_0 = mysql_query(connection, query5_tmp);
				if (state5_0 == 0)
				{
					sql_result = mysql_store_result(connection);
					while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
					{
						strcpy(c_id,sql_row[0]);
						break;
					}
					mysql_free_result(sql_result);
				}
				
				char query5_t1[255] = "create view t5_1 as select name, address, bill_date, service_id, charge from shipment S join bill B on (S.shipment_id=B.shipment_id) join customer C on (S.customer_id=C.customer_id)";
				mysql_query(connection, query5_t1);
				char query5_t2[255] = "create view t5_2 as select name,bill_date,service_id,charge from shipment S join bill B on (S.shipment_id=B.shipment_id) join customer C on (S.customer_id=C.customer_id)";
				mysql_query(connection, query5_t2);
				char query5_t3[255] = "create view t5_3 as select customer_id, B.bill_id, content,value,service_id,bill_type,bill_date,charge from shipment S join bill B on (S.shipment_id=B.shipment_id) join package P on (S.package_id=P.package_id)";
				mysql_query(connection, query5_t3);
				
				char query5_1[255] = "select name, address, sum(charge) from t5_1 where name='";
				strcat(query5_1, customer); 
				strcat(query5_1, "' and bill_date like '");
				strcat(query5_1, yrmth);
				strcat(query5_1, "%' group by name, address");
				int state5_1 = 0;
				state5_1 = mysql_query(connection, query5_1);
				if (state5_1 == 0)
				{ 
					sql_result = mysql_store_result(connection);
					fprintf(bill, "*** Simple Billing List ***\n");
					fprintf(bill, "| %20s | %-50s | %10s |\t\n", "Customer Name", "Address", "Amount");
					while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
					{
						fprintf(bill, "| %20s | %-50s | %10s |\t\n", sql_row[0], sql_row[1], sql_row[2]);
					}
					mysql_free_result(sql_result);
				}
				fprintf(bill,"\n\n");
				char query5_2[255] = "select bill_date, service_id, charge from t5_2 where name='";
				strcat(query5_2, customer); 
				strcat(query5_2, "' and bill_date like '");
				strcat(query5_2, yrmth);
				strcat(query5_2, "%'");
				int state5_2 = 0;
				state5_2 = mysql_query(connection, query5_2);
				if (state5_2 == 0)
				{
					sql_result = mysql_store_result(connection);
					fprintf(bill, "*** Type of Service Billing List ***\n");
					fprintf(bill, "| %20s | %20s | %20s |\t\n", "Bill_date", "Type_of_Service", "Charge");

					while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
					{
						fprintf(bill, "| %20s | %20s | %20s |\t\n", sql_row[0], sql_row[1], sql_row[2]);
					}
					mysql_free_result(sql_result);
				}
				fprintf(bill, "\n\n");
				char query5_3[255] = "select bill_id, content, value, service_id, bill_type, bill_date, charge from t5_3 where customer_id = '";
				strcat(query5_3, c_id);
				strcat(query5_3, "'");
				int state5_3 = 0;
				state5_3 = mysql_query(connection, query5_3);
				if (state5_3 == 0)
				{
					sql_result = mysql_store_result(connection);
					fprintf(bill, "*** Itemized Billing List ***\n");
					fprintf(bill, "| %15s | %30s | %15s | %15s | %15s | %15s | %15s |\n","Bill_id","Content","Value","Service_id","Bill_type","Bill_date","Charge");
					while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
					{
						fprintf(bill,"| %15s | %30s | %15s | %15s | %15s | %15s | %15s | \n", sql_row[0], sql_row[1], sql_row[2], sql_row[3], sql_row[4], sql_row[5], sql_row[6]);
					}
					mysql_free_result(sql_result);
				}

				fclose(bill);
				printf("Generation Completed\n\n");
			}
			else
				printf("Wrong choice.");
		}
		mysql_close(connection);
	}
	FILE* pFile2 = NULL;
	pFile2 = fopen("20120968_2.txt", "r"); //"CRUD를 위한 텍스트 파일 2 읽어오기"
	if (pFile2 != NULL)
	{
		char strTemp[255];
		while (!feof(pFile2))
		{
			query = fgets(strTemp, sizeof(strTemp), pFile2);
			mysql_query(connection, query); //mysql에 txt의 줄마다 있는 query를 보내 처리
		}
		fclose(pFile2);
	}
	return 0;
}