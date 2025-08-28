#include "Customer.h"    // Εισαγωγή του header της Customer
#include <iostream>      // Για είσοδο/έξοδο δεδομένων
#include <fstream>       // Για την ανάγνωση/εγγραφή αρχείων
#include <sstream>       // Για επεξεργασία strings
#include <iomanip>       // Για διαμόρφωση της εξόδου
#include <algorithm>     // Για τη χρήση της find_if
#include <vector>
#include "Product.h"



using namespace std; // Αποφυγή επαναλαμβανόμενου std::

// Κατασκευαστής που αρχικοποιεί τα πεδία της User
Customer::Customer(const string& username, const string& password)
    : User(username, password, false) {} // Ορίζουμε ότι δεν είναι admin (isAdmin = false)

// Επιστρέφει το μονοπάτι του αρχείου ιστορικού παραγγελιών του πελάτη
string Customer::getHistoryFilePath() const {
    return "files/order_history/" + username + "_history.txt"; // Δημιουργεί το path του αρχείου ιστορικού
}

// Προσθήκη προϊόντος στο καλάθι
void Customer::addToCart(const Product& product, int quantity) {
    // Ελέγχουμε αν το προϊόν υπάρχει ήδη στο καλάθι
    for (auto& item : cart) {
        if (item.getTitle() == product.getTitle()) {
            item.setQuantity(item.getQuantity() + quantity); // Αυξάνουμε την ποσότητα
            cout << "Added " << quantity << " more of " << product.getTitle() << " to your cart.\n";
            return;
        }
    }
    // Αν το προϊόν δεν υπάρχει στο καλάθι, το προσθέτουμε ως νέο
    Product newProduct = product;
    newProduct.setQuantity(quantity); // Ρυθμίζουμε την ποσότητα
    cart.push_back(newProduct);
    cout << "Added " << quantity << " of " << product.getTitle() << " to your cart.\n";
}


// Ενημέρωση ποσότητας ή αφαίρεση προϊόντος από το καλάθι
void Customer::updateCart(const string& title, int newQuantity) {
    for (auto it = cart.begin(); it != cart.end(); ++it) { // Διατρέχουμε το καλάθι
        if (it->getTitle() == title) { // Αν βρούμε το προϊόν βάσει τίτλου
            if (newQuantity == 0) { // Αν η νέα ποσότητα είναι 0
                cart.erase(it); // Διαγραφή προϊόντος από το καλάθι
                cout << "Removed " << title << " from your cart.\n"; // Μήνυμα επιβεβαίωσης
            } else { // Αν η νέα ποσότητα είναι μεγαλύτερη από 0
                it->setQuantity(newQuantity); // Ενημέρωση ποσότητας
                cout << "Updated " << title << " quantity to " << newQuantity << ".\n"; // Μήνυμα επιβεβαίωσης
            }
            return; // Τέλος μεθόδου
        }
    }
    cout << "The product \"" << title << "\" is not in your cart.\n"; // Μήνυμα αν το προϊόν δεν βρεθεί
}

// Προβολή καλαθιού αγορών
void Customer::viewCart() const {
    if (cart.empty()) { // Έλεγχος αν το καλάθι είναι άδειο
        cout << "---CART START---\n"; // Έναρξη καλαθιού
        cout << "---CART END---\n";   // Λήξη καλαθιού
        cout << "Total Cost: 0\n";    // Εμφάνιση συνολικού κόστους
        return; // Έξοδος από τη μέθοδο
    }

    cout << "---CART START---\n"; // Έναρξη εκτύπωσης καλαθιού
    double totalCost = 0.0; // Αρχικοποίηση συνολικού κόστους

    for (const auto& item : cart) { // Διατρέχουμε όλα τα προϊόντα στο καλάθι
        cout << item.getQuantity() << " " << item.getTitle() << "\n"; // Εκτύπωση ποσότητας και τίτλου προϊόντος
        totalCost += item.getPrice() * item.getQuantity(); // Προσθήκη κόστους προϊόντος στο συνολικό κόστος
    }

    cout << "---CART END---\n"; // Λήξη εκτύπωσης καλαθιού
    cout << "Total Cost: " << fixed << setprecision(2) << totalCost << "\n"; // Εμφάνιση συνολικού κόστους
}



