

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

struct student {
    string name;
    int id = 0;
    int* tests = nullptr;   // dynamically allocated per student
    double avg = 0.0;
    char letter = 'F';
};

char letterGrade(double avg) {
    if (avg >= 90.0) return 'A';
    if (avg >= 80.0) return 'B';
    if (avg >= 70.0) return 'C';
    if (avg >= 60.0) return 'D';
    return 'F';
}


student* getData(ifstream& file, int& studentCnt, int& testsCnt) {
    file >> studentCnt >> testsCnt;

    student* students = new student[studentCnt];

    for (int i = 0; i < studentCnt; i++) {
        file >> students[i].name >> students[i].id;

        students[i].tests = new int[testsCnt];
        for (int t = 0; t < testsCnt; t++) {
            file >> students[i].tests[t];
        }
    }

    return students;
}



void calcAverage(student students[], int studentCnt, int testsCnt) {
    for (int i = 0; i < studentCnt; i++) {
        int sum = 0;
        for (int t = 0; t < testsCnt; t++) {
            sum += students[i].tests[t];
        }

        students[i].avg = static_cast<double>(sum) / testsCnt;
        students[i].letter = letterGrade(students[i].avg);
    }
}


void printReport(const student students[], int studentCnt) {
    cout << left
         << setw(12) << "Student"
         << setw(8)  << "ID"
         << setw(10) << "Score"
         << "Grade" << "\n\n";

    cout << fixed << setprecision(1);

    for (int i = 0; i < studentCnt; i++) {
        cout << left
             << setw(12) << students[i].name
             << setw(8)  << students[i].id
             << setw(10) << students[i].avg
             << students[i].letter << "\n";
    }
}

int main() {
    const string filename = "student_data.txt";  
    ifstream file(filename);

    if (!file) {
        cerr << "Error: Could not open '" << filename << "'.\n";
        return 1;
    }

    int studentCnt = 0, testsCnt = 0;

    student* students = getData(file, studentCnt, testsCnt);
    file.close();

    calcAverage(students, studentCnt, testsCnt);
    printReport(students, studentCnt);

    // Free dynamic memory:
    // 1) delete each student's test array
    for (int i = 0; i < studentCnt; i++) {
        delete[] students[i].tests;
        students[i].tests = nullptr;
    }
    // 2) delete the student array
    delete[] students;
    students = nullptr;

    return 0;
}
