#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <windows.h>
#include <conio.h>

using namespace std;

struct AttendanceDate {
    string date;
    char status;
    AttendanceDate* next;
};

struct Attendance {
    int studentID;
    string studentName;
    AttendanceDate* dates;
    Attendance* next;
};

struct Student {
    int id;
    string name;
    int year;
    char gender;
    string department;
    Student *next;
};

struct List {
    Student *head;
    Student *tail;
    int n;
};

struct AttendanceList {
    Attendance *head;
    Attendance *tail;
    int n;
    string* dates;
    int dateCount;
};

List* createStudentList() {
    List *myList = new List;
    myList->n = 0;
    myList->head = NULL;
    myList->tail = NULL;
    return myList;
}

AttendanceList* createAttendanceList() {
    AttendanceList *attList = new AttendanceList;
    attList->n = 0;
    attList->head = NULL;
    attList->tail = NULL;
    attList->dates = nullptr;
    attList->dateCount = 0;
    return attList;
}

void saveStudentList(List *myList);
void readStudentList(List *myList);
void SetColor(int color);
void insertStudent(List *myList, int id, string name, int year, char gender, string department);
void updateStudentByID(List *myList, int id);
void deleteStudentByID(List *myList, int id);
void searchStudentByID(List *myList, int id);
void displayStudents(List *myList);
void saveAttendanceList(AttendanceList *attList);
void readAttendanceList(AttendanceList *attList);
void recordAttendanceForStudents(AttendanceList *attList, List *stuList);
void displayAttendance(AttendanceList *attList);
void Menu();
void login_menu();
string passGet();

const int RED = 4, DEFAULT = 7, GREEN = 2;

void SetColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void readStudentList(List *myList) {
    ifstream file("StudentList.csv");
    string line;
    if (!file.is_open()) {
        SetColor(RED);
        cout << "Could not open the file for reading." << endl;
        SetColor(DEFAULT);
        return;
    }
    getline(file, line); // Skip header
    while (getline(file, line)) {
        stringstream ss(line);
        string idStr, name, yearStr, genderStr, department;
        getline(ss, idStr, ',');
        getline(ss, name, ',');
        getline(ss, yearStr, ',');
        getline(ss, genderStr, ',');
        getline(ss, department, ',');
        int id = stoi(idStr);
        int year = stoi(yearStr);
        char gender = genderStr[0];
        insertStudent(myList, id, name, year, gender, department);
    }
    file.close();
}

void saveStudentList(List *myList) {
    ofstream file("StudentList.csv");
    if (!file.is_open()) {
        SetColor(RED);
        cout << "Could not open the file for writing." << endl;
        SetColor(DEFAULT);
        return;
    }

    file << "ID,Name,Year,Gender,Department\n";

    Student* current = myList->head;
    while (current != NULL) {
        file << current->id << ","
             << current->name << ","
             << current->year << ","
             << current->gender << ","
             << current->department << "\n";
        current = current->next;
    }

    file.close();
}

bool studentIDExists(List *myList, int id) {
    Student *current = myList->head;
    while (current != NULL) {
        if (current->id == id) {
            return true;
        }
        current = current->next;
    }
    return false;
}

void insertStudent(List *myList, int id, string name, int year, char gender, string department) {
    if (studentIDExists(myList, id)) {
        SetColor(RED);
        cout << "Student with ID " << id << " already exists. Cannot add duplicate ID." << endl;
        SetColor(DEFAULT);
        return;
    }
    Student* newStudent = new Student;
    newStudent->id = id;
    newStudent->name = name;
    newStudent->year = year;
    newStudent->gender = gender;
    newStudent->department = department;
    newStudent->next = NULL;
    if (myList->n == 0) {
        myList->head = newStudent;
        myList->tail = newStudent;
    } else {
        myList->tail->next = newStudent;
        myList->tail = newStudent;
    }
    myList->n++;

    saveStudentList(myList);
    SetColor(GREEN);
    cout << "Student added successfully." << endl;
    SetColor(DEFAULT);
}

void updateStudentByID(List *myList, int id) {
    Student* current = myList->head;
    bool found = false;
    while (current != NULL) {
        if (current->id == id) {
            cout << "Enter new Name: ";
            cin.ignore();
            getline(cin, current->name);
            cout << "Enter new Gender (M/F): ";
            cin >> current->gender;
            cout << "Enter new Year: ";
            cin >> current->year;
            cout << "Enter new Department: ";
            cin.ignore();
            getline(cin, current->department);
            found = true;
            saveStudentList(myList);
            SetColor(GREEN);
            cout << "Student updated successfully." << endl;
            SetColor(DEFAULT);
            break;
        }
        current = current->next;
    }
    if (!found) {
        SetColor(RED);
        cout << "Student with ID " << id << " not found." << endl;
        SetColor(DEFAULT);
    }
}

