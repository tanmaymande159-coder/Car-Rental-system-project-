#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

class Car {
private:
    int carId;
    string brand;
    string model;
    string color;
    double rentPerDay;
    bool available;

public:
    Car() {
        carId = 0;
        brand = "";
        model = "";
        color = "";
        rentPerDay = 0.0;
        available = true;
    }

    Car(int id, string b, string m, string c, double rent, bool avail = true) {
        carId = id;
        brand = b;
        model = m;
        color = c;
        rentPerDay = rent;
        available = avail;
    }

    int getCarId() const { return carId; }
    string getBrand() const { return brand; }
    string getModel() const { return model; }
    string getColor() const { return color; }
    double getRentPerDay() const { return rentPerDay; }
    bool isAvailable() const { return available; }

    void setAvailable(bool value) {
        available = value;
    }

    void display() const {
        cout << left << setw(8) << carId
             << setw(15) << brand
             << setw(15) << model
             << setw(12) << color
             << setw(12) << fixed << setprecision(2) << rentPerDay
             << setw(12) << (available ? "Yes" : "No") << endl;
    }

    void save(ofstream &out) const {
        out << carId << endl;
        out << brand << endl;
        out << model << endl;
        out << color << endl;
        out << rentPerDay << endl;
        out << available << endl;
    }

    void load(ifstream &in) {
        in >> carId;
        in.ignore();

        getline(in, brand);
        getline(in, model);
        getline(in, color);

        in >> rentPerDay;
        in >> available;
        in.ignore();
    }
};

class Customer {
private:
    int customerId;
    string name;
    string phone;

public:
    Customer() {
        customerId = 0;
        name = "";
        phone = "";
    }

    Customer(int id, string n, string p) {
        customerId = id;
        name = n;
        phone = p;
    }

    int getCustomerId() const { return customerId; }
    string getName() const { return name; }
    string getPhone() const { return phone; }

    void display() const {
        cout << "Customer ID: " << customerId << endl;
        cout << "Name       : " << name << endl;
        cout << "Phone      : " << phone << endl;
    }

    void save(ofstream &out) const {
        out << customerId << endl;
        out << name << endl;
        out << phone << endl;
    }

    void load(ifstream &in) {
        in >> customerId;
        in.ignore();

        getline(in, name);
        getline(in, phone);
    }
};

class Rental {
private:
    int rentalId;
    int carId;
    int customerId;
    int days;
    double totalCost;
    bool active;

public:
    Rental() {
        rentalId = 0;
        carId = 0;
        customerId = 0;
        days = 0;
        totalCost = 0.0;
        active = false;
    }

    Rental(int rid, int cid, int custid, int d, double cost, bool act = true) {
        rentalId = rid;
        carId = cid;
        customerId = custid;
        days = d;
        totalCost = cost;
        active = act;
    }

    int getRentalId() const { return rentalId; }
    int getCarId() const { return carId; }
    int getCustomerId() const { return customerId; }
    int getDays() const { return days; }
    double getTotalCost() const { return totalCost; }
    bool isActive() const { return active; }

    void setActive(bool value) {
        active = value;
    }

    void display() const {
        cout << left << setw(10) << rentalId
             << setw(10) << carId
             << setw(12) << customerId
             << setw(8) << days
             << setw(12) << fixed << setprecision(2) << totalCost
             << setw(10) << (active ? "Yes" : "No") << endl;
    }

    void save(ofstream &out) const {
        out << rentalId << endl;
        out << carId << endl;
        out << customerId << endl;
        out << days << endl;
        out << totalCost << endl;
        out << active << endl;
    }

    void load(ifstream &in) {
        in >> rentalId >> carId >> customerId >> days >> totalCost >> active;
        in.ignore();
    }
};

class CarRentalSystem {
private:
    vector<Car> cars;
    vector<Customer> customers;
    vector<Rental> rentals;

    int nextCarId;
    int nextCustomerId;
    int nextRentalId;

public:
    CarRentalSystem() {
        nextCarId = 1;
        nextCustomerId = 1;
        nextRentalId = 1;
    }

    void addCar() {
        string brand, model, color;
        double rent;

        cout << "Enter brand: ";
        getline(cin, brand);

        cout << "Enter model: ";
        getline(cin, model);

        cout << "Enter color: ";
        getline(cin, color);

        cout << "Enter rent per day: ";
        cin >> rent;
        cin.ignore();

        cars.push_back(Car(nextCarId++, brand, model, color, rent));

        cout << "Car added successfully." << endl;
    }

    void displayCars() const {
        if (cars.empty()) {
            cout << "No cars available." << endl;
            return;
        }

        cout << left << setw(8) << "ID"
             << setw(15) << "Brand"
             << setw(15) << "Model"
             << setw(12) << "Color"
             << setw(12) << "Rent/Day"
             << setw(12) << "Available" << endl;

        for (const auto &car : cars) {
            car.display();
        }
    }

    void addCustomer() {
        string name, phone;

        cout << "Enter customer name: ";
        getline(cin, name);

        cout << "Enter phone number: ";
        getline(cin, phone);

        customers.push_back(Customer(nextCustomerId++, name, phone));

        cout << "Customer registered successfully." << endl;
    }

    void displayCustomers() const {
        if (customers.empty()) {
            cout << "No customers found." << endl;
            return;
        }

        for (const auto &c : customers) {
            c.display();
            cout << "----------------------" << endl;
        }
    }

    Car* findCarById(int id) {
        for (auto &car : cars) {
            if (car.getCarId() == id)
                return &car;
        }
        return nullptr;
    }

    Customer* findCustomerById(int id) {
        for (auto &customer : customers) {
            if (customer.getCustomerId() == id)
                return &customer;
        }
        return nullptr;
    }

