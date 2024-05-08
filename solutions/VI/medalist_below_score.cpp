#include <iostream>
#include <fstream>
#include "person.h"
#include <iomanip>


void printMedalistBelowScore(const char* filename, int score) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Error opening file" << std::endl;
        return;
    }

    Applicant applicant;
    while (file.read(reinterpret_cast<char*>(&applicant), sizeof(Applicant))) {
        if (applicant.medal && applicant.score < score) {
            std::cout << applicant.lastName << " " << applicant.initials << std::endl;
        }
    }

    file.close();
}

void printApplicants(const char* filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Error opening file" << std::endl;
        return;
    }

    Applicant applicant;
    std::cout << std::left << std::setw(15) << "Last Name"
              << std::setw(15) << "Initials"
              << std::setw(10) << "Gender"
              << std::setw(15) << "School Number"
              << std::setw(10) << "Medal"
              << std::setw(10) << "Score"
              << std::setw(10) << "Pass" << std::endl;
    std::cout << "-----------------------------------------------------------------------------" << std::endl;

    while (file.read(reinterpret_cast<char*>(&applicant), sizeof(Applicant))) {
        std::cout << std::left << std::setw(15) << applicant.lastName
                  << std::setw(15) << applicant.initials
                  << std::setw(10) << applicant.gender
                  << std::setw(15) << applicant.schoolNumber
                  << std::setw(10) << (applicant.medal ? "Yes" : "No")
                  << std::setw(10) << applicant.score
                  << std::setw(10) << (applicant.pass ? "Yes" : "No") << std::endl;
    }

    file.close();
}

int main(int argc, char* argv[]) {
    if (argc < 2 || argc > 3) {
        std::cerr << "Usage: " << argv[0] << " filename [score]" << std::endl;
        return 1;
    }

    const char* filename = argv[1];

    if (argc == 2) {
        printApplicants(filename);
    } else if (argc == 3) {
        int score = std::atoi(argv[2]);
        if (score < 0 || score > 100) {
            std::cerr << "Score must be between 0 and 100" << std::endl;
            return 1;
        }
        printMedalistBelowScore(filename, score);
    }

    return 0;
}