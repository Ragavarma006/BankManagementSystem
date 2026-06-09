#include<iostream>
#include<fstream>
#include<string>
using namespace std;

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define CYAN    "\033[36m"

class Account {
public:
    int accountNumber;
    string name;
    string phone;
    double balance;
    string password;

    void createAccount(){
        cout << CYAN << "\n=====================================" << RESET << endl;
        cout << CYAN << "        CREATE NEW ACCOUNT           " << RESET << endl;
        cout << CYAN << "=====================================" << RESET << endl;
        cout << "Enter Account Number : ";
        cin >> accountNumber;
        cout << "Enter Your Name      : ";
        cin >> name;
        cout << "Enter Phone Number   : ";
        cin >> phone;
        cout << "Enter Initial Balance: ";
        cin >> balance;
        cout << "Set Password         : ";
        cin >> password;
        cout << GREEN << "\n✓ Account Created Successfully!" << RESET << endl;
    }

    bool login(){
        int accNo;
        string pass;
        cout << CYAN << "\n=====================================" << RESET << endl;
        cout << CYAN << "              LOGIN                  " << RESET << endl;
        cout << CYAN << "=====================================" << RESET << endl;
        cout << "Enter Account Number: ";
        cin >> accNo;
        cout << "Enter Password      : ";
        cin >> pass;

        ifstream file("accounts.txt");
        if(file.is_open()){
            while(file >> accountNumber >> name >> phone >> balance >> password){
                if(accountNumber == accNo && password == pass){
                    file.close();
                    cout << GREEN << "\n✓ Login Successful! Welcome " << name << "!" << RESET << endl;
                    return true;
                }
            }
            file.close();
        }
        cout << RED << "\n✗ Invalid Account Number or Password!" << RESET << endl;
        return false;
    }

    void deposit(){
        double amount;
        cout << CYAN << "\n=====================================" << RESET << endl;
        cout << CYAN << "           DEPOSIT MONEY             " << RESET << endl;
        cout << CYAN << "=====================================" << RESET << endl;
        cout << "Enter Amount to Deposit: ";
        cin >> amount;
        if(amount <= 0){
            cout << RED << "✗ Invalid Amount!" << RESET << endl;
        } else {
            balance += amount;
            cout << GREEN << "✓ Rs." << amount << " Deposited Successfully!" << RESET << endl;
            cout << YELLOW << "  New Balance: Rs." << balance << RESET << endl;
        }
    }

    void withdraw(){
        double amount;
        cout << CYAN << "\n=====================================" << RESET << endl;
        cout << CYAN << "          WITHDRAW MONEY             " << RESET << endl;
        cout << CYAN << "=====================================" << RESET << endl;
        cout << "Enter Amount to Withdraw: ";
        cin >> amount;
        if(amount <= 0){
            cout << RED << "✗ Invalid Amount!" << RESET << endl;
        } else if(amount > balance){
            cout << RED << "✗ Insufficient Balance!" << RESET << endl;
        } else {
            balance -= amount;
            cout << GREEN << "✓ Rs." << amount << " Withdrawn Successfully!" << RESET << endl;
            cout << YELLOW << "  Remaining Balance: Rs." << balance << RESET << endl;
        }
    }

    void checkBalance(){
        cout << CYAN << "\n=====================================" << RESET << endl;
        cout << CYAN << "          BALANCE DETAILS            " << RESET << endl;
        cout << CYAN << "=====================================" << RESET << endl;
        cout << "  Account Number : " << accountNumber << endl;
        cout << "  Name           : " << name << endl;
        cout << YELLOW << "  Balance        : Rs." << balance << RESET << endl;
    }

    void displayAccount(){
        cout << CYAN << "\n=====================================" << RESET << endl;
        cout << CYAN << "         ACCOUNT DETAILS             " << RESET << endl;
        cout << CYAN << "=====================================" << RESET << endl;
        cout << "  Account Number : " << accountNumber << endl;
        cout << "  Name           : " << name << endl;
        cout << "  Phone          : " << phone << endl;
        cout << YELLOW << "  Balance        : Rs." << balance << RESET << endl;
    }

    // NEW: Delete account
    void deleteAccount(){
        int accNo;
        string pass;
        cout << CYAN << "\n=====================================" << RESET << endl;
        cout << CYAN << "          DELETE ACCOUNT             " << RESET << endl;
        cout << CYAN << "=====================================" << RESET << endl;
        cout << "Enter Account Number to Delete: ";
        cin >> accNo;
        cout << "Enter Password to Confirm     : ";
        cin >> pass;

        ifstream inFile("accounts.txt");
        ofstream tempFile("temp.txt");
        bool found = false;

        if(inFile.is_open()){
            int tAccNo;
            string tName, tPhone, tPassword;
            double tBalance;

            while(inFile >> tAccNo >> tName >> tPhone >> tBalance >> tPassword){
                if(tAccNo == accNo && tPassword == pass){
                    found = true;
                    // Skip this record = delete it
                } else {
                    tempFile << tAccNo << " "
                             << tName << " "
                             << tPhone << " "
                             << tBalance << " "
                             << tPassword << "\n";
                }
            }
            inFile.close();
            tempFile.close();
        }

        remove("accounts.txt");
        rename("temp.txt", "accounts.txt");

        if(found){
            cout << GREEN << "✓ Account Deleted Successfully!" << RESET << endl;
        } else {
            cout << RED << "✗ Account Not Found or Wrong Password!" << RESET << endl;
        }
    }

