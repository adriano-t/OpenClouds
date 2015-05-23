//#include "mysql_connection.h"

#include "MySQL\include\mysql_connection.h"
#include "MySQL\include\cppconn\driver.h"
#include "MySQL\include\cppconn\exception.h"
#include "MySQL\include\cppconn\resultset.h"
#include "MySQL\include\cppconn\statement.h"

using namespace std;

int main(void)
{
	cout << endl;
	cout << "Running 'SELECT 'Hello World!'  >> AS _message'..." << endl;

		try {
		sql::Driver *driver;
		sql::Connection *con;
		sql::Statement *stmt;
		sql::ResultSet *res;

		/* Create a connection */
		driver = get_driver_instance();
		con = driver->connect("tcp://127.0.0.1:3306", "root", "root");
		/* Connect to the MySQL test database */
		con->setSchema("test");

		stmt = con->createStatement();
		res = stmt->executeQuery("SELECT * FROM test.csfa");

		while (res->next()) {
			cout << "\t... MySQL replies: ";
			/* Access column data by alias or column name */
			cout << res->getString("CSFAcol") << endl;
			cout << "\t... MySQL says it again: ";
			cout << res->getString(2+1) << endl << flush;
			/* Access column fata by numeric offset, 1 is the first column */
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

	return EXIT_SUCCESS;
}