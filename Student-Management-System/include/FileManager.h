#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include "Student.h"

#include <cstddef>
#include <string>
#include <vector>

struct LoadResult {
    bool success = false;
    bool fileFound = false;
    std::size_t recordsLoaded = 0;
    std::size_t malformedRecords = 0;
    std::string message;
};

class FileManager {
private:
    std::string filePath_;

public:
    explicit FileManager(std::string filePath);

    bool saveToFile(const std::vector<Student>& students, std::string& message) const;
    LoadResult loadFromFile(std::vector<Student>& students) const;
};

#endif