    Rental* findRentalById(int id) {
        for (auto &rental : rentals) {
            if (rental.getRentalId() == id)
                return &rental;
        }
        return nullptr;
    }

    void rentCar() {
        int customerId, carId, days;

        cout << "Enter customer ID: ";
        cin >> customerId;

        cout << "Enter car ID: ";
        cin >> carId;

        cout << "Enter number of days: ";
        cin >> days;

        cin.ignore();

        Customer* customer = findCustomerById(customerId);
        Car* car = findCarById(carId);

        if (!customer) {
            cout << "Customer not found." << endl;
            return;
        }

        if (!car) {
            cout << "Car not found." << endl;
            return;
        }

        if (!car->isAvailable()) {
            cout << "Car is currently not available." << endl;
            return;
        }

        double total = days * car->getRentPerDay();

        rentals.push_back(
            Rental(nextRentalId++, carId, customerId, days, total, true)
        );

        car->setAvailable(false);

        cout << "Car rented successfully." << endl;
        cout << "Total cost: " << fixed << setprecision(2) << total << endl;
    }

    void returnCar() {
        int rentalId;

        cout << "Enter rental ID: ";
        cin >> rentalId;
        cin.ignore();

        Rental* rental = findRentalById(rentalId);

        if (!rental) {
            cout << "Rental record not found." << endl;
            return;
        }

        if (!rental->isActive()) {
            cout << "This car is already returned." << endl;
            return;
        }

        Car* car = findCarById(rental->getCarId());

        if (car) {
            car->setAvailable(true);
        }

        rental->setActive(false);

        cout << "Car returned successfully." << endl;
    }

    void showActiveRentals() const {
        bool found = false;

        cout << left << setw(10) << "RentID"
             << setw(10) << "CarID"
             << setw(12) << "CustID"
             << setw(8) << "Days"
             << setw(12) << "Total"
             << setw(10) << "Active" << endl;

        for (const auto &r : rentals) {
            if (r.isActive()) {
                r.display();
                found = true;
            }
        }

        if (!found) {
            cout << "No active rentals." << endl;
        }
    }

    void showAllRentals() const {
        if (rentals.empty()) {
            cout << "No rental records." << endl;
            return;
        }

        cout << left << setw(10) << "RentID"
             << setw(10) << "CarID"
             << setw(12) << "CustID"
             << setw(8) << "Days"
             << setw(12) << "Total"
             << setw(10) << "Active" << endl;

        for (const auto &r : rentals) {
            r.display();
        }
    }

    void saveData() {
        ofstream carFile("cars.txt");
        ofstream customerFile("customers.txt");
        ofstream rentalFile("rentals.txt");

        if (!carFile || !customerFile || !rentalFile) {
            cout << "Error opening files for saving." << endl;
            return;
        }

        carFile << nextCarId << endl;
        carFile << cars.size() << endl;

        for (const auto &car : cars) {
            car.save(carFile);
        }

        customerFile << nextCustomerId << endl;
        customerFile << customers.size() << endl;

        for (const auto &c : customers) {
            c.save(customerFile);
        }

        rentalFile << nextRentalId << endl;
        rentalFile << rentals.size() << endl;

        for (const auto &r : rentals) {
            r.save(rentalFile);
        }

        cout << "Data saved successfully." << endl;
    }

    void loadData() {
        ifstream carFile("cars.txt");
        ifstream customerFile("customers.txt");
        ifstream rentalFile("rentals.txt");

        if (!carFile || !customerFile || !rentalFile) {
            return;
        }

        size_t n;

        carFile >> nextCarId;
        carFile >> n;
        carFile.ignore();

        cars.clear();

        for (size_t i = 0; i < n; i++) {
            Car car;
            car.load(carFile);
            cars.push_back(car);
        }

        customerFile >> nextCustomerId;
        customerFile >> n;
        customerFile.ignore();

        customers.clear();

        for (size_t i = 0; i < n; i++) {
            Customer c;
            c.load(customerFile);
            customers.push_back(c);
        }

        rentalFile >> nextRentalId;
        rentalFile >> n;
        rentalFile.ignore();

        rentals.clear();

        for (size_t i = 0; i < n; i++) {
            Rental r;
            r.load(rentalFile);
            rentals.push_back(r);
        }
    }

    void menu() {
        int choice;

        do {
            cout << "\n========== CAR RENTAL SYSTEM ==========\n";

            cout << "1. Add Car\n";
            cout << "2. View Cars\n";
            cout << "3. Add Customer\n";
            cout << "4. View Customers\n";
            cout << "5. Rent Car\n";
            cout << "6. Return Car\n";
            cout << "7. View Active Rentals\n";
            cout << "8. View All Rentals\n";
            cout << "9. Save Data\n";
            cout << "10. Exit\n";

            cout << "Enter choice: ";
            cin >> choice;
            cin.ignore();

            switch (choice) {
                case 1:
                    addCar();
                    break;

                case 2:
                    displayCars();
                    break;

                case 3:
                    addCustomer();
                    break;

                case 4:
                    displayCustomers();
                    break;

                case 5:
                    rentCar();
                    break;

                case 6:
                    returnCar();
                    break;

                case 7:
                    showActiveRentals();
                    break;

                case 8:
                    showAllRentals();
                    break;

                case 9:
                    saveData();
                    break;

                case 10:
                    saveData();
                    cout << "Exiting..." << endl;
                    break;

                default:
                    cout << "Invalid choice." << endl;
            }

        } while (choice != 10);
    }
};

int main() {
    CarRentalSystem system;

    system.loadData();
    system.menu();

    return 0;
}