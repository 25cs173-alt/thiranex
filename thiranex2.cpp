#include <iostream>
#include <fstream>
#include <cstdio>
using namespace std;

class Account
{
    int accNo;
    char name[50];
    char type;
    float balance;

public:
    void createAccount();
    void showAccount() const;
    void modify();
    void deposit(float);
    void withdraw(float);
    void report() const;
    int returnAccNo() const;
    float returnBalance() const;
};

void Account::createAccount()
{
    cout << "\nEnter Account Number : ";
    cin >> accNo;

    cout << "Enter Account Holder Name : ";
    cin.ignore();
    cin.getline(name, 50);

    cout << "Enter Type of Account (S/C) : ";
    cin >> type;

    cout << "Enter Initial Amount : ";
    cin >> balance;

    cout << "\nAccount Created Successfully...";
}

void Account::showAccount() const
{
    cout << "\nAccount Number : " << accNo;
    cout << "\nAccount Holder Name : " << name;
    cout << "\nType of Account : " << type;
    cout << "\nBalance Amount : " << balance;
}

void Account::modify()
{
    cout << "\nModify Account Holder Name : ";
    cin.ignore();
    cin.getline(name, 50);

    cout << "Modify Type of Account : ";
    cin >> type;

    cout << "Modify Balance Amount : ";
    cin >> balance;
}

void Account::deposit(float amt)
{
    balance += amt;
}

void Account::withdraw(float amt)
{
    balance -= amt;
}

void Account::report() const
{
    cout << accNo << "\t" << name << "\t" << type
         << "\t" << balance << endl;
}

int Account::returnAccNo() const
{
    return accNo;
}

float Account::returnBalance() const
{
    return balance;
}
void writeAccount()
{
    Account ac;
    ofstream outFile;

    outFile.open("account.dat", ios::binary | ios::app);

    ac.createAccount();

    outFile.write(reinterpret_cast<char *>(&ac), sizeof(Account));

    outFile.close();
}
void displayAll()
{
    Account ac;
    ifstream inFile;

    inFile.open("account.dat", ios::binary);

    cout << "\n\nACCOUNT HOLDER LIST\n";
    cout << "====================================\n";
    cout << "A/c no.\tNAME\tTYPE\tBALANCE\n";
    cout << "====================================\n";

    while (inFile.read(reinterpret_cast<char *>(&ac), sizeof(Account)))
    {
        ac.report();
    }

    inFile.close();
}
void displaySp(int n)
{
    Account ac;
    bool found = false;

    ifstream inFile;
    inFile.open("account.dat", ios::binary);

    while (inFile.read(reinterpret_cast<char *>(&ac), sizeof(Account)))
    {
        if (ac.returnAccNo() == n)
        {
            ac.showAccount();
            found = true;
        }
    }

    inFile.close();

    if (!found)
        cout << "\nAccount number does not exist";
}
int main()
{
    int choice, num;

    do
    {
        cout << "\n\n===== BANK MANAGEMENT SYSTEM =====";
        cout << "\n1. Create Account";
        cout << "\n2. Display All Accounts";
        cout << "\n3. Search Account";
        cout << "\n4. Exit";
        cout << "\nEnter Your Choice : ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            writeAccount();
            break;

        case 2:
            displayAll();
            break;

        case 3:
            cout << "\nEnter Account Number : ";
            cin >> num;
            displaySp(num);
            break;

        case 4:
            cout << "\nThank You...";
            break;

        default:
            cout << "\nInvalid Choice";
        }

    } while (choice != 4);

    return 0;
}