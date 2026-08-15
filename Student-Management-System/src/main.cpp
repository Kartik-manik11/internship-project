#include "FileManager.h"
#include "Student.h"
#include "Validator.h"

#include <algorithm>
#include <array>
#include <cctype>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace {
constexpr const char* DATA_FILE_PATH = "data/students.txt";

std::string formatMarks(double marks) {
    std::ostringstream stream;
    stream << std::fixed << std::setprecision(2) << marks;
    return stream.str();
}

std::string toLower(std::string text) {
    std::transform(text.begin(), text.end(), text.begin(), [](unsigned char character) {
        return static_cast<char>(std::tolower(character));
    });
    return text;
}

bool readLine(const std::string& prompt, std::string& value) {
    std::cout << prompt;
    if (!std::getline(std::cin, value)) {
        std::cout << "\nInput stream closed. Operation cancelled.\n";
        return false;
    }
    return true;
}

bool readStudentId(int& id) {
    while (true) {
        std::string input;
        if (!readLine("Enter Student ID: ", input)) {
            return false;
        }
        if (Validator::parseInteger(input, id) && Validator::isValidStudentId(id)) {
            return true;
        }
        std::cout << "Invalid student ID. Enter a positive numeric ID.\n";
    }
}

bool readName(std::string& name) {
    while (true) {
        std::string input;
        if (!readLine("Enter Name: ", input)) {
            return false;
        }
        name = Validator::trim(input);
        if (Validator::isValidName(name)) {
            return true;
        }
        std::cout << "Invalid name. Enter 1-100 letters, spaces, apostrophes, hyphens, or periods.\n";
    }
}

bool readCourse(std::string& course) {
    while (true) {
        std::string input;
        if (!readLine("Enter Course: ", input)) {
            return false;
        }
        course = Validator::trim(input);
        if (Validator::isValidCourse(course)) {
            return true;
        }
        std::cout << "Invalid course. It cannot be empty, over 100 characters, or contain '|'.\n";
    }
}

bool readSemester(int& semester) {
    while (true) {
        std::string input;
        if (!readLine("Enter Semester (1-8): ", input)) {
            return false;
        }
        if (Validator::parseInteger(input, semester) && Validator::isValidSemester(semester)) {
            return true;
        }
        std::cout << "Invalid semester. Enter a whole number from 1 to 8.\n";
    }
}

bool readEmail(std::string& email) {
    while (true) {
        std::string input;
        if (!readLine("Enter Email: ", input)) {
            return false;
        }
        email = Validator::trim(input);
        if (Validator::isValidEmail(email)) {
            return true;
        }
        std::cout << "Invalid email. Enter an address such as name@example.com.\n";
    }
}

bool readMarks(double& marks) {
    while (true) {
        std::string input;
        if (!readLine("Enter Marks (0-100): ", input)) {
            return false;
        }
        if (Validator::parseDouble(input, marks) && Validator::isValidMarks(marks)) {
            return true;
        }
        std::cout << "Invalid marks. Enter a numeric value from 0 to 100.\n";
    }
}

bool containsStudentId(const std::vector<Student>& students, int id) {
    return std::find_if(students.begin(), students.end(), [id](const Student& student) {
        return student.getId() == id;
    }) != students.end();
}

void printStudentDetails(const Student& student) {
    std::cout << "Student ID: " << student.getId() << '\n'
              << "Name: " << student.getName() << '\n'
              << "Course: " << student.getCourse() << '\n'
              << "Semester: " << student.getSemester() << '\n'
              << "Email: " << student.getEmail() << '\n'
              << "Marks: " << formatMarks(student.getMarks()) << '\n';
}

void displayStudentTable(const std::vector<Student>& students) {
    if (students.empty()) {
        std::cout << "No student records available.\n";
        return;
    }

    using Row = std::array<std::string, 6>;
    const Row headings = {"ID", "Name", "Course", "Semester", "Email", "Marks"};
    std::vector<Row> rows;
    rows.reserve(students.size());

    std::array<std::size_t, 6> widths{};
    for (std::size_t column = 0; column < headings.size(); ++column) {
        widths[column] = headings[column].size();
    }

    for (const Student& student : students) {
        Row row = {std::to_string(student.getId()), student.getName(), student.getCourse(),
                   std::to_string(student.getSemester()), student.getEmail(), formatMarks(student.getMarks())};
        for (std::size_t column = 0; column < row.size(); ++column) {
            widths[column] = std::max(widths[column], row[column].size());
        }
        rows.push_back(std::move(row));
    }

    const auto printSeparator = [&widths]() {
        std::cout << '+';
        for (const std::size_t width : widths) {
            std::cout << std::string(width + 2, '-') << '+';
        }
        std::cout << '\n';
    };

    const auto printRow = [&widths](const Row& row) {
        std::cout << '|';
        for (std::size_t column = 0; column < row.size(); ++column) {
            std::cout << ' ' << std::left << std::setw(static_cast<int>(widths[column])) << row[column] << " |";
        }
        std::cout << '\n';
    };

    printSeparator();
    printRow(headings);
    printSeparator();
    for (const Row& row : rows) {
        printRow(row);
    }
    printSeparator();
    std::cout << std::right;
}

