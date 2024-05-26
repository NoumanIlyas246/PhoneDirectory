#include <iostream>
#include <list>
#include <string>

using namespace std;

struct Contact {
    string firstName;
    string lastName;
    string mobile;
    string home;
    string work;
    string email;

    void display() const {
        cout << "Name: " << firstName << " " << lastName << endl;
        cout << "Mobile: " << mobile << endl;
        cout << "Home: " << home << endl;
        cout << "Work: " << work << endl;
        if (!email.empty()) {
            cout << "Email: " << email << endl;
        }
    }
};

class PhoneDirectory {
private:
    list<Contact> contacts;

public:
    void addContact(const Contact& contact) {
        contacts.push_back(contact);
    }

    void modifyContact(const string& mobile, const Contact& updatedContact) {
        for (auto& contact : contacts) {
            if (contact.mobile == mobile) {
                contact = updatedContact;
                return;
            }
        }
        cout << "Contact not found!" << endl;
    }

    void removeContact(const string& mobile) {
        for (auto it = contacts.begin(); it != contacts.end(); ++it) {
            if (it->mobile == mobile) {
                contacts.erase(it);
                cout << "Contact deleted." << endl;
                return;
            }
        }
        cout << "Contact not found!" << endl;
    }

    void findContacts(const string& query) const {
        for (const auto& contact : contacts) {
            if (contact.firstName.find(query) != string::npos ||
                contact.lastName.find(query) != string::npos ||
                contact.mobile.find(query) != string::npos) {
                contact.display();
                cout << "---------------------" << endl;
            }
        }
    }

    void showContacts() const {
        for (const auto& contact : contacts) {
            contact.display();
            cout << "---------------------" << endl;
        }
    }

    void orderContactsByName() {
        contacts.sort([](const Contact& a, const Contact& b) {
            if (a.lastName != b.lastName) return a.lastName < b.lastName;
            return a.firstName < b.firstName;
            });
    }

    void orderContactsByPhoneNumber() {
        contacts.sort([](const Contact& a, const Contact& b) {
            return a.mobile < b.mobile;
            });
    }
};

int main() {
    PhoneDirectory directory;
    char choice;

    do {
        cout << "\nPhone Directory Application\n";
        cout << "a. Add Contact\n";
        cout << "b. Edit Contact\n";
        cout << "c. Delete Contact\n";
        cout << "d. Search Contacts\n";
        cout << "e. Display All Contacts\n";
        cout << "f. Sort Contacts by Name\n";
        cout << "g. Sort Contacts by Phone Number\n";
        cout << "q. Quit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Clear newline character from input buffer

        if (choice == 'a') {
            Contact contact;
            cout << "Enter First Name: ";
            getline(cin, contact.firstName);
            cout << "Enter Last Name: ";
            getline(cin, contact.lastName);
            cout << "Enter Mobile Number: ";
            getline(cin, contact.mobile);
            cout << "Enter Home Number: ";
            getline(cin, contact.home);
            cout << "Enter Work Number: ";
            getline(cin, contact.work);
            cout << "Enter Email (optional): ";
            getline(cin, contact.email);
            directory.addContact(contact);
        }
        else if (choice == 'b') {
            string mobile;
            cout << "Enter Mobile Number of the Contact to Edit: ";
            getline(cin, mobile);
            Contact updatedContact;
            cout << "Enter First Name: ";
            getline(cin, updatedContact.firstName);
            cout << "Enter Last Name: ";
            getline(cin, updatedContact.lastName);
            cout << "Enter Mobile Number: ";
            getline(cin, updatedContact.mobile);
            cout << "Enter Home Number: ";
            getline(cin, updatedContact.home);
            cout << "Enter Work Number: ";
            getline(cin, updatedContact.work);
            cout << "Enter Email (optional): ";
            getline(cin, updatedContact.email);
            directory.modifyContact(mobile, updatedContact);
        }
        else if (choice == 'c') {
            string mobile;
            cout << "Enter Mobile Number of the Contact to Delete: ";
            getline(cin, mobile);
            directory.removeContact(mobile);
        }
        else if (choice == 'd') {
            string query;
            cout << "Enter Name or Phone Number to Search: ";
            getline(cin, query);
            directory.findContacts(query);
        }
        else if (choice == 'e') {
            directory.showContacts();
        }
        else if (choice == 'f') {
            directory.orderContactsByName();
            cout << "Contacts sorted by name." << endl;
        }
        else if (choice == 'g') {
            directory.orderContactsByPhoneNumber();
            cout << "Contacts sorted by phone number." << endl;
        }
    } while (choice != 'q');

    return 0;
}