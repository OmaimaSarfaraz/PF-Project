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
void saveCoursesToFile() {
    ofstream outFile("courses.txt");
    if (!outFile) {
        cout << "Error: Unable to save courses to file.\n";
        return;
    }
    for (int i = 0; i < courseCount; ++i) {
        outFile << courses[i].courseId << "\n" << courses[i].courseName << "\n" << courses[i].instructor << "\n";
    }
    outFile.close();
}

void loadCoursesFromFile() {
    ifstream inFile("courses.txt");
    if (!inFile) {
        cout << "Note: No existing course data found. Starting fresh.\n";
        return;
    }
    courseCount = 0;
    while (inFile) {
        Course c;
        inFile >> c.courseId;
        inFile.ignore();  // Ignore newline after reading courseId
        if (inFile.eof()) break;
        getline(inFile, c.courseName);
        getline(inFile, c.instructor);
        courses[courseCount++] = c;
    }
    inFile.close();
}

void markAttendance() {
    int courseId, studentId;
    bool isPresent;

    cout << "Enter course ID to mark attendance: ";
    cin >> courseId;
    if (cin.fail()) {  // Check for invalid input
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid course ID. Please enter a valid number.\n";
        return;
    }

    bool courseFound = false;
    for (int i = 0; i < courseCount; ++i) {
        if (courses[i].courseId == courseId) {
            courseFound = true;
            break;
        }
    }
    if (!courseFound) {
        cout << "Invalid course ID.\n";
        return;
    }

    cout << "Enter student ID to mark attendance: ";
    cin >> studentId;
    if (cin.fail()) {  // Check for invalid input
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid student ID. Please enter a valid number.\n";
        return;
    }

    bool studentFound = false;
    for (int i = 0; i < studentCount; ++i) {
        if (students[i].id == studentId) {
            studentFound = true;
            break;
        }
    }
    if (!studentFound) {
        cout << "Invalid student ID.\n";
        return;
    }

    cout << "Enter attendance status (1 for present, 0 for absent): ";
    cin >> isPresent;
    if (cin.fail()) {  // Check for invalid input
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input. Please enter 1 or 0.\n";
        return;
    }

    for (int i = 0; i < studentCount; ++i) {
        if (students[i].id == studentId) {
            attendance[courseId][i].studentId = studentId;
            attendance[courseId][i].isPresent = isPresent;
            cout << "Attendance for student " << students[i].name << " has been marked as "
                 << (isPresent ? "Present" : "Absent") << ".\n";
            break;
        }
    }
}

void viewAttendance() {
    int courseId;

    cout << "Enter course ID to view attendance: ";
    cin >> courseId;
    if (cin.fail()) {  // Check for invalid input
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid course ID. Please enter a valid number.\n";
        return;
    }

    bool courseFound = false;
    for (int i = 0; i < courseCount; ++i) {
        if (courses[i].courseId == courseId) {
            courseFound = true;
            break;
        }
    }
    if (!courseFound) {
        cout << "Invalid course ID.\n";
        return;
    }

    cout << "\nAttendance for Course: " << courses[courseId].courseName << "\n";
    bool attendanceFound = false;

    for (int i = 0; i < studentCount; ++i) {
        if (attendance[courseId][i].studentId != 0) {
            cout << students[i].name << " - " << (attendance[courseId][i].isPresent ? "Present" : "Absent") << endl;
            attendanceFound = true;
        }
    }

    if (!attendanceFound) {
        cout << "No attendance records found for this course.\n";
    }
}
int main() {
    loadStudentsFromFile();
    loadCoursesFromFile();

    if (!login()) {
        return 0;
    }

    int choice;
    do {
        cout << "\nUniversity Management System\n";
        cout << "1. Add Student\n";
        cout << "2. View Students\n";
        cout << "3. Add Course\n";
        cout << "4. View Courses\n";
        cout << "5. Mark Attendance\n";
        cout << "6. View Attendance\n";
        cout << "7. Save and Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail()) {  // Check for invalid input
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid choice. Please enter a number.\n";
            continue;
        }

        switch (choice) {
        case 1: {
            int id;
            string name, department;
            cout << "Enter student ID: ";
            cin >> id;
            cin.ignore();
            cout << "Enter student name: ";
            getline(cin, name);
            cout << "Enter student department: ";
            getline(cin, department);
            students[studentCount].id = id;
            students[studentCount].name = name;
            students[studentCount].department = department;
            ++studentCount;
            break;
        }
        case 2: {
            cout << "\nList of Students:\n";
            for (int i = 0; i < studentCount; ++i) {
                displayStudent(students[i]);
            }
            break;
        }