class StudentManagementSystem {
public:
    StudentManagementSystem() : fileManager_(DATA_FILE_PATH) {}

    void run() {
        loadFromFile();

        bool running = true;
        while (running) {
            printMainMenu();

            std::string input;
            if (!readLine("Enter choice: ", input)) {
                saveAfterInputClosure();
                break;
            }

            int choice = 0;
            if (!Validator::parseInteger(input, choice)) {
                std::cout << "Invalid menu choice. Please enter a number from 1 to 8.\n";
                continue;
            }

            switch (choice) {
                case 1:
                    addStudent();
                    break;
                case 2:
                    displayStudents();
                    break;
                case 3:
                    searchStudent();
                    break;
                case 4:
                    updateStudent();
                    break;
                case 5:
                    deleteStudent();
                    break;
                case 6:
                    sortStudents();
                    break;
                case 7:
                    saveToFile();
                    break;
                case 8:
                    running = exitSafely();
                    break;
                default:
                    std::cout << "Invalid menu choice. Please enter a number from 1 to 8.\n";
                    break;
            }
        }
    }

private:
    std::vector<Student> students_;
    FileManager fileManager_;

    void printMainMenu() const {
        std::cout << "\n===== STUDENT MANAGEMENT SYSTEM =====\n\n"
                  << "1. Add Student\n"
                  << "2. Display Students\n"
                  << "3. Search Student\n"
                  << "4. Update Student\n"
                  << "5. Delete Student\n"
                  << "6. Sort Students\n"
                  << "7. Save Data\n"
                  << "8. Exit\n\n";
    }

    void loadFromFile() {
        const LoadResult result = fileManager_.loadFromFile(students_);
        std::cout << result.message << '\n';
        if (result.success && result.fileFound) {
            std::cout << "Records loaded: " << result.recordsLoaded << '\n';
            if (result.malformedRecords > 0) {
                std::cout << "Malformed records ignored: " << result.malformedRecords << '\n';
            }
        }
    }

    void addStudent() {
        std::cout << "\n--- Add Student ---\n";

        int id = 0;
        while (true) {
            if (!readStudentId(id)) {
                return;
            }
            if (!containsStudentId(students_, id)) {
                break;
            }
            std::cout << "A student with this ID already exists. Record not added.\n";
        }

        std::string name;
        std::string course;
        std::string email;
        int semester = 0;
        double marks = 0.0;

        if (!readName(name) || !readCourse(course) || !readSemester(semester) || !readEmail(email) || !readMarks(marks)) {
            return;
        }

        students_.emplace_back(id, name, course, semester, email, marks);
        std::cout << "Student added successfully.\n";
    }

    void displayStudents() const {
        std::cout << "\n--- Student Records ---\n";
        displayStudentTable(students_);
    }

    void searchStudent() const {
        std::cout << "\n--- Search Student ---\n"
                  << "1. Search by Student ID\n"
                  << "2. Search by Name\n";

        std::string input;
        if (!readLine("Enter search choice: ", input)) {
            return;
        }

        int choice = 0;
        if (!Validator::parseInteger(input, choice) || (choice != 1 && choice != 2)) {
            std::cout << "Invalid search choice.\n";
            return;
        }

        if (choice == 1) {
            int id = 0;
            if (!readStudentId(id)) {
                return;
            }

            const auto student = std::find_if(students_.begin(), students_.end(), [id](const Student& record) {
                return record.getId() == id;
            });
            if (student == students_.end()) {
                std::cout << "Student not found.\n";
                return;
            }

            std::cout << "Student found:\n";
            printStudentDetails(*student);
            return;
        }

        std::string name;
        while (true) {
            if (!readLine("Enter student name: ", name)) {
                return;
            }
            name = Validator::trim(name);
            if (Validator::isValidName(name)) {
                break;
            }
            std::cout << "Invalid name. Enter a valid student name.\n";
        }

        const std::string searchText = toLower(name);
        std::vector<Student> matches;
        for (const Student& student : students_) {
            if (toLower(student.getName()).find(searchText) != std::string::npos) {
                matches.push_back(student);
            }
        }

        if (matches.empty()) {
            std::cout << "Student not found.\n";
            return;
        }

        std::cout << "Matching student record(s):\n";
        displayStudentTable(matches);
    }

