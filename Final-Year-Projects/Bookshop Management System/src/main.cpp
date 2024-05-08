// NURSYAZA NISA BINITI ARFARIZAL
// B032010244

#include<iostream>
#include <stdio.h>
#include<mysql.h>
#include<conio.h>
#include<windows.h>
#include<cstdlib> // access to exit() function
#include<cstdio>
#include<fstream>
#include<sstream>
#include<string>
#include<iomanip> 

using namespace std;

//Global variable
int qstate;
MYSQL* conn;
MYSQL_ROW row;
MYSQL_RES* res;

class db_response
{
public:
	static void ConnectionFunction()
	{
		conn = mysql_init(0);
		if (conn)
		{
			cout << "DATABASE CONNECTED" << endl;
			system("cls");
		}
		else
			cout << "FAILED TO CONNECT" << mysql_errno(conn) << endl;
		conn = mysql_real_connect(conn, "localhost", "root", "", "db_bookshop", 3306, NULL, 0);
		if (conn)
		{
			cout << "DATABASE CONNECTED TO MYSQL" << conn << endl;
			system("pause");
		}
		else
			cout << "FAILED TO CONNECT!" << mysql_errno(conn) << endl;
	}
};

// Admin
void AdminLogin();
void AdminMenu();
void CustomerRegistration();
void AddBook();
void DeleteBook();
void UpdatePrice();
void UpdateStock();
void GenerateReport();
void StockAnalysis();
void BookAnalysis();
void CustomerAnalysis();

// Customer
void CustomerMenu();
void ViewBook();
void PurchaseBook();

int main()
{
	// Initial Load
	system("cls");
	system("title BOOKSHOP MANAGEMENT SYSTEM");
	system("color 0f");
	// Initial Load End

	// Call Methods
	db_response::ConnectionFunction();
	system("cls");
	// Admin
	// AdminLogin();
	// AdminMenu();
	// CustomerRegistration();
	// AddBook();
	// DeleteBook();
	// UpdatePrice();
	// UpdateStock();
	// GenerateReport();
	// StockAnalysis();
	// BookAnalysis();
	// CustomerAnalysis();
	
	// Customer
	// CustomerMenu();
	// PurchaseBook();
	// ViewBook();
	// Call Methods End

	// Variables
	int choose = 0;
	char exitSecurity;
	// Variables End

	cout << endl << endl;
	cout << "	---------------------------------------------------------------------------------------------------\n";
	cout << "					WELCOME TO BOOKSHOP MANAGEMENT SYSTEM 		  " << endl ;
	cout << "	---------------------------------------------------------------------------------------------------\n" << endl << endl;
	cout << "\n					1. ADMIN";
	cout << "\n					2. CUSTOMER";
	cout << "\n					3. EXIT" << endl << endl;

	cout << "\n			CHOOSE ONE: ";
	cin >> choose;

	switch (choose)
	{
	case 1:
		AdminLogin();
		break;
	case 2:
		CustomerMenu();
		break;
	case 3:
	ExitProgram:
		cout << "\n\n		PROGRAM TERMINATING. ARE YOU SURE? (y/N): ";
		cin >> exitSecurity;
		if (exitSecurity == 'y' || exitSecurity == 'Y') {
			exit(0);
		}
		else if (exitSecurity == 'n' || exitSecurity == 'N') {
			system("cls");
			main();
		}
		else {
			cout << "		NEXT TIME CHOOSE AFTER CORRESPONING RULES." << endl;
			goto ExitProgram;
		}
		break;
	default:
		cout << "\n		PLEASE CHOOSE BETWEEN 1-3....PRESS TO CONTINUE";
		system("PAUSE");
		system("cls");
		main();
		break;
		
	}
	return 0; 
}

void AdminLogin()
{
	system("cls");

	// Variables
	string adminID, username, validusername, validpassword;
	//char ch;
	cout << "\n\n				****** ADMINISTRATOR LOGIN ******				\n\n" << endl << endl;

	cout << "			1.	ENTER USERNAME : ";
	cin >> username;
	cout << "			2.	ENTER PASSWORD : ";

	char password[32];//to store password.
	int i = 0;
	char a;//a Temp char
	for (i = 0;;)//infinite loop
	{
		a = _getch();//stores char typed in a
		if ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z') || (a >= '0' && a <= '9'))
			//check if a is numeric or alphabet
		{
			password[i] = a;//stores a in pass
			++i;
			cout << "*";
		}
		if (a == '\b' && i >= 1)//if user typed backspace
			//i should be greater than 1.
		{
			cout << "\b \b";//rub the character behind the cursor.
			--i;
		}
		if (a == '\r')//if enter is pressed
		{
			password[i] = '\0';//null means end of string.
			break;//break the loop
		}
	}

	string login_query = "SELECT * FROM admin WHERE username ='" + username + "'"; 
	char const* q = login_query.c_str(); // c_str converts string to constant char and this is required
	qstate = mysql_query(conn, q);

	if (!qstate)
	{
		res = mysql_store_result(conn);
		while ((row = mysql_fetch_row(res)))

		{
			validusername = row[1];
			validpassword = row[2];
		}
		if (username == validusername && password == validpassword)
		{
			system("cls");
			cout << endl << endl;
			cout << "	---------------------------------------------------------------------------------------------------\n";
			cout << "					 ADMIN HAS SUCCESSFULLY LOGIN!!! 		  " << endl;
			cout << "	---------------------------------------------------------------------------------------------------\n" << endl << endl;
			system("PAUSE");
			system("cls");
			AdminMenu();

		}
		else
		{

			system("cls");
			cout << endl << endl;
			cout << "	---------------------------------------------------------------------------------------------------\n";
			cout << "			UNSUCCESSFULL TO LOGIN!!! INVALID USERNAME OR PASSWORD!!! 		  " << endl;
			cout << "					 PLEASE TRY AGAIN!! 		  " << endl;
			cout << "	---------------------------------------------------------------------------------------------------\n" << endl << endl;
			system("PAUSE");
			system("cls");
			AdminLogin();
		}
	}
	else
	{
		cout << "		QUERY EXECUTION PROBLEM!" << mysql_errno(conn) << endl;
	}
}

