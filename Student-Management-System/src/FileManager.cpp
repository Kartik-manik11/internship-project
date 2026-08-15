#include "FileManager.h"

#include "Validator.h"

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <optional>
#include <sstream>
#include <system_error>
#include <utility>

namespace {
std::vector<std::string> splitRecord(const std::string& line) {
    std::vector<std::string> fields;
    std::size_t start = 0;

    while (true) {
        const std::size_t separator = line.find('|', start);
        if (separator == std::string::npos) {
            fields.push_back(line.substr(start));
            return fields;
        }
        fields.push_back(line.substr(start, separator - start));
        start = separator + 1;
    }
}

bool containsId(const std::vector<Student>& students, int id) {
    return std::find_if(students.begin(), students.end(), [id](const Student& student) {
        return student.getId() == id;
    }) != students.end();
}

std::optional<Student> parseRecord(const std::string& line) {
    const std::vector<std::string> fields = splitRecord(line);
    if (fields.size() != 6) {
        return std::nullopt;
    }

    int id = 0;
    int semester = 0;
    double marks = 0.0;
    const std::string name = Validator::trim(fields[1]);
    const std::string course = Validator::trim(fields[2]);
    const std::string email = Validator::trim(fields[4]);

    if (!Validator::parseInteger(fields[0], id) || !Validator::isValidStudentId(id) ||
        !Validator::isValidName(name) || !Validator::isValidCourse(course) ||
        !Validator::parseInteger(fields[3], semester) || !Validator::isValidSemester(semester) ||
        !Validator::isValidEmail(email) || !Validator::parseDouble(fields[5], marks) ||
        !Validator::isValidMarks(marks)) {
        return std::nullopt;
    }

    return Student(id, name, course, semester, email, marks);
}
}  // namespace

FileManager::FileManager(std::string filePath) : filePath_(std::move(filePath)) {}

bool FileManager::saveToFile(const std::vector<Student>& students, std::string& message) const {
    std::ofstream output(filePath_);
    if (!output.is_open()) {
        message = "Unable to open data file.";
        return false;
    }

    output << std::setprecision(15);
    for (const Student& student : students) {
        output << student.getId() << '|' << student.getName() << '|' << student.getCourse() << '|'
               << student.getSemester() << '|' << student.getEmail() << '|' << student.getMarks() << '\n';

        if (!output) {
            message = "Unable to write data file.";
            return false;
        }
    }

    output.close();
    if (!output) {
        message = "Unable to write data file.";
        return false;
    }

    message = "Data saved successfully.";
    return true;
}

LoadResult FileManager::loadFromFile(std::vector<Student>& students) const {
    LoadResult result;
    std::error_code error;
    const bool exists = std::filesystem::exists(filePath_, error);
    if (error) {
        result.message = "Unable to check the data file.";
        return result;
    }

    if (!exists) {
        result.success = true;
        result.message = "No existing data file found. Starting with an empty list.";
        return result;
    }

    result.fileFound = true;
    if (!std::filesystem::is_regular_file(filePath_, error)) {
        if (error) {
            result.message = "Unable to check the data file.";
        } else {
            result.message = "Unable to open data file.";
        }
        return result;
    }

    std::ifstream input(filePath_);
    if (!input.is_open()) {
        result.message = "Unable to open data file.";
        return result;
    }

    std::vector<Student> loadedStudents;
    std::string line;
    while (std::getline(input, line)) {
        if (Validator::trim(line).empty()) {
            ++result.malformedRecords;
            continue;
        }

        const std::optional<Student> parsedStudent = parseRecord(line);
        if (!parsedStudent || containsId(loadedStudents, parsedStudent->getId())) {
            ++result.malformedRecords;
            continue;
        }

        loadedStudents.push_back(*parsedStudent);
    }

    if (input.bad() || (!input.eof() && input.fail())) {
        result.message = "Unable to read data file.";
        return result;
    }

    students = std::move(loadedStudents);
    result.success = true;
    result.recordsLoaded = students.size();
    if (result.malformedRecords == 0) {
        result.message = "Data loaded successfully.";
    } else {
        result.message = "Data loaded with malformed records ignored.";
    }
    return result;
}
