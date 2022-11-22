//
// Created by Alex Campean on 10.06.2022.
//

#include "QuestionRepo.h"
#include "CustomException.h"
#include <iostream>
#include <fstream>
#include <sstream>

QuestionRepo::QuestionRepo(const std::string &filename) : fileName(filename) {
    this->load();
}

int QuestionRepo::getLength() {
    return questions.size();
}

std::vector<Question> QuestionRepo::getAll() const {
    return questions;
}

void QuestionRepo::addQuestion(const Question &question) {
    questions.push_back(question);
    this->save();
}

Question &QuestionRepo::operator[](int index) {
    return questions[index];
}

void QuestionRepo::load() {
    std::ifstream input(fileName, 0);

    std::string line;
    while (std::getline(input, line)) {
        std::istringstream iss(line);
        Question question;
        if (!(iss >> question)) { break; } // error

        questions.push_back(question);
    }
}

void QuestionRepo::save() {
    std::ofstream output(fileName);
    output << *this;
    output.close();
}
