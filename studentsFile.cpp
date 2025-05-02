#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Student {
    int roll;
    string name, division, address;
};

void addStudent() {
    Student s;
    cout << "Enter Roll No: ";
    cin >> s.roll;
    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, s.name);
    cout << "Enter Division: ";
    getline(cin, s.division);
    cout << "Enter Address: ";
    getline(cin, s.address);

    ofstream fout("students.txt", ios::app);
    fout << s.roll << "," << s.name << "," << s.division << "," << s.address << "\n";
    fout.close();
    cout << "Student added.\n";
}

void displayStudent(int rollNo) {
    ifstream fin("students.txt");
    string line;
    bool found = false;

    while (getline(fin, line)) {
        int r;
        string name, div, addr;
        size_t pos1 = line.find(','), pos2 = line.find(',', pos1 + 1), pos3 = line.find(',', pos2 + 1);
        r = stoi(line.substr(0, pos1));
        name = line.substr(pos1 + 1, pos2 - pos1 - 1);
        div = line.substr(pos2 + 1, pos3 - pos2 - 1);
        addr = line.substr(pos3 + 1);

        if (r == rollNo) {
            cout << "Roll: " << r << "\nName: " << name << "\nDivision: " << div << "\nAddress: " << addr << endl;
            found = true;
            break;
        }
    }
    fin.close();

    if (!found) cout << "Student not found.\n";
}

void deleteStudent(int rollNo) {
    ifstream fin("students.txt");
    ofstream fout("temp.txt");

    string line;
    bool deleted = false;

    while (getline(fin, line)) {
        int r = stoi(line.substr(0, line.find(',')));
        if (r != rollNo)
            fout << line << "\n";
        else
            deleted = true;
    }

    fin.close();
    fout.close();

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (deleted)
        cout << "Student deleted.\n";
    else
        cout << "Student not found.\n";
}

int main() {
    int choice, roll;

    while (true) {
        cout << "\n1. Add Student\n2. Display Student\n3. Delete Student\n4. Exit\nEnter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addStudent(); break;
            case 2:
                cout << "Enter Roll No: ";
                cin >> roll;
                displayStudent(roll);
                break;
            case 3:
                cout << "Enter Roll No: ";
                cin >> roll;
                deleteStudent(roll);
                break;
            case 4: return 0;
            default: cout << "Invalid choice.\n";
        }
    }
}
