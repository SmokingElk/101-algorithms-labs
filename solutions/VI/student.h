#ifndef STUDENT_H
#define STUDENT_H

const int MAX_SURNAME_LENGTH = 50;
const int MAX_INITIALS_LENGTH = 4;
const int MAX_GROUP_LENGTH = 3;

struct Student
{
    char surname[MAX_SURNAME_LENGTH];
    char initials[MAX_INITIALS_LENGTH];
    char group[MAX_GROUP_LENGTH];
    float math_grade;
    float physics_grade;
    float informatics_grade;
};

#endif