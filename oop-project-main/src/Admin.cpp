#include "Admin.h"
#include <iostream>  // Βιβλιοθήκη για είσοδο/έξοδο
#include <fstream>   // Βιβλιοθήκη για διαχείριση αρχείων
#include <algorithm> // Βιβλιοθήκη για λειτουργίες όπως find_if
#include <sstream> // Για χρήση της κλάσης stringstream
#include <map>       // Για τη διαχείριση μετρήσεων προϊόντων
#include <iomanip>   // Για διαμόρφωση της εξόδου
#include <filesystem> // Για διαχείριση αρχείων (C++17)
#include <dirent.h>      // Για ανάγνωση αρχείων από φακέλους



Admin::Admin(const std::string& username, const std::string& password, std::vector<Product>& products)
    : User(username, password, true), products(products) {}


// Προσθέτει νέο προϊόν στη λίστα προϊόντων
void Admin::addProduct(const Product& product) {
    
    // Έλεγχος αν το προϊόν υπάρχει ήδη στη λίστα προϊόντων
    auto it = std::find_if(products.begin(), products.end(), [&product](const Product& p) {
        return p.getTitle() == product.getTitle(); // Σύγκριση με βάση τον τίτλο του προϊόντος
    });

    if (it != products.end()) { // Αν το προϊόν υπάρχει ήδη

        it->setQuantity(it->getQuantity() + product.getQuantity()); // Προσθήκη της ποσότητας στο υπάρχον προϊόν

    } else { // Αν το προϊόν δεν υπάρχει

        products.push_back(product); // Προσθήκη του νέου προϊόντος στη λίστα
        std::cout << "The product \"" << product.getTitle() << "\" has been successfully added.\n"; // Μήνυμα επιτυχίας
    }
}


// Μέθοδος για ενημέρωση υπάρχοντος προϊόντος
void Admin::editProduct(const std::string& title) {
    
    // Αναζήτηση του προϊόντος στη λίστα
    auto it = std::find_if(products.begin(), products.end(), [&title](const Product& product) {
        return product.getTitle() == title; // Έλεγχος αν ο τίτλος ταιριάζει
    });

    if (it == products.end()) { // Αν το προϊόν δεν βρέθηκε
        cout << "Product not found.\n"; // Μήνυμα λάθους
        return; // Έξοδος από τη μέθοδο
    }

    // Εμφάνιση επιλογών για επεξεργασία
    cout << "Enter number of field you want to edit: \n";
    cout << "1. Title\n";
    cout << "2. Description\n";
    cout << "3. Category and Subcategory\n";
    cout << "4. Price\n";
    cout << "5. Available Kg\n";
    cout << "6. Nothing\n";

    int choice; // Μεταβλητή για την επιλογή του χρήστη
   
    cin >> choice; // Ανάγνωση επιλογής
     
    if (cin.fail()) { // Αν υπάρχει σφάλμα στην είσοδο
        
        cin.clear(); // Καθαρισμός του σφάλματος
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Παράβλεψη υπολοίπου εισόδου
        cout << "Invalid input. Returning to menu.\n"; // Μήνυμα λάθους
        return; // Έξοδος από τη μέθοδο
    }

    cin.ignore(); // Καθαρισμός του buffer
    switch (choice) {

    case 1: { 
        string newTitle; // Νέος τίτλος
        cout << "Enter new title: "; // Ερώτηση για τον νέο τίτλο
        getline(cin, newTitle); // Ανάγνωση του νέου τίτλου
        it->setTitle(newTitle); // Ενημέρωση του τίτλου
        break;
    }
    case 2: {
        string newDescription; // Νέα περιγραφή
        cout << "Enter new description: "; // Ερώτηση για τη νέα περιγραφή
        getline(cin, newDescription); // Ανάγνωση της νέας περιγραφής
        it->setDescription(newDescription); // Ενημέρωση της περιγραφής
        break;
    }
    case 3: {
        string newCategory, newSubcategory; // Νέα κατηγορία και υποκατηγορία
        cout << "Enter new category: "; // Ερώτηση για την κατηγορία
        getline(cin, newCategory); // Ανάγνωση κατηγορίας
        cout << "Enter new subcategory: "; // Ερώτηση για την υποκατηγορία
        getline(cin, newSubcategory); // Ανάγνωση υποκατηγορίας
        it->setCategory(newCategory, newSubcategory); // Ενημέρωση κατηγορίας
        break;
    }
    case 4: {
        double newPrice; // Νέα τιμή
        cout << "Enter new price: "; // Ερώτηση για την τιμή
        cin >> newPrice; // Ανάγνωση της νέας τιμής
        it->setPrice(newPrice); // Ενημέρωση της τιμής
        break;
    }
    case 5: {
        int newQuantity; // Νέα ποσότητα
        cout << "Enter new quantity: "; // Ερώτηση για την ποσότητα
        cin >> newQuantity; // Ανάγνωση της ποσότητας
        it->setQuantity(newQuantity); // Ενημέρωση της ποσότητας
        break;
    }
    case 6: {
        cout << "No changes made.\n"; // Μήνυμα αν δεν έγινε καμία αλλαγή
        return; // Έξοδος από τη μέθοδο
    }
    default: {
        cout << "Invalid choice.\n"; // Μήνυμα για μη έγκυρη επιλογή
        return; // Έξοδος από τη μέθοδο
    }
    }
    cout << "Product updated!\n"; // Μήνυμα επιτυχίας
}