void AdminMenu()
{
	// Initial load
	system("cls");

	// Variables
	int choose = 0;
	char exitSecurity;
	char exitMain;
	// Variables End
	
	cout << endl << endl;
	cout << "	---------------------------------------------------------------------------------------------------\n";
	cout << "					ADMINISTRATOR MENU 		  " << endl;
	cout << "	---------------------------------------------------------------------------------------------------\n" << endl << endl;
	cout << "\n					1. CUSTOMER REGISTRATION";
	cout << "\n					2. ADD BOOK";
	cout << "\n					3. DELETE BOOK";
	cout << "\n					4. VIEW BOOK'S DETAILS";
	cout << "\n					5. UPDATE BOOK'S PRICE";
	cout << "\n					6. UPDATE BOOK'S STOCK";
	cout << "\n					7. GENERATE REPORT";
	cout << "\n					8. LOGOUT";
	cout << "\n					9. EXIT" << endl << endl;

	cout << "\n			CHOOSE ONE: ";
	cin >> choose;

	switch (choose)
	{
	case 1:
		CustomerRegistration();
		break;
	case 2:
		AddBook();
		break;
	case 3:
		DeleteBook();
		break;
	case 4:
		ViewBook();
		break;
	case 5:
		UpdatePrice();
		break;
	case 6:
		UpdateStock();
	case 7:
		GenerateReport();
		break;
	case 8 :
		main();
		break;
	case 9:
ExitProgram:
		cout << "\n\n	PROGRAM IS TERMINATING. ARE YOU SURE? (Y/N): ";
		cin >> exitSecurity;
		if (exitSecurity == 'y' || exitSecurity == 'Y') {
			exit(0);
		}
		else if (exitSecurity == 'n' || exitSecurity == 'N') {
			system("cls");
			main();
		}
		else {
			cout << "		NEXT TIME CHOOSE AFTER CORRESPONDING LINES." << endl;
			goto ExitProgram;
		}
		break;
	default:
		cout << "\n		PLEASE CHOOSE BETWEEN 1-6. PRESS ENTER TO CONTINUE...";
		system("PAUSE");
		system("cls");
		main();
		break;
	}
}

void CustomerRegistration()
{
	system("cls");

	// Variables
	string customerID ;
	string custname ;
	string custphone;
	string custaddress;
	// Variables end

	char choose;

	cout << "\n\n				****** CUSTOMER REGISTRATION ******				\n\n" << endl << endl;

	cout << "			1.	ENTER CUSTOMER NAME	: ";
	getline(cin >> ws, custname);
	cout << "			2.	ENTER PHONE NO		: ";
	cin >> custphone;
	cout << "			3.	ENTER CUSTOMER ADDRESS	: ";
	getline(cin >> ws, custaddress);

	string insert_query = "INSERT INTO customer (customerID, custname, custphone, custaddress) VALUES ('""', '" + custname + "', '" + custphone + "',  '" + custaddress + "')";

	const char* q = insert_query.c_str();

	qstate = mysql_query(conn, q);

	if (!qstate)
	{
		cout << endl << "\n		CUSTOMER HAS SUCCESSFULLY ADDED!! \n" << endl;
	}
	else
	{
		cout << "\n		QUERY EXECUTION PROBLEM!" << mysql_errno(conn) << endl;
	}

	// Exit Code
	cout << "\n		PRESS 'M' to ADMIN MENU AND 'A' TO INSERT ANY KEY TO EXIT: ";
	cin >> choose;
	if (choose == 'm' || choose == 'M')
	{
		AdminMenu();
	}
	else if (choose == 'a' || choose == 'A')
	{
		CustomerRegistration();
	}
	else
	{
		exit(0);
	}
}

void AddBook()
{
	// Initial load
	system("cls");

	// Variables
	string bookISBN;
	string subject;
	string price;
	string title;
	string author;
	string quantity;
	char choose;
	// Variables end

	cout << "\n\n					****** ADDING BOOK ******					\n\n" << endl << endl;
	cout << "			1.	ENTER BOOK ISBN	: ";
	cin >> bookISBN;
	cout << "			2.	ENTER SUBJECT	: ";
	getline(cin >> ws, subject);
	cout << "			3.	ENTER PRICE	: ";
	cin >> price;
	cout << "			4.	ENTER TITLE	: ";
	getline(cin >> ws, title);
	cout << "			5.	ENTER AUTHOR	: ";
	getline(cin >> ws, author);
	cout << "			6.	ENTER QUANTITY	: ";
	cin >> quantity;

	string insert_query = "INSERT INTO books (bookISBN, subject, price, title, author, quantity) VALUES ('" + bookISBN + "', '" + subject + "', '" + price + "',  '" + title + "',  '" + author + "', '" + quantity + "')";
	
	const char* q = insert_query.c_str();

	qstate = mysql_query(conn, q);

	if (!qstate)
	{
		cout << endl << "\n		BOOK HAS SUCCESSFULLY ADDED!!" << endl;
		goto ExitMenu;
	}
	else
	{
		cout << "\n		QUERY EXECUTION PROBLEM!" << mysql_errno(conn) << endl;
	}

	// Exit Code
ExitMenu:
	cout << "\n		PRESS 'M' to ADMIN MENU AND 'A' TO INSERT ANY KEY TO EXIT: ";
	cin >> choose;
	if (choose == 'm' || choose == 'M')
	{
		AdminMenu();
	}
	else if (choose == 'a' || choose == 'A')
	{
		AddBook();
	}
	else
	{
		exit(0);
	}
}

void DeleteBook() {

	system("cls");

	// Variables
	char choose;
	string bkISBN;
	string books[30];
	int indexForbookISBN = 0;
	bool HaveException = false;
	bool NotInDatabase = false;

	// Store Variables
	string storeISBN, storesubject, storeprice, storetitle, storeauthor, storequantity;

	cout << "\n\n						****** DELETING BOOK ******				\n\n" << endl << endl;

	qstate = mysql_query(conn, "SELECT * FROM books");

	if (!qstate)
	{
		res = mysql_store_result(conn);
		printf("	-----------------------------------------------------------------------------------------------------------\n");
		printf("	| %-5s | %-25s | %-10s | %-20s | %-15s | %-10s |\n", "BOOK ISBN", "SUBJECT", "PRICE", "TITLE", "AUTHOR", "QUANTITY");
		printf("	-----------------------------------------------------------------------------------------------------------\n");
		while ((row = mysql_fetch_row(res)))
		{
			printf("	| %-5s | %-25s | %-10s | %-20s | %-15s | %-10s |\n", row[0], row[1], row[2], row[3], row[4], row[5]);
			books[indexForbookISBN] = row[0];
			indexForbookISBN++;
		}
	}
	else
	{
		cout << "\n		QUERY EXCEPTION PROBLEM!" << mysql_errno(conn) << endl;
	}

	try
	{
		cout << endl;
		cout << "\n\n	1.	ENTER BOOK ISBN TO DELETE BOOK : ";
		cin >> bkISBN;
		cout << endl;
	}
	catch (exception e)
	{
		cout << "\n		PLEASE ENTER A VALID NUMBER." << endl;
		HaveException = true;
	}

	if (HaveException == false)
	{
		stringstream streamISBN;
		string strISBN;
		streamISBN << bkISBN;
		streamISBN >> strISBN;

		for (int i = 0; i < indexForbookISBN; i++)
		{
			if (strISBN != books[i])
			{
				NotInDatabase = true;
				
			}
			else
			{
				NotInDatabase = false;
				break;
				goto ExitMenu;
			}
		}
		if (NotInDatabase == false)
		{
			if (!qstate)
			{

				string findbyISBN_query = "SELECT * FROM books WHERE bookISBN like '" + strISBN + "%'";
				const char* qi = findbyISBN_query.c_str();
				qstate = mysql_query(conn, qi);
				res = mysql_store_result(conn);
				while (row = mysql_fetch_row(res))
				{
					cout << "				BOOK ISBN	: " << row[0]
						<< "\n				SUBJECT		: " << row[1]
						<< "\n				PRICE		: " << row[2]
						<< "\n				TITLE		: " << row[3]
						<< "\n				AUTHOR		: " << row[4]
						<< "\n				QUANTITY	: " << row[5]
						<< endl << endl;

					storeISBN		= row[0];
					storesubject	= row[1];
					storeprice		= row[2];
					storetitle		= row[3];
					storeauthor		= row[4];
					storequantity	= row[5];

				}
			}
			else
			{
				cout << "		QUERY EXECUTION PROBLEM!!" << mysql_errno(conn) << endl;
			}


			string delete_query = "DELETE FROM books WHERE bookISBN = '" + strISBN + "'";
			const char* qd = delete_query.c_str();
			qstate = mysql_query(conn, qd);

			if (!qstate)
			{
				cout << endl << "\n		BOOK HAS SUCCESSFULLY DELETED!! " << endl;
				goto ExitMenu;
			}
			else
			{
				cout << "\n		FAILED TO UPDATE!!" << mysql_errno(conn) << endl;
			}

		}
	
		else
		{
			cout << "\n		BOOK NOT FOUND IN DATABASE." << endl;
		}
		
	}
	
	// Exit Code
ExitMenu:
	cout << endl;
	cout << "\n		PRESS 'M' to ADMIN MENU AND 'A' TO INSERT ANY KEY TO EXIT:";
	cin >> choose;
	if (choose == 'm' || choose == 'M')
	{
		AdminMenu();
	}
	else if (choose == 'a' || choose == 'A')
	{
		DeleteBook();
	}
	else
	{
		exit(0);
	}
}

