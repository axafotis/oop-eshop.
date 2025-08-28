#include "Product.h" // Εισαγωγή του αρχείου header για την κλάση Product

#include <iomanip> // Απαραίτητο για std::setprecision και std::fixed


// Κατασκευαστής για αρχικοποίηση των χαρακτηριστικών
Product::Product(const string& title, const string& description, const string& category,
                 const string& subcategory, double price, const string& unit, int quantity)
    : title(title), description(description), category(category),
      subcategory(subcategory), price(price), unit(unit), quantity(quantity) {}

// Getters (επιστροφή τιμών χαρακτηριστικών)
string Product::getTitle() const { return title; }        // Επιστρέφει τον τίτλο
string Product::getDescription() const { return description; } // Επιστρέφει την περιγραφή
string Product::getCategory() const { return category; }  // Επιστρέφει την κατηγορία
string Product::getSubcategory() const { return subcategory; } // Επιστρέφει την υποκατηγορία
double Product::getPrice() const { return price; }        // Επιστρέφει την τιμή
string Product::getUnit() const { return unit; }          // Επιστρέφει τη μονάδα μέτρησης
int Product::getQuantity() const { return quantity; }     // Επιστρέφει την ποσότητα

// Setters (τροποποίηση τιμών χαρακτηριστικών)
void Product::setTitle(const string& newTitle) { title = newTitle; } // Θέτει νέο τίτλο
void Product::setDescription(const string& newDescription) { description = newDescription; } // Θέτει νέα περιγραφή
void Product::setCategory(const string& newCategory, const string& newSubcategory) {
    category = newCategory;      // Θέτει νέα κατηγορία
    subcategory = newSubcategory; // Θέτει νέα υποκατηγορία
}
void Product::setPrice(double newPrice) { price = newPrice; } // Θέτει νέα τιμή
void Product::setQuantity(int newQuantity) { quantity = newQuantity; } // Θέτει νέα ποσότητα



// Επιστρέφει string με όλες τις πληροφορίες του προϊόντος
std::string Product::toString() const {
    std::ostringstream oss; // Δημιουργία stringstream για να φτιάξουμε το format
    oss << title << " @ " // Τίτλος του προϊόντος
        << description << " @ " // Περιγραφή του προϊόντος
        << category << " @ " // Κατηγορία του προϊόντος
        << subcategory << " @ " // Υποκατηγορία
        << std::fixed << std::setprecision(2) << price << " @ " // Τιμή με 2 δεκαδικά
        << unit << " @ " // Μονάδα μέτρησης
        << quantity; // Ποσότητα
    return oss.str(); // Επιστροφή της μορφοποιημένης συμβολοσειράς
}









// Μειώνει την ποσότητα του προϊόντος αν υπάρχει επαρκής απόθεμα
void Product::reduceQuantity(int amount) {
    if (amount <= quantity) {
        quantity -= amount; // Μείωση ποσότητας
    } else {
        throw invalid_argument("Insufficient stock to reduce the requested amount."); // Εξαίρεση αν δεν υπάρχει αρκετό απόθεμα
    }
}
