#include <iostream>
#include <string.h>
#include "student.h"


int read_student(Student* st){
    std::cin >> st->surname;
    if (strcmp(st->surname, "END") == 0){
        return 0;
    }
    std::cin >> st->initials;
    std::cin >> st->group;
    std::cin >> st->math_grade;
    std::cin >> st->physics_grade;
    std::cin >> st->informatics_grade;
    return 1;
}

int main(){
    char db_name[] = "database.bin";
    FILE* output = fopen(db_name, "w");
    Student st;
    while(read_student(&st));
    {
        fwrite(&st, sizeof(st), 1, output);
    }
    fclose(output);
}