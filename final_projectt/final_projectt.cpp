#include <iostream>
#include <limits>
#include <string>
#include <fstream>  
using namespace std;

// Forward declaration of Course class
class Course;

class Student {
public:
    string name;
    string roll_num;
    int age;
    string contact;
    Course* enrolledCourses[5];

public:
    // Constructor for Student
    Student(const string& n, const string& roll, int a, const string& c)
        : name(n), roll_num(roll), age(a), contact(c) {
        for (int i = 0; i < 5; ++i) {
            enrolledCourses[i] = nullptr;
        }
    }

    // Getter for roll_num
    string getRollNum() const {
        return roll_num;
    }

    // Function to enroll in a course
    void enroll(Course* course);

    // Function to withdraw from a course
    void withdraw(Course* course);

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
    Student* enrolledStudents[5];
    bool attendance[5];  // Attendance status for each student
    int marks[5];       // Marks for each student

    // Constructor for Course
    Course(const string& c, const string& n, const string& instr, int cred, int cap)
        : code(c), name(n), instructor(instr), credits(cred), capacity(cap) {
        for (int i = 0; i < 5; ++i) {
            enrolledStudents[i] = nullptr;
            attendance[i] = false;
            marks[i] = -1;
        }
    }

    // Other member functions...

    void enrollStudent(Student* student);

    void withdrawStudent(Student* student);

    void markAttendance(Student* student);

    void recordMarks(Student* student);

    void displayEnrolledStudents(int studentIndex) const;
};

// Continuing from the previous code...

void Student::enroll(Course* course) {
    for (int i = 0; i < 5; ++i) {
        if (enrolledCourses[i] == nullptr) {
            enrolledCourses[i] = course;
            return;
        }
    }
    cout << "Student cannot enroll in more courses. Maximum limit reached." << endl;
}

void Student::withdraw(Course* course) {
    for (int i = 0; i < 5; ++i) {
        if (enrolledCourses[i] == course) {
            enrolledCourses[i] = nullptr;
            cout << "Course withdrawn successfully." << endl;
            return;
        }
    }
    cout << "Student is not enrolled in this course." << endl;
}

void Student::displayInfo() const {
    cout << "Name: " << name << endl;
    cout << "Roll Number: " << roll_num << endl;
    cout << "Age: " << age << endl;
    cout << "Contact: " << contact << endl;

    cout << "Enrolled Courses:" << endl;
    for (int i = 0; i < 5; ++i) {
        if (enrolledCourses[i] != nullptr) {
            cout << "   " << enrolledCourses[i]->name << endl;
        }
    }
}

void Course::enrollStudent(Student* student) {
    for (int i = 0; i < 5; ++i) {
        if (enrolledStudents[i] == nullptr) {
            enrolledStudents[i] = student;
            student->enroll(this); // Enroll the student in the course
            cout << "Student enrolled in the course successfully." << endl;
            return;
        }
    }
    cout << "Course already at full capacity." << endl;
}

void Course::withdrawStudent(Student* student) {
    for (int i = 0; i < 5; ++i) {
        if (enrolledStudents[i] == student) {
            // Withdraw the student from the course
            enrolledStudents[i] = nullptr;
            attendance[i] = false;  // Reset attendance
            marks[i] = -1;          // Reset marks
            cout << "Student withdrawn from the course successfully." << endl;
            return;
        }
    }
    cout << "Student is not enrolled in this course." << endl;
}

void Course::markAttendance(Student* student) {
    for (int i = 0; i < 5; ++i) {
        if (enrolledStudents[i] == student) {
            attendance[i] = true;
            cout << "Attendance marked for student in course." << endl;
            return;
        }
    }
    cout << "Student not enrolled in this course." << endl;
}

void Course::recordMarks(Student* student) {
    for (int i = 0; i < 5; ++i) {
        if (enrolledStudents[i] == student) {
            cout << "Enter marks for the student: ";
            cin >> marks[i];
            cout << "Marks recorded for student in course." << endl;
            return;
        }
    }
    cout << "Student not enrolled in this course." << endl;
}