// Μέθοδος για προβολή όλων των προϊόντων
void Admin::viewProducts() const {
    if (products.empty()) { // Αν η λίστα προϊόντων είναι κενή
        cout << "There are no products in the list.\n";
        return;
    }

    cout << "--- Product List ---\n"; // Τίτλος λίστας
    for (const auto& product : products) { // Για κάθε προϊόν στη λίστα
        cout << product.toString() << "\n"; // Εκτύπωση πληροφοριών προϊόντος
    }
}

// Εμφάνιση Admin Menu
void Admin::displayMenu() const {
    cout << "--- Admin Menu ---\n";
    cout << "1. Add Product\n";
    cout << "2. Edit Product\n";
    cout << "3. Remove Product\n";
    cout << "4. Search Product\n";
    cout <<"5. Show Unavailable Products\n" ;
    cout << "6. Show Top 5 Products\n";
    cout << "7.Exit\n";
}

//adminmenu
void Admin::adminMenu() {
    int choice; // Αποθηκεύει την επιλογή του διαχειριστή.

    do {
        
        displayMenu();
        cout << "Enter your choice: "; // Εισαγωγη επιλογης
        
        // Ανάγνωση επιλογής από τον χρήστη.
        std::cin >> choice;

         // Έλεγχος αν η εισαγωγή ήταν έγκυρη
        if (cin.fail()) {
            cin.clear(); // Καθαρισμός του σφάλματος
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Απαλλαγή από την κακή είσοδο στο buffer
            cout << "Invalid input. Please enter a number.\n"; // Ενημέρωση του χρήστη
            continue; // Επιστροφή στην αρχή του loop
        }
        
        // Καθαρισμός buffer από περιττά δεδομένα.
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        // Εκτέλεση της κατάλληλης επιλογής.
        switch (choice) {
            case 1: {
                // Εισαγωγή νέου προϊόντος.
                std::string title, description, category, subcategory, unit;
                double price;
                int quantity;

                // Εισαγωγή τίτλου προϊόντος.
                std::cout << "Enter product title: ";
                std::getline(std::cin, title);

                // Εισαγωγή περιγραφής προϊόντος.
                std::cout << "Enter product description: ";
                std::getline(std::cin, description);

                // Εισαγωγή κατηγορίας προϊόντος.
                std::cout << "Enter category (e.g., Tech, Book, Clothing, Drink, Food): ";
                std::getline(std::cin, category);

                // Εισαγωγή υποκατηγορίας προϊόντος.
                std::cout << "Enter subcategory (e.g., Laptop, Phone, Tablet): ";
                std::getline(std::cin, subcategory);

                // Εισαγωγή τιμής προϊόντος.
                std::cout << "Enter product price: ";
                std::cin >> price;

                // Καθαρισμός buffer για να διασφαλιστεί η επόμενη ανάγνωση.
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                // Εισαγωγή μονάδας μέτρησης προϊόντος.
                std::cout << "Enter measurement unit (e.g., Kg, Unit): ";
                std::getline(std::cin, unit);

                // Εισαγωγή ποσότητας προϊόντος.
                std::cout << "Enter product quantity: ";
                std::cin >> quantity;

                // Καθαρισμός buffer για να διασφαλιστεί η επόμενη ανάγνωση.
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                // Δημιουργία νέου προϊόντος και προσθήκη του στη λίστα.
                Product newProduct(title, description, category, subcategory, price, unit, quantity);
                addProduct(newProduct);
                for (const auto& product : products) {    //DEBUG
                    std::cout << "Product in vector: " << product.toString() << std::endl;
                }

                // Μήνυμα επιβεβαίωσης.
                std::cout << "Product added successfully!\n";
                break;
            }
            case 2: {
                // Επεξεργασία υπάρχοντος προϊόντος.
                std::string title;

                // Εισαγωγή τίτλου του προϊόντος που θα επεξεργαστεί.
                std::cout << "Enter the title of the product to edit: ";
                std::getline(std::cin, title);

                // Κλήση της μεθόδου επεξεργασίας προϊόντος.
                editProduct(title);

                // Μήνυμα ολοκλήρωσης.
                std::cout << "Product edited successfully!\n";
                break;
            }
            case 3: {
                std::string title;
                //εισαγωγη τιτλου προιοντος που θα διαγραφει
                std::cout<<"Enter product title you wish to remove: ";
                std::getline(std::cin, title);
                removeProduct(title);
                std::cout <<"Product removed!\n";
                break;
            }
            case 4: {
                searchProduct();
                break;
            }
            case 5: {
                showUnavailableProducts();
                break;
            }
            case 6: {
                showTopFiveProducts();
                break;
            }

            case 7: {
                // Έξοδος από το Admin Menu.
                std::cout << "Exiting Admin Menu...\n";
                return; // Τερματισμός της συνάρτησης.
            }
            default: {
                // Μήνυμα για μη έγκυρη επιλογή.
                std::cout << "Invalid input. Please try again.\n";
                break;
            }
        }
    } while (true); // Επανάληψη του βρόχου μέχρι να επιλεχθεί έξοδος.
}

