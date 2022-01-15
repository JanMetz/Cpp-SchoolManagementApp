#pragma once

#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <fstream>
#include <iomanip>

#include <algorithm>
#include <utility>
#include <vector>
#include <set>
#include <map>
#include <string>


class Person {
protected:
    std::string _name;
    std::string _surname;

public:
    Person(const std::string name, const std::string surname) : _name{ name }, _surname{ surname } {}
    void changeName(const std::string new_name);
    void changeSurname(const std::string new_surname);
    void printFullName() const;
    std::pair <std::string, std::string> getFullName() const;
    virtual ~Person() = default;

    bool operator==(const Person& other) const;
    bool operator<(const Person& other) const;
    bool operator<=(const Person& other) const;
    bool operator>=(const Person& other) const;
    bool operator>(const Person& other) const;
};

void Person::changeName(const std::string new_name) {
    _name = new_name;
}

void Person::changeSurname(const std::string new_surname) {
    _surname = new_surname;
}

void Person::printFullName() const {
    std::cout << "Name:\t" << _name << "\nSurname:\t" << _surname << '\n';
}

std::pair <std::string, std::string> Person::getFullName() const {
    return std::make_pair(_name, _surname);
}

bool Person::operator==(const Person& other) const {
    return other._name == this->_name && other._surname == this->_surname;
}

bool Person::operator<(const Person& other) const {
    if (other._surname != this->_surname) {
        return this->_surname.compare(other._surname) < 0;
    }
    return this->_name.compare(other._name) < 0;
}

bool Person::operator>(const Person& other) const {
    if (other._surname != this->_surname) {
        return this->_surname.compare(other._surname) > 0;
    }
    return this->_name.compare(other._name) > 0;
}

bool Person::operator<=(const Person& other) const {
    return !(*this > other);
}

bool Person::operator>=(const Person& other) const {
    return !(*this < other);
}

#endif // !PERSON_H
