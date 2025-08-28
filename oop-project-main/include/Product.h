#ifndef PRODUCT_H
#define PRODUCT_H
using namespace std;

#include <string> // Βιβλιοθήκη για τη χρήση strings


class Product {
private:
    string title;        // Τίτλος προϊόντος
    string description;  // Περιγραφή προϊόντος
    string category;     // Κατηγορία προϊόντος
    string subcategory;  // Υποκατηγορία προϊόντος
    double price;        // Τιμή προϊόντος
    string unit;         // Μονάδα μέτρησης (Kg ή Unit)
    int quantity;        // Διαθέσιμη ποσότητα

public:
    // Κατασκευαστής για αρχικοποίηση των χαρακτηριστικών του προϊόντος
    Product(const string& title, const string& description, const string& category,
            const string& subcategory, double price, const string& unit, int quantity);

    // Μέθοδοι για επιστροφή των χαρακτηριστικών (getters)
    string getTitle() const;        // Επιστρέφει τον τίτλο
    string getDescription() const; // Επιστρέφει την περιγραφή
    string getCategory() const;    // Επιστρέφει την κατηγορία
    string getSubcategory() const; // Επιστρέφει την υποκατηγορία
    double getPrice() const;       // Επιστρέφει την τιμή
    string getUnit() const;        // Επιστρέφει τη μονάδα μέτρησης
    int getQuantity() const;       // Επιστρέφει την ποσότητα

    // Μέθοδοι για τροποποίηση των χαρακτηριστικών (setters)
    void setTitle(const string& newTitle);             // Θέτει νέο τίτλο
    void setDescription(const string& newDescription); // Θέτει νέα περιγραφή
    void setCategory(const string& newCategory, const string& newSubcategory); // Θέτει κατηγορία/υποκατηγορία
    void setPrice(double newPrice);                    // Θέτει νέα τιμή
    void setQuantity(int newQuantity);                 // Θέτει νέα ποσότητα

    // Βοηθητικές μέθοδοι
    string toString() const;  // Επιστρέφει string με όλες τις πληροφορίες του προϊόντος
    void reduceQuantity(int amount); // Μειώνει την ποσότητα κατά ένα δεδομένο ποσό
    std::string trim(const std::string& str);
};

#endif // PRODUCT_H
