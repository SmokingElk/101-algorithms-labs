#pragma once

const int MAX_SURNAME_LENGTH = 50;
const int MAX_INITIALS_LENGTH = 4;
const int MAX_GROUP_LENGTH = 3;

struct Student
{
    char surname[MAX_SURNAME_LENGTH];
    char initials[MAX_INITIALS_LENGTH];
    char group[MAX_GROUP_LENGTH];
    int math_grade;
    int physics_grade;
    int informatics_grade;
};