void Admin::removeProduct(const string& title) {
    // Αναζήτηση προϊόντος στη λίστα με βάση τον τίτλο
    auto it = find_if(products.begin(), products.end(), [&title](const Product& p) {
        return p.getTitle() == title; // Επιστρέφει true αν ο τίτλος του προϊόντος ταιριάζει
    });

    if (it != products.end()) {  // Αν το προϊόν βρέθηκε
        products.erase(it); // Διαγραφή του προϊόντος από τη λίστα
        cout << "Product removed!\n"; // Μήνυμα επιτυχίας
    }
    else {
        cout << "The product \"" << title << "\" was not found.\n"; // Μήνυμα αν το προϊόν δεν βρέθηκε
    }
}

void Admin::searchProduct() const {
    // Έλεγχος αν υπάρχουν προϊόντα στη λίστα
    if (products.empty()) {
        cout << "No products available to search.\n"; // Εμφάνιση μηνύματος αν η λίστα προϊόντων είναι κενή
        return; // Τερματισμός της μεθόδου
    }

    int searchOption; // Μεταβλητή για την επιλογή του χρήστη
    cout << "--- Product Search Options ---\n"; // Εμφάνιση μενού αναζήτησης
    cout << "1. Search for a specific product (by title).\n"; // Επιλογή 1: Αναζήτηση προϊόντος με βάση τον τίτλο
    cout << "2. View the products of a specific category.\n"; // Επιλογή 2: Προβολή προϊόντων μιας κατηγορίας
    cout << "3. Show all the available products.\n"; // Επιλογή 3: Εμφάνιση όλων των διαθέσιμων προϊόντων
    //cout << "Enter your choice:"; // Ζήτηση επιλογής από τον χρήστη
    cin >> searchOption; // Ανάγνωση της επιλογής

    // Έλεγχος αν η είσοδος είναι έγκυρη
    if (cin.fail() || searchOption < 1 || searchOption > 3) {
        cin.clear(); // Καθαρισμός του λάθους στο cin
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Άδειασμα του buffer εισόδου
        cout << "Invalid choice. Please try again.\n"; // Μήνυμα για μη έγκυρη επιλογή
        return; // Τερματισμός της μεθόδου
    }

    switch (searchOption) {
        case 1: { // Αναζήτηση με βάση τον τίτλο
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
        }
        case 2: {
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
            std::cout << "Laptop, Phone, Tablet\n"; // Υποκατηγορίες για Tech
            } else if (category == "Book") {
                std::cout << "Mystery, Sci-Fi, Romance\n"; // Υποκατηγορίες για Book
            } else if (category == "Clothing") {
                std::cout << "Shirt, Pant, Hat\n"; // Υποκατηγορίες για Clothing
            } else if (category == "Drink") {
                std::cout << "Juice, Coffee, Alcohol\n"; // Υποκατηγορίες για Drink
            } else if (category == "Food") {
                std::cout << "Fruit, Vegetable, Meat\n"; // Υποκατηγορίες για Food
            } else {
            std::cout << "Invalid category.\n"; // Αν η κατηγορία είναι μη έγκυρη
            break; // Έξοδος από το case
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
                break; // Έξοδος από το case
            }

            // Εμφάνιση αποτελεσμάτων
            std::cout << "Results: ";
            for (const auto& product : filteredProducts) { // Διατρέχουμε τα φιλτραρισμένα προϊόντα
            std::cout << "\"" << product.getTitle() << "\" "; // Εμφάνιση τίτλου προϊόντος
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
                // Εμφάνιση λεπτομερειών προϊόντος
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

        break;
    }

        case 3: { 
            // Επιλογή 3: Προβολή όλων των προϊόντων
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
    }
}


void Admin::showUnavailableProducts() const {
    if (products.empty()) { // Έλεγχος αν η λίστα προϊόντων είναι άδεια
        cout << "No products available in the system.\n"; // Μήνυμα αν δεν υπάρχουν προϊόντα
        return;
    }

    cout << "--- Unavailable Products ---\n"; // Τίτλος ενότητας
    bool found = false; // Σημαία για να ελέγξουμε αν υπάρχουν μη διαθέσιμα προϊόντα

    for (const auto& product : products) {
        if (product.getQuantity() == 0) { // Έλεγχος ποσότητας προϊόντος
            // Εμφάνιση πληροφοριών προϊόντος
            cout << "----- " << product.getTitle() << " -----\n";
            cout << "Category: " << product.getCategory() << "\n";
            cout << "Subcategory: " << product.getSubcategory() << "\n";
            found = true; // Ενημέρωση σημαίας
        }
    }

    if (!found) { // Αν δεν βρέθηκαν μη διαθέσιμα προϊόντα
        cout << "All products are in stock.\n"; // Μήνυμα για διαθέσιμα προϊόντα
    }
}



void Admin::showTopFiveProducts() const {
    std::map<std::string, int> productPopularity; // Χάρτης για τη δημοφιλία προϊόντων

    // Άνοιγμα του φακέλου με το ιστορικό παραγγελιών
    DIR* dir = opendir("files/order_history"); // Άνοιγμα του φακέλου
    if (!dir) { // Αν αποτύχει το άνοιγμα του φακέλου
        std::cerr << "Error: Could not open the directory files/order_history.\n"; // Εμφάνιση σφάλματος
        return; // Τερματισμός συνάρτησης
    }

    struct dirent* entry; // Δομή για πληροφορίες κάθε αρχείου
    while ((entry = readdir(dir)) != nullptr) { // Για κάθε αρχείο στον φάκελο
        std::string filename = entry->d_name; // Παίρνουμε το όνομα του αρχείου
        if (filename == "." || filename == "..") { // Αγνόηση ειδικών αρχείων . και ..
            continue; // Συνέχιση με το επόμενο αρχείο
        }

        std::ifstream file("files/order_history/" + filename); // Άνοιγμα αρχείου ιστορικού
        if (!file) { // Αν αποτύχει το άνοιγμα του αρχείου
            std::cerr << "Error: Could not open file " << filename << ".\n"; // Εμφάνιση σφάλματος
            continue; // Συνέχιση με το επόμενο αρχείο
        }

        std::string line; // Μεταβλητή για αποθήκευση γραμμών
        while (std::getline(file, line)) { // Διαβάζουμε κάθε γραμμή
            // Εντοπισμός της αρχής ενός καλαθιού
            if (line.find("--CART") != std::string::npos && line.find("START") != std::string::npos) {
                while (std::getline(file, line) && // Συνεχίζουμε να διαβάζουμε
                       (line.find("--CART") == std::string::npos || line.find("END") == std::string::npos)) {
                    // Επεξεργασία κάθε γραμμής εντός καλαθιού
                    std::istringstream iss(line); // Δημιουργία stream για ανάλυση γραμμής
                    int quantity; // Μεταβλητή για την ποσότητα
                    std::string productName; // Μεταβλητή για το όνομα του προϊόντος

                    if (iss >> quantity) { // Ανάγνωση ποσότητας
                        std::getline(iss, productName); // Ανάγνωση ονόματος προϊόντος
                        
                        productPopularity[productName] += quantity; // Ενημέρωση δημοφιλίας προϊόντος
                    }
                }
            }
        }
        file.close(); // Κλείσιμο αρχείου
    }

    closedir(dir); // Κλείσιμο του φακέλου

    // Μετατροπή των δεδομένων σε vector για ταξινόμηση
    std::vector<std::pair<std::string, int>> sortedProducts(productPopularity.begin(), productPopularity.end());
    // Ταξινόμηση προϊόντων κατά φθίνουσα δημοφιλία
    std::sort(sortedProducts.begin(), sortedProducts.end(), [](const auto& a, const auto& b) {
        return a.second > b.second; // Σύγκριση βάσει ποσότητας
    });

    // Εμφάνιση των 5 πιο δημοφιλών προϊόντων
    std::cout << "--- Top 5 Products ---\n"; // Επικεφαλίδα
    for (size_t i = 0; i < std::min(sortedProducts.size(), size_t(5)); ++i) { // Εμφάνιση έως 5 προϊόντων
        std::cout << sortedProducts[i].first << ": " << sortedProducts[i].second << " orders\n"; // Εμφάνιση προϊόντος
    }
}








