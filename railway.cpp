#include <iostream>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/exception.h>

using namespace std;
using namespace sql;

class Passenger {
private:
    int id;
    string name;
    int price = 5000;
    int seats = 20;
    sql::Connection* conn;

public:
    // Constructor to initialize database connection
    Passenger() {
        mysql::MySQL_Driver* driver;
        driver = mysql::get_mysql_driver_instance();
        conn = driver->connect("tcp://127.0.0.1:3306", "root", "password"); // Use your MySQL credentials
        conn->setSchema("flightDB"); // Assuming your database is named "flightDB"
    }

    // Destructor to close the connection
    ~Passenger() {
        delete conn;
    }

    // Function to create passengers table
    void initDB() {
        Statement* stmt = conn->createStatement();
        stmt->execute("CREATE TABLE IF NOT EXISTS Passengers ("
                      "ID INT PRIMARY KEY, "
                      "Name VARCHAR(255) NOT NULL);");
        delete stmt;
    }

    // Function to set passenger data and insert into DB
    void setData() {
        cout << "Enter your Name: ";
        cin >> name;
        cout << "Enter Your Flight ID: ";
        cin >> id;

        PreparedStatement* pstmt = conn->prepareStatement("INSERT INTO Passengers (ID, Name) VALUES (?, ?)");
        pstmt->setInt(1, id);
        pstmt->setString(2, name);
        pstmt->execute();
        delete pstmt;
    }

    // Function to show passenger data from the DB
    void printAllPassengers() {
        Statement* stmt = conn->createStatement();
        ResultSet* res = stmt->executeQuery("SELECT * FROM Passengers");

        while (res->next()) {
            cout << "Name: " << res->getString("Name") << " -- ID: " << res->getInt("ID") << endl;
        }

        delete res;
        delete stmt;
    }

    // Function to cancel a booking (delete entry)
    void cancelBooking(string passengerName) {
        PreparedStatement* pstmt = conn->prepareStatement("DELETE FROM Passengers WHERE Name = ?");
        pstmt->setString(1, passengerName);
        pstmt->execute();
        delete pstmt;
    }

    // Function to calculate and display price
    int showPrice(int count) {
        if (count > 0) {
            return price + (count * 200);
        } else {
            return price;
        }
    }

    // Function to show available seats
    int balanceSeat(int count) {
        return seats - count;
    }
};

int main() {
    Passenger passenger;
    passenger.initDB(); // Initialize the database and create the table

    int count = 0, n, opt;
    string passengerName;

    while (opt != 4) {
        cout << "1. BOOK 2. Cancel 3. Print 4. Exit" << endl;
        cout << "Enter Your Choice: ";
        cin >> opt;

        switch (opt) {
            case 1:
                cout << "Price is: " << passenger.showPrice(count) << endl;
                cout << "Remaining Seats: " << passenger.balanceSeat(count) << endl;
                cout << "How many seats do you want to book?" << endl;
                cin >> n;
                for (int i = 0; i < n; ++i) {
                    passenger.setData();
                    count++;
                    cout << "Price is: " << passenger.showPrice(count) << endl;
                    cout << "Remaining Seats: " << passenger.balanceSeat(count) << endl;
                }
                break;

            case 2:
                cout << "Enter your Name to Cancel: ";
                cin >> passengerName;
                passenger.cancelBooking(passengerName);
                count--;
                cout << "Price after cancellation: " << passenger.showPrice(count) << endl;
                cout << "Remaining Seats after cancellation: " << passenger.balanceSeat(count) << endl;
                break;

            case 3:
                passenger.printAllPassengers();
                break;

            case 4:
                cout << "Exiting..." << endl;
                break;

            default:
                cout << "Invalid choice!" << endl;
                break;
        }
    }

    return 0;
}