void UpdatePrice()
{
	system("cls");

	// Variables
	string bookISBN, price;
	char choose;
	string bkISBN;
	string books[30];
	int indexForbookISBN = 0;
	bool HaveException = false;
	bool NotInDatabase = false;

	// Store Variables
	string storeISBN, storeprice;

	cout << "\n\n					****** UPDATING BOOK'S PRICE ******				\n\n" << endl << endl;

	qstate = mysql_query(conn, "SELECT * FROM books");

	if (!qstate)
	{
		res = mysql_store_result(conn);
		printf("	-----------------------------------------------------------------------------------------------------------\n");
		printf("	| %-5s | %-25s | %-10s | %-20s | %-15s | %-10s |\n", "BOOK ISBN", "SUBJECT", "PRICE", "TITLE", "AUTHOR", "QUANTITY");
		printf("	-----------------------------------------------------------------------------------------------------------\n");
		while ((row = mysql_fetch_row(res))) {
			printf("	| %-5s | %-25s | %-10s | %-20s | %-15s | %-10s |\n", row[0], row[1], row[2], row[3], row[4], row[5]);
			books[indexForbookISBN] = row[0];
			indexForbookISBN++;
		}
	}
	else
	{
		cout << "\n		QUERY EXECUTION PROBLEM!!" << mysql_errno(conn) << endl;
	}
	try
	{
		cout << endl;
		cout << "\n\n	1.	ENTER BOOK ISBN TO UPDATE PRICE	: ";
		cin >> bkISBN;
		cout << endl;
	}
	catch (exception e)
	{
		cout << "\n		PLEASE ENTER A VALID NUMBER." << endl;
		HaveException = true;
	}

	if (HaveException == false)
	{
		stringstream streamISBN;
		string strISBN;
		streamISBN << bkISBN;
		streamISBN >> strISBN;

		for (int i = 0; i < indexForbookISBN; i++)
		{
			if (strISBN != books[i])
			{
				NotInDatabase = true;

			}
			else
			{
				NotInDatabase = false;
				break;
				goto ExitMenu;
			}
		}

		if (NotInDatabase == false)
		{
			string findbyISBN_query = "SELECT * FROM books WHERE bookISBN LIKE '" + strISBN + "%'";
			const char* qi = findbyISBN_query.c_str();
			qstate = mysql_query(conn, qi);

			if (!qstate)
			{

				res = mysql_store_result(conn);
				while (row = mysql_fetch_row(res))
				{
					cout << "				BOOK ISBN	: " << row[0]
						<< "\n				PRICE		: " << row[2]
						<< endl << endl;

					storeISBN = row[0];
					storeprice = row[2];

				}
			}
			else
			{
				cout << "\n		QUERY EXECUTION PROBLEM!!" << mysql_errno(conn) << endl;
			}

			cin.ignore(1, '\n');
			cout << endl;
			cout << "		ENTER UPDATED PRICE (0 TO NOT CHANGE): ";
			cin >> price;
			if (price == "0")
			{
				price = storeprice;
			}

			string update_query = "UPDATE books SET price = '" + price + "'WHERE bookISBN = '" + storeISBN + "'";
			const char* qu = update_query.c_str();
			qstate = mysql_query(conn, qu);

			if (!qstate)
			{
				cout << endl << "		BOOK PRICE HAS SUCCESSFULLY UPDATED!! \n" << endl;
				string  findbyISBN_query = "SELECT * FROM books WHERE bookISBN LIKE '" + storeISBN + "%'";
				const char* qi = findbyISBN_query.c_str();
				qstate = mysql_query(conn, qi);

				if (!qstate)
				{
					res = mysql_store_result(conn);
					while ((row = mysql_fetch_row(res)))
					{
						printf("					-------------------------\n");
						printf("					| %-5s | %-10s |\n", "BOOK ISBN", "PRICE");
						printf("					-------------------------\n");
						printf("					| %-5s | %-10s |\n", row[0], row[2]);
					}
				}
			}
			else
			{
				cout << "\n		FAILED TO UPDATE!!" << mysql_errno(conn) << endl;
			}

		}
		else
		{
			cout << "\n		BOOK NOT FOUND IN DATABASE." << endl;
		}
	}


	// Exit Code
ExitMenu:
	cout << endl;
	cout << "\n		PRESS 'M' to ADMIN MENU AND 'A' TO INSERT ANY KEY TO EXIT: ";
	cin >> choose;
	if (choose == 'm' || choose == 'M')
	{
		AdminMenu();
	}
	else if (choose == 'a' || choose == 'A')
	{
		UpdatePrice();
	}
	else
	{
		exit(0);
	}
}

