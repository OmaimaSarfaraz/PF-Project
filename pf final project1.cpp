#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// User authentication
struct User {
    string username;
    string password;
};

User users[] = { {"admin", "admin123"} };

bool login() {
    string username, password;
    cout << "\n--- Login ---\n";
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    for (int i = 0; i < sizeof(users) / sizeof(users[0]); ++i) {
        if (users[i].username == username && users[i].password == password) {
            cout << "Login successful!\n";
            return true;
        }
    }
    cout << "Invalid username or password.\n";
    return false;
}
struct Student {
    int id;
    string name;
    string department;
};

// Course data
struct Course {
    int courseId;
    string courseName;
    string instructor;
};

// Attendance data
struct Attendance {
    int studentId;
    bool isPresent;  // true for present, false for absent
};

Student students[100];
Course courses[100];
Attendance attendance[100][100];  // Assuming a max of 100 students and 100 courses

int studentCount = 0;
int courseCount = 0;

void displayStudent(const Student& student) {
    cout << "ID: " << student.id << ", Name: " << student.name << ", Department: " << student.department << endl;
}

void displayCourse(const Course& course) {
    cout << "Course ID: " << course.courseId << ", Course Name: " << course.courseName << ", Instructor: " << course.instructor << endl;
}
void saveStudentsToFile() {
    ofstream outFile("students.txt");
    if (!outFile) {
        cout << "Error: Unable to save students to file.\n";
        return;
    }
    for (int i = 0; i < studentCount; ++i) {
        outFile << students[i].id << "\n" << students[i].name << "\n" << students[i].department << "\n";
    }
    outFile.close();
}

void loadStudentsFromFile() {
    ifstream inFile("students.txt");
    if (!inFile) {
        cout << "Note: No existing student data found. Starting fresh.\n";
        return;
    }
    studentCount = 0;
    while (inFile) {
        Student s;
        inFile >> s.id;
        inFile.ignore();  // Ignore newline after reading id
        if (inFile.eof()) break;
        getline(inFile, s.name);
        getline(inFile, s.department);
        students[studentCount++] = s;
    }
    inFile.close();
}

