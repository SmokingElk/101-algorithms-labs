#include <iostream>
#include <iomanip>
#include "student.h"

int main() {
    FILE * file = fopen("database.bin", "r");
    Student data[100];
    int count = 0;

    Student line;
    while (fread(&line, sizeof(Student), 1, file) == 1) {
        data[count] = line;
        ++count;
    }

    fclose(file);
    std::cout << std::left << std::setw(15) << "Surname"
              << std::setw(15) << "Initials"
              << std::setw(15) << "Group"
              << std::setw(15) << "Math"
              << std::setw(15) << "Physics"
              << std::setw(15) << "Informatics" << std::endl;

    for (int i = 0; i < count; ++i){
        std::cout << std::setw(15) << data[i].surname
                  << std::setw(15) << data[i].initials
                  << std::setw(15) << data[i].group
                  << std::setw(15) << data[i].math_grade
                  << std::setw(15) << data[i].physics_grade
                  << std::setw(15) << data[i].informatics_grade << std::endl;
    }

    int number_group;
    int cnt_st = 0;
    std::cin >> number_group;
    std::cout << "Answer:" << std::endl;
    for (Student elem: data) {
        if ((elem.group[0] - '0') == number_group) {
            if ((elem.informatics_grade == 5) && (elem.math_grade != 5) && (elem.physics_grade != 5)) {
                ++cnt_st;
                std::cout << elem.surname << std::endl;
                continue;
            } else if ((elem.informatics_grade != 5) && (elem.math_grade == 5) && (elem.physics_grade != 5)) {
                ++cnt_st;
                std::cout << elem.surname << std::endl;
                continue;
            } else if ((elem.informatics_grade != 5) && (elem.math_grade != 5) && (elem.physics_grade == 5)) {
                ++cnt_st;
                std::cout << elem.surname << std::endl;
                continue;
            }
        }
    }
}