    void updateStudent() {
        std::cout << "\n--- Update Student ---\n";
        int id = 0;
        if (!readStudentId(id)) {
            return;
        }

        const auto position = std::find_if(students_.begin(), students_.end(), [id](const Student& student) {
            return student.getId() == id;
        });
        if (position == students_.end()) {
            std::cout << "Student not found.\n";
            return;
        }

        std::cout << "Current student information:\n";
        printStudentDetails(*position);
        std::cout << "Enter all replacement values. The Student ID remains unchanged.\n";

        std::string name;
        std::string course;
        std::string email;
        int semester = 0;
        double marks = 0.0;
        if (!readName(name) || !readCourse(course) || !readSemester(semester) || !readEmail(email) || !readMarks(marks)) {
            return;
        }

        // Build a fully valid replacement before changing the original record.
        const Student updatedStudent(id, name, course, semester, email, marks);
        *position = updatedStudent;
        std::cout << "Student updated successfully.\n";
    }

    void deleteStudent() {
        std::cout << "\n--- Delete Student ---\n";
        int id = 0;
        if (!readStudentId(id)) {
            return;
        }

        const auto position = std::find_if(students_.begin(), students_.end(), [id](const Student& student) {
            return student.getId() == id;
        });
        if (position == students_.end()) {
            std::cout << "Student not found.\n";
            return;
        }

        std::cout << "Student selected for deletion:\n";
        printStudentDetails(*position);

        while (true) {
            std::string confirmation;
            if (!readLine("Are you sure you want to delete this student? (Y/N): ", confirmation)) {
                return;
            }

            confirmation = toLower(Validator::trim(confirmation));
            if (confirmation == "y") {
                students_.erase(position);
                std::cout << "Student deleted successfully.\n";
                return;
            }
            if (confirmation == "n") {
                std::cout << "Deletion cancelled.\n";
                return;
            }
            std::cout << "Invalid confirmation. Enter Y or N.\n";
        }
    }

    void sortStudents() {
        std::cout << "\n--- Sort Students ---\n";
        if (students_.empty()) {
            std::cout << "No student records available.\n";
            return;
        }

        std::cout << "1. Sort by Student ID\n"
                  << "2. Sort by Name\n"
                  << "3. Sort by Marks\n";
        std::string input;
        if (!readLine("Enter sort choice: ", input)) {
            return;
        }

        int choice = 0;
        if (!Validator::parseInteger(input, choice) || choice < 1 || choice > 3) {
            std::cout << "Invalid sort choice.\n";
            return;
        }

        if (choice == 1) {
            std::sort(students_.begin(), students_.end(), [](const Student& first, const Student& second) {
                return first.getId() < second.getId();
            });
            std::cout << "Students sorted by Student ID.\n";
        } else if (choice == 2) {
            std::sort(students_.begin(), students_.end(), [](const Student& first, const Student& second) {
                if (toLower(first.getName()) == toLower(second.getName())) {
                    return first.getId() < second.getId();
                }
                return toLower(first.getName()) < toLower(second.getName());
            });
            std::cout << "Students sorted by name.\n";
        } else {
            std::sort(students_.begin(), students_.end(), [](const Student& first, const Student& second) {
                if (first.getMarks() == second.getMarks()) {
                    return first.getId() < second.getId();
                }
                return first.getMarks() < second.getMarks();
            });
            std::cout << "Students sorted by marks.\n";
        }
    }

    void saveToFile() const {
        std::string message;
        fileManager_.saveToFile(students_, message);
        std::cout << message << '\n';
    }

    bool exitSafely() const {
        std::string message;
        if (fileManager_.saveToFile(students_, message)) {
            std::cout << message << "\nExiting Student Management System.\n";
            return false;
        }

        std::cout << message << '\n';
        while (true) {
            std::string confirmation;
            if (!readLine("Data could not be saved. Exit anyway? (Y/N): ", confirmation)) {
                return false;
            }
            confirmation = toLower(Validator::trim(confirmation));
            if (confirmation == "y") {
                std::cout << "Exiting without saving the latest in-memory changes.\n";
                return false;
            }
            if (confirmation == "n") {
                std::cout << "Exit cancelled. Return to the menu and save after fixing the file issue.\n";
                return true;
            }
            std::cout << "Invalid confirmation. Enter Y or N.\n";
        }
    }

    void saveAfterInputClosure() const {
        std::string message;
        if (fileManager_.saveToFile(students_, message)) {
            std::cout << message << "\nExiting Student Management System.\n";
        } else {
            std::cout << message << "\nExiting because input is unavailable.\n";
        }
    }
};
}  // namespace

int main() {
    StudentManagementSystem application;
    application.run();
    return 0;
}
