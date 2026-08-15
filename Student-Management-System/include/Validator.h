#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <string>

class Validator {
public:
    static std::string trim(const std::string& value);
    static bool parseInteger(const std::string& text, int& value);
    static bool parseDouble(const std::string& text, double& value);

    static bool isValidStudentId(int id);
    static bool isValidName(const std::string& name);
    static bool isValidCourse(const std::string& course);
    static bool isValidSemester(int semester);
    static bool isValidEmail(const std::string& email);
    static bool isValidMarks(double marks);
};

#endif