void UpdateStock()
{
	system("cls");

	// Variables
	string bookISBN, quantity;
	char choose;
	string bkISBN;
	string books[30];
	int indexForbookISBN = 0;
	bool HaveException = false;
	bool NotInDatabase = false;

	// Store Variables
	string storeISBN, storequantity;

	cout << "\n\n					****** UPDATING BOOK'S STOCK ******				\n\n" << endl << endl;

	qstate = mysql_query(conn, "SELECT * FROM books");

	if (!qstate)
	{
		res = mysql_store_result(conn);
		printf("	-----------------------------------------------------------------------------------------------------------\n");
		printf("	| %-5s | %-25s | %-10s | %-20s | %-15s | %-10s |\n", "BOOK ISBN", "SUBJECT", "PRICE", "TITLE", "AUTHOR", "QUANTITY");
		printf("	-----------------------------------------------------------------------------------------------------------\n");
		while ((row = mysql_fetch_row(res))) {
			printf("	| %-5s | %-25s | %-10s | %-20s | %-15s | %-10s |\n", row[0], row[1], row[2], row[3], row[4], row[5]);
			books[indexForbookISBN] = row[0];
			indexForbookISBN++;
		}
	}
	else
	{
		cout << "		QUERY EXECUTION PROBLEM!!" << mysql_errno(conn) << endl;
	}
	try
	{
		cout << endl;
		cout << "\n\n	1.	ENTER BOOK ISBN TO UPDATE QUANTITY	: ";
		cin >> bkISBN;
		cout << endl;
	}
	catch (exception e)
	{
		cout << "		PLEASE ENTER A VALID NUMBER." << endl;
		HaveException = true;
	}

	if (HaveException == false)
	{
		stringstream streamISBN;
		string strISBN;
		streamISBN << bkISBN;
		streamISBN >> strISBN;

		for (int i = 0; i < indexForbookISBN; i++)
		{
			if (strISBN != books[i])
			{
				NotInDatabase = true;

			}
			else
			{
				NotInDatabase = false;
				break;
				goto ExitMenu;
			}
		}

		if (NotInDatabase == false)
		{
			string findbyISBN_query = "SELECT * FROM books WHERE bookISBN LIKE '" + strISBN + "%'";
			const char* qi = findbyISBN_query.c_str();
			qstate = mysql_query(conn, qi);

			if (!qstate)
			{

				res = mysql_store_result(conn);
				while (row = mysql_fetch_row(res))
				{
					cout << "				BOOK ISBN	: " << row[0]
						<< "\n				QUANTITY	: " << row[5]
						<< endl << endl;

					storeISBN = row[0];
					storequantity = row[5];

				}
			}
			else
			{
				cout << "		QUERY EXECUTION PROBLEM!!" << mysql_errno(conn) << endl;
			}

			cin.ignore(1, '\n');
			cout << endl;
			cout << "		ENTER UPDATED STOCK (0 TO NOT CHANGE): ";
			cin >> quantity;
			if (quantity == "0")
			{
				quantity = storequantity;
			}

			string update_query = "UPDATE books SET quantity = '" + quantity + "'WHERE bookISBN = '" + storeISBN + "'";
			const char* qu = update_query.c_str();
			qstate = mysql_query(conn, qu);

			if (!qstate)
			{
				cout << endl << "		BOOK QUANTITY HAS SUCCESSFULLY UPDATED!! \n" << endl;
				string  findbyISBN_query = "select * from books where bookISBN like '" + storeISBN + "%'";
				const char* qi = findbyISBN_query.c_str();
				qstate = mysql_query(conn, qi);

				if (!qstate)
				{
					res = mysql_store_result(conn);
					while ((row = mysql_fetch_row(res)))
					{
						printf("					-------------------------\n");
						printf("					| %-5s | %-10s |\n", "BOOK ISBN", "QUANTITY");
						printf("					-------------------------\n");
						printf("					| %-5s | %-10s |\n", row[0], row[5]);
					}
				}
			}
			else
			{
				cout << "\n		FAILED TO UPDATE!!" << mysql_errno(conn) << endl;
			}

		}
		else
		{
			cout << "\n		BOOK NOT FOUND IN DATABASE." << endl;
		}
	}


	// Exit Code
ExitMenu:
	cout << endl;
	cout << "\n		PRESS 'M' to MENU AND 'A' TO INSERT ANY KEY TO EXIT: ";
	cin >> choose;
	if (choose == 'm' || choose == 'M')
	{
		AdminMenu();
	}
	else if (choose == 'a' || choose == 'A')
	{
		UpdateStock();
	}
	else
	{
		exit(0);
	}
}

void GenerateReport() {

	system("cls");

	// Variables
	int choose;
	cout << endl;
	cout << endl<< "\n					****** GENERATING REPORT ******				\n\n" << endl;

	cout << "\n					1. DISPLAY STOCK ANALYSIS ";
	cout << "\n					2. DISPLAY BOOK ANALYSIS ";
	cout << "\n					3. DISPLAY CUSTOMER ANALYSIS ";
	cout << "\n					4. BACK TO ADMIN MENU" << endl << endl;

	cout << "\n			CHOOSE ONE: ";
	cin >> choose;

	switch (choose)
	{
	case 1:
		StockAnalysis();
		break;
	case 2:
		BookAnalysis();
		break;
	case 3:
		CustomerAnalysis();
		break;
	case 4:
		AdminMenu();
	}

}

void StockAnalysis() {

	system("cls");

	// Variables
	char choose;
	string getISBN;
	string bookISBN[50], subject[30], price[30], title[30], author[30], quantity[30];
	char viewAnalysis;
	int bookIndex = 0;
	float totalStock = 0.0;
	float eachPrice = 0.0;
	float totalstPrice = 0.0;
	float quan1 = 0.0;
	bool analysis = false;
	bool itemFalse = false;
	string storeISBN[30], storesubject[30], storeprice[30], storetitle[30], storeauthor[30], storequantity[30];
	int storeIndex = 0;
	int storeIndexN = 0;
	// Variables End

	cout << "\n\n					****** DISPLAY STOCK ANALYSIS ******				\n" << endl;


	qstate = mysql_query(conn, "SELECT * FROM books");

	if (!qstate)
	{
		res = mysql_store_result(conn);
		printf("	-----------------------------------------------------------------------------------------------------------\n");
		printf("	| %-5s | %-25s | %-10s | %-20s | %-15s | %-10s |\n", "BOOK ISBN", "SUBJECT", "PRICE", "TITLE", "AUTHOR", "QUANTITY");
		printf("	-----------------------------------------------------------------------------------------------------------\n");

		while ((row = mysql_fetch_row(res)))
		{
			if (atoi(row[5]) > 0)
			{
				cout << endl;
				printf("	| %-5s | %-25s | %-10s | %-20s | %-15s | %-10s |\n", row[0], row[1], row[2], row[3], row[4], row[5]);
				storeISBN[storeIndex] = row[0];
				storesubject[storeIndex] = row[1];
				storeprice[storeIndex] = row[2];
				storetitle[storeIndex] = row[3];
				storeauthor[storeIndex] = row[4];
				storequantity[storeIndex] = row[5];
				storeIndex++;
			}
		}
	}
	else
	{
		cout << "		QUERY EXECUTION PROBLEM!!" << mysql_errno(conn) << endl;
	}


	for (bookIndex = 0;; bookIndex++)
	{

		cout << endl << "\n\n		1.	ENTER BOOK ISBN TO GET BOOK ANALYSIS (ENTER Q TO EXIT): ";
		cin >> getISBN;
		if (getISBN == "Q" || getISBN == "q")
		{
			exit(0);
		}
		else
		{
			for (int i = 0; i < storeIndex; i++)
			{
				if (getISBN == storeISBN[i])
				{
					bookISBN[bookIndex] = getISBN;
					bookIndex++;
					itemFalse = false;
					goto VIEWANALYSIS;
				}
				else
				{
					itemFalse = true;
				}
			}
			if (itemFalse == true)
			{
				cout << endl << "		BOOK ISBN IS NOT AVAILABLE IN DATABASE!! PLEASE ENTER BOOK ISBN THAT IS IN VIEW TABLE." << endl;
				bookIndex--;
				itemFalse = false;
				goto ExitMenu;
			}
		}
	}


VIEWANALYSIS:
	cout << endl << "\n			YOU CHOOSE THIS BOOK'S ISBN: ";
	for (int i = 0; i < bookIndex; i++)
	{
		cout << bookISBN[i] << " ";
	}


	cout << endl << "\n			DO YOU WANT TO VIEW STOCK ANALYSIS FOR THIS BOOK? (ENTER V TO VIEW ANY KEY TO EXIT) : ";
	cin >> viewAnalysis;

	if (viewAnalysis == 'V' || viewAnalysis == 'v')
	{
		for (int i = 0; i < bookIndex; i++)
		{
			for (int j = 0; j < storeIndex; j++)
			{
				if (bookISBN[i] == storeISBN[j])
				{
					qstate = mysql_query(conn, "SELECT bookISBN FROM books");
					if (!qstate)
					{
						res = mysql_store_result(conn);
						while ((row = mysql_fetch_row(res)))
						{
							if (atoi(row[0]) > 0)
							{
								storequantity[storeIndexN] = row[0];
								storeIndexN++;
							}
						}
						storeIndexN = 0;
					}
					else
					{
						cout << "		QUERY EXECUTION PROBLEM!" << mysql_errno(conn) << endl;
					}

					totalStock += strtof((storequantity[j]).c_str(), 0);
					eachPrice += strtof((storeprice[j]).c_str(), 0);
					
					totalstPrice = strtof((storequantity[j]).c_str(), 0)*strtof((storeprice[j]).c_str(), 0);

					analysis = true;

				}
			}
		}

		if (analysis == true)
		{

			string getStock;
			stringstream strstock;
			strstock << totalStock;
			strstock >> getStock;

			string getPrice;
			stringstream strprice;
			strprice << eachPrice;
			strprice >> getPrice;

			string getstPrice;
			stringstream strstprice;
			strstprice << totalstPrice;
			strstprice >> getstPrice;

			cout << endl;
			cout << endl << "			TOTAL BOOKS STOCK FOR THIS ISBN		: " << getStock << endl;
			cout << endl << "			PRICE OF EACH THIS BOOK ISBN		: " << getPrice << endl;
			cout << endl << "			TOTAL PRICE OF THE BOOKS STOCK		: " << getstPrice << endl;
		}
	}

	// Exit Code
ExitMenu:
	cout << endl << "\n			PRESS 'G' to GENERATE REPORT, 'A' TO VIEW STOCK ANALYSIS AGAIN ANY KEY TO EXIT. ";
	cin >> choose;

	if (choose == 'g' || choose == 'G')
	{
		GenerateReport();
	}
	else if (choose == 'a' || choose == 'A')
	{
		StockAnalysis();
	}
	else
	{
		exit(0);
	}
}

