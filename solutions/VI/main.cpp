#include <iostream>

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
    std::cout << count << std::endl;
    std::cout << data[0].math_grade << std::endl;
    std::cout << data[0].group << std::endl;
    int number_group;
    int cnt_st = 0;
    std::cin >> number_group;
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
    std::cout << cnt_st << std::endl;
}