void deleteStudentByID(List *myList, int id) {
    Student *current = myList->head;
    Student *prev = NULL;
    bool found = false;
    while (current != NULL) {
        if (current->id == id) {
            if (prev == NULL) {
                myList->head = current->next;
            } else {
                prev->next = current->next;
            }
            if (current == myList->tail) {
                myList->tail = prev;
            }
            delete current;
            saveStudentList(myList);
            SetColor(GREEN);
            cout << "Student deleted successfully." << endl;
            SetColor(DEFAULT);
            found = true;
        }
        prev = current;
        current = current->next;
    }
    if (!found) {
        SetColor(RED);
        cout << "Student with ID " << id << " not found." << endl;
        SetColor(DEFAULT);
    }
}

void searchStudentByID(List *myList, int id) {
    Student *current = myList->head;
    bool found = false;
    while (current != NULL) {
        if (current->id == id) {
            cout << "ID: " << current->id << "\n"
                 << "Name: " << current->name << "\n"
                 << "Year: " << current->year << "\n"
                 << "Gender: " << current->gender << "\n"
                 << "Department: " << current->department << endl;
            found = true;
            break;
        }
        current = current->next;
    }
    if (!found) {
        SetColor(RED);
        cout << "Student with ID " << id << " not found." << endl;
        SetColor(DEFAULT);
    }
}

void displayStudents(List *myList) {
    Student *current = myList->head;
    cout << "\t\tList of Students:\n";
    SetColor(GREEN);
    cout << "ID\t\tName\t\tYear\t\tGender\t\tDepartment" << endl;
    SetColor(DEFAULT);
    while (current != NULL) {
        cout << current->id << "\t\t"
             << current->name << "\t\t"
             << current->year << "\t\t"
             << current->gender << "\t\t"
             << current->department << "\n";
        current = current->next;
    }
}

void saveAttendanceList(AttendanceList *attList) {
    ofstream file("AttendanceList.csv");
    // Write the header row with "StudentID,StudentName" followed by each date
    file << "StudentID,StudentName";
    for (int i = 0; i < attList->dateCount; i++) {
        file << "," << attList->dates[i];
    }
    file << "\n";
    Attendance* current = attList->head;
    // Iterate through each student in the attendance list
    while (current != NULL) {
        file << current->studentID << "," << current->studentName;  
        // Initialize pointer to the dates for the current student
        AttendanceDate* dateNode = current->dates;
        int dateIndex = 0; 
        // Iterate through the attendance dates for the current student
        while (dateNode != NULL) {
            if (dateIndex < attList->dateCount) {
                // Write the attendance status for each date
                file << "," << dateNode->status;
                dateNode = dateNode->next;
                dateIndex++;
            }
        }       
        // Fill remaining dates with empty status if needed
        while (dateIndex < attList->dateCount) {
            file << ",";
            dateIndex++;
        }  
        file << "\n";
        // Move to the next student in the linked list
        current = current->next;
    }
    file.close();
}
void recordAttendance(AttendanceList* attList, int studentID, string studentName, string date, char status) {
    Attendance* currentAtt = attList->head;
     // Loop to find the student with the given studentID
    while (currentAtt != NULL && currentAtt->studentID != studentID) {
        currentAtt = currentAtt->next;
    }
    // If the student is not found, create a new student node
    if (currentAtt == NULL) {
        currentAtt = new Attendance;
        currentAtt->studentID = studentID;
        currentAtt->studentName = studentName;
        currentAtt->dates = NULL; // Initialize dates pointer to nullptr
        currentAtt->next = NULL;  // Initialize next pointer to nullptr
        // Add the new student to the attendance list
        if (attList->head == NULL) {
            // If the list is empty, set the new student as head and tail
            attList->head = currentAtt;
            attList->tail = currentAtt;
        } else {
            // Otherwise, add the new student to the end of the list
            attList->tail->next = currentAtt;
            attList->tail = currentAtt;
        }
        attList->n++;// Increment the student count in the list
    }
    
    // Create a new AttendanceDate node for the attendance date
    AttendanceDate* newDate = new AttendanceDate;
    newDate->date = date;
    newDate->status = status;
    newDate->next = NULL; // Initialize next pointer to nullptr
    
    // Add the new attendance date to the student's list of dates
    if (currentAtt->dates == NULL) {
        // If the student has no dates, set the new date as the first date
        currentAtt->dates = newDate;
    } else {
        // Otherwise, find the last date and add the new date to the end
        AttendanceDate* lastDate = currentAtt->dates;
        while (lastDate->next != NULL) {
            lastDate = lastDate->next;
        }
        lastDate->next = newDate;
    }
}

