#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"       // Η Admin κληρονομεί την User
#include "Product.h"    // Για διαχείριση αντικειμένων Product
#include <vector>       // Για τη διαχείριση λιστών


class Admin : public User {
private:
    std::vector<Product>& products; // Αναφορά σε λίστα προϊόντων

public:
     // Κατασκευαστής που αρχικοποιεί την Admin και συνδέει την αναφορά προϊόντων
     Admin(const std::string& username, const std::string& password, std::vector<Product>& products);
    

    // Εισαγωγή νέου προϊόντος
    //void addProduct(const Product& product);
    void addProduct(const Product& product); // Τροποποίηση


    // Επεξεργασία υπάρχοντος προϊόντος
    void editProduct(const std::string& title);

    // Προβολή όλων των προϊόντων
    void viewProducts() const;

    // Αποθήκευση προϊόντων στο αρχείο
    void saveProductsToFile(const std::string& filename) const;

    // Φόρτωση προϊόντων από το αρχείο
    void loadProductsFromFile(const std::string& filename);

    // Εμφάνιση του μενού του Admin
    void displayMenu() const override;

    // Διαχείριση λειτουργιών Admin
    void adminMenu();

    // Αφαίρεση προϊόντος βάσει τίτλου
    void removeProduct(const std::string& title);

    // Μέθοδος για αναζήτηση προϊόντων βάσει επιλογών
    void searchProduct() const;

    // Μέθοδος για εμφάνιση μη διαθέσιμων προϊόντων
    void showUnavailableProducts() const;

    // Μέθοδος για εμφάνιση των 5 πιο δημοφιλών προϊόντων βάσει ιστορικού
    void showTopFiveProducts() const;
};

#endif // ADMIN_H

