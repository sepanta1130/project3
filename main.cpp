#include <iostream>
#include <string>
using namespace std;

// class Person  base class
class Person {
public:
    string firstName;
    string lastName;
    string nationalID;
    int birthYear;
    string gender;

    // showInfo  namayeshe etelaat shakhs
    void showInfo() {
        cout << "Name: " << firstName << " " << lastName << endl;
        cout << "National ID: " << nationalID << endl;
        cout << "Birth Year: " << birthYear << endl;
        cout << "Gender: " << gender << endl;
    }
};



// class Product  baraye kala
class Product {
public:
    int productID;
    string name;
    double price;
    string brand;
    double weight;

    Product(int id, string n, double p, string b, double w) {
        productID = id;
        name = n;
        price = p;
        brand = b;
        weight = w;
    }

    int getProductID() {
        return productID;
    }

    void showInfo() {
        cout << "Product ID: " << productID << endl;
        cout << "Name: " << name << endl;
        cout << "Price: " << price << endl;
        cout << "Brand: " << brand << endl;
        cout << "Weight: " << weight << endl;
    }
};

// class Customer  ers bari az Person
class Customer : public Person {
public:
    string customerID;
    string province;
    string city;

    // showInfo etelaat mokamel
    void showInfo() {
        Person::showInfo();
        cout << "Customer ID: " << customerID << endl;
        cout << "Province: " << province << endl;
        cout << "City: " << city << endl;
    }
};
// class Dealer baraye namayandegi
class Dealer {
public:
    string dealerID;
    string name;
    int establishmentYear;
    string economicCode;
    string ownerFirstName;
    string ownerLastName;
    string province;
    string city;

    void showInfo() {
        cout << "Dealer ID: " << dealerID << endl;
        cout << "Name: " << name << endl;
        cout << "Establishment Year: " << establishmentYear << endl;
        cout << "Economic Code: " << economicCode << endl;
        cout << "Owner: " << ownerFirstName << " " << ownerLastName << endl;
        cout << "Province: " << province << endl;
        cout<< ", City: " << city << endl;
    }
};
// class Purchase  baraye kharid
class Purchase {
public:
    Customer* customer;
    Product* product;
    Dealer* dealer;
    int quantity;
    string purchaseDate;

    void showInfo() {
        cout << "Purchase Date: " << purchaseDate << endl;
        cout << "Quantity: " << quantity << endl;
        customer->showInfo();
        product->showInfo();
        dealer->showInfo();
    }
};
// max  object ha
const int MAX_SIZE = 100;

// array ha
Product* products[MAX_SIZE];
int productCount = 0;

Customer* customers[MAX_SIZE];
int customerCount = 0;

Dealer* dealers[MAX_SIZE];
int dealerCount = 0;

Purchase* purchases[MAX_SIZE];
int purchaseCount = 0;




void addProduct() {
    if (productCount >= MAX_SIZE) {
        cout << "Product list is full "<<endl;
        return;
    }

    string name, brand;
    int id;
    double price = 0, weight = 0;

    // gereftane ID va check kardane unique bodan
    cout << "Enter Product ID: ";
    cin >> id;
    for (int i = 0; i < productCount; i++) {
        if (products[i]->productID == id) {
            cout << " Product with this ID already exists "<<endl;
            return;
        }
    }

    cout << "Enter Name: ";
    cin >> name;

    // check kardane gheymat
    while (true) {
        cout << "Enter Price: ";
        cin >> price;

        if (cin.fail() || price <= 0) {
            cout << " Error: Price must be a positive number "<<endl;
            cin.clear();                // reset mikone error ro
            cin.ignore(1000, '\n');     // input ghalat ro mizane biroon
        } else {
            break;
        }
    }

    cout << "Enter Brand: ";
    cin >> brand;

    // check kardane weight
    while (true) {
        cout << "Enter Weight: ";
        cin >> weight;

        if (cin.fail() || weight <= 0) {
            cout << " Error: Weight must be a positive number "<<endl;
            cin.clear();
            cin.ignore(1000, '\n');
        } else {
            break;
        }
    }

    // sakhtane product ba constructor
    Product* p = new Product(id, name, price, brand, weight);
    products[productCount++] = p;

    cout << " Product added successfully  "<<endl;
}