    void saveToFile(){
        ifstream inFile("accounts.txt");
        ofstream tempFile("temp.txt");
        bool found = false;

        if(inFile.is_open()){
            int tAccNo;
            string tName, tPhone, tPassword;
            double tBalance;

            while(inFile >> tAccNo >> tName >> tPhone >> tBalance >> tPassword){
                if(tAccNo == accountNumber){
                    tempFile << accountNumber << " "
                             << name << " "
                             << phone << " "
                             << balance << " "
                             << password << "\n";
                    found = true;
                } else {
                    tempFile << tAccNo << " "
                             << tName << " "
                             << tPhone << " "
                             << tBalance << " "
                             << tPassword << "\n";
                }
            }
            inFile.close();
            tempFile.close();
        }

        remove("accounts.txt");
        rename("temp.txt", "accounts.txt");

        if(!found){
            ofstream file("accounts.txt", ios::app);
            file << accountNumber << " "
                 << name << " "
                 << phone << " "
                 << balance << " "
                 << password << "\n";
            file.close();
        }
    }
};

// NEW: View all accounts
void viewAllAccounts(){
    cout << CYAN << "\n=====================================" << RESET << endl;
    cout << CYAN << "          ALL ACCOUNTS               " << RESET << endl;
    cout << CYAN << "=====================================" << RESET << endl;

    ifstream file("accounts.txt");
    if(file.is_open()){
        int accNo;
        string name, phone, password;
        double balance;
        int count = 0;

        while(file >> accNo >> name >> phone >> balance >> password){
            count++;
            cout << YELLOW << "\n  Account " << count << RESET << endl;
            cout << "  Account Number : " << accNo << endl;
            cout << "  Name           : " << name << endl;
            cout << "  Phone          : " << phone << endl;
            cout << GREEN << "  Balance        : Rs." << balance << RESET << endl;
            cout << CYAN << "  -----------------------------------" << RESET << endl;
        }
        file.close();

        if(count == 0){
            cout << RED << "  No accounts found!" << RESET << endl;
        } else {
            cout << YELLOW << "\n  Total Accounts: " << count << RESET << endl;
        }
    } else {
        cout << RED << "✗ No accounts file found!" << RESET << endl;
    }
}

void showMainMenu(){
    cout << CYAN << "\n=====================================" << RESET << endl;
    cout << CYAN << "      BANK MANAGEMENT SYSTEM         " << RESET << endl;
    cout << CYAN << "=====================================" << RESET << endl;
    cout << "  1. Create New Account" << endl;
    cout << "  2. Login to Existing Account" << endl;
    cout << "  3. View All Accounts" << endl;
    cout << "  4. Delete Account" << endl;
    cout << "  5. Exit" << endl;
    cout << CYAN << "=====================================" << RESET << endl;
    cout << "Enter Choice: ";
}

void showBankMenu(){
    cout << CYAN << "\n=====================================" << RESET << endl;
    cout << CYAN << "            BANK MENU                " << RESET << endl;
    cout << CYAN << "=====================================" << RESET << endl;
    cout << "  1. Deposit Money" << endl;
    cout << "  2. Withdraw Money" << endl;
    cout << "  3. Check Balance" << endl;
    cout << "  4. Display Account Details" << endl;
    cout << "  5. Exit" << endl;
    cout << CYAN << "=====================================" << RESET << endl;
    cout << "Enter Choice: ";
}

int main(){
    Account acc;
    int choice;

    showMainMenu();
    cin >> choice;

    if(choice == 1){
        acc.createAccount();
        acc.saveToFile();
        cout << GREEN << "\nPlease login to continue..." << RESET << endl;
        if(!acc.login()) return 0;
    } else if(choice == 2){
        if(!acc.login()) return 0;
    } else if(choice == 3){
        viewAllAccounts();
        return 0;
    } else if(choice == 4){
        acc.deleteAccount();
        return 0;
    } else {
        cout << YELLOW << "\nThank you! Goodbye!" << RESET << endl;
        return 0;
    }

    int menuChoice;
    do {
        showBankMenu();
        cin >> menuChoice;

        switch(menuChoice){
            case 1: acc.deposit(); acc.saveToFile(); break;
            case 2: acc.withdraw(); acc.saveToFile(); break;
            case 3: acc.checkBalance(); break;
            case 4: acc.displayAccount(); break;
            case 5:
                cout << YELLOW << "\nThank you! Goodbye!" << RESET << endl;
                break;
            default:
                cout << RED << "✗ Invalid Choice!" << RESET << endl;
        }
    } while(menuChoice != 5);

    return 0;
}