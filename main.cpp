#include <iostream>
#include <fstream>
#include <iomanip>
#include <Windows.h>

#include <algorithm>
#include <utility>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <array>

#include "School.h"
#include "Person.h"
#include "Teacher.h"
#include "SportsSchool.h"
#include "AcademicSchool.h"


std::vector < std::pair < Person, std::string> > readStudentsfromfile(const std::string fileName) {
    std::fstream sfile;
    sfile.open(fileName, std::ios::in);

    int N = 0;
    sfile >> N;

    std::string name, surname, cls;
    std::vector < std::pair < Person, std::string> > students;

    for (int i = 0; i < N; i++) {
        sfile >> name >> surname >> cls;
        students.push_back(std::make_pair(Person(name, surname), cls));
    }

    sfile.close();


    return students;
}

std::vector < Teacher > readTeachersfromfile(const std::string fileName) {
    std::fstream tfile;
    tfile.open(fileName, std::ios::in);

    int N = 0;
    tfile >> N;

    std::string name, surname, ssubjects;
    std::vector < Teacher > teachers;

    for (int i = 0; i < N; i++) {
        tfile >> name >> surname >> ssubjects; 

        size_t pos_start = 0, pos_end;
        std::string token;
        std::set<std::string> subjects;

        while ((pos_end = ssubjects.find(',', pos_start)) != std::string::npos) {
            token = ssubjects.substr(pos_start, pos_end - pos_start);
            pos_start = pos_end + 1;
            subjects.insert(token);
        }

        teachers.push_back(Teacher(name, surname, subjects));
    }

    tfile.close();

    return teachers;
}

void menu() {
    std::cout << "\n\nChose a number, corresponding to the action you are willing to perform.\n"
        << "To exit press 0\n"
        << "\n***PRINTING***\n"
        << "To print all the students of chosen school press 1\n"
        << "To print all the classes of chosen school press 2\n"
        << "To print specific class of chosen school press 3\n"
        << "To print all teachers working in chosen school press 4\n"
        << "To print information about school press 5\n"
        << "\n***STUDENTS***\n"
        << "To add a new student press 6\n"
        << "To move a student to different class press 7\n"
        << "To remove a student from school press 8\n"
        << "\n***TEACHERS***\n"
        << "To add a teacher to the school press 9\n"
        << "To remove a teacher from the school press 10\n"
        << "\n***CLASSES***\n"
        << "To add a class to the school press 11\n"
        << "To remove a class from the school press 12\n"
        << "\n***SCHOOL***\n"
        << "To set a new name for the school press 13\n"
        << "To set a new number for the school press 14\n"
        << "To select different school press 15\n"
        << "To add a new school press 16\n"
        << "To set class capacity press 17\n";

}


int main()
{
    AcademicSchool Acad;
    Acad.setName("JFK New York City Academic School");
    Acad.setNumber(11);
    Acad.setClassCapacity(31);

    SportsSchool Sport;
    Sport.setName("Babe Ruth Boston Sport School");
    Sport.setNumber(10);
    Sport.setClassCapacity(18);


    auto students = readStudentsfromfile("students_final.txt");

    for (auto& a : students) {
        Sport.addStudentF(a.first, a.second);
    }

    auto teachers = readTeachersfromfile("teachers_final.txt");

    for (auto& a : teachers) {
        Sport.addTeacher(a);
    }


    int opt = 0, num=0, i = 0, sub_num = 0;
    std::string name, surname, cls, sub;
    std::set<std::string> subjects;
    std::array<std::string, 12> sub_arr = { "PE", "Mathematics", "Physics", "English", "Biology", "Chemistry", "IT", "History", "Spanish", "French", "Music", "Arts" };
    std::vector<School*> schools;
    School* school = &Sport;
    schools.push_back(&Sport);
    schools.push_back(&Acad);

    do {
        menu();
        std::cin >> opt;
        switch (opt) {

        case 0: exit(0);

        case 1:  school->printStudents(); break;

        case 2:  school->printClasses();  break;

        case 3:  school->printClass(); break;

        case 4:  school->printTeachers(); break;

        case 5:  school->printInfo(); break;

        case 6: 
        //addStudent
        {
            std::cout << "Please provide students name and surname and select a class of your choice:\nName:\t";
            std::cin >> name;
            std::cout << "Surname:\t";
            std::cin >> surname;

            school->addStudent(Person(name, surname));
            break;
        } 

        case 7: school->moveStudent(); break;

        case 8: school->removeStudent(); break;

        case 9: 
        //addTeacher
        {
            std::cout << "Please provide teachers name, surname and list of subjects that can be taught by this teacher:\nName:\t";
            std::cin >> name;
            std::cout << "Surname:\t";
            std::cin >> surname;
            std::cout << "Number of subjects:\t";
            std::cin >> num;
            std::cout << "List of possible subjects:\n"
                << "Number\tSubject\n";
            i = 1;
            for (auto& a : sub_arr) {
                std::cout << "#" << i++ << '\t' << a << '\n';
            }
            std::cout << '\n';

            for (int i = 0; i < num; i++) {
                std::cout << "\nProvide subject number:\n";
                do {
                    std::cin >> sub_num;
                    sub_num--;
                } while (sub_num < 0 || sub_num > sub_arr.size());
                subjects.insert(sub_arr[sub_num]);
            }

            school->addTeacher(Teacher(name, surname, subjects));
            break;
        }

        case 10: school->removeTeacher(); break;

        case 11: 
        //addClass
        {
            do {
                std::cout << "Please, specify class ID. Class ID has to consist one number from 1-9 and one capital latin letter (1A, 2B, etc.):\n";
                std::cin >> cls;
                if (cls.length() != 2 || cls[0] > 57 || cls[0] < 49 || cls[1] > 90 || cls[1] < 65)
                    std::cout << "Invalid ID.\n";
            } while (cls.length() != 2 || cls[0] > 57 || cls[0] < 49 || cls[1] > 90 || cls[1] < 65);

            school->addClass(cls); break;
        }

        case 12: school->removeClass(); break;

        case 13: 
        //setName
        {
            std::cout << "Please specify the new name:\n";
            std::cin.ignore();
            std::getline(std::cin, name);
            school->setName(name); 
            break;
        }

        case 14:
        //setNumber
        {
            std::cout << "Please specify the new number:\n";
            std::cin >> num;
            school->setNumber(num);
            break;
        }
              
        case 15:
        //select different school
        {
            std::cout << "Please, select a school from list below:\n";

            for (auto& a : schools) {
                a->printInfo();
                std::cout << "\n\n";
            }

            int num = school->getNum("school", schools.size());
            school = schools[num];
            break;
        }

        case 16:
        //add a new school to the list
        {
            std::cout << "Please, specify what type of school would you like to add (Academic school - 1, Sports school - 2):\n";
            do {
                std::cin >> num;
                if (num < 0 || num > 2)
                    std::cout << "Wrong number selected!\n";
            } while (num < 0 || num > 2);

            if (num == 1)
                schools.push_back(new AcademicSchool);
            else
                schools.push_back(new SportsSchool);

            school = schools.back();
            std::cout << "Now it is recommended to give your school a name and number, set class capacity and add at least one class.\n";
            break;
        }

        case 17:
        //setClassCapacity
        {
            std::cout << "Please specify the class size:\n";
            do {
                std::cin >> num;
                if (num < 1)
                    std::cout << "Classes cannot be smaller than 1.\n";
            } while (num < 1);

            school->setClassCapacity(num);
            break;
        }

        default:
            std::cout << "Wrong number selected!\n";

        }
    } while (opt != 0);
}

