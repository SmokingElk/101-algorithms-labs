#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
#include "person.h"

std::vector<std::string> lastNames = {"Petrov", "Ivanov", "Sidorov", "Kotov", "Agapov"};
std::vector<std::string> firstNames = {"Ivan", "Petr", "Oleg", "Alex", "Lev"};

void generateApplicants(const char* filename, int count) {
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Error opening file" << std::endl;
        return;
    }

    srand(static_cast<unsigned int>(time(nullptr)));
    for (int i = 0; i < count; ++i) {
        Applicant applicant;
        int lastNameIndex = rand() % lastNames.size();
        strncpy(applicant.lastName, lastNames[lastNameIndex].c_str(), sizeof(applicant.lastName) - 1);
        applicant.lastName[sizeof(applicant.lastName) - 1] = '\0'; // Ensure null termination

        int firstNameIndex = rand() % firstNames.size();
        std::string initial = firstNames[firstNameIndex].substr(0, 1) + ". ";
        strncpy(applicant.initials, initial.c_str(), sizeof(applicant.initials) - 1);
        applicant.initials[sizeof(applicant.initials) - 1] = '\0'; // Ensure null termination

        applicant.gender = rand() % 2 == 0 ? 'M' : 'F';
        applicant.schoolNumber = rand() % 100 + 1; // Random school number from 1 to 100
        applicant.medal = rand() % 2 == 0; // Randomly assign medal
        applicant.score = rand() % 101; // Random score from 0 to 100
        applicant.pass = applicant.score >= 50; // Assuming passing score is 50

        file.write(reinterpret_cast<const char*>(&applicant), sizeof(Applicant));
    }

    file.close();
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " filename count" << std::endl;
        return 1;
    }

    const char* filename = argv[1];
    int count = std::atoi(argv[2]);
    if (count <= 0) {
        std::cerr << "Count must be a positive integer" << std::endl;
        return 1;
    }

    generateApplicants(filename, count);
    std::cout << "Generated " << count << " applicants to " << filename << std::endl;

    return 0;
}