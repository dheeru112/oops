#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

class Account {
private:
    int accountNumber;
    char name[50];
    char type;
    double balance;

public:
    void createAccount() {
        cout << "\nEnter The Account No.: ";
        cin >> accountNumber;

        cout << "Enter The Name of The Account Holder: ";
        cin.ignore();
        cin.getline(name, 50);

        cout << "Enter Type of Account (C/S): ";
        cin >> type;
        type = toupper(type);

        cout << "Enter Initial Amount: ";
        cin >> balance;

        cout << "\nAccount Successfully Created...\n";
    }

    void showAccount() const {
        cout << "\nAccount No.: " << accountNumber;
        cout << "\nAccount Holder Name: " << name;
        cout << "\nType of Account: " << type;
        cout << "\nBalance Amount: " << balance << "\n";
    }

    void modify() {
        cout << "\nModify Account Holder Name: ";
        cin.ignore();
        cin.getline(name, 50);

        cout << "Modify Type of Account: ";
        cin >> type;
        type = toupper(type);

        cout << "Modify Balance amount: ";
        cin >> balance;
    }

    void deposit(double amt) {
        balance += amt;
    }

    bool withdraw(double amt) {
        if (amt > balance)
            return false;
        balance -= amt;
        return true;
    }

    void report() const {
        cout << setw(10) << accountNumber << setw(20) << name 
             << setw(10) << type << setw(10) << balance << endl;
    }

    int getAccountNumber() const {
        return accountNumber;
    }
};

const char* FILENAME = "accounts.dat";

// ------------------ FUNCTION DEFINITIONS ------------------

void writeAccount() {
    Account ac;
    ofstream outFile;
    outFile.open(FILENAME, ios::binary | ios::app);

    ac.createAccount();
    outFile.write(reinterpret_cast<char*>(&ac), sizeof(Account));
    outFile.close();

    cout << "\nAccount Added Successfully\n";
}

void displaySpecific(int n) {
    Account ac;
    bool found = false;
    ifstream inFile;

    inFile.open(FILENAME, ios::binary);
    if (!inFile) {
        cout << "File could not be opened!";
        return;
    }

    while (inFile.read(reinterpret_cast<char*>(&ac), sizeof(Account))) {
        if (ac.getAccountNumber() == n) {
            ac.showAccount();
            found = true;
        }
    }

    inFile.close();
    if (!found)
        cout << "\nAccount number does not exist\n";
}

void modifyAccount(int n) {
    Account ac;
    bool found = false;
    fstream File;

    File.open(FILENAME, ios::binary | ios::in | ios::out);
    if (!File) {
        cout << "File could not be open !!";
        return;
    }

    while (File.read(reinterpret_cast<char*>(&ac), sizeof(Account))) {
        if (ac.getAccountNumber() == n) {
            ac.showAccount();
            cout << "\nEnter New Details of Account:\n";
            ac.modify();

            int pos = -static_cast<int>(sizeof(ac));
            File.seekp(pos, ios::cur);
            File.write(reinterpret_cast<char*>(&ac), sizeof(Account));

            cout << "\nRecord Updated\n";
            found = true;
            break;
        }
    }
    File.close();

    if (!found)
        cout << "\nRecord Not Found\n";
}

void deleteAccount(int n) {
    Account ac;
    ifstream inFile;
    ofstream outFile;

    inFile.open(FILENAME, ios::binary);
    if (!inFile) {
        cout << "File could not be opened!";
        return;
    }

    outFile.open("Temp.dat", ios::binary);

    while (inFile.read(reinterpret_cast<char*>(&ac), sizeof(Account))) {
        if (ac.getAccountNumber() != n) {
            outFile.write(reinterpret_cast<char*>(&ac), sizeof(Account));
        }
    }

    inFile.close();
    outFile.close();

    remove(FILENAME);
    rename("Temp.dat", FILENAME);

    cout << "\nRecord Deleted Successfully\n";
}

void displayAll() {
    Account ac;
    ifstream inFile;

    inFile.open(FILENAME, ios::binary);
    if (!inFile) {
        cout << "File could not be opened!";
        return;
    }

    cout << "\n\n\tACCOUNT HOLDER LIST\n\n";
    cout << "Acc No." << setw(15) << "Name" << setw(15) << "Type" 
         << setw(15) << "Balance\n\n";

    while (inFile.read(reinterpret_cast<char*>(&ac), sizeof(Account))) {
        ac.report();
    }

    inFile.close();
}

void depositWithdraw(int n, int option) {
    Account ac;
    fstream File;
    double amt;
    bool found = false;

    File.open(FILENAME, ios::binary | ios::in | ios::out);
    if (!File) {
        cout << "File could not be opened!";
        return;
    }

    while (File.read(reinterpret_cast<char*>(&ac), sizeof(Account))) {
        if (ac.getAccountNumber() == n) {
            ac.showAccount();

            if (option == 1) {
                cout << "\nEnter amount to deposit: ";
                cin >> amt;
                ac.deposit(amt);
            } else {
                cout << "\nEnter amount to withdraw: ";
                cin >> amt;

                if (!ac.withdraw(amt)) {
                    cout << "Insufficient Balance!\n";
                    File.close();
                    return;
                }
            }

            int pos = -static_cast<int>(sizeof(ac));
            File.seekp(pos, ios::cur);
            File.write(reinterpret_cast<char*>(&ac), sizeof(Account));

            cout << "\nRecord Updated\n";
            found = true;
            break;
        }
    }

    File.close();

    if (!found)
        cout << "\nRecord Not Found\n";
}

// ------------------------ MAIN MENU ------------------------

int main() {
    char choice;
    int num;

    do {
        cout << "\n\n\tBANK MANAGEMENT SYSTEM";
        cout << "\n1. NEW ACCOUNT";
        cout << "\n2. DEPOSIT AMOUNT";
        cout << "\n3. WITHDRAW AMOUNT";
        cout << "\n4. BALANCE ENQUIRY";
        cout << "\n5. ALL ACCOUNT HOLDER LIST";
        cout << "\n6. CLOSE AN ACCOUNT";
        cout << "\n7. MODIFY AN ACCOUNT";
        cout << "\n8. EXIT";
        cout << "\n\nSelect (1-8): ";
        cin >> choice;

        switch (choice) {
            case '1': writeAccount(); break;
            case '2': 
                cout << "Enter Account No.: ";
                cin >> num;
                depositWithdraw(num, 1);
                break;
            case '3':
                cout << "Enter Account No.: ";
                cin >> num;
                depositWithdraw(num, 2);
                break;
            case '4':
                cout << "Enter Account No.: ";
                cin >> num;
                displaySpecific(num);
                break;
            case '5': displayAll(); break;
            case '6':
                cout << "Enter Account No.: ";
                cin >> num;
                deleteAccount(num);
                break;
            case '7':
                cout << "Enter Account No.: ";
                cin >> num;
                modifyAccount(num);
                break;
            case '8': 
                cout << "\nThanks for using Bank Management System\n";
                break;
            default:
                cout << "Invalid Choice!";
        }
    } while (choice != '8');

    return 0;
}