#pragma once

#ifndef TEACHER_H
#define TEACHER_H

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


class Teacher : public Person {
private:
    std::set<std::string> _subjects;

public:
    Teacher(const std::string name, const std::string surname) : Person(name, surname) {}
    Teacher(const std::string name, const std::string surname, const std::set<std::string> subjects) : Person(name, surname), _subjects(subjects) {}
    std::set<std::string> getSubjects() const;
    void printSubjects() const;
    void addSubject(const std::string subject);
    void removeSubject(const std::string subject);
    ~Teacher() = default;
};

std::set<std::string> Teacher::getSubjects() const {
    return _subjects;
}

void Teacher::printSubjects() const {
    for (auto& a : _subjects) {
        std::cout << a << '\n';
    }
}

void Teacher::addSubject(const std::string subject) {
    if (std::find(_subjects.begin(), _subjects.end(), subject) == _subjects.end()) {
        _subjects.insert(subject);
    }
    else {
        std::cout << "Subject already exist in the list!\n";
    }
}

void Teacher::removeSubject(const std::string subject) {
    auto pos = std::find(_subjects.begin(), _subjects.end(), subject);

    if (pos != _subjects.end()) {
        _subjects.erase(pos);
    }
    else {
        std::cout << "Subject does not exist in the list!\n";
    }
}

#endif // !TEACHER_H
