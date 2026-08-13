#include "Student.h"

#include <utility>

Student::Student(int id, std::string name, std::string course, int semester,
                 std::string email, double marks)
    : id_(id),
      name_(std::move(name)),
      course_(std::move(course)),
      semester_(semester),
      email_(std::move(email)),
      marks_(marks) {}

int Student::getId() const {
    return id_;
}

const std::string& Student::getName() const {
    return name_;
}

const std::string& Student::getCourse() const {
    return course_;
}

int Student::getSemester() const {
    return semester_;
}

const std::string& Student::getEmail() const {
    return email_;
}

double Student::getMarks() const {
    return marks_;
}

void Student::setName(const std::string& name) {
    name_ = name;
}

void Student::setCourse(const std::string& course) {
    course_ = course;
}

void Student::setSemester(int semester) {
    semester_ = semester;
}

void Student::setEmail(const std::string& email) {
    email_ = email;
}

void Student::setMarks(double marks) {
    marks_ = marks;
}
