#include <iostream>
#include <limits>
#include<string>
using namespace std;

// Forward declaration of Course class
class Course;

class Student {
private:
    string name;
    string roll_num;
    int age;
    string contact;
    Course* enrolledCourse;

public:
    // Constructor for Student
    Student(const string& n, const string& roll, int a, const string& c, Course* course)
        : name(n), roll_num(roll), age(a), contact(c), enrolledCourse(course) {}

    // Getter for roll_num
    string getRollNum() const {
        return roll_num;
    }

    void enroll(Course* course) {
        enrolledCourse = course;
    }

    // Declaration of displayInfo function
    void displayInfo() const;
};

class Course {
public:
    string code;
    string name;
    string instructor;
    int credits;
    int capacity;
    Student* enrolledStudent;

    // Constructor for Course
    Course(const string& c, const string& n, const string& instr, int cred, int cap, Student* student)
        : code(c), name(n), instructor(instr), credits(cred), capacity(cap), enrolledStudent(student) {}

    // Other member functions...


    void enrollStudent(Student* student) {
        if (enrolledStudent == nullptr) {
            enrolledStudent = student;
            student->enroll(this);
            cout << "Student enrolled in the course successfully." << endl;
        }
        else {
            cout << "Course already at full capacity." << endl;
        }
    }

    void withdrawStudent(Student* student) {
        if (enrolledStudent == student) {
            enrolledStudent = nullptr;
            student->enroll(nullptr);
            cout << "Student withdrawn from the course successfully." << endl;
        }
        else {
            cout << "Student not enrolled in this course." << endl;
        }
    }

    void displayEnrolledStudent() {
        if (enrolledStudent != nullptr) {
            enrolledStudent->displayInfo();
        }
        else {
            cout << "No student enrolled in this course." << endl;
        }
    }
};

void Student::displayInfo() const {
    cout << "Name: " << name << endl;
    cout << "Roll Number: " << roll_num << endl;
    cout << "Age: " << age << endl;
    cout << "Contact: " << contact << endl;
    cout << "Enrolled Course: " << (enrolledCourse ? enrolledCourse->name : "None") << endl;
}

class System {
private:
    Student* students[100]; // Assuming a maximum of 100 students
    Course* courses[5];    // Assuming a maximum of 5 cours

public:

    System()
    {
        for (int i = 0; i < 100;i++)
        {
            students[i] = nullptr;
        }

        for (int i = 0; i < 5;i++)
        {
            courses[i] = nullptr;
        }
    }
    void displayMainMenu() {
        cout << "Main Menu" << endl;
        cout << "1- Enroll a student" << endl;
        cout << "2- Course Registration" << endl;
        cout << "3- Attendance" << endl;
        cout << "4- Marks" << endl;
        cout << "5- Course Withdraw" << endl;
        cout << "6- Exit" << endl;
        cout << "Press 1 to 6 to select an option: ";
    }

    void processOption(int option) {
        switch (option) {
        case 1:
            addStudent();
            break;
        case 2:
            registerCourse();
            break;
        case 3:
            markAttendance();
            break;
        case 4:
            recordMarks();
            break;
        case 5:
            withdrawFromCourse();
            break;
        case 6:
            cout << "Exiting the program." << endl;
            break;
        default:
            cout << "Invalid option. Please select a valid option." << endl;
        }
    }

private:
    void addStudent() {
        string name, roll_num, contact;
        int age;

        cout << "Enter student name: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, name);

        cout << "Enter student roll number: ";
        getline(cin, roll_num);

        cout << "Enter student age: ";
        cin >> age;

        cout << "Enter student contact: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, contact);

        for (int i = 0; i < 100; ++i) {

            if (students[i] == nullptr) {
                students[i] = new Student(name, roll_num, age, contact, nullptr);
                cout << "Student added successfully." << endl;
                break;
            }
        }

        for (int i = 0; i < 100; ++i) {

            if (students[i] != nullptr) {
                cout << "   Displaying student information  :  " << endl;
                students[i]->displayInfo();


            }
        }
    }
    void registerCourse() {
        string courseCode, courseName, courseins;
        static int  index = 0;
        cout << "Enter course code: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, courseCode);

        cout << "Enter course name: ";
        getline(cin, courseName);

        cout << "Enter instructor name : ";
        getline(cin, courseins);

        // Check if the course code already exists  
        //is ko sahi karna
        for (int i = 0; i < 5; ++i) {
            if (courses[i] != nullptr && courses[i]->code == courseCode) {
                cout << "Course with the same code already exists. Please choose a different code." << endl;
                return;
            }
        }

        // Find an empty slot to register the course

        for (int i = 0; i < 5; ++i) {
            if (courses[i] == nullptr) {
                courses[i] = new Course(courseCode, courseName, courseins, 3, 1, students[index]);
                students[index]->enroll(courses[i]);

                cout << "Course registered successfully." << endl;

            }
        }

        index++;


        cout << "Cannot register more courses. Maximum limit reached." << endl;
    }

    // Inside the System class definition:

    void markAttendance() {
        string roll;
        cout << "Enter student roll number for attendance: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, roll);

        // Find the student with the given roll number
        for (int i = 0; i < 100; i++) {
            if (students[i] != nullptr && students[i]->getRollNum() == roll) {
                // Implement the logic to mark attendance for the found student
                cout << "Attendance marked for student with roll number " << roll << "." << endl;
                return;
            }
        }

        cout << "Student not found with the given roll number." << endl;
    }

    void recordMarks() {
        string roll;
        cout << "Enter student roll number for recording marks: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, roll);

        // Find the student with the given roll number
        for (int i = 0; i < 100; i++) {
            if (students[i] != nullptr && students[i]->getRollNum() == roll) {
                // Implement the logic to record marks for the found student
                cout << "Marks recorded for student with roll number " << roll << "." << endl;
                return;
            }
        }

        cout << "Student not found with the given roll number." << endl;
    }

    void withdrawFromCourse() {
        string roll;
        cout << "Enter student roll number for course withdrawal: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, roll);

        // Find the student with the given roll number
        for (int i = 0; i < 100; i++) {
            if (students[i] != nullptr && students[i]->getRollNum() == roll) {
                // Implement the logic to withdraw the student from a course
                cout << "Student with roll number " << roll << " withdrawn from the course." << endl;
                return;
            }
        }

        cout << "Student not found with the given roll number." << endl;
    }

    // Rest of the System class definition...

};

int main() {
    System system;
    int option;

    do {
        system.displayMainMenu();
        cin >> option;
        system.processOption(option);
    } while (option != 6);

    return 0;
}