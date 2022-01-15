#pragma once

#ifndef SPORTSSCHOOL_H
#define SPORTSSCHOOL_H

#include <iostream>
#include <fstream>
#include <iomanip>

#include <algorithm>
#include <utility>
#include <vector>
#include <set>
#include <map>
#include <string>

#include "School.h"
#include "Teacher.h"
#include "Person.h"

class SportsSchool : public School {
private:
    int _class_capacity;
public:
    void setNumber(const int new_number) override;
    void setName(const std::string new_name) override;
    void addTeacher(const Teacher teacher) override;
    void addStudent(const Person student) override;
    void moveStudent() override;
    void setClassCapacity(const int new_cap) override;
    void printInfo() const override;
};

void SportsSchool::setNumber(const int new_number) {
    if (new_number % 2 == 0) {
        _number = new_number;
    }
    else {
        std::cout << "Sports School number has to be even!\n";
    }
}

void SportsSchool::setName(const std::string new_name) {

    if (new_name.find("Sport") != std::string::npos) {
        _name = new_name;
    }
    else {
        std::cout << "Name of Sports School has to have \"Sport\" in it!\n";
    }
}

void SportsSchool::addTeacher(const Teacher teacher) {

    auto vec = teacher.getSubjects();
    if (std::find(vec.begin(), vec.end(), "PE") != vec.end()) {
        _teachers.insert(teacher);
    }
    else {
        std::cout << "Every teacher from Sports School has to be able to teach PE.\n";
    }
}

void SportsSchool::addStudent(const Person student) {
    if (_classes.size() > 0) {
        printClasses();
        int num = getNum("class", _classes.size());
        auto it = _classes.begin();
        std::advance(it, num);

        if (_classes[it->first] < _class_capacity) {
            _classes[it->first] += 1;
            _students[student] = it->first;
        }
        else
            std::cout << "Unable to add student to chosen class. Classes in " << this->_name << " number " << this->_number << " cannot be bigger than " << this->_class_capacity << ".\n";
    }
    else {
        std::cout << "Unable to add student to a school without classes. Create a class first.\n";
    }
}

void SportsSchool::moveStudent() {
    printStudents();
    int num = getNum("student", _students.size());
    auto it_s = _students.begin();
    std::advance(it_s, num);

    printClasses();
    std::cout << "\nSelect destination class:\n";
    int num1 = getNum("class", _classes.size());
    auto it_c = _classes.begin();
    std::advance(it_c, num1);


    if (_classes[it_c->first] < _class_capacity) {
        _classes[it_c->first] += 1;
        _classes[it_s->second] -= 1;
        _students[it_s->first] = it_c->first;
    }
    else {
        std::cout << "Unable to add student to chosen class. Classes in " << this->_name << " cannot be bigger than " << _class_capacity << " students.\n";
    }
}

void SportsSchool::setClassCapacity(const int new_cap) {
    if (new_cap > 0) {
        _class_capacity = new_cap;
    }
    else
        std::cout << "Class capacity cannot be smaller than 1!\n";
}

void SportsSchool::printInfo() const {

    std::cout << "School name\t" << this->_name
        << "\nNumber\t" << this->_number
        << "\nNumber of students\t" << _students.size()
        << "\nNumber of classes\t" << _classes.size()
        << "\nNumber of teachers\t" << _teachers.size()
        << "\nClass capacity\t" << _class_capacity << '\n';
}


#endif SPORTSSCHOOL_H