void BookAnalysis() {

	system("cls");
	// Variables
	char choose;
	string getISBN;
	string purchaseID[30], sales[30], totalprice[30], bookISBN[30], customerID[30];
	char viewAnalysis;
	int purchaseIndex = 0;
	float totalcustPrice = 0.0;
	float totalcustBuy = 0;
	bool analysis = false;
	bool itemFalse = false;

	string storeID[30], storesales[30], storeprice[30], storeISBN[30], storecustID[30];
	int storeIndex = 0;
	int storeIndexN = 0;
	// Variables End

	cout << "\n\n					****** DISPLAY BOOK ANALYSIS ******				" << endl;


	qstate = mysql_query(conn, "SELECT * FROM purchase");

	if (!qstate)
	{
		res = mysql_store_result(conn);
		//printf("	-----------------------------------------------------------------------------------------------------------\n");
		//printf("	| %-5s | %-25s | %-10s | %-20s | %-15s | %-10s |\n", "BOOK ISBN", "SUBJECT", "PRICE", "TITLE", "AUTHOR", "QUANTITY");
		//printf("	-----------------------------------------------------------------------------------------------------------\n");

		//printf("		------------------------------------------------------------------------------------\n");
		//printf("		| %-15s | %-15s | %-10s | %-10s | %-10s |\n", "CUSTOMER ID", "PURCHASE ID", "BOOK ISBN", "SALES", "TOTAL PRICE");
		//printf("		------------------------------------------------------------------------------------\n");

		while ((row = mysql_fetch_row(res)))
		{
			if (atoi(row[4]) > 0)
			{
				//cout << endl;
				//printf("		| %-15s | %-15s | %-10s | %-10s | %-10s |\n", row[4], row[0], row[3], row[1], row[2]);

				storeID[storeIndex] = row[0];
				storesales[storeIndex] = row[1];
				storeprice[storeIndex] = row[2];
				storeISBN[storeIndex] = row[3];
				storecustID[storeIndex] = row[4];
				storeIndex++;

				//storeISBN[storeIndex] = row[0];
				//storesubject[storeIndex] = row[1];
				//storeprice[storeIndex] = row[2];
				//storetitle[storeIndex] = row[3];
				//storeauthor[storeIndex] = row[4];
				//storequantity[storeIndex] = row[5];
				//storeIndex++;
			}
		}
	}
	else
	{
		cout << "		QUERY EXECUTION PROBLEM!!" << mysql_errno(conn) << endl;
	}


	for (purchaseIndex = 0;; purchaseIndex++)
	{
		string findbyISBN_query = "SELECT * FROM books";
		const char* qi = findbyISBN_query.c_str();
		qstate = mysql_query(conn, qi);

		if (!qstate)
		{

			res = mysql_store_result(conn);
			cout << endl;
			printf("	-----------------------------------------------------------------------------------------------------------\n");
			printf("	| %-5s | %-25s | %-10s | %-20s | %-15s | %-10s |\n", "BOOK ISBN", "SUBJECT", "PRICE", "TITLE", "AUTHOR", "QUANTITY");
			printf("	-----------------------------------------------------------------------------------------------------------\n");
			while (row = mysql_fetch_row(res))
			{
				printf("	| %-5s | %-25s | %-10s | %-20s | %-15s | %-10s |\n", row[0], row[1], row[2], row[3], row[4], row[5]);

			}
		}
		else
		{
			cout << "	QUERY EXECUTION PROBLEM!!" << mysql_errno(conn) << endl;
		}

		cout << endl << "\n\n		1.	ENTER BOOK ISBN TO GET BOOK ANALYSIS (ENTER Q TO EXIT): ";
		cin >> getISBN;
		if (getISBN == "Q" || getISBN == "q")
		{
			exit(0);
		}
		else
		{
			for (int i = 0; i < storeIndex; i++)
			{
				if (getISBN== storeISBN[i])
				{
					bookISBN[purchaseIndex] = getISBN;
					purchaseIndex++;
					itemFalse = false;
					goto VIEWANALYSIS;
				}
				else
				{
					itemFalse = true;
				}
			}
			if (itemFalse == true)
			{
				cout << endl << "		BOOK ISBN IS NOT AVAILABLE IN DATABASE!! PLEASE ENTER BOOK ISBN THAT IS IN VIEW TABLE." << endl;
				purchaseIndex--;
				itemFalse = false;
				goto ExitMenu;
			}
		}
	}


VIEWANALYSIS:
	cout << endl << "\n			YOU CHOOSE THIS BOOK'S ISBN: ";
	for (int i = 0; i < purchaseIndex; i++)
	{
		cout << bookISBN[i] << " ";
	}

	cout << endl << "\n			DO YOU WANT TO VIEW BOOK ANALYSIS FOR THIS BOOK? (ENTER V TO VIEW): ";
	cin >> viewAnalysis;

	if (viewAnalysis == 'V' || viewAnalysis == 'v')
	{
		for (int i = 0; i < purchaseIndex; i++)
		{
			for (int j = 0; j < storeIndex; j++)
			{
				if (bookISBN[i] == storeISBN[j])
				{
					qstate = mysql_query(conn, "SELECT sales, totalprice FROM purchase");
					if (!qstate)
					{
						res = mysql_store_result(conn);
						while ((row = mysql_fetch_row(res)))
						{
							if (atoi(row[0]) > 0)
							{
								storesales[storeIndexN] = row[0];
								storeprice[storeIndexN] = row[1];
								storeIndexN++;
							}
						}
						storeIndexN = 0;
					}
					else
					{
						cout << "		QUERY EXECUTION PROBLEM!" << mysql_errno(conn) << endl;
					}

					totalcustBuy += strtof((storesales[j]).c_str(), 0);
					totalcustPrice += strtof((storeprice[j]).c_str(), 0);

					analysis = true;

				}
			}
		}

		if (analysis == true)
		{

			cout << endl;
			cout << endl << "			TOTAL CUSTOMER BOUGHT THIS BOOK		: " << totalcustBuy << endl;
			cout << endl << "			TOTAL PROFIT FOR THIS BOOK ISBN		: " << totalcustPrice << endl;
		}
	}
	
	// Exit Code
ExitMenu:
	cout << endl << "\n			PRESS 'G' to GENERATE REPORT, 'A' TO VIEW BOOK ANALYSIS AGAIN ANY KEY TO EXIT. ";
	cin >> choose;

	if (choose == 'g' || choose == 'G')
	{
		GenerateReport();
	}
	else if (choose == 'a' || choose == 'A')
	{
		BookAnalysis();
	}
	else
	{
		exit(0);
	}

}

