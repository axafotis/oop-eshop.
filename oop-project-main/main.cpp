#include <iostream> // Για είσοδο/έξοδο δεδομένων (cin, cout)
#include <vector> // Για χρήση του container vector (π.χ. λίστα προϊόντων)
#include <fstream> // Για ανάγνωση και εγγραφή σε αρχεία
#include <sstream> // Για ανάλυση strings, π.χ. μετατροπή γραμμών αρχείου σε δεδομένα
#include <algorithm> // Για συναρτήσεις όπως find_if, sort, transform
#include "Product.h" // Για τον ορισμό της κλάσης Product και τις συναρτήσεις της
#include "User.h" // Για τον ορισμό της βασικής κλάσης User
#include "Admin.h" // Για τον ορισμό της κλάσης Admin (κληρονομιά από User)
#include "Customer.h" // Για τον ορισμό της κλάσης Customer (κληρονομιά από User)
#include <unordered_map> // Για τη χρήση του unordered_map (π.χ. αποθήκευση χρηστών με βάση το username για γρήγορη πρόσβαση)


using namespace std;

std::unordered_map<std::string, User*> loadUsers(const std::string& filename, std::vector<Product>& products) {
    std::unordered_map<std::string, User*> users; // Χάρτης για τους χρήστες
    std::ifstream file(filename); // Άνοιγμα αρχείου για ανάγνωση
    if (!file) { // Έλεγχος αν το αρχείο άνοιξε σωστά
        std::cerr << "Error: Could not open file \"" << filename << "\" for reading.\n"; // Μήνυμα σφάλματος
        return users;
    }

    std::string line;
    while (std::getline(file, line)) { // Διαβάζει κάθε γραμμή από το αρχείο
        std::stringstream ss(line);
        std::string username, password, isAdminStr;

        if (std::getline(ss, username, ',') && // Διαβάζει το όνομα χρήστη
            std::getline(ss, password, ',') && // Διαβάζει τον κωδικό πρόσβασης
            std::getline(ss, isAdminStr, ',')) { // Διαβάζει αν είναι admin
            bool isAdmin = (isAdminStr == "1"); // Μετατροπή σε boolean
            if (isAdmin) {
                users[username] = new Admin(username, password, products); // Δημιουργία admin
            } else {
                users[username] = new Customer(username, password); // Δημιουργία πελάτη
            }
        } else {
            std::cerr << "Warning: Malformed line in users file: " << line << "\n"; // Προειδοποίηση για λανθασμένη γραμμή
        }
    }

    file.close(); // Κλείσιμο αρχείου
   
    return users; // Επιστροφή του χάρτη χρηστών
}


void saveUsers(const std::string& filename, const std::unordered_map<std::string, User*>& users) {
    std::ofstream file(filename); // Άνοιγμα αρχείου για εγγραφή
    if (!file) { // Έλεγχος αν το αρχείο άνοιξε σωστά
        std::cerr << "Error: Could not open file \"" << filename << "\" for writing.\n"; // Μήνυμα σφάλματος
        return;
    }

    for (const auto& pair : users) {
        const User* user = pair.second; // Παίρνουμε τον χρήστη
        file << user->getUsername() << "," // Αποθήκευση ονόματος χρήστη
             << user->getPasswordForStorage() << "," // Αποθήκευση κωδικού πρόσβασης
             << (dynamic_cast<const Admin*>(user) ? "1" : "0") << "\n"; // 1 αν είναι admin, 0 αν είναι πελάτης
    }

    file.close(); // Κλείσιμο αρχείου
   
}


// Συναρτήσεις για αποθήκευση και φόρτωση προϊόντων
void saveProductsToFile(const vector<Product>& products, const string& filename) {
    ofstream file(filename); // Άνοιγμα αρχείου για εγγραφή
    if (!file) {
        cerr << "Error: Could not open file \"" << filename << "\" for writing.\n"; // Έλεγχος σφάλματος
        return;
    }
 
    for (const auto& product : products) {
        file << product.toString() << "\n"; // Αποθήκευση κάθε προϊόντος με τη μέθοδο toString
    }

    file.close(); // Κλείσιμο αρχείου
}

