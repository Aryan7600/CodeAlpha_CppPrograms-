/*
 * TASK 1: CGPA Calculator
 * CodeAlpha C++ Programming Internship
 *
 * Logic:
 * 1. Number of courses lo
 * 2. Har course ke liye grade point (0-10 scale) aur credit hours lo
 * 3. Total grade points = grade * credit hours (sab courses ka sum)
 * 4. Total credits = sab credit hours ka sum
 * 5. GPA = Total grade points / Total credits
 * 6. Yahan hum single semester ka CGPA nikal rahe hain (overall CGPA
 *    same formula follow karta hai agar multiple semesters ka data ho)
 */

#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

struct Course {
    string name;
    double grade;   // grade point out of 10
    double credit;  // credit hours
};

int main() {
    int n;
    cout << "===== CGPA Calculator =====\n";
    cout << "Enter number of courses taken: ";
    cin >> n;

    vector<Course> courses(n);
    double totalGradePoints = 0.0;
    double totalCredits = 0.0;

    for (int i = 0; i < n; i++) {
        cout << "\n--- Course " << i + 1 << " ---\n";
        cout << "Enter course name: ";
        cin >> ws; // clear whitespace/newline before getline
        getline(cin, courses[i].name);

        cout << "Enter grade point (0-10 scale): ";
        cin >> courses[i].grade;

        cout << "Enter credit hours: ";
        cin >> courses[i].credit;

        // Validation
        while (courses[i].grade < 0 || courses[i].grade > 10 || courses[i].credit <= 0) {
            cout << "Invalid input! Grade should be 0-10 and credit hours > 0.\n";
            cout << "Re-enter grade point: ";
            cin >> courses[i].grade;
            cout << "Re-enter credit hours: ";
            cin >> courses[i].credit;
        }

        totalGradePoints += courses[i].grade * courses[i].credit;
        totalCredits += courses[i].credit;
    }

    double gpa = totalGradePoints / totalCredits;

    // Display individual course grades
    cout << "\n===== Course-wise Grades =====\n";
    cout << left << setw(20) << "Course" << setw(10) << "Grade" << setw(10) << "Credits" << "\n";
    for (auto &c : courses) {
        cout << left << setw(20) << c.name << setw(10) << c.grade << setw(10) << c.credit << "\n";
    }

    cout << fixed << setprecision(2);
    cout << "\nTotal Credit Hours : " << totalCredits << "\n";
    cout << "Total Grade Points : " << totalGradePoints << "\n";
    cout << "Semester GPA       : " << gpa << "\n";

    // For overall CGPA across multiple semesters, same formula applies
    // if you accumulate totalGradePoints and totalCredits across semesters.
    cout << "Overall CGPA       : " << gpa << "\n";

    return 0;
}