// Ολοκλήρωση παραγγελίας
void Customer::completeOrder(vector<Product>& products) {
    if (cart.empty()) { // Αν το καλάθι είναι άδειο
        cout << "Your cart is empty. Nothing to checkout.\n"; // Ενημέρωση ότι το καλάθι είναι κενό
        return; // Τερματισμός της συνάρτησης
    }

    // Έλεγχος και ενημέρωση αποθέματος
    for (size_t i = 0; i < cart.size(); ++i) { // Διατρέχουμε όλα τα προϊόντα στο καλάθι
        bool found = false; // Σημαία για να ελέγξουμε αν το προϊόν βρέθηκε στο απόθεμα
        for (size_t j = 0; j < products.size(); ++j) { // Διατρέχουμε όλα τα διαθέσιμα προϊόντα
            if (products[j].getTitle() == cart[i].getTitle()) { // Αν τα προϊόντα έχουν τον ίδιο τίτλο
                found = true; // Το προϊόν βρέθηκε
                if (products[j].getQuantity() < cart[i].getQuantity()) { // Αν δεν υπάρχει αρκετό απόθεμα
                    cout << "Not enough stock for " << products[j].getTitle() << ".\n"; // Μήνυμα έλλειψης
                    cart[i].setQuantity(products[j].getQuantity()); // Ρύθμιση της ποσότητας στο μέγιστο διαθέσιμο
                }
                products[j].setQuantity(products[j].getQuantity() - cart[i].getQuantity()); // Μείωση αποθέματος
            }
        }
        if (!found) { // Αν το προϊόν δεν βρέθηκε καθόλου
            cout << "Product \"" << cart[i].getTitle() << "\" is not available in stock.\n"; // Μήνυμα έλλειψης
            cart[i].setQuantity(0); // Ρύθμιση ποσότητας σε μηδέν
        }
    }

     // Έλεγχος αν το username είναι έγκυρο
    if (username.empty()) { 
        cerr << "Error: Username is empty. Cannot create order history file.\n";
        return;
    }

    // Αποθήκευση στο ιστορικό παραγγελιών
    string historyFilePath = "files/order_history/" + username + "_history.txt"; // Διαδρομή αρχείου
    ofstream historyFile(historyFilePath, ios::app); // Άνοιγμα αρχείου σε λειτουργία προσάρτησης
    if (!historyFile) { // Έλεγχος ανοίγματος
        cerr << "Error: Unable to write to order history file.\n"; // Ενημέρωση
        return; // Τερματισμός
    }

    // Υπολογισμός αριθμού καλαθιού
    int cartNumber = 1; // Αρχικό καλάθι
    ifstream existingFile(historyFilePath); // Άνοιγμα υπάρχοντος αρχείου
    string line;
    while (getline(existingFile, line)) { // Διατρέχουμε το αρχείο
        if (line.find("--- CART ") != string::npos) { // Αν βρεθεί αριθμός καλαθιού
            cartNumber++; // Αύξηση αριθμού
        }
    }
    existingFile.close(); // Κλείσιμο αρχείου

    // Εγγραφή στο αρχείο
    historyFile << "--- CART " << cartNumber << " START ---\n"; // Έναρξη καλαθιού
    double totalCost = 0.0; // Συνολικό κόστος
    for (const auto& cartItem : cart) { // Διατρέχουμε τα προϊόντα του καλαθιού
        if (cartItem.getQuantity() > 0) { // Αν η ποσότητα είναι έγκυρη
            historyFile << cartItem.getQuantity() << " " << cartItem.getTitle() << "\n"; // Εγγραφή προϊόντος
            totalCost += cartItem.getQuantity() * cartItem.getPrice(); // Προσθήκη στο συνολικό κόστος
        }
    }
    historyFile << "--- CART " << cartNumber << " END ---\n"; // Τέλος καλαθιού
    historyFile << "Total Cost: " << totalCost << "\n"; // Εγγραφή συνολικού κόστους
    historyFile.close(); // Κλείσιμο αρχείου

    // Εκκαθάριση καλαθιού
    cart.clear(); // Αδειάζουμε το καλάθι
    cout << "Order completed successfully! Thank you for shopping.\n"; // Ενημέρωση χρήστη
}

    