void readAttendanceList(AttendanceList* attList) {
    ifstream file("AttendanceList.csv");
    string line;
    getline(file, line); // Read header line
    stringstream headerSS(line);
    string header;
    // Skip "StudentID" and "StudentName" columns
    getline(headerSS, header, ','); 
    getline(headerSS, header, ','); 
   // Count dates in the header
    int dateCount = 0;
    while (getline(headerSS, header, ',')) {
        dateCount++;
    }
    // Allocate memory for dates
    attList->dates = new string[dateCount];
    attList->dateCount = dateCount;
    // Store dates in the array
    headerSS.clear();
    headerSS.str(line);
    getline(headerSS, header, ','); // Skip "StudentID"
    getline(headerSS, header, ','); // Skip "StudentName"
    for (int i = 0; i < dateCount; i++) {
        getline(headerSS, attList->dates[i], ',');
    }
    // Read each student's data
    while (getline(file, line)) {
        stringstream ss(line);
        string idStr, name, status;
        // Read student ID and name
        getline(ss, idStr, ',');
        getline(ss, name, ',');
        int studentID = stoi(idStr);
        // Create a new Attendance node for the student
        Attendance* currentAtt = new Attendance;
        currentAtt->studentID = studentID;
        currentAtt->studentName = name;
        currentAtt->dates = nullptr;
        currentAtt->next = nullptr;
        // Add the new node to the linked list
        if (attList->head == nullptr) {
            attList->head = currentAtt;
            attList->tail = currentAtt;
        } else {
            attList->tail->next = currentAtt;
            attList->tail = currentAtt;
        }
        // Read and record attendance status for each date
        for (int i = 0; i < dateCount; i++) {
            if (getline(ss, status, ',')) {
                recordAttendance(attList, studentID, name, attList->dates[i], status[0]);
            }
        }
    }
    file.close();
}
void recordAttendanceForStudents(AttendanceList* attList, List* myList) {
    // Prompt the user to enter a new date
    cout << "Enter date (DD-MM-YYYY): ";
    string date;
    cin >> date;
    // Add the new date to the dates array
    string* newDates = new string[attList->dateCount + 1]; // Allocate memory for the new dates array
    for (int i = 0; i < attList->dateCount; i++) {
        newDates[i] = attList->dates[i]; // Copy old dates to the new array
    }
    newDates[attList->dateCount] = date; // Add the new date
    attList->dates = newDates; // Update with the new dates array
    attList->dateCount++; // Increment the date count
    Student* currentStu = myList->head;
    while (currentStu != NULL) {
        // Prompt for the student's attendance status
        cout << "Enter attendance for " << currentStu->name << " (P/A): ";
        char status;
        cin >> status;
        // Record the attendance
        recordAttendance(attList, currentStu->id, currentStu->name, date, status);    
        currentStu = currentStu->next;   // Move to the next student
    }
    // Save the updated attendance list to a file
    saveAttendanceList(attList);
    SetColor(GREEN);
    cout << "Attendance recorded successfully." << endl;
    SetColor(DEFAULT);
}
void displayAttendance(AttendanceList *attList) {
    Attendance* current = attList->head;
    SetColor(GREEN);
    cout << "\t\tAttendance Records:\n";
    SetColor(DEFAULT);
    while (current != NULL) {
        cout << current->studentID << " " << current->studentName << " "; // print ID,Name
        AttendanceDate* dateNode = current->dates;
         //Initialize counter for present and absent
        int presentCount = 0;
        int absentCount = 0;
        while (dateNode != NULL) {
            if (dateNode->status == 'P') { // if status =P print present
                SetColor(GREEN);
                cout << "Present ";
                presentCount++;
            } else if (dateNode->status == 'A') { // if status =P print absent
                SetColor(RED);
                cout << "Absent ";
                absentCount++;
            }else{
                cout<<" ";
            }
            SetColor(DEFAULT);
            dateNode = dateNode->next;
        }
        cout << "\n";
        cout << "\t\tTotal absent: " << absentCount << endl;
        cout << "\t\tTotal present: " << presentCount << endl;
        cout << "..............................................." << endl;
        current = current->next;
    }
} 
string passGet() {
    string pass; // Variable to store the password
    char ch; // Variable to store the character input

    // Read characters until Enter key (ASCII 13) is pressed
    while ((ch = _getch()) != 13) {
        if (ch == 8) { // Check for Backspace key (ASCII 8)
            if (!pass.empty()) {
                cout << "\b \b"; // Move cursor back, print space, move cursor back again
                pass.pop_back(); // Remove the last character from the password
            }
        } else {
            pass.push_back(ch); // Add the character to the password
            cout << '*'; // Print asterisk instead of the actual character
        }
    }
    cout << endl; // Move to the next line after Enter key is pressed
    return pass; // Return the entered password
}
void login_menu() {
    string username;
    string password;

    while (true) {
        cout << "Enter Username: ";
        cin >> username;
        cout << "Enter password: ";
        password = passGet();

        if (username == "admin" && password == "admin") {
            SetColor(GREEN);
            cout << "\t\tLogin successful!" << endl;
            cout << "\t\tGoing to Menu" << endl;
            SetColor(DEFAULT);
            break;
        } else {
            SetColor(RED);
            cout << "Sorry! Invalid username/password. Please try again." << endl;
            SetColor(DEFAULT);
        }
    }
}