// Συνάρτηση για τη φόρτωση προϊόντων από το αρχείο
vector<Product> loadProductsFromFile(const string& filename) {
    vector<Product> products; // Δημιουργία λίστας προϊόντων
    ifstream file(filename);  // Άνοιγμα αρχείου για ανάγνωση
    if (!file) {
        cerr << "Error: Could not open file \"" << filename << "\" for reading.\n"; // Έλεγχος σφάλματος
        return products;
    }   

    string line;
    while (getline(file, line)) { // Διαβάζει κάθε γραμμή από το αρχείο
        if (line.empty()) continue; // Αγνοεί κενές γραμμές

        // Διαχωρισμός πεδίων με βάση το " @ "
        size_t pos = 0;
        string title, description, category, subcategory, unit;
        double price = 0.0;
        int quantity = 0;

        try {

            // Διαχωρισμός και απομόνωση των πεδίων
            pos = line.find(" @ "); // Εντοπισμός της θέσης του διαχωριστικού " @ " για το πεδίο τίτλου
            if (pos == string::npos) throw invalid_argument("Missing field: title"); // Αν δεν βρεθεί το πεδίο, δημιουργείται εξαίρεση
            title = line.substr(0, pos); // Απομόνωση του τίτλου από την αρχή μέχρι τη θέση του διαχωριστικού
            line = line.substr(pos + 3); // Αφαίρεση του πεδίου τίτλου και του " @ " από τη γραμμή

            pos = line.find(" @ "); // Εντοπισμός της θέσης του διαχωριστικού " @ " για το πεδίο περιγραφής
            if (pos == string::npos) throw invalid_argument("Missing field: description"); // Αν δεν βρεθεί το πεδίο, δημιουργείται εξαίρεση
            description = line.substr(0, pos); // Απομόνωση της περιγραφής
            line = line.substr(pos + 3); // Αφαίρεση του πεδίου περιγραφής και του " @ "

            pos = line.find(" @ "); // Εντοπισμός της θέσης του διαχωριστικού " @ " για το πεδίο κατηγορίας
            if (pos == string::npos) throw invalid_argument("Missing field: category"); // Αν δεν βρεθεί το πεδίο, δημιουργείται εξαίρεση
            category = line.substr(0, pos); // Απομόνωση της κατηγορίας
            line = line.substr(pos + 3); // Αφαίρεση του πεδίου κατηγορίας και του " @ "

            pos = line.find(" @ "); // Εντοπισμός της θέσης του διαχωριστικού " @ " για το πεδίο υποκατηγορίας
            if (pos == string::npos) throw invalid_argument("Missing field: subcategory"); // Αν δεν βρεθεί το πεδίο, δημιουργείται εξαίρεση
            subcategory = line.substr(0, pos); // Απομόνωση της υποκατηγορίας
            line = line.substr(pos + 3); // Αφαίρεση του πεδίου υποκατηγορίας και του " @ "

            pos = line.find(" @ "); // Εντοπισμός της θέσης του διαχωριστικού " @ " για το πεδίο τιμής
            if (pos == string::npos) throw invalid_argument("Missing field: price"); // Αν δεν βρεθεί το πεδίο, δημιουργείται εξαίρεση
            price = stod(line.substr(0, pos)); // Μετατροπή του string σε double για την τιμή
            line = line.substr(pos + 3); // Αφαίρεση του πεδίου τιμής και του " @ "

            pos = line.find(" @ "); // Εντοπισμός της θέσης του διαχωριστικού " @ " για το πεδίο μονάδας
            if (pos == string::npos) throw invalid_argument("Missing field: unit"); // Αν δεν βρεθεί το πεδίο, δημιουργείται εξαίρεση
            unit = line.substr(0, pos); // Απομόνωση της μονάδας
            line = line.substr(pos + 3); // Αφαίρεση του πεδίου μονάδας και του " @ "

            // Το υπόλοιπο της γραμμής είναι η ποσότητα
            quantity = stoi(line); // Μετατροπή του string σε ακέραιο για την ποσότητα

            // Δημιουργία αντικειμένου Product και προσθήκη στο vector
            products.emplace_back(title, description, category, subcategory, price, unit, quantity); // Δημιουργία προϊόντος με τα δεδομένα που αναγνώστηκαν

        } catch (const exception& e) {
            cerr << "Warning: Malformed line in products file: " << line << "\n"; // Προειδοποίηση για λανθασμένη γραμμή
        }
    }

    file.close(); // Κλείσιμο αρχείου                   
    return products; // Επιστροφή της λίστας προϊόντων
}




