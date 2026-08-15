#ifndef STUDENT_H
#define STUDENT_H

#include <string>

class Student {
private:
    int id_;
    std::string name_;
    std::string course_;
    int semester_;
    std::string email_;
    double marks_;

public:
    Student(int id, std::string name, std::string course, int semester,
            std::string email, double marks);

    int getId() const;
    const std::string& getName() const;
    const std::string& getCourse() const;
    int getSemester() const;
    const std::string& getEmail() const;
    double getMarks() const;

    void setName(const std::string& name);
    void setCourse(const std::string& course);
    void setSemester(int semester);
    void setEmail(const std::string& email);
    void setMarks(double marks);
};

#endif