// The rest of the code remains unchanged...


void Course::displayEnrolledStudents(int studentIndex) const {
    for (int i = 0; i < 5; ++i) {
        if (enrolledStudents[i] != nullptr && i == studentIndex) {
            cout << "   " << enrolledStudents[i]->getRollNum() << " - ";

            // Check if the student has withdrawn from the course
            if (enrolledStudents[i]->enrolledCourses[studentIndex] != nullptr &&
                enrolledStudents[i]->enrolledCourses[studentIndex]->code == code) {
                cout << "Withdrawn" << endl;
            }
            else {
                // Display attendance status
                cout << "Attendance: " << (attendance[i] ? "Present" : "NA") << ", ";

                // Display marks status
                cout << "Marks: " << (marks[i] != -1 ? to_string(marks[i]) : "NA") << endl;
            }
        }
    }
}

class System {
private:
    Student* students[100];
    Course* courses[5];
    ofstream outputFile;  // File stream for writing

public:
    System() {
        for (int i = 0; i < 100; i++) {
            students[i] = nullptr;
        }

        for (int i = 0; i < 5; i++) {
            courses[i] = nullptr;
        }
    }

    // Open a text file for writing
    void openOutputFile(const string& filename) {
        outputFile.open(filename);
        if (!outputFile.is_open()) {
            cerr << "Error opening file: " << filename << endl;
        }
    }

    // Close the text file
    void closeOutputFile() {
        outputFile.close();
    }