int main(int argc, char* argv[]) {
    if (argc < 4) { // Έλεγχος αν δόθηκαν όλα τα απαραίτητα ορίσματα
        cerr << "Usage: " << argv[0] << " <categories_file> <products_file> <users_file>\n"; // Μήνυμα χρήσης
        return 1; // Τερματισμός με σφάλμα αν λείπουν ορίσματα
    }

    string categoriesFile = argv[1]; // Αποθήκευση του αρχείου κατηγοριών
    string productsFile = argv[2];  // Αποθήκευση του αρχείου προϊόντων
    string usersFile = argv[3];     // Αποθήκευση του αρχείου χρηστών

    // Φόρτωση προϊόντων από το αρχείο
    vector<Product> products = loadProductsFromFile(productsFile);

    // Φόρτωση χρηστών από το αρχείο
    auto users = loadUsers(usersFile, products);

    cout << "Welcome to the e-shop!\n"; // Μήνυμα καλωσορίσματος
    string option; // Μεταβλητή για την επιλογή του χρήστη
    cout << "Do you want to login or register? (enter \"login\" or \"register\"): ";
    cin >> option; // Εισαγωγή επιλογής

    if (option == "login") { // Αν ο χρήστης επιλέξει να συνδεθεί
        string username, password;
        cout << "Please enter your username: "; // Ζήτηση ονόματος χρήστη
        cin >> username; // Εισαγωγή ονόματος χρήστη
        cout << "Please enter your password: "; // Ζήτηση κωδικού πρόσβασης
        cin >> password; // Εισαγωγή κωδικού πρόσβασης

        auto it = users.find(username); // Αναζήτηση του χρήστη στον χάρτη
        // Έλεγχος αν ο χρήστης υπάρχει και ο κωδικός είναι σωστός
        if (it != users.end() && it->second->checkPassword(password)) {
            cout << "Welcome " << username << "!\n"; // Μήνυμα καλωσορίσματος
            // Έλεγχος αν ο χρήστης είναι admin και είσοδος στο admin menu
            if (auto admin = dynamic_cast<Admin*>(it->second)) {
                admin->adminMenu();
            } 
            // Αν είναι πελάτης, είσοδος στο customer menu
            else if (auto customer = dynamic_cast<Customer*>(it->second)) {
                customer->customerMenu(products);
            }
        } else {
            cout << "Invalid username or password.\n"; // Μήνυμα για λανθασμένα στοιχεία
        }
    } 
    else if (option == "register") { // Αν ο χρήστης επιλέξει εγγραφή
        string username, password;
        char isAdmin;
        cout << "Please enter your username: "; // Ζήτηση ονόματος χρήστη
        cin >> username; // Εισαγωγή ονόματος χρήστη

        // Έλεγχος αν το όνομα χρήστη υπάρχει ήδη στον χάρτη
        auto userExists = users.find(username);
        if (userExists != users.end()) {
            cout << "Error: Username already exists. Please try a different username.\n"; // Μήνυμα σφάλματος
            return 0; // Τερματισμός της εγγραφής
        }

        cout << "Please enter your password: "; // Ζήτηση κωδικού πρόσβασης
        cin >> password; // Εισαγωγή κωδικού πρόσβασης

        cout << "Are you an admin user? (Y/N): "; // Ζήτηση ρόλου χρήστη (admin ή πελάτης)
        cin >> isAdmin; // Εισαγωγή ρόλου χρήστη

        User* newUser = nullptr; // Δείκτης για τον νέο χρήστη
        // Δημιουργία χρήστη admin
        if (isAdmin == 'Y' || isAdmin == 'y') {
            newUser = new Admin(username, password, products);
        } 
        // Δημιουργία χρήστη πελάτη
        else {
            newUser = new Customer(username, password);
        }
        users[username] = newUser; // Προσθήκη του νέου χρήστη στον χάρτη

        cout << "User registered successfully!\n"; // Μήνυμα επιτυχούς εγγραφής

        // Προχωράμε στο κατάλληλο μενού ανάλογα με τον ρόλο
        if (dynamic_cast<Admin*>(newUser)) {
            dynamic_cast<Admin*>(newUser)->adminMenu();
        } else if (dynamic_cast<Customer*>(newUser)) {
            dynamic_cast<Customer*>(newUser)->customerMenu(products);
        }
    } 
    else { // Αν η επιλογή είναι μη έγκυρη
        cout << "Invalid option. Exiting...\n"; // Μήνυμα για μη έγκυρη επιλογή
    }

    // Αποθήκευση αλλαγών στα αρχεία
    saveProductsToFile(products, productsFile); // Αποθήκευση προϊόντων
    saveUsers(usersFile, users); // Αποθήκευση χρηστών

    // Καθαρισμός μνήμης για τους χρήστες
    for (auto& pair : users) {
        delete pair.second; // Διαγραφή δυναμικά κατανεμημένων χρηστών
    }

    return 0; // Επιστροφή επιτυχούς τερματισμού
}
