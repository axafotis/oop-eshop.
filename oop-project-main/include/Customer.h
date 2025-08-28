#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "User.h"       // Η Customer κληρονομεί την User
#include "Product.h"    // Χρησιμοποιούμε την κλάση Product για τα προϊόντα
#include <vector>       // Για την αποθήκευση του καλαθιού και άλλων δεδομένων


class Customer : public User {
private:
    vector<Product> cart;          // Καλάθι αγορών (λίστα προϊόντων)
    string getHistoryFilePath() const; // Επιστρέφει τη διαδρομή του αρχείου ιστορικού παραγγελιών

public:
    // Κατασκευαστής που καλεί τον κατασκευαστή της User
    Customer(const string& username, const string& password);

    // Προσθήκη προϊόντος στο καλάθι
    void addToCart(const Product& product, int quantity);

    // Ενημέρωση ποσότητας ή αφαίρεση προϊόντος από το καλάθι
    void updateCart(const string& title, int newQuantity);

    // Προβολή περιεχομένων του καλαθιού
    void viewCart() const;

    // Ολοκλήρωση παραγγελίας
    void checkout(vector<Product>& products);

    // Προβολή ιστορικού παραγγελιών από αρχείο
    void viewOrderHistory() const;

    // Εμφάνιση του μενού του πελάτη
    void displayMenu() const override;

    // Λειτουργία του Customer Menu
    void customerMenu(vector<Product>& products);

    //Αναζήτηση προϊόντων
    void searchProduct(const vector<Product>& products) const;

    // Δήλωση της μεθόδου στο header (αν δεν υπάρχει ήδη)
    void removeProductFromCart(const string& title);

    // Ολοκλήρωση παραγγελίας
    void completeOrder(vector<Product>& products);

    // Destructor
    ~Customer() override = default; // Χρησιμοποιούμε τον default destructor


};

#endif // CUSTOMER_H
