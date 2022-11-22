//
// Created by Alex Campean on 10.06.2022.
//
#pragma once

#include <vector>
#include "./Domain/Answer.h"
#include "Observer.h"

class AnswerRepo {
private:
    std::vector<Answer> answers;
    std::string fileName;

    void load();
    void save();

public:
    AnswerRepo(const std::string &filename = "Answers.txt");
    ~AnswerRepo() {};

    int getLength();
    std::vector<Answer> getAll() const;
    void updateNumberOfVotes(int id, int votes);

    void addAnswer(const Answer &answer);

    Answer &operator[](int index);
    friend std::ostream &operator<<(std::ostream &stream, const AnswerRepo &repository);
};

inline std::ostream &operator<<(std::ostream &stream, const AnswerRepo &repository) {
    for (auto &it: repository.getAll()) {
        stream << it << "\n";
    }
    return stream;
}