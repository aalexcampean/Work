//
// Created by Alex Campean on 08.06.2022.
//

#include "QuestionRepo.h"
#include "../Exception/CustomException.h"

#include <iostream>
#include <fstream>
#include <sstream>

QuestionRepo::QuestionRepo(const std::string &filename) : fileName(filename) {
    this->load();
}

void QuestionRepo::load() {
    std::ifstream input(fileName, 0);

    std::string line;
    while (std::getline(input, line)) {
        std::istringstream iss(line);
        Question question;
        if (!(iss >> question)) { break; } // error

        this->addQuestion(question);
    }
}

void QuestionRepo::save() {
    std::ofstream output(fileName);
    output << *this;
    output.close();
}

int QuestionRepo::getLength() {
    return questions.size();
}

std::vector<Question> QuestionRepo::getAll() const {
    return questions;
}

void QuestionRepo::addQuestion(const Question &question) {
    auto it = std::find(questions.begin(), questions.end(), question);
    if (it != questions.end()) {
        throw CustomException(ExceptionTypes::AddException);
    }
    questions.push_back(question);
    this->save();
    this->notify();
}

void QuestionRepo::answerQuestion(int index) {
    questions[index].setAnswered(true);
    this->notify();
}

Question &QuestionRepo::operator[](int index) {
    return questions[index];
}