void removeProduct() {
    int id;
    cout << "Enter Product ID to remove:"<<endl;
    cin >> id;

    int index = -1;

    // peyda kardan index kala
    for (int i = 0; i < productCount; i++) {
        if (products[i]->productID == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "Product not found" <<endl;
        return;
    }

    // delete memory
    delete products[index];

    // shift  ha be aghab
    for (int i = index; i < productCount - 1; i++) {
        products[i] = products[i + 1];
    }

    productCount--;

    // delete kharid haye marbut be in kala
    for (int i = 0; i < purchaseCount; ) {
        if (purchases[i]->product->productID == id) {
            delete purchases[i];
            for (int j = i; j < purchaseCount - 1; j++) {
                purchases[j] = purchases[j + 1];
            }
            purchaseCount--;
        } else {
            i++;
        }
    }

    cout << "Product removed successfully "<<endl;
}

void addCustomer() {
    if (customerCount >= MAX_SIZE) {
        cout << "Customer list is full "<<endl;
        return;
    }

    string firstName, lastName, nationalID, gender, province, city, customerID;
    int birthYear;

    cout << "Enter National ID: ";
    cin >> nationalID;

    // check unique bodan nationalID
    for (int i = 0; i < customerCount; i++) {
        if (customers[i]->nationalID == nationalID) {
            cout << "Customer with this National ID already exists "<<endl;
            return;
        }
    }

    cout << "Enter Customer ID: ";
    cin >> customerID;
    cout << "Enter First Name: ";
    cin >> firstName;
    cout << "Enter Last Name: ";
    cin >> lastName;
    cout << "Enter Birth Year: ";
    cin >> birthYear;
    cout << "Enter Gender: ";
    cin >> gender;
    cout << "Enter Province: ";
    cin >> province;
    cout << "Enter City: ";
    cin >> city;

    Customer* c = new Customer();
    c->customerID = customerID;
    c->firstName = firstName;
    c->lastName = lastName;
    c->nationalID = nationalID;
    c->birthYear = birthYear;
    c->gender = gender;
    c->province = province;
    c->city = city;

    customers[customerCount++] = c;

    cout << "Customer added successfully "<<endl;
}

void removeCustomer() {
    string nationalID;
    cout << "Enter National ID to remove: "<<endl;
    cin >> nationalID;

    int index = -1;

    for (int i = 0; i < customerCount; i++) {
        if (customers[i]->nationalID == nationalID) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "Customer not found  "<<endl;
        return;
    }

    delete customers[index];
    for (int i = index; i < customerCount - 1; i++) {
        customers[i] = customers[i + 1];
    }

    customerCount--;

    // delete kharid haye marbut be in customer
    for (int i = 0; i < purchaseCount;) {
        if (purchases[i]->customer->nationalID == nationalID) {
            delete purchases[i];
            for (int j = i; j < purchaseCount - 1; j++) {
                purchases[j] = purchases[j + 1];
            }
            purchaseCount--;
        } else {
            i++;
        }
    }

    cout << "Customer removed successfully "<<endl;
}
void addDealer() {
    if (dealerCount >= MAX_SIZE) {
        cout << "Dealer list is full "<<endl;
        return;
    }

    string dealerID, name, economicCode, ownerFirstName, ownerLastName, province, city;
    int establishmentYear;

    cout << "Enter Dealer ID: ";
    cin >> dealerID;

    for (int i = 0; i < dealerCount; i++) {
        if (dealers[i]->dealerID == dealerID) {
            cout << "Dealer with this ID already exists "<<endl;
            return;
        }
    }

    cout << "Enter Dealer Name: "<<endl;
    cin >> name;
    cout << "Enter Establishment Year: "<<endl;
    cin >> establishmentYear;
    cout << "Enter Economic Code: "<<endl;
    cin >> economicCode;
    cout << "Enter Owner First Name: "<<endl;
    cin >> ownerFirstName;
    cout << "Enter Owner Last Name: "<<endl;
    cin >> ownerLastName;
    cout << "Enter Province: "<<endl;
    cin >> province;
    cout << "Enter City: "<<endl;
    cin >> city;

    Dealer* d = new Dealer();
    d->dealerID = dealerID;
    d->name = name;
    d->establishmentYear = establishmentYear;
    d->economicCode = economicCode;
    d->ownerFirstName = ownerFirstName;
    d->ownerLastName = ownerLastName;
    d->province = province;
    d->city = city;

    dealers[dealerCount++] = d;

    cout << "Dealer added successfully "<<endl;
}

void removeDealer() {
    string dealerID;
    cout << "Enter Dealer ID to remove: "<<endl;
    cin >> dealerID;

    int index = -1;

    for (int i = 0; i < dealerCount; i++) {
        if (dealers[i]->dealerID == dealerID) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "Dealer not found "<<endl;
        return;
    }

    delete dealers[index];
    for (int i = index; i < dealerCount - 1; i++) {
        dealers[i] = dealers[i + 1];
    }

    dealerCount--;

    for (int i = 0; i < purchaseCount;) {
        if (purchases[i]->dealer->dealerID == dealerID) {
            delete purchases[i];
            for (int j = i; j < purchaseCount - 1; j++) {
                purchases[j] = purchases[j + 1];
            }
            purchaseCount--;
        } else {
            i++;
        }
    }

    cout << "Dealer removed successfully "<<endl;
}














void recordPurchase() {
    if (purchaseCount >= MAX_SIZE) {
        cout << "Purchase list is full"<<endl;
        return;
    }

    string nationalID, dealerID;
    int productID;
    int quantity;
    string purchaseDate;

    //  get nationalID
    cout << "Enter Customer National ID: ";
    cin >> nationalID;

    //  find customer
    Customer* c = nullptr;
    for (int i = 0; i < customerCount; i++) {
        if (customers[i]->nationalID == nationalID) {
            c = customers[i];
            break;
        }
    }

    if (c == nullptr) {
        cout << "Customer not found "<<endl;
        return;
    }

    //  get productID
    cout << "Enter Product ID: ";
    cin >> productID;

    // find product
    Product* p = nullptr;
    for (int i = 0; i < productCount; i++) {
        if (products[i]->productID == productID) {
            p = products[i];
            break;
        }
    }

    if (p == nullptr) {
        cout << "Product not found "<<endl;
        return;
    }

    // get dealerID
    cout << "Enter Dealer ID : ";
    cin >> dealerID;

    //  find dealer
    Dealer* d = nullptr;
    for (int i = 0; i < dealerCount; i++) {
        if (dealers[i]->dealerID == dealerID) {
            d = dealers[i];
            break;
        }
    }

    if (d == nullptr) {
        cout << "Dealer not found "<<endl;
        return;
    }

    // get quantity
    cout << "Enter Quantity: "<<endl;
    cin >> quantity;
    if (quantity <= 0) {
        cout << "Quantity must be positive "<<endl;
        return;
    }

    //  get purchase date
    cout << "Enter Purchase Date (YYYY/MM/DD): ";
    cin >> purchaseDate;

    //  create new purchase
    Purchase* purchase = new Purchase();
    purchase->customer = c;
    purchase->product = p;
    purchase->dealer = d;
    purchase->quantity = quantity;
    purchase->purchaseDate = purchaseDate;

    purchases[purchaseCount++] = purchase;

    cout << "Purchase recorded successfully.\n";
}

void totalPurchaseOfCustomer() {
    string nationalID;
    cout << "Enter Customer National ID: ";
    cin >> nationalID;

    // peyda kardan moshtari
    Customer* c = nullptr;
    for (int i = 0; i < customerCount; i++) {
        if (customers[i]->nationalID == nationalID) {
            c = customers[i];
            break;
        }
    }

    if (c == nullptr) {
        cout << "Customer not found.\n";
        return;
    }

    double total = 0;

    for (int i = 0; i < purchaseCount; i++) {
        if (purchases[i]->customer->nationalID == nationalID) {
            total += purchases[i]->product->price * purchases[i]->quantity;
        }
    }

    cout << "Total purchase amount for " << c->firstName << " " << c->lastName << " is: " << total << "\n";
}









void listCustomersOfProduct() {
    int productID;
    cout << "Enter Product ID: ";
    cin >> productID;

    Product* p = nullptr;
    for (int i = 0; i < productCount; i++) {
        if (products[i]->productID == productID) {
            p = products[i];
            break;
        }
    }

    if (p == nullptr) {
        cout << "Product not found.\n";
        return;
    }

    cout << "Customers who bought product " << p->name << ":\n";

    bool found = false;

    for (int i = 0; i < purchaseCount; i++) {
        if (purchases[i]->product->productID == productID) {
            Customer* c = purchases[i]->customer;
            cout << "- " << c->firstName << " " << c->lastName << ", National ID: " << c->nationalID << "\n";
            found = true;
        }
    }

    if (!found) {
        cout << "No customers found for this product "<<endl;
    }
}
void productsSoldByDealer() {
    string dealerID;
    cout << "Enter Dealer ID: ";
    cin >> dealerID;

    Dealer* d = nullptr;
    for (int i = 0; i < dealerCount; i++) {
        if (dealers[i]->dealerID == dealerID) {
            d = dealers[i];
            break;
        }
    }

    if (d == nullptr) {
        cout << "Dealer not found.\n";
        return;
    }

    cout << "Products sold by dealer " << d->name << ":\n";

    // list kardan productID ha ta az namayesh tekrari jalo giri beshe
    int displayedProductIDs[MAX_SIZE]; // -> int
    int displayedCount = 0;

    for (int i = 0; i < purchaseCount; i++) {
        if (purchases[i]->dealer->dealerID == dealerID) {
            int pid = purchases[i]->product->productID;

            bool alreadyDisplayed = false;
            for (int j = 0; j < displayedCount; j++) {
                if (displayedProductIDs[j] == pid) {
                    alreadyDisplayed = true;
                    break;
                }
            }

            if (!alreadyDisplayed) {
                displayedProductIDs[displayedCount++] = pid;
                Product* p = purchases[i]->product;
                cout << "- " << p->name << " (ID: " << p->productID << ", Price: " << p->price << ")"<<endl;
            }
        }
    }

    if (displayedCount == 0) {
        cout << "No products found for this dealer "<<endl;
    }
}

void numberOfSalesOfProduct() {
    int productID;
    cout << "Enter Product ID: ";
    cin >> productID;

    int totalQuantity = 0;

    for (int i = 0; i < purchaseCount; i++) {
        if (purchases[i]->product->productID == productID) {
            totalQuantity += purchases[i]->quantity;
        }
    }

    cout << "Total units sold for product " << productID << " is: " << totalQuantity << endl;
}
void productsPurchasedByCustomer() {
    string nationalID;
    cout << "Enter Customer National ID: "<<endl;
    cin >> nationalID;

    Customer* c = nullptr;
    for (int i = 0; i < customerCount; i++) {
        if (customers[i]->nationalID == nationalID) {
            c = customers[i];
            break;
        }
    }

    if (c == nullptr) {
        cout << "Customer not found "<<endl;
        return;
    }

    cout << "Products purchased by " << c->firstName << " " << c->lastName << endl;

    int displayedProductIDs[MAX_SIZE];
    int displayedCount = 0;

    for (int i = 0; i < purchaseCount; i++) {
        if (purchases[i]->customer->nationalID == nationalID) {
            int pid = purchases[i]->product->productID;

            bool alreadyDisplayed = false;
            for (int j = 0; j < displayedCount; j++) {
                if (displayedProductIDs[j] == pid) {
                    alreadyDisplayed = true;
                    break;
                }
            }

            if (!alreadyDisplayed) {
                displayedProductIDs[displayedCount++] = pid;
                Product* p = purchases[i]->product;
                cout << "- " << p->name << " (ID: " << p->productID << ", Price: " << p->price << ")\n";
            }
        }
    }

    if (displayedCount == 0) {
        cout << "No products found for this customer" <<endl;
    }
}
void salesReportByDealer() {
    if (dealerCount == 0) {
        cout << "No dealers available "<<endl;
        return;
    }

    cout << "Sales report for all dealers : "<<endl;

    for (int i = 0; i < dealerCount; i++) {
        Dealer* d = dealers[i];
        double totalSales = 0;

        for (int j = 0; j < purchaseCount; j++) {
            if (purchases[j]->dealer->dealerID == d->dealerID) {
                totalSales += purchases[j]->product->price * purchases[j]->quantity;
            }
        }

        cout << "- " << d->name << " (ID: " << d->dealerID << ") : Total Sales = " << totalSales << "\n";
    }
}
void showMenu() {
    cout << "1. Add a Product"<<endl;
    cout << "2. Remove a Product"<<endl;
    cout << "3. Add a Customer"<<endl;
    cout << "4. Remove a Customer"<<endl;
    cout << "5. Add a Dealer"<<endl;
    cout << "6. Remove a Dealer"<<endl;
    cout << "7. Record a Purchase"<<endl;
    cout << "8. Calculate total purchase amount for a Customer "<<endl;
    cout << "9. List Customers of a Product "<<endl;
    cout << "10. List Products sold by a Dealer "<<endl;
    cout << "11. Total units sold of a Product"<<endl;
    cout << "12. List Products purchased by a Customer"<<endl;
    cout << "13. Sales Report by Dealer"<<endl;
    cout << "14. Exit"<<endl;
    cout << "Enter your choice: "<<endl;
}


int main() {
    int num;
    do {
        showMenu();
        cin >> num;

        switch(num) {
            case 1: addProduct(); break;
            case 2: removeProduct(); break;
            case 3: addCustomer(); break;
            case 4: removeCustomer(); break;
            case 5: addDealer(); break;
            case 6: removeDealer(); break;
            case 7: recordPurchase(); break;
            case 8: totalPurchaseOfCustomer(); break;
            case 9: listCustomersOfProduct(); break;
            case 10: productsSoldByDealer(); break;
            case 11: numberOfSalesOfProduct(); break;
            case 12: productsPurchasedByCustomer(); break;
            case 13: salesReportByDealer(); break;
            case 14: cout << "Exiting program "<<endl; break;
            default: cout << "Invalid choice. Try again"<<endl;
        }
    } while(num != 14);

    // khali kardan faza ghabl az khoroj
    for (int i = 0; i < productCount; i++) delete products[i];
    for (int i = 0; i < customerCount; i++) delete customers[i];
    for (int i = 0; i < dealerCount; i++) delete dealers[i];
    for (int i = 0; i < purchaseCount; i++) delete purchases[i];

    return 0;
}






