#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Fruit {
public:
    string name;
    double price;
    int quantity;

    Fruit(const string& name, double price, int quantity)
        : name(name), price(price), quantity(quantity) {}
};

class Inventory {
public:
    vector<Fruit> fruits;

    void addFruit(const Fruit& fruit) {
        fruits.push_back(fruit);
    }

    void removeFruit(const string& name) {
        auto it = find_if(fruits.begin(), fruits.end(), [&name](const Fruit& fruit) {
            return fruit.name == name;
        });

        if (it != fruits.end()) {
            fruits.erase(it);
            cout << "Fruit removed from inventory." << endl;
        } else {
            cout << "Fruit not found in inventory." << endl;
        }
    }

    void updateFruit(const string& name, double price, int quantity) {
        auto it = find_if(fruits.begin(), fruits.end(), [&name](const Fruit& fruit) {
            return fruit.name == name;
        });

        if (it != fruits.end()) {
            it->price = price;
            it->quantity = quantity;
            cout << "Fruit updated." << endl;
        } else {
            cout << "Fruit not found in inventory." << endl;
        }
    }

    void viewFruits() const {
        if (fruits.empty()) {
            cout << "No fruits available in inventory." << endl;
        } else {
            cout<<" "<<endl;
            cout << "Available Fruits:" << endl;
            for (const auto& fruit : fruits) {
                cout << "Name: " << fruit.name << endl;
                cout << "Price:$ " << fruit.price << endl;
                cout << "Quantity: " << fruit.quantity << endl;
                cout << endl;
            }
        }
    }
};

class User {
public:
    string username;
    string password;

public:
    User(const string& username, const string& password)
        : username(username), password(password) {}

    bool authenticate(const string& username, const string& password) const {
        return this->username == username && this->password == password;
    }
};

class Admin : public User {
public:
    Admin(const string& username, const string& password)
        : User(username, password) {}

    void adminOptions(Inventory& inventory) {
        int option;
        while (true) {
            cout << endl;
            cout << "Admin Menu:" << endl;
            cout << "1. Add Fruit" << endl;
            cout << "2. Remove Fruit" << endl;
            cout << "3. Update Fruit Quantity & Price" << endl;
            cout << "4. View Fruits" << endl;
            cout << "5. Change Username" << endl;
            cout << "6. Change Password" << endl;
            cout << "7. Logout" << endl;
            cout << "Select an option: ";
            cin >> option;

            if (option == 1) {
                string name;
                double price;
                int quantity;

                cout << "Enter the fruit name: ";
                cin >> name;
                cout << "Enter the price:$ ";
                cin >> price;
                cout << "Enter the quantity: ";
                cin >> quantity;

                inventory.addFruit(Fruit(name, price, quantity));
                cout << "Fruit added to inventory." << endl;
            } else if (option == 2) {
                string name;

                cout << "Enter the fruit name to remove: ";
                cin >> name;

                inventory.removeFruit(name);
            } else if (option == 3) {
                string name;
                double price;
                int quantity;

                cout << "Enter the fruit name to update: ";
                cin >> name;
                cout << "Enter the new price: ";
                cin >> price;
                cout << "Enter the new quantity: ";
                cin >> quantity;

                inventory.updateFruit(name, price, quantity);
            } else if (option == 4) {
                inventory.viewFruits();
            } else if (option == 5) {
                cout << "Enter the new username: ";
                cin >> username;
                cout << "Username changed." << endl;
            } else if (option == 6) {
                cout << "Enter the new password: ";
                cin >> password;
                cout << "Password changed." << endl;
            } else if (option == 7) {
                break;
            } else {
                cout << "Invalid option! Please try again." << endl;
            }
        }
    }
};

class Customer : public User {
private:
    string name;
    string address;
    vector<Fruit> cart;
public:
    Customer(const string& username, const string& password)
        : User(username, password) {}

    void addFruitToCart(const Fruit& fruit) {
        cart.push_back(fruit);
        cout<<" "<<endl;
        cout << "Fruit added to cart." << endl;
    }

    void removeFruitFromCart(const string& name) {
        auto it = find_if(cart.begin(), cart.end(), [&name](const Fruit& fruit) {
            return fruit.name == name;
        });

        if (it != cart.end()) {
            cart.erase(it);
            cout<<" "<<endl;
            cout << "Fruit removed from cart." << endl;
        } else {
            cout << "Fruit not found in cart." << endl;
        }
    }