    void displayMainMenu() {
        cout << "Main Menu" << endl;
        cout << "1- Enroll a student" << endl;
        cout << "2- Course Registration" << endl;
        cout << "3- Mark Attendance" << endl;
        cout << "4- Record Marks" << endl;
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
                students[i] = new Student(name, roll_num, age, contact);
                cout << "Student added successfully." << endl;
                displayStudentInfo(i);
                break;
            }
        }
    }

    void registerCourse() {
        string courseCode, courseName, courseins;

        cout << "Enter course code: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, courseCode);

        cout << "Enter course name: ";
        getline(cin, courseName);

        cout << "Enter instructor name: ";
        getline(cin, courseins);

        // Check if the course code already exists
        for (int i = 0; i < 5; ++i) {
            if (courses[i] != nullptr && courses[i]->code == courseCode) {
                cout << "Course with the same code already exists. Please choose a different code." << endl;
                return;
            }
        }

        // Find an empty slot to register the course
        for (int i = 0; i < 5; ++i) {
            if (courses[i] == nullptr) {
                int studentIndex;
                cout << "Enter the index of the student to enroll in the course: ";
                cin >> studentIndex;

                if (studentIndex >= 0 && studentIndex < 100 && students[studentIndex] != nullptr) {
                    courses[i] = new Course(courseCode, courseName, courseins, 3, 5);
                    courses[i]->enrollStudent(students[studentIndex]);
                    cout << "Course registered successfully." << endl;
                }
                else {
                    cout << "Invalid student index." << endl;
                }

                displayAllCourses(studentIndex);
                return;
            }
        }

        cout << "Cannot register more courses. Maximum limit reached." << endl;
    }

    void markAttendance() {
        string roll, courseCode;

        cout << "Enter student roll number for attendance: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, roll);

        for (int i = 0; i < 100; i++) {
            if (students[i] != nullptr && students[i]->getRollNum() == roll) {
                students[i]->displayInfo();
                cout << "Enter course code for attendance: ";
                getline(cin, courseCode);

                for (int j = 0; j < 5; j++) {
                    if (courses[j] != nullptr && courses[j]->code == courseCode) {
                        courses[j]->markAttendance(students[i]);
                        displayStudentInfo(i);
                        return;
                    }
                }

                cout << "Course not found with the given code." << endl;
                return;
            }
        }

        cout << "Student not found with the given roll number." << endl;
    }

    void recordMarks() {
        string roll, courseCode;

        cout << "Enter student roll number for recording marks: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, roll);

        for (int i = 0; i < 100; i++) {
            if (students[i] != nullptr && students[i]->getRollNum() == roll) {
                students[i]->displayInfo();
                cout << "Enter course code for recording marks: ";
                getline(cin, courseCode);

                for (int j = 0; j < 5; j++) {
                    if (courses[j] != nullptr && courses[j]->code == courseCode) {
                        courses[j]->recordMarks(students[i]);
                        displayStudentInfo(i);
                        return;
                    }
                }

                cout << "Course not found with the given code." << endl;
                return;
            }
        }

        cout << "Student not found with the given roll number." << endl;
    }

    void withdrawFromCourse() {
        string roll, courseCode;

        cout << "Enter student roll number for course withdrawal: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, roll);

        for (int i = 0; i < 100; i++) {
            if (students[i] != nullptr && students[i]->getRollNum() == roll) {
                students[i]->displayInfo();
                cout << "Enter course code for withdrawal: ";
                getline(cin, courseCode);

                for (int j = 0; j < 5; j++) {
                    if (courses[j] != nullptr && courses[j]->code == courseCode) {
                        courses[j]->enrolledStudents[i] = nullptr;
                        cout << "Student with roll number " << roll << " withdrawn from the course." << endl;
                        displayStudentInfo(i);
                        return;
                    }
                }

                cout << "Course not found with the given code." << endl;
                return;
            }
        }

        cout << "Student not found with the given roll number." << endl;
    }

    void displayAllStudents() {
        cout << "List of all students:" << endl;
        for (int i = 0; i < 100; ++i) {
            if (students[i] != nullptr) {
                students[i]->displayInfo();
                cout << "---------------------" << endl;
            }
        }
    }
    void displayStudentInfo(int studentIndex) {
        if (students[studentIndex] != nullptr) {
            openOutputFile("StudentInfo.txt");

            students[studentIndex]->displayInfo();

            outputFile << "Enrolled Courses:" << endl;
            for (int i = 0; i < 5; ++i) {
                if (students[studentIndex]->enrolledCourses[i] != nullptr) {
                    Course* course = students[studentIndex]->enrolledCourses[i];
                    outputFile << "   Course Code: " << course->code << endl;
                    outputFile << "   Course Name: " << course->name << endl;
                    outputFile << "   Instructor: " << course->instructor << endl;
                    outputFile << "   Credits: " << course->credits << endl;
                    outputFile << "   Capacity: " << course->capacity << endl;

                    if (course->enrolledStudents[studentIndex] == nullptr) {
                        outputFile << "   Status: Withdrawn" << endl;
                    }
                    else {
                        outputFile << "   Attendance: " << (course->attendance[studentIndex] ? "Present" : "NA") << endl;

                        if (course->marks[studentIndex] != -1) {
                            outputFile << "   Marks: " << course->marks[studentIndex] << endl;
                        }
                        else {
                            outputFile << "   Marks: NA" << endl;
                        }
                    }

                    outputFile << "---------------------" << endl;
                }
            }

            closeOutputFile();
        }
        else {
            cout << "Student not found." << endl;
        }
    }

    void displayAllCourses(int studentIndex) {
        openOutputFile("CourseInfo.txt");

        for (int i = 0; i < 5; ++i) {
            if (courses[i] != nullptr) {
                outputFile << "Course Code: " << courses[i]->code << endl;
                outputFile << "Course Name: " << courses[i]->name << endl;
                outputFile << "Instructor: " << courses[i]->instructor << endl;
                outputFile << "Credits: " << courses[i]->credits << endl;
                outputFile << "Capacity: " << courses[i]->capacity << endl;

                courses[i]->displayEnrolledStudents(studentIndex);

                outputFile << "---------------------" << endl;
            }
        }

        closeOutputFile();
    }
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

