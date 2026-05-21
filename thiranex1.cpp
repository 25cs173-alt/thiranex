#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdio>
using namespace std;
class Student {
private:
    int id;
    char name[50];
    int age;
    char course[50];
    float marks;
    char grade;
public:
    void calculateGrade() {
        if (marks >= 90)
            grade = 'A';
        else if (marks >= 75)
            grade = 'B';
        else if (marks >= 50)
            grade = 'C';
        else
            grade = 'F';
    }
    void addStudent() {
        cout << "\nEnter Student ID: ";
        cin >> id;

        cout << "Enter Name: ";
        cin.ignore();
        cin.getline(name, 50);

        cout << "Enter Age: ";
        cin >> age;

        cout << "Enter Course: ";
        cin.ignore();
        cin.getline(course, 50);

        cout << "Enter Marks: ";
        cin >> marks;

        calculateGrade();
    }

    void displayStudent() const {
        cout << left << setw(10) << id
             << setw(20) << name
             << setw(10) << age
             << setw(20) << course
             << setw(10) << marks
             << setw(10) << grade << endl;
    }

    int getId() const {
        return id;
    }

    void updateStudent() {
        cout << "\nEnter New Name: ";
        cin.ignore();
        cin.getline(name, 50);

        cout << "Enter New Age: ";
        cin >> age;

        cout << "Enter New Course: ";
        cin.ignore();
        cin.getline(course, 50);

        cout << "Enter New Marks: ";
        cin >> marks;

        calculateGrade();
    }
};
void addRecord() {
    Student s;
    ofstream file("students.dat", ios::binary | ios::app);

    s.addStudent();
    file.write((char*)&s, sizeof(s));

    file.close();
    cout << "\nStudent Record Added Successfully!\n";
}
void displayRecords() {
    Student s;
    ifstream file("students.dat", ios::binary);

    if (!file) {
        cout << "\nNo Records Found!\n";
        return;
    }

    cout << "\n================ STUDENT RECORDS ================\n";
    cout << left << setw(10) << "ID"
         << setw(20) << "Name"
         << setw(10) << "Age"
         << setw(20) << "Course"
         << setw(10) << "Marks"
         << setw(10) << "Grade" << endl;

    while (file.read((char*)&s, sizeof(s))) {
        s.displayStudent();
    }

    file.close();
}
void searchRecord() {
    Student s;
    int searchId;
    bool found = false;

    ifstream file("students.dat", ios::binary);

    cout << "\nEnter Student ID to Search: ";
    cin >> searchId;

    while (file.read((char*)&s, sizeof(s))) {
        if (s.getId() == searchId) {
            cout << "\nStudent Found:\n";
            cout << left << setw(10) << "ID"
                 << setw(20) << "Name"
                 << setw(10) << "Age"
                 << setw(20) << "Course"
                 << setw(10) << "Marks"
                 << setw(10) << "Grade" << endl;

            s.displayStudent();
            found = true;
            break;
        }
    }

    file.close();

    if (!found)
        cout << "\nStudent Record Not Found!\n";
}
    void updateRecord() {
    Student s;
    int searchId;
    bool found = false;

    fstream file("students.dat", ios::binary | ios::in | ios::out);

    cout << "\nEnter Student ID to Update: ";
    cin >> searchId;

    while (file.read((char*)&s, sizeof(s))) {
        if (s.getId() == searchId) {
            cout << "\nExisting Record Found.\n";
            s.updateStudent();

            int pos = file.tellg();
            file.seekp(pos - sizeof(s));

            file.write((char*)&s, sizeof(s));

            cout << "\nRecord Updated Successfully!\n";
            found = true;
            break;
        }
    }

    file.close();

    if (!found)
        cout << "\nStudent Record Not Found!\n";
}
void deleteRecord() {
    Student s;
    int searchId;
    bool found = false;

    ifstream file("students.dat", ios::binary);
    ofstream temp("temp.dat", ios::binary);

    cout << "\nEnter Student ID to Delete: ";
    cin >> searchId;

    while (file.read((char*)&s, sizeof(s))) {
        if (s.getId() == searchId) {
            found = true;
        } else {
            temp.write((char*)&s, sizeof(s));
        }
    }

    file.close();
    temp.close();

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found)
        cout << "\nRecord Deleted Successfully!\n";
    else
        cout << "\nStudent Record Not Found!\n";
}
int main() {
    int choice;

    do {
        cout << "\n====================================";
        cout << "\n   STUDENT MANAGEMENT SYSTEM";
        cout << "\n====================================";
        cout << "\n1. Add Student";
        cout << "\n2. Display Students";
        cout << "\n3. Search Student";
        cout << "\n4. Update Student";
        cout << "\n5. Delete Student";
        cout << "\n6. Exit";
        cout << "\n\nEnter Your Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addRecord();
                break;

            case 2:
                displayRecords();
                break;

            case 3:
                searchRecord();
                break;

            case 4:
                updateRecord();
                break;

            case 5:
                deleteRecord();
                break;

            case 6:
                cout << "\nExiting Program...\n";
                break;

            default:
                cout << "\nInvalid Choice! Try Again.\n";
        }

    } while (choice != 6);

    return 0;
}