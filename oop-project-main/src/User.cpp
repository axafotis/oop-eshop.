#include "User.h" // Εισαγωγή του header αρχείου

// Κατασκευαστής που αρχικοποιεί τα χαρακτηριστικά του χρήστη
User::User(const std::string& username, const std::string& password, bool isAdmin)
    : username(username), password(password), isAdmin(isAdmin) {}

// Επιστρέφει το όνομα χρήστη
std::string User::getUsername() const {
    return username;
}

// Επιστρέφει true αν ο κωδικός που δόθηκε ταιριάζει με τον αποθηκευμένο
bool User::checkPassword(const std::string& inputPassword) const {
    return password == inputPassword;
}

// Getter για την πρόσβαση στο password από υποκλάσεις (protected)
const std::string& User::getPassword() const {
    return password;
}

// Getter για την πρόσβαση στο isAdmin από υποκλάσεις (protected)
bool User::getIsAdmin() const {
    return isAdmin;
}

std::string User::getPasswordForStorage() const {
    return password; // Επιστρέφει το password
}

// Εικονικός Destructor
User::~User() {
    // Δεν χρειάζεται επιπλέον διαχείριση δυναμικής μνήμης
}