    void viewCart() const {
        if (cart.empty()) {
            cout << "Cart is empty." << endl;
        } else {
            cout << "Cart Contents:" << endl;
            for (const auto& fruit : cart) {
                cout << "Name: " << fruit.name << endl;
                cout << "Price: " << fruit.price << endl;
                cout << "Quantity: " << fruit.quantity << endl;
                cout << endl;
            }
        }
    }

   void placeOrder() {
    if (cart.empty()) {
        cout << "Cannot place order. Cart is empty!!" << endl;
    } else {
        // Place order logic goes here
        cout<<" "<<endl;
        cout << "Order placed successfully!" << endl;
        cart.clear();
    }
}

    

    void customerOptions(Inventory& inventory) {
        int option;
        while (true) {
            cout << endl;
            cout << "Customer Menu:" << endl;
            cout << "1. View Available Fruits" << endl;
            cout << "2. Add Fruit to Cart" << endl;
            cout << "3. View Cart" << endl;
            cout << "4. Remove Fruit from Cart" << endl;
            cout << "5. Place Order" << endl;
            cout << "6. Change Username" << endl;
            cout << "7. Change Password" << endl;
            cout << "8. Logout" << endl;
            cout << "Select an option: ";
            cin >> option;

            if (option == 1) {
                inventory.viewFruits();
            } else if (option == 2) {
                string name;

                cout << "Enter the name of the fruit to add to cart: ";
                cin >> name;

                auto it = find_if(inventory.fruits.begin(), inventory.fruits.end(), [&name](const Fruit& fruit) {
                    return fruit.name == name;
                });

                if (it != inventory.fruits.end()) {
                    addFruitToCart(*it);
                } else {
                    cout << "Fruit not found in inventory." << endl;
                }
            } else if (option == 3) {
                viewCart();
            } else if (option == 4) {
                string name;

                cout << "Enter the name of the fruit to remove from cart: ";
                cin >> name;

                removeFruitFromCart(name);
            } else if (option == 5) {
                placeOrder();
            } else if (option == 6) {
                cout << "Enter the new username: ";
                cin >> username;
                cout << "Username changed." << endl;
            } else if (option == 7) {
                cout << "Enter the new password: ";
                cin >> password;
                cout << "Password changed." << endl;
            } else if (option == 8) {
                break;
            } else {
                cout << "Invalid option! Please try again." << endl;
            }
        }
    }
};

void customerRegistration(vector<Customer>& customers) {
    string username, password, name, address;
    cout << "Enter a username: ";
    cin >> username;

    auto it = find_if(customers.begin(), customers.end(), [&username](const Customer& customer) {
        return customer.username == username;
    });

    if (it != customers.end()) {
        cout << "Username already exists! Please choose a different username." << endl;
        return;
    }

    cout << "Enter a password: ";
    cin >> password;
    cout << "Enter your name: ";
    cin >> name;
    cout << "Enter your address: ";
    // cin.ignore();
    // getline(cin, address);
    cin>>address;

    customers.push_back(Customer(username, password));
    cout << "Registration successful!" << endl;
}

int main() {
    Admin admin("admin", "admin");
    Inventory inventory;
    vector<Customer> customers;

    while (true) {
        cout << endl;
        cout << "Welcome To The Fruit Shop!" << endl;
        cout << endl;
        cout << "1. Admin Login" << endl;
        cout << "2. Customer Login" << endl;
        cout << "3. Customer Registration" << endl;
        cout << "4. Exit" << endl;
        cout << "Select an option: ";
        
        
        int option;
        cin >> option;
        cout<<endl;
       // cout << " "<<endl;

        if (option == 1) {
            string username, password;
            cout << "Admin Login:" << endl;
            cout << "Enter your username: ";
            cin >> username;
            cout << "Enter your password: ";
            cin >> password;

            if (admin.authenticate(username, password)) {
                admin.adminOptions(inventory);
            } else {
                cout << "Invalid username or password!" << endl;
            }
        } else if (option == 2) {
            string username, password;
            cout << "Customer Login:" << endl;
            cout << "Enter your username: ";
            cin >> username;
            cout << "Enter your password: ";
            cin >> password;

            auto it = find_if(customers.begin(), customers.end(), [&username, &password](const Customer& customer) {
                return customer.authenticate(username, password);
            });

            if (it != customers.end()) {
                it->customerOptions(inventory);
            } else {
                cout << "Invalid username or password! Please provide correct information or register first." << endl;
            }
        } else if (option == 3) {
            customerRegistration(customers);
        } else if (option == 4) {
            cout << "Thanks for visiting our site." << endl;
            cout<<"Best of Luck!!"<<endl;
            break;
        } else {
            cout << "Invalid option! Please try again." << endl;
        }
    }

    return 0;
}
