# Student Attendance Management System

## Overview
The **Student Attendance Management System** is a console-based application developed in C++. It allows users to manage student records and attendance efficiently. The system supports functionalities such as adding, updating, deleting, and searching for student records, as well as recording and displaying attendance.

## Features
- **Student Management**:
  - Add new students
  - Update existing student information
  - Delete students by ID
  - Search for students by ID
  - Display all students

- **Attendance Management**:
  - Record attendance for students
  - Display attendance records

## Technologies Used
- C++
- File I/O (CSV format)
- Windows Console for user interface

## Code Structure
The project consists of several key components:

### Data Structures
1. **Student**: Represents a student with attributes:
   - `id`: Unique identifier for the student.
   - `name`: Name of the student.
   - `year`: Year of study.
   - `gender`: Gender of the student (M/F).
   - `department`: Department of the student.
   - `next`: Pointer to the next student in the linked list.

2. **Attendance**: Represents attendance records for each student with attributes:
   - `studentID`: Unique identifier for the student.
   - `studentName`: Name of the student.
   - `dates`: Pointer to a linked list of attendance dates.
   - `next`: Pointer to the next attendance record in the linked list.

3. **AttendanceDate**: Represents individual attendance entries with attributes:
   - `date`: Date of attendance.
   - `status`: Attendance status (P for Present, A for Absent).
   - `next`: Pointer to the next attendance date in the linked list.

4. **List**: Represents a linked list of students with attributes:
   - `head`: Pointer to the first student in the list.
   - `tail`: Pointer to the last student in the list.
   - `n`: Number of students in the list.

5. **AttendanceList**: Represents a linked list of attendance records with attributes:
   - `head`: Pointer to the first attendance record in the list.
   - `tail`: Pointer to the last attendance record in the list.
   - `n`: Number of attendance records.
   - `dates`: Array of strings representing attendance dates.
   - `dateCount`: Number of dates recorded.

### Functions
- `createStudentList()`: Initializes the student list.
- `createAttendanceList()`: Initializes the attendance list.
- `insertStudent()`: Adds a new student to the list.
- `updateStudentByID()`: Updates student information by ID.
- `deleteStudentByID()`: Deletes a student by ID.
- `searchStudentByID()`: Searches for a student by ID.
- `displayStudents()`: Displays all students in the list.
- `recordAttendanceForStudents()`: Records attendance for all students.
- `displayAttendance()`: Displays attendance records for all students.
- `login_menu()`: Handles user login.
- `Menu()`: Displays the main menu options.

## Getting Started
To run the project, follow these steps:

1. **Clone the Repository**:
   bash
   git clone https://github.com/SoeukBondol-ai/StudentAttendanceManagementSystem.git
2. **Compile the Code**:
   Use a C++ compiler (like g++) to compile the code
## Login Credentials
- **Username**: `admin`
- **Password**: `admin`

## Contribution
Feel free to fork the repository and submit pull requests for any improvements or features you would like to add.

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

