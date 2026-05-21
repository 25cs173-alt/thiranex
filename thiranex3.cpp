#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

class Book
{
    int bookID;
    char title[50];
    char author[50];
    bool available;

public:
    void addBook();
    void displayBook() const;
    int getBookID() const;
    bool isAvailable() const;
    void issueBook();
    void returnBook();
};

void Book::addBook()
{
    cout << "\nEnter Book ID : ";
    cin >> bookID;

    cin.ignore();

    cout << "Enter Book Title : ";
    cin.getline(title, 50);

    cout << "Enter Author Name : ";
    cin.getline(author, 50);

    available = true;

    cout << "\nBook Added Successfully...\n";
}

void Book::displayBook() const
{
    cout << "\nBook ID : " << bookID;
    cout << "\nTitle : " << title;
    cout << "\nAuthor : " << author;
    cout << "\nAvailability : ";

    if (available)
        cout << "Available";
    else
        cout << "Issued";

    cout << endl;
}

int Book::getBookID() const
{
    return bookID;
}

bool Book::isAvailable() const
{
    return available;
}

void Book::issueBook()
{
    available = false;
}

void Book::returnBook()
{
    available = true;
}
void addBookRecord()
{
    Book bk;

    ofstream outFile("library.dat", ios::binary | ios::app);

    bk.addBook();

    outFile.write(reinterpret_cast<char *>(&bk), sizeof(Book));

    outFile.close();
}
void displayAllBooks()
{
    Book bk;

    ifstream inFile("library.dat", ios::binary);

    cout << "\n========== BOOK LIST ==========\n";

    while (inFile.read(reinterpret_cast<char *>(&bk), sizeof(Book)))
    {
        bk.displayBook();
        cout << "---------------------------\n";
    }

    inFile.close();
}
void searchBook(int id)
{
    Book bk;
    bool found = false;

    ifstream inFile("library.dat", ios::binary);

    while (inFile.read(reinterpret_cast<char *>(&bk), sizeof(Book)))
    {
        if (bk.getBookID() == id)
        {
            bk.displayBook();
            found = true;
        }
    }

    inFile.close();

    if (!found)
    {
        cout << "\nBook not found.\n";
    }
}
void issueBookRecord(int id)
{
    Book bk;
    fstream file("library.dat", ios::binary | ios::in | ios::out);

    while (file.read(reinterpret_cast<char *>(&bk), sizeof(Book)))
    {
        if (bk.getBookID() == id)
        {
            if (bk.isAvailable())
            {
                bk.issueBook();

                int pos = -1 * static_cast<int>(sizeof(Book));

                file.seekp(pos, ios::cur);

                file.write(reinterpret_cast<char *>(&bk), sizeof(Book));

                cout << "\nBook Issued Successfully.\n";
            }
            else
            {
                cout << "\nBook Already Issued.\n";
            }

            file.close();
            return;
        }
    }

    cout << "\nBook not found.\n";

    file.close();
}
void returnBookRecord(int id)
{
    Book bk;
    fstream file("library.dat", ios::binary | ios::in | ios::out);

    while (file.read(reinterpret_cast<char *>(&bk), sizeof(Book)))
    {
        if (bk.getBookID() == id)
        {
            bk.returnBook();

            int pos = -1 * static_cast<int>(sizeof(Book));

            file.seekp(pos, ios::cur);

            file.write(reinterpret_cast<char *>(&bk), sizeof(Book));

            cout << "\nBook Returned Successfully.\n";

            file.close();
            return;
        }
    }

    cout << "\nBook not found.\n";

    file.close();
}
int main()
{
    int choice, id;

    do
    {
        cout << "\n\n===== LIBRARY MANAGEMENT SYSTEM =====";
        cout << "\n1. Add Book";
        cout << "\n2. Display All Books";
        cout << "\n3. Search Book";
        cout << "\n4. Issue Book";
        cout << "\n5. Return Book";
        cout << "\n6. Exit";

        cout << "\n\nEnter Your Choice : ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            addBookRecord();
            break;

        case 2:
            displayAllBooks();
            break;

        case 3:
            cout << "\nEnter Book ID : ";
            cin >> id;
            searchBook(id);
            break;

        case 4:
            cout << "\nEnter Book ID to Issue : ";
            cin >> id;
            issueBookRecord(id);
            break;

        case 5:
            cout << "\nEnter Book ID to Return : ";
            cin >> id;
            returnBookRecord(id);
            break;

        case 6:
            cout << "\nExiting Program...";
            break;

        default:
            cout << "\nInvalid Choice.";
        }

    } while (choice != 6);

    return 0;
}