// Προβολή ιστορικού παραγγελιών
void Customer::viewOrderHistory() const {
    string filepath = getHistoryFilePath(); // Παίρνουμε το path του αρχείου ιστορικού
    ifstream file(filepath); // Άνοιγμα αρχείου για ανάγνωση
    if (!file) { // Έλεγχος αν το αρχείο ανοίγει
        cout << "No order history found for user \"" << username << "\".\n"; // Μήνυμα αν δεν υπάρχει ιστορικό
        return; // Τέλος μεθόδου
    }

    cout << "--- Order History ---\n"; // Τίτλος ιστορικού
    string line;
    int orderCount = 1; // Μετρητής για τις παραγγελίες
    while (getline(file, line)) { // Διαβάζουμε κάθε γραμμή του αρχείου
        // Ελέγχουμε για την έναρξη και το τέλος κάθε παραγγελίας
        if (line.find("---CART START---") != string::npos) {
            cout << "--- CART " << orderCount++ << " START ---\n"; // Προσθέτουμε αριθμό παραγγελίας
        } else if (line.find("---CART END---") != string::npos) {
            cout << "--- CART " << orderCount - 1 << " END ---\n"; // Κλείνουμε την παραγγελία
        } else {
            cout << line << "\n"; // Εμφάνιση γραμμών με προϊόντα και συνολικό κόστος
        }
    }
    file.close(); // Κλείσιμο αρχείου
}


// Εμφάνιση του μενού του πελάτη
void Customer::displayMenu() const {
    cout << "--- Customer Menu ---\n"; // Τίτλος μενού
    cout << "1. Search for a product\n"; // Επιλογή αναζήτησης προϊόντος
    cout << "2. Add product to cart\n"; // Επιλογή προσθήκης προϊόντος στο καλάθι
    cout << "3. Update product from cart\n"; // Επιλογή ενημέρωσης προϊόντος στο καλάθι
    cout << "4. Remove product from cart\n"; // Επιλογή αφαίρεσης προϊόντος από το καλάθι
    cout << "5. Complete order\n"; // Επιλογή ολοκλήρωσης παραγγελίας
    cout << "6. View order history\n"; // Επιλογή προβολής ιστορικού παραγγελιών
    cout << "7. View cart\n"; // Επιλογή προβολής καλαθιού
    cout << "8. Exit\n"; // Επιλογή εξόδου
}


