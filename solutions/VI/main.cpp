#include <iostream>

#include "student.h"

int main(){
    FILE* file = fopen("database.bin", "r");
    Student data[100];
    int count = 0;
    
    Student person;
    while (fread(&person, sizeof(Student), 1, file) == 1){
        data[count] = person;
        count++;
    }

    fclose(file);
    char* number_group;
    int cnt_st = 0;
    std::cin >> number_group;
    for (Student elem : data){
        if (elem.group == number_group){
            if (elem.informatics_grade == 5){
                ++cnt_st;
                continue;
            }
            if (elem.math_grade == 5){
                ++cnt_st;
                continue;
            }
            if (elem.physics_grade == 5){
                ++cnt_st;
                continue;
            }
        }
    }
    std::cout << cnt_st << std::endl;
    


}