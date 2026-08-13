#include "Validator.h"

#include <algorithm>
#include <cctype>
#include <cmath>
#include <limits>
#include <stdexcept>

namespace {
bool containsReservedOrControlCharacter(const std::string& value) {
    return std::any_of(value.begin(), value.end(), [](unsigned char character) {
        return character == '|' || std::iscntrl(character) != 0;
    });
}
}  // namespace

std::string Validator::trim(const std::string& value) {
    const auto first = std::find_if_not(value.begin(), value.end(), [](unsigned char character) {
        return std::isspace(character) != 0;
    });

    if (first == value.end()) {
        return "";
    }

    const auto last = std::find_if_not(value.rbegin(), value.rend(), [](unsigned char character) {
        return std::isspace(character) != 0;
    }).base();

    return std::string(first, last);
}

bool Validator::parseInteger(const std::string& text, int& value) {
    const std::string cleaned = trim(text);
    if (cleaned.empty()) {
        return false;
    }

    try {
        std::size_t processed = 0;
        const long long parsed = std::stoll(cleaned, &processed);
        if (processed != cleaned.size() || parsed < std::numeric_limits<int>::min() ||
            parsed > std::numeric_limits<int>::max()) {
            return false;
        }
        value = static_cast<int>(parsed);
        return true;
    } catch (const std::invalid_argument&) {
        return false;
    } catch (const std::out_of_range&) {
        return false;
    }
}

bool Validator::parseDouble(const std::string& text, double& value) {
    const std::string cleaned = trim(text);
    if (cleaned.empty()) {
        return false;
    }

    try {
        std::size_t processed = 0;
        const double parsed = std::stod(cleaned, &processed);
        if (processed != cleaned.size() || !std::isfinite(parsed)) {
            return false;
        }
        value = parsed;
        return true;
    } catch (const std::invalid_argument&) {
        return false;
    } catch (const std::out_of_range&) {
        return false;
    }
}

bool Validator::isValidStudentId(int id) {
    return id > 0;
}

bool Validator::isValidName(const std::string& name) {
    const std::string cleaned = trim(name);
    if (cleaned.empty() || cleaned.size() > 100 || containsReservedOrControlCharacter(cleaned)) {
        return false;
    }

    bool containsLetter = false;
    for (const unsigned char character : cleaned) {
        if (std::isalpha(character) != 0) {
            containsLetter = true;
            continue;
        }
        if (std::isspace(character) == 0 && character != '\'' && character != '-' && character != '.') {
            return false;
        }
    }
    return containsLetter;
}

bool Validator::isValidCourse(const std::string& course) {
    const std::string cleaned = trim(course);
    return !cleaned.empty() && cleaned.size() <= 100 &&
           !containsReservedOrControlCharacter(cleaned);
}

bool Validator::isValidSemester(int semester) {
    return semester >= 1 && semester <= 8;
}

bool Validator::isValidEmail(const std::string& email) {
    const std::string cleaned = trim(email);
    if (cleaned.empty() || cleaned.size() > 254 || containsReservedOrControlCharacter(cleaned) ||
        std::any_of(cleaned.begin(), cleaned.end(), [](unsigned char character) {
            return std::isspace(character) != 0;
        })) {
        return false;
    }

    const std::size_t at = cleaned.find('@');
    if (at == std::string::npos || at == 0 || at != cleaned.rfind('@') || at == cleaned.size() - 1) {
        return false;
    }

    const std::string domain = cleaned.substr(at + 1);
    const std::size_t dot = domain.rfind('.');
    return dot != std::string::npos && dot != 0 && dot != domain.size() - 1;
}

bool Validator::isValidMarks(double marks) {
    return std::isfinite(marks) && marks >= 0.0 && marks <= 100.0;
}