void CustomerAnalysis() {

	system("cls");

	// Variables
	char choose;
	string getcustID;
	string purchaseID[30], sales[30], totalprice[30], bookISBN[30], customerID[30];
	char viewAnalysis;
	int purchaseIndex = 0;
	float totalbkPrice = 0.0;
	float totalbkBuy = 0;
	bool analysis = false;
	bool itemFalse = false;

	string storeID[30], storesales[30], storeprice[30], storeISBN[30], storecustID[30];
	int storeIndex = 0;
	int storeIndexN = 0;
	// Variables End

	cout << "\n\n					****** DISPLAY CUSTOMER ANALYSIS ******				" << endl;


	qstate = mysql_query(conn, "SELECT * FROM purchase");

	if (!qstate)
	{
		res = mysql_store_result(conn);
		//printf("	-----------------------------------------------------------------------------------------------------------\n");
		//printf("	| %-5s | %-25s | %-10s | %-20s | %-15s | %-10s |\n", "BOOK ISBN", "SUBJECT", "PRICE", "TITLE", "AUTHOR", "QUANTITY");
		//printf("	-----------------------------------------------------------------------------------------------------------\n");
		
		//printf("		------------------------------------------------------------------------------------\n");
		//printf("		| %-15s | %-15s | %-10s | %-10s | %-10s |\n", "CUSTOMER ID", "PURCHASE ID", "BOOK ISBN", "SALES", "TOTAL PRICE");
		//printf("		------------------------------------------------------------------------------------\n");

		while ((row = mysql_fetch_row(res)))
		{
			if (atoi(row[4]) > 0)
			{
				//cout << endl;
				//printf("		| %-15s | %-15s | %-10s | %-10s | %-10s |\n", row[4], row[0], row[3], row[1], row[2]);
				
				storeID[storeIndex] = row[0];
				storesales[storeIndex] = row[1];
				storeprice[storeIndex] = row[2];
				storeISBN[storeIndex] = row[3];
				storecustID[storeIndex] = row[4];
				storeIndex++;
				
				//storeISBN[storeIndex] = row[0];
				//storesubject[storeIndex] = row[1];
				//storeprice[storeIndex] = row[2];
				//storetitle[storeIndex] = row[3];
				//storeauthor[storeIndex] = row[4];
				//storequantity[storeIndex] = row[5];
				//storeIndex++;
			}
		}
	}
	else
	{
		cout << "		QUERY EXECUTION PROBLEM!!" << mysql_errno(conn) << endl;
	}


	for (purchaseIndex = 0;; purchaseIndex++)
	{
		string findbyISBN_query = "SELECT * FROM customer";
		const char* qi = findbyISBN_query.c_str();
		qstate = mysql_query(conn, qi);

		if (!qstate)
		{

			res = mysql_store_result(conn);
			cout << endl;
			printf("		---------------------------------------------------------------------------------------\n");
			printf("		| %-15s | %-15s | %-20s | %-25s | \n", "CUSTOMER ID", "CUSTOMER NAME", "CUSTOMER PHONE", "CUSTOMER ADDRESS");
			printf("		----------------------------------------------------------------------------------------\n");
			while (row = mysql_fetch_row(res))
			{
				printf("		| %-15s | %-15s | %-20s | %-25s | \n", row[0], row[1], row[2], row[3]);

			}
		}
		else
		{
			cout << "	QUERY EXECUTION PROBLEM!!" << mysql_errno(conn) << endl;
		}

		cout << endl << "\n\n		1.	ENTER CUSTOMER ID TO GET CUSTOMER ANALYSIS (ENTER Q TO EXIT): ";
		cin >> getcustID;
		if (getcustID == "Q" || getcustID == "q")
		{
			exit(0);
		}
		else
		{
			for (int i = 0; i < storeIndex; i++)
			{
				if (getcustID == storecustID[i])
				{
					customerID[purchaseIndex] = getcustID;
					purchaseIndex++;
					itemFalse = false;
					goto VIEWANALYSIS;
				}
				else
				{
					itemFalse = true;
				}
			}
			if (itemFalse == true)
			{
				cout << endl << "		CUSTOMER ID IS NOT AVAILABLE IN DATABASE!! PLEASE ENTER CUSTOMER ID THAT IS IN VIEW TABLE." << endl;
				purchaseIndex--;
				itemFalse = false;
				goto ExitMenu;
			}
		}
	}


VIEWANALYSIS:
	cout << endl << "\n			YOU CHOOSE THIS CUSTOMER'S ID: ";
	for (int i = 0; i < purchaseIndex; i++)
	{
		cout << customerID[i] << " ";
	}


	cout << endl << "\n			DO YOU WANT TO VIEW ANALYSIS FOR THIS CUSTOMER? (ENTER V TO VIEW): ";
	cin >> viewAnalysis;

	if (viewAnalysis == 'V' || viewAnalysis == 'v')
	{
		for (int i = 0; i < purchaseIndex; i++)
		{
			for (int j = 0; j < storeIndex; j++)
			{
				if (customerID[i] == storecustID[j])
				{
					qstate = mysql_query(conn, "SELECT sales, totalprice FROM purchase");
					if (!qstate)
					{
						res = mysql_store_result(conn);
						while ((row = mysql_fetch_row(res)))
						{
							if (atoi(row[0]) > 0)
							{
								storesales[storeIndexN] = row[0];
								storeprice[storeIndexN] = row[1];
								storeIndexN++;
							}
						}
						storeIndexN = 0;
					}
					else
					{
						cout << "		QUERY EXECUTION PROBLEM!" << mysql_errno(conn) << endl;
					}
					
					totalbkBuy += strtof((storesales[j]).c_str(), 0);
					totalbkPrice += strtof((storeprice[j]).c_str(), 0);
					
					analysis = true;

				}
			}
		}

		if (analysis == true)
		{
			
			cout << endl;
			cout << endl << "			TOTAL BOOKS BOUGHT BY THIS CUSTOMER	: " << totalbkBuy << endl;
			cout << endl << "			TOTAL PRICE OF THE BOOKS BOUGHT		: " << totalbkPrice << endl;
		}
	}

	// Exit Code
ExitMenu:
	cout << endl << "\n			PRESS 'G' to GENERATE REPORT, 'A' TO VIEW BOOK ANALYSIS AGAIN ANY KEY TO EXIT. ";
	cin >> choose;

	if (choose == 'g' || choose == 'G')
	{
		GenerateReport();
	}
	else if (choose == 'a' || choose == 'A')
	{
		CustomerAnalysis();
	}
	else
	{
		exit(0);
	}
}

