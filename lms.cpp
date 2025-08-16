// Laundry Management System (Final Clean Version)
#include <iostream>
#include <string>
using namespace std;

// 1. User Module
class User {
protected:
    string username;
    string password;

public:
    void login() {
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;
    }

    string getUsername() {
        return username;
    }
};

// 2. Customer Module
class Customer : public User {
private:
    string name;
    string phone;

public:
    void inputCustomer() {
        cout << "Enter name: ";
        cin >> name;
        cout << "Enter phone: ";
        cin >> phone;
    }

    void displayCustomer() {
        cout << "Name: " << name << "\nPhone: " << phone << "\nUsername: " << username << endl;
    }
};

// 3. Laundry Module
class Laundry {
protected:
    int shirts, pants;

public:
    Laundry() {
        shirts = 0;
        pants = 0;
    }

    void inputItems() {
        cout << "Shirts: ";
        cin >> shirts;
        cout << "Pants: ";
        cin >> pants;
    }

    void displayItems() {
        cout << "Shirts: " << shirts << " x 50 = " << shirts * 50 << endl;
        cout << "Pants: " << pants << " x 60 = " << pants * 60 << endl;
    }

    int getTotal() {
        return shirts * 50 + pants * 60;
    }
};

// 4. Status Module
class Status {
public:
    string getStatusName(int code) {
        if (code == 0) return "Pending";
        else if (code == 1) return "In Progress";
        else if (code == 2) return "Completed";
        else if (code == 3) return "Delivered";
        else return "Unknown";
    }
};

// 5. Billing Module
class Billing {
public:
    void printBill(int total) {
        float discount = (total > 500) ? 0.1f * total : 0;
        cout << "\n--- BILL ---" << endl;
        cout << "Subtotal: Rs. " << total << endl;
        cout << "Discount: Rs. " << discount << endl;
        cout << "Total: Rs. " << total - discount << endl;
    }
};

// 6. Admin Module
class Admin : public User {
public:
    void viewAllOrders(string logs[], int count) {
        cout << "\nAll Orders Summary:\n";
        if (count == 0) {
            cout << "No orders yet.\n";
            return;
        }
        for (int i = 0; i < count; i++)
            cout << logs[i] << endl;
    }
};

// 7. Report Module
class Report {
public:
    void showSummary(int orderCount, int revenue) {
        cout << "\n--- Report ---\n";
        cout << "Total Orders: " << orderCount << endl;
        cout << "Total Revenue: Rs. " << revenue << endl;
    }
};

// 8. Menu Module
void showMenu() {
    cout << "\n=== Laundry Management Menu ===\n";
    cout << "1. Create Order\n";
    cout << "2. View Order\n";
    cout << "3. Admin View\n";
    cout << "4. Exit\n";
    cout << "Choose: ";
}

// 9. Order Processing Module
class OrderProcess {
private:
    Customer customer;
    Laundry laundry;
    Status statusObj;
    Billing bill;
    int statusCode;
    int total;

public:
    string orderSummary;

    OrderProcess() {
        statusCode = 0;
        total = 0;
        orderSummary = "";
    }

    void createOrder() {
        customer.login();
        customer.inputCustomer();
        laundry.inputItems();
        statusCode = 0; // Pending
        total = laundry.getTotal();

        orderSummary = "Customer: " + customer.getUsername() +
                       ", Total: Rs. " + to_string(total) +
                       ", Status: " + statusObj.getStatusName(statusCode);

        cout << "\nOrder created successfully!\n";
    }

    void viewOrder() {
        if (total == 0) {
            cout << "No order created yet!\n";
            return;
        }
        customer.displayCustomer();
        laundry.displayItems();
        cout << "Status: " << statusObj.getStatusName(statusCode) << endl;
        bill.printBill(total);
    }

    int getTotal() { return total; }
    string getSummary() { return orderSummary; }
};

// 10. Main Function
int main() {
    string logs[100];
    int logCount = 0;
    int totalRevenue = 0;
    int orderCount = 0;

    OrderProcess order;
    Admin admin;
    Report report;
    int choice;

    cout << "Welcome to Laundry Management System!\n";

    do {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                order.createOrder();
                logs[logCount++] = order.getSummary();
                totalRevenue += order.getTotal();
                orderCount++;
                break;
            case 2:
                order.viewOrder();
                break;
            case 3:
                admin.viewAllOrders(logs, logCount);
                report.showSummary(orderCount, totalRevenue);
                break;
            case 4:
                cout << "Thank you! Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 4);

    return 0;
}
