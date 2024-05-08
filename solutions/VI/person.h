#ifndef PERSON_H
#define PERSON_H

#include <cstring>

struct Applicant {
    char lastName[50];
    char initials[50];
    char gender; // 'M' for male, 'F' for female
    int schoolNumber;
    bool medal; // true if has medal, false otherwise
    int score;
    bool pass; // true if pass, false otherwise
};

#endif // PERSON_H