// Λειτουργία διαχείρισης μενού πελάτη
void Customer::customerMenu(vector<Product>& products) {
    int choice; // Αποθηκεύει την επιλογή του πελάτη
    do {
        displayMenu(); // Εμφάνιση μενού
        cout << "Enter your choice: "; // Εισαγωγή επιλογής
        cin >> choice; // Ανάγνωση επιλογής
        
         // Έλεγχος αν η εισαγωγή ήταν έγκυρη
        if (cin.fail()) {
            cin.clear(); // Καθαρισμός του σφάλματος
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Απαλλαγή από την κακή είσοδο στο buffer
            cout << "Invalid input. Please enter a number.\n"; // Ενημέρωση του χρήστη
            continue; // Επιστροφή στην αρχή του loop
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
         
        switch (choice) {
            case 1: {
                // Αναζήτηση προϊόντων
                searchProduct(products); // Κλήση της μεθόδου αναζήτησης προϊόντων
                break;
            }
            case 2: {
                // Προσθήκη προϊόντος στο καλάθι
                string title;
                int quantity;

            

                cout << "Which product do you want to add? "; // Ζήτηση τίτλου προϊόντος
                //cin.ignore(); // Καθαρισμός buffer εισόδου
                getline(cin, title); // Ανάγνωση τίτλου

                cout << "Enter quantity: "; // Ζήτηση ποσότητας
                cin >> quantity; // Ανάγνωση ποσότητας

                // Αναζήτηση του προϊόντος στον κατάλογο
                auto it = find_if(products.begin(), products.end(), [&title](const Product& p) {
                return p.getTitle() == title; // Έλεγχος αν υπάρχει το προϊόν με βάση τον τίτλο
                });

                if (it != products.end()) {
                addToCart(*it, quantity); // Κλήση της addToCart για προσθήκη
                } else {
                cout << "Product \"" << title << "\" not found.\n"; // Μήνυμα αν το προϊόν δεν βρεθεί
                }
                break;
            }

            case 3: { // Ενημέρωση καλαθιού
                string title;
                int quantity;
                cout << "Which product do you want to update?"; // Εισαγωγή τίτλου προϊόντος
                getline(cin, title); // Διαβάζουμε το όνομα του προϊόντος
                cout << "Enter new quantity: "; // Εισαγωγή νέας ποσότητας
                cin >> quantity;
                updateCart(title, quantity); // Ενημέρωση καλαθιού
                break;
            }
            case 4: { // Αφαίρεση προϊόντος από το καλάθι
                string title; // Μεταβλητή για τον τίτλο του προϊόντος
                cout << "Which product do you want to remove from your cart? "; // Μήνυμα προς τον χρήστη
                getline(cin, title); // Ανάγνωση τίτλου προϊόντος
                removeProductFromCart(title); // Κλήση της μεθόδου για αφαίρεση
                break; // Τέλος επιλογής
            }
            case 5: {
                // Κλήση της συνάρτησης completeOrder
                completeOrder(products); // Ολοκληρώνει την παραγγελία και ενημερώνει το ιστορικό
                // Εμφάνιση μηνύματος επιτυχίας, όπως στα samples
                cout << "Order Completed!\n";
                break; // Έξοδος από την επιλογή
            }
            case 6: { // Προβολή ιστορικού παραγγελιών
                viewOrderHistory();
                break;
            }
            case 7: { // Προβολή καλαθιού
                viewCart(); // Κλήση της συνάρτησης που εμφανίζει το καλάθι
                    break; // Τερματισμός της επιλογής
                   
            }
            case 8 : {
                cout << "Goodbye!\n"; //εμφανιση μηνυματος αποχαιρετισμου
                return;
            }
            default: // Μη έγκυρη επιλογή
                cout << "Invalid choice. Try again.\n";
        }
    } 
    while (choice != 8); // Επανάληψη μέχρι να επιλεγεί έξοδος
}

void Customer::searchProduct(const vector<Product>& products) const {
    cout << "Product Search Options:\n" // Εμφάνιση επιλογών αναζήτησης
         << "1. Search for a specific product (by title).\n" // Αναζήτηση βάσει τίτλου
         << "2. View the products of a specific category.\n" // Εμφάνιση προϊόντων συγκεκριμένης κατηγορίας
         << "3. Show all the available products.\n" // Εμφάνιση όλων των προϊόντων
         << "Enter your choice: ";

    int choice;
    cin >> choice; // Εισαγωγή επιλογής από τον χρήστη

    if (choice == 1) { // Επιλογή 1: Αναζήτηση βάσει τίτλου
        cout << "Enter product title: "; // Ζητάμε τον τίτλο του προϊόντος
        string title;
        cin.ignore(); // Καθαρισμός του buffer
        getline(cin, title); // Εισαγωγή του τίτλου από τον χρήστη

        // Αναζήτηση προϊόντος βάσει τίτλου
        auto it = find_if(products.begin(), products.end(), [&title](const Product& product) {
            return product.getTitle() == title; // Επιστροφή true αν ο τίτλος ταιριάζει
        });

        if (it != products.end()) { // Αν το προϊόν βρέθηκε
            // Εμφάνιση λεπτομερειών προϊόντος
            cout << "-----" << it->getTitle() << "-----\n"
                 << "Description: " << it->getDescription() << "\n"
                 << "Category: " << it->getCategory() << "\n"
                 << "Subcategory: " << it->getSubcategory() << "\n"
                 << "Price per unit: " << it->getPrice() << "€\n"
                 << "Total units available: " << it->getQuantity() << "\n";
        } else { // Αν δεν βρέθηκε προϊόν
            cout << "Product not found.\n"; // Μήνυμα λάθους
        }

    } else if (choice == 2) {
        std::string category, subcategory; // Δημιουργία μεταβλητών για την κατηγορία και την υποκατηγορία

         // Καθαρισμός του buffer για την αποφυγή προβλημάτων με προηγούμενα δεδομένα
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 


        // Εμφάνιση όλων των διαθέσιμων κατηγοριών
        std::cout << "Available categories: Tech, Book, Clothing, Drink, Food\n"; // Εμφάνιση κατηγοριών
        std::cout << "Enter a category: ";
        std::getline(std::cin, category); // Εισαγωγή κατηγορίας από τον χρήστη

        // Εμφάνιση υποκατηγοριών αν ο χρήστης επέλεξε έγκυρη κατηγορία
        std::cout << "Available subcategories for " << category << ": ";
        if (category == "Tech") {
            std::cout << "Laptop, Phone, Tablet\n";
        } else if (category == "Book") {
            std::cout << "Mystery, Sci-Fi, Romance\n";
        } else if (category == "Clothing") {
            std::cout << "Shirt, Pant, Hat\n";
        } else if (category == "Drink") {
            std::cout << "Juice, Coffee, Alcohol\n";
        } else if (category == "Food") {
            std::cout << "Fruit, Vegetable, Meat\n";
        } else {
            std::cout << "Invalid category.\n";
          
        }

        std::cout << "Enter a subcategory (or leave empty to view all): ";
        std::getline(std::cin, subcategory); // Εισαγωγή υποκατηγορίας (ή κενό)

        std::vector<Product> filteredProducts; // Λίστα για τα φιλτραρισμένα προϊόντα

        // Φιλτράρισμα προϊόντων βάσει κατηγορίας και υποκατηγορίας
        for (const auto& product : products) { // Διατρέχουμε όλα τα προϊόντα
            if (product.getCategory() == category && // Έλεγχος αν ταιριάζει η κατηγορία
                (subcategory.empty() || product.getSubcategory() == subcategory)) { // Έλεγχος υποκατηγορίας (αν έχει δοθεί)
                filteredProducts.push_back(product); // Προσθήκη του προϊόντος στη φιλτραρισμένη λίστα
            }
        }

        // Έλεγχος αν δεν βρέθηκαν προϊόντα
        if (filteredProducts.empty()) {
            std::cout << "No products found for the given category and subcategory.\n"; // Μήνυμα αν δεν βρεθούν προϊόντα
            
        }

        std::cout << "Results: "; // Εμφάνιση αποτελεσμάτων
        for (const auto& product : filteredProducts) {
            std::cout << "\"" << product.getTitle() << "\" "; // Εμφάνιση τίτλων των προϊόντων
        }
        std::cout << "\n";

        std::cout << "Select a product title: ";
        std::string selectedTitle;
        std::getline(std::cin, selectedTitle); // Εισαγωγή τίτλου προϊόντος από τον χρήστη

        // Αναζήτηση του προϊόντος με βάση τον τίτλο
        auto it = std::find_if(filteredProducts.begin(), filteredProducts.end(),
            [&selectedTitle](const Product& product) {
                return product.getTitle() == selectedTitle; // Έλεγχος αν ο τίτλος ταιριάζει
            });

        if (it != filteredProducts.end()) { // Αν το προϊόν βρεθεί
            // Εμφάνιση πληροφοριών προϊόντος
            std::cout << "-----" << it->getTitle() << "-----\n";
            std::cout << "Description: " << it->getDescription() << "\n";
            std::cout << "Category: " << it->getCategory() << "\n";
            std::cout << "Subcategory: " << it->getSubcategory() << "\n";
            std::cout << "Price per unit: " << it->getPrice() << "€\n";
            std::cout << "Total units available: " << it->getQuantity() << "\n";
        } else {
            // Αν δεν βρεθεί το προϊόν, εμφάνιση μηνύματος σφάλματος
            std::cout << "Error: Product not found.\n";
        }
        
    }
    else if (choice == 3) { // Επιλογή 3: Προβολή όλων των προϊόντων
        cout << "Results: "; // Προβολή αποτελεσμάτων
        for (const auto& product : products) { // Διατρέχουμε όλα τα προϊόντα
            cout << "\"" << product.getTitle() << "\" "; // Εμφάνιση τίτλου προϊόντος
        }
        cout << "\n";

        cout << "Select a product title: "; // Ζητάμε από τον χρήστη να επιλέξει τίτλο προϊόντος
        string title;
        cin.ignore(); // Καθαρισμός buffer
        getline(cin, title); // Εισαγωγή τίτλου από τον χρήστη

        // Αναζήτηση προϊόντος βάσει τίτλου
        auto it = find_if(products.begin(), products.end(), [&title](const Product& product) {
            return product.getTitle() == title; // Επιστροφή true αν ο τίτλος ταιριάζει
        });

        if (it != products.end()) { // Αν το προϊόν βρέθηκε
            // Εμφάνιση λεπτομερειών προϊόντος
            cout << "-----" << it->getTitle() << "-----\n"
                 << "Description: " << it->getDescription() << "\n"
                 << "Category: " << it->getCategory() << "\n"
                 << "Subcategory: " << it->getSubcategory() << "\n"
                 << "Price per unit: " << it->getPrice() << "€\n"
                 << "Total units available: " << it->getQuantity() << "\n";
         }
         else { // Αν ο χρήστης έδωσε λάθος τίτλο
            cout << "Invalid selection. Product not found.\n"; // Μήνυμα λάθους
        }
    }
    else {
        cout << "Invalid choice. Returning to menu.\n"; // Μήνυμα για μη έγκυρη επιλογή
    }
}


// Αφαίρεση προϊόντος από το καλάθι (χωρίς εκτυπώσεις, παραδοσιακή υλοποίηση)
void Customer::removeProductFromCart(const string& title) {
    // Βρόχος για αναζήτηση του προϊόντος στο καλάθι
    for (size_t i = 0; i < cart.size(); ++i) {
        if (cart[i].getTitle() == title) { // Έλεγχος αν ο τίτλος ταιριάζει
            cart.erase(cart.begin() + i); // Αφαίρεση προϊόντος από το καλάθι
            break; // Τερματισμός αφού βρούμε το προϊόν
        }
    }
    
}

    