void Menu() {
    SetColor(GREEN);
    cout << "\t\t================================" << endl;
    cout << "\t\t\t     Menu " << endl;
    cout << "\t\t--------------------------------" << endl;
    SetColor(DEFAULT);
    cout << "\t\t     1. Add Student" << endl;
    cout << "\t\t     2. Update Student by ID" << endl;
    cout << "\t\t     3. Delete Student by ID" << endl;
    cout << "\t\t     4. Search Student by ID" << endl;
    cout << "\t\t     5. Display All Students" << endl;
    cout << "\t\t     6. Record Attendance" << endl;
    cout << "\t\t     7. Display Attendance" << endl;
    cout << "\t\t     8. Exit" << endl;
    SetColor(GREEN);
    cout << "\t\t================================" << endl;
    SetColor(DEFAULT);
}

int main() {
    List* studentList = createStudentList();
    AttendanceList* attendanceList = createAttendanceList();
    readStudentList(studentList);
    readAttendanceList(attendanceList);
    SetColor(GREEN);
    cout << "\tWelcome to Student Attendance Management System " << endl;
    cout << "\t     Please Login to access the program." << endl;
    SetColor(DEFAULT);
    login_menu();
    cout << "Loading ";
    for (int j = 0; j < 15; j++) {
        cout << ". ";
        Sleep(300);
    }
    cout << "\n";
    while (true) {
        Menu();
        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            int id, year;
            string name, department;
            char gender;
            int m;
            cout << "Enter number of students you want to add: ";
            cin >> m;
            for (int i = 0; i < m; i++) {
                cout << "For Student ## " << i + 1 << endl;
                cout << "Enter Student ID: ";
                cin >> id;
                cout << "Enter Student Name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter Year: ";
                cin >> year;
                cout << "Enter Gender (M/F): ";
                cin >> gender;
                cout << "Enter Department: ";
                cin.ignore();
                getline(cin, department);
                insertStudent(studentList, id, name, year, gender, department);
            }
        } else if (choice == 2) {
            int id;
            cout << "Enter Student ID to update: ";
            cin >> id;
            updateStudentByID(studentList, id);
        } else if (choice == 3) {
            int id;
            cout << "Enter Student ID to delete: ";
            cin >> id;
            deleteStudentByID(studentList, id);
        } else if (choice == 4) {
            int id;
            cout << "Enter Student ID to search: ";
            cin >> id;
            searchStudentByID(studentList, id);
        } else if (choice == 5) {
            displayStudents(studentList);
        } else if (choice == 6) {
            recordAttendanceForStudents(attendanceList, studentList);
        } else if (choice == 7) {
            displayAttendance(attendanceList);
        } else if (choice == 8) {
            for (int j = 0; j < 10; j++) {
                cout << ". ";
                Sleep(300);
            }
            cout << "\n";
            SetColor(GREEN);
            cout << "Exiting the program." << endl;
            SetColor(DEFAULT);
            break;
        } else {
            cout << "Invalid option, please try again!" << endl;
        }
    }
}
