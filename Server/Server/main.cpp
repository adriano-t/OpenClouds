//#include "mysql_connection.h"

#include "MySQL\include\mysql_connection.h"
#include "MySQL\include\cppconn\driver.h"
#include "MySQL\include\cppconn\exception.h"
#include "MySQL\include\cppconn\resultset.h"
#include "MySQL\include\cppconn\statement.h"

#include "Packet.h"
using namespace std;

int main(void)
{

	OpenClouds::PacketTime date1{ 2015, 12, 30, 18, 6, 7 };
	OpenClouds::PacketTime date2{ 2015, 12, 30, 18, 6, 8 };
	cout << (date1 < date2 ? "lt" : "not lt") << endl;
	cout << (date1 > date2 ? "gt" : "not gt") << endl;
	cout << (date1 < date2 ? "e" : "not e") << endl;

	cout << endl;
	cout << "SELECT * FROM openclouds.users" << endl;

	



		try {
		sql::Driver *driver;
		sql::Connection *con;
		sql::Statement *stmt;
		sql::ResultSet *res;

		/* Create a connection */
		driver = get_driver_instance();
		

		sql::SQLString hosting = "tcp://db4free.net:3306";
		sql::SQLString user = "openclouds";
		std::cout << "Insert the password for " << hosting.c_str() << ": ";
		
		std::string inputPassword;
		std::cin >> inputPassword;
		sql::SQLString password = inputPassword.c_str();

		con = driver->connect(hosting, user, password);
		/* Connect to the MySQL test database */
		con->setSchema("openclouds");

		stmt = con->createStatement();
		res = stmt->executeQuery("SELECT * FROM openclouds.users");
		 
		while (res->next()) {
			cout << "\t... MySQL replies: ";
			/* Access column data by alias or column name */
			cout << res->getString("name").c_str() << endl; 
			/* Access column fata by numeric offset, 1 is the first column */
			cout << res->getString(3).c_str() << endl << flush;
		}
		delete res;
		delete stmt;
		delete con;

	}
	catch (sql::SQLException &e) {
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
		cout << "# ERR: " << e.what();
		cout << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
	}


	
	cout << endl;
	 
#ifdef _WIN32
	system("pause");
#else
	getchar();
#endif


	return EXIT_SUCCESS;
}