void CustomerMenu() {
	
	// Initial load
	system("cls");

	// Variables
	int choose=0;
	char exitSecurity;
	// Variables End

	cout << endl;
	
	cout << endl << endl;
	cout << "	---------------------------------------------------------------------------------------------------\n";
	cout << "						CUSTOMER MENU 		  " << endl;
	cout << "	---------------------------------------------------------------------------------------------------\n" << endl << endl;
	cout << "\n					1. PURCHASE BOOK";
	cout << "\n					2. VIEW BOOK";
	cout << "\n					3. EXIT" << endl << endl;
	
	cout << "\n			CHOOSE ONE: ";
	cin >> choose;
	
	switch (choose)
	{
	case 1:
		PurchaseBook();
		break;
	case 2:
		ViewBook();
		break;
	case 3:
	ExitProgram:
		cout << "\n\n	PROGRAM IS TERMINATING. ARE YOU SURE? (Y/N): ";
		cin >> exitSecurity;
		if (exitSecurity == 'y' || exitSecurity == 'Y') {
			exit(0);
		}
		else if (exitSecurity == 'n' || exitSecurity == 'N') {
			system("cls");
			main();
		}
		else {
			cout << "		NEXT TIME CHOOSE AFTER CORRESPONDING LINES." << endl;
			goto ExitProgram;
		}
		break;
	default:
		cout << "\n		PLEASE CHOOSE BETWEEN 1-4. PRESS ENTER TO CONTINUE...";
		system("PAUSE");
		system("cls");
		main();
		break;

	}

}

