#ifndef USER_H
#define USER_H

#include <string> // Για την χρήση της κλάσης string

class User {
protected:
    std::string username; // Όνομα χρήστη
    std::string password; // Κωδικός πρόσβασης
    bool isAdmin;         // true αν ο χρήστης είναι διαχειριστής, false αν είναι πελάτης

protected:
    // Getters για τα μέλη, προσβάσιμα από υποκλάσεις
    const std::string& getPassword() const;
    bool getIsAdmin() const;

public:
    // Κατασκευαστής που αρχικοποιεί τα βασικά χαρακτηριστικά του χρήστη
    User(const std::string& username, const std::string& password, bool isAdmin);

    // Επιστρέφει το όνομα χρήστη
    std::string getUsername() const;

    // Ελέγχει αν ο κωδικός που εισήγαγε ο χρήστης είναι σωστός
    bool checkPassword(const std::string& inputPassword) const;

    // Καθαρά εικονική μέθοδος που θα υλοποιηθεί στις υποκλάσεις (Admin, Customer)
    virtual void displayMenu() const = 0;

    std::string getPasswordForStorage() const; // Επιστρέφει το password για αποθήκευση


    // Destructor (δηλωμένος ως virtual για ασφαλή διαγραφή δυναμικών αντικειμένων)
    virtual ~User();
};

#endif // USER_H

