
#pragma once

#ifndef SCHOOL_H
#define SCHOOL_H

#include <iostream>
#include <fstream>
#include <iomanip>

#include <algorithm>
#include <utility>
#include <vector>
#include <set>
#include <map>
#include <string>

#include "Person.h"
#include "Teacher.h"


class School {
protected:
    std::string _name;
    int _number;
    std::map<Person, std::string> _students;    //Person, class
    std::set<Teacher> _teachers;
    std::map<std::string, int> _classes;        //class, number of students

private:
    int _class_capacity;

public:
    virtual void setNumber(const int new_number);
    virtual void setName(const std::string new_name);
    virtual void setClassCapacity(const int new_cap);
    virtual void addTeacher(const Teacher teacher) = 0;
    void removeTeacher();
    virtual void addStudent(const Person student);
    void addStudentF(const Person student, const std::string cls);
    void removeStudent();
    virtual void moveStudent();
    virtual void addClass(const std::string cls);
    void removeClass();
    void printClasses() const;
    void printClass() const;
    void printStudents() const;
    void printTeachers() const;
    virtual void printInfo() const;
    int getNum(const std::string who, const int size) const;


    virtual ~School() = default;
};

void School::setNumber(const int new_number) {
    _number = new_number;
}

void School::setName(const std::string new_name) {
    _name = new_name;
}

void School::setClassCapacity(const int new_cap) {
    if (new_cap > 0) {
        _class_capacity = new_cap;
    }
    else
        std::cout << "Class capacity cannot be smaller than 1!\n";
}

void School::addTeacher(const Teacher teacher) {
    if (std::find(_teachers.begin(), _teachers.end(), teacher) == _teachers.end())
        _teachers.insert(teacher);
    else
        std::cout << "This teacher has already been added!\n";
}

void School::removeTeacher() {
    
    printTeachers();
    int num = getNum("teacher", _teachers.size());

    auto it = _teachers.begin();
    std::advance(it, num);
    _teachers.erase(it);
}

void School::addStudent(const Person student) {
    if (_classes.size() > 0) {
        printClasses();
        int num = getNum("class", _classes.size());
        auto it = _classes.begin();
        std::advance(it, num);
    
        _classes[it->first] += 1;
        _students[student] = it->first;
    }
    else {
        std::cout << "Unable to add student to a school without classes. Create a class first.\n";
    }
}

void School::addStudentF(const Person student, const std::string cls) {
    //_classes[cls] < _class_capacity
    if (true) {
        _classes[cls] += 1;
        _students[student] = cls;
    }
    else {
        std::cout << "Unable to add student to chosen class. Classes in " << this->_name << " cannot be bigger than " << _class_capacity << " students.\n";
    }
}

void School::removeStudent() {
    
    printStudents();
    int num = getNum("student", _students.size());
    auto it = _students.begin();
    std::advance(it, num);
    _students.erase(it);
}

void School::moveStudent() {

    printStudents();
    int num = getNum("student", _students.size());
    auto it_s = _students.begin();
    std::advance(it_s, num);

    printClasses();
    std::cout << "\nSelect destination class:\n";
    int num1 = getNum("class", _classes.size());
    auto it_c = _classes.begin();
    std::advance(it_c, num1);

    //_classes[it_c->first] < _class_capacity
    if (true) {
        _classes[it_c->first] += 1;
        _classes[it_s->second] -= 1;
        _students[it_s->first] = it_c->first;
    }
    else {
        std::cout << "Unable to add student to chosen class. Classes in " << this->_name << " cannot be bigger than " << _class_capacity << " students.\n";
    }
}

int School::getNum(const std::string who, const int size) const{
    int num = 0;
    do {
        if (num < 0 || num > size) {
            std::cout << "Wrong number inserted! Number has to be greater than 0 and lesser than " << size << ".\n";
        }
        std::cout << "Which " << who << " would you like to select? Provide an ID number : ";
        std::cin >> num;
        num--;

    } while (num < 0 || num > size);

    return num;
}

void School::addClass(const std::string cls) {
    if (_classes.find(cls) == _classes.end())
        _classes[cls] = 0;
    else
        std::cout << "Class already exists!\n";
}

void School::removeClass() {
    printClasses();
    int num = getNum("class", _classes.size());
    
    auto it = _classes.begin();
    std::advance(it, num);

    int count = 0;
    for (auto& a : _students) {
        if (a.second == it->first) {
            a.second = "NO CLASS SELECTED!";
            count++;
        }
    }

    _classes.erase(it);

    if (count != 0)
        std::cout << count << " students need to be moved to new classes.\n";
}

void School::printStudents() const {
    std::cout << "Students of " << this->_name << " number " << this->_number << '\n';
    std::cout << "Number\t" << std::setw(15) << "First Name" << std::setw(15) << "Last Name" << "\tClass\n";
    int i = 1;
    for (const auto& a : _students) {
        auto fullName = a.first.getFullName();
        std::cout << "#" << i++ << '\t' << std::setw(15) << fullName.first << std::setw(15) << fullName.second << "\t" << a.second << '\n';
    }
}

void School::printClasses() const {

    std::cout << "Classes in " << this->_name << " number " << this->_number << '\n';
    std::cout << "Number\tClass id\tNumber of students\n";
    int i = 1;
    for (const auto& a : _classes) {
        std::cout << "#" << i++ << '\t' << std::setw(8) << a.first << '\t' << a.second << '\n';
    }
}

void School::printClass() const {
    printClasses();
    int num = getNum("class", _classes.size());
    auto it = _classes.begin();
    std::advance(it, num);
    auto cls = it->first;
 
    std::cout << "\nClass " << cls << " in " << this->_name << " number " << this->_number << '\n';
    std::cout << "Number\t " << std::setw(15) << "Name" << std::setw(15) << "Surname" << "\n";
    int i = 1;

    for (const auto& a : _students) {
        if (a.second == cls) {
            const std::pair<std::string, std::string> name = a.first.getFullName();
            std::cout << "#" << i++ << '\t' << std::setw(15) << name.first << std::setw(15) << name.second << '\n';
        }
    }
   
}

void School::printTeachers() const {

    std::cout << "Teachers from " << this->_name << " number " << this->_number << '\n';
    std::cout << "Number\t " << std::setw(15) << "Name" << std::setw(15) << "Surname" << '\t' << std::setw(12) << "Subjects\n";
    int i = 1;

    for (const auto& a : _teachers) {

        auto name = a.getFullName();
        std::cout << "#" << i++ << '\t' << std::setw(15) << name.first << std::setw(15) << name.second << "\t";

        auto subjects = a.getSubjects();

        for (const auto& b : subjects) {
            std::cout << std::setw(12) << b;
        }

        std::cout << '\n';

    }
}

void School::printInfo() const {

    std::cout << "School name\t" << this->_name
        << "\nNumber\t" << this->_number
        << "\nNumber of students\t" << _students.size()
        << "\nNumber of classes\t" << _classes.size()
        << "\nNumber of teachers\t" << _teachers.size()
        << "\nClass capacity\t" << _class_capacity << '\n';
}


#endif SCHOOL_H