void PurchaseBook() {

	system("cls");

	// Variables
	char choose;
	string getISBN;
	string bookISBN[50], subject[30], price[30], title[30], author[30], quantity[30];
	int customerID;
	string custname, custphone, custaddress, sales;
	string customers[30];
	char chooseToBuy;
	int bookIndex = 0;
	int indexForId = 0;
	float quan1 = 0.0;
	float totalPrice = 0.0;
	bool purchase = false;
	bool itemFalse = false;
	bool HaveException = false;
	bool NotInDatabase = false;

	string storeISBN[30], storesubject[30], storeprice[30], storetitle[30], storeauthor[30], storequantity[30];
	string storeId, storename,storephone;
	int storeIndex = 0;
	int storeIndexN = 0;
	// Variables End

	cout << "\n\n					****** PURCHASE BOOK ******				\n\n" << endl;

	qstate = mysql_query(conn, "SELECT * FROM customer");

	if (!qstate)
	{
		res = mysql_store_result(conn);
		//printf("	-----------------------------------------------------------------------------------------------------------\n");
		//printf("	| %-5s | %-25s | %-10s | %-20s | %-15s | %-10s |\n", "BOOK ISBN", "SUBJECT", "PRICE", "TITLE", "AUTHOR", "QUANTITY");
		//printf("	-----------------------------------------------------------------------------------------------------------\n");
		while ((row = mysql_fetch_row(res))) {
			//printf("	| %-5s | %-25s | %-10s | %-20s | %-15s | %-10s |\n", row[0], row[1], row[2], row[3], row[4], row[5]);
			customers[indexForId] = row[0];
			indexForId++;
		}
	}
	else
	{
		cout << "		QUERY EXECUTION PROBLEM!!" << mysql_errno(conn) << endl;
	}

	try
	{
		cout << endl;
		cout << "		1.	ENTER CUSTOMER ID	: ";
		cin >> customerID;
		cout << endl;
	}
	catch (exception e)
	{
		cout << "\n		PLEASE ENTER A VALID NUMBER." << endl;
		HaveException = true;
	}

	if (HaveException == false)
	{
		stringstream streamId;
		string strId;
		streamId << customerID;
		streamId >> strId;

		for (int i = 0; i < indexForId; i++)
		{
			if (strId != customers[i])
			{
				NotInDatabase = true;

			}
			else
			{
				NotInDatabase = false;
				break;
				goto ExitMenu;
			}
		}

		if (NotInDatabase == false)
		{
			string findbyISBN_query = "SELECT * FROM customer WHERE customerId = '" + strId + "%'";
			const char* qi = findbyISBN_query.c_str();
			qstate = mysql_query(conn, qi);

			if (!qstate)
			{

				res = mysql_store_result(conn);
				while (row = mysql_fetch_row(res))
				{
					cout << "		CUSTOMER NAME		: " << row[1]
						<<  "		CUSTOMER PHONE		: " << row[2]
						<< endl << endl;

					storename = row[1];
					storephone = row[2];

				}
			}
			else
			{
				cout << "\n		QUERY EXECUTION PROBLEM!!" << mysql_errno(conn) << endl;
			}

			/*cout << "		1.	ENTER CUSTOMER ID	: ";
			cin >> customerID;

			string findbyISBN_query = "SELECT * FROM customer WHERE customerID LIKE '" + customerID + "%'";
			const char* qi = findbyISBN_query.c_str();
			qstate = mysql_query(conn, qi);

			if (!qstate)
			{

				res = mysql_store_result(conn);
				//cout << endl;
				//printf("				-------------------------------------\n");
				//printf("				| %-15s | %-15s | \n", "CUSTOMER ID", "CUSTOMER NAME");
				//printf("				--------------------------------------\n");
				//while (row = mysql_fetch_row(res))
				{
					//printf("				| %-15s | %-15s | \n", row[0], row[1]);
				}
			}
			else
			{
				cout << "		QUERY EXECUTION PROBLEM!!" << mysql_errno(conn) << endl;
			}*/

			qstate = mysql_query(conn, "SELECT * FROM books");

			if (!qstate)
			{
				res = mysql_store_result(conn);
				cout << endl;
				printf("	-----------------------------------------------------------------------------------------------------------\n");
				printf("	| %-5s | %-25s | %-10s | %-20s | %-15s | %-10s |\n", "BOOK ISBN", "SUBJECT", "PRICE", "TITLE", "AUTHOR", "QUANTITY");
				printf("	-----------------------------------------------------------------------------------------------------------\n");
				while ((row = mysql_fetch_row(res)))
				{
					if (atoi(row[5]) > 0)
					{
						cout << endl;
						printf("	| %-5s | %-25s | %-10s | %-20s | %-15s | %-10s |\n", row[0], row[1], row[2], row[3], row[4], row[5]);
						storeISBN[storeIndex] = row[0];
						storesubject[storeIndex] = row[1];
						storeprice[storeIndex] = row[2];
						storetitle[storeIndex] = row[3];
						storeauthor[storeIndex] = row[4];
						storequantity[storeIndex] = row[5];
						storeIndex++;
					}
				}
			}
			else
			{
				cout << "		QUERY EXECUTION PROBLEM!!" << mysql_errno(conn) << endl;
			}


			for (bookIndex = 0;; bookIndex++)
			{
				cout << endl << "\n\n	2.	ENTER BOOK ISBN TO PURCHASE (ENTER Q TO EXIT): ";
				cin >> getISBN;
				if (getISBN == "Q" || getISBN == "q")
				{
					exit(0);
				}
				else
				{
					for (int i = 0; i < storeIndex; i++)
					{
						if (getISBN == storeISBN[i])
						{
							bookISBN[bookIndex] = getISBN;
							bookIndex++;
							itemFalse = false;
							goto CHOOSETOBUY;
						}
						else
						{
							itemFalse = true;
						}
					}
					if (itemFalse == true)
					{
						cout << endl << "		BOOK ISBN NOT AVAILABLE IN DATABASE!! PLEASE ENTER BOOK ISBN THAT IS IN VIEW TABLE." << endl;
						bookIndex--;
						itemFalse = false;
						goto ExitMenu;
					}
				}
			}

		CHOOSETOBUY:
			cout << endl << "\n		YOU CHOOSE THIS BOOK'S ISBN: ";
			for (int i = 0; i < bookIndex; i++)
			{
				cout << bookISBN[i] << " ";
			}

			cout << endl << "\n		DO YOU WANT TO BUY THIS BOOK (ENTER B TO BUY): ";
			cin >> chooseToBuy;

			if (chooseToBuy == 'B' || chooseToBuy == 'b')
			{
				for (int i = 0; i < bookIndex; i++)
				{
					for (int j = 0; j < storeIndex; j++)
					{
						if (bookISBN[i] == storeISBN[j])
						{
							qstate = mysql_query(conn, "SELECT quantity FROM books");
							if (!qstate)
							{
								res = mysql_store_result(conn);
								while ((row = mysql_fetch_row(res)))
								{
									if (atoi(row[0]) > 0)
									{
										storequantity[storeIndexN] = row[0];
										storeIndexN++;
									}
								}
								storeIndexN = 0;
							}
							else
							{
								cout << "	QUERY EXECUTION PROBLEM!" << mysql_errno(conn) << endl;
							}


							cout << endl << "\n\n	3.	ENTER QUANTITY TO PURCHASE BOOK	: ";
							cin >> quan1;

							float quan2 = strtof((storequantity[j]).c_str(), 0);

							if (quan2 >= quan1)
							{
								float quan = quan2 - quan1;
								string getQuan;
								stringstream strquan;
								strquan << quan;
								strquan >> getQuan;

								totalPrice = quan1 * strtof((storeprice[j]).c_str(), 0);

								purchase = true;

								string update_query = "UPDATE books SET quantity = '" + getQuan + "' WHERE bookISBN = '" + storeISBN[j] + "'";
								const char* qu = update_query.c_str();
								//cout << update_query << endl;

								qstate = mysql_query(conn, qu);

								if (qstate)
								{
									cout << "		FAILED TO UPDATE!" << mysql_errno(conn) << endl;
								}
							}
							else
							{
								cout << endl << "		ENTER A VALID NUMBER." << endl;
								goto ExitMenu;
							}
						}
					}
				}

				if (purchase == true)
				{
					string getQuan1;
					stringstream strquan1;
					strquan1 << quan1;
					strquan1 >> getQuan1;

					string getPrice;
					stringstream strprice;
					strprice << totalPrice;
					strprice >> getPrice;

					string insert_query = "INSERT INTO purchase (purchaseID, sales, totalPrice, bookISBN, customerID) VALUES ('" "',  '" + getQuan1 + "', '" + getPrice + "', '" + getISBN + "', '" + strId + "')";

					const char* q = insert_query.c_str();

					qstate = mysql_query(conn, q);

					if (!qstate)
					{
						cout << endl << "		BOOK SUCESSFULLY PURCHASED." << endl;
						cout << endl << "		TOTAL PRICE: RM " << getPrice << endl;
						goto ExitMenu;
					}
					else
					{
						cout << "		QUERY EXECUTION PROBLEM!" << mysql_errno(conn) << endl;
					}

				}
			}
		}
		else
		{
		cout << "\n		CUSTOMER NOT FOUND IN DATABASE." << endl;
		}
	}
	


	// Exit Code
ExitMenu:
	cout << endl << "\n		PRESS 'M' to CUSTOMER MENU, 'A' TO PURCHASE AGAIN ANY KEY TO EXIT. ";
	cin >> choose;

	if (choose == 'm' || choose == 'M')
	{
		CustomerMenu();
	}
	else if (choose == 'a' || choose == 'A')
	{
		PurchaseBook();
	}
	else
	{
		exit(0);
	}
}

void ViewBook()
{
	system("cls");

	// Variables
	char choose;
	// Variables end

	cout << "\n\n					****** VIEW BOOK DETAILS *****										" << endl << endl;

	qstate = mysql_query(conn, "SELECT * FROM books");

	if (!qstate)
	{
		res = mysql_store_result(conn);

		printf("	---------------------------------------------------------------------------------------------------------------\n");
		printf("	| %-5s | %-25s | %-10s | %-20s | %-15s |%-15s |\n", "BOOK ISBN", "SUBJECT", "PRICE", "TITLE", "AUTHOR", "QUANTITY");
		printf("	---------------------------------------------------------------------------------------------------------------\n");

		while ((row = mysql_fetch_row(res)))
		{
			printf("	| %-5s | %-25s | %-10s | %-20s | %-15s | %-15s|\n", row[0], row[1], row[2], row[3], row[4], row[5]);
		}
		printf("	---------------------------------------------------------------------------------------------------------------\n");
	}
	else
	{
		cout << "		QUERY EXECUTION PROBLEM!" << mysql_errno(conn) << endl;
		goto ExitMenu;
	}

	// Exit Code
ExitMenu:
	cout << endl << "\n		PRESS 'M' to CUSTOMER MENU ANY KEY TO EXIT. ";
	cin >> choose;

	if (choose == 'm' || choose == 'M')
	{
		CustomerMenu();
	}
	else
	{
		exit(0);
	}

}