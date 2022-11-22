//
// Created by Alex Campean on 10.06.2022.
//

#include "AnswerRepo.h"
#include <iostream>
#include <fstream>
#include <sstream>

AnswerRepo::AnswerRepo(const std::string &filename) : fileName(filename) {
    this->load();
}

int AnswerRepo::getLength() {
    return answers.size();
}

std::vector<Answer> AnswerRepo::getAll() const {
    return answers;
}

void AnswerRepo::updateNumberOfVotes(int id, int votes) {
    auto it = std::find(answers.begin(), answers.end(), id);
    it->setNrVotes(votes);
}

void AnswerRepo::addAnswer(const Answer &answer) {
    answers.push_back(answer);
    this->save();
}

Answer &AnswerRepo::operator[](int index) {
    return answers[index];
}

void AnswerRepo::load() {
    std::ifstream input(fileName, 0);

    std::string line;
    while (std::getline(input, line)) {
        std::istringstream iss(line);
        Answer answer;
        if (!(iss >> answer)) { break; } // error

        answers.push_back(answer);
    }
}

void AnswerRepo::save() {
    std::ofstream output(fileName);
    output << *this;
    output.close();
}