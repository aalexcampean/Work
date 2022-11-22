//
// Created by Alex Campean on 08.06.2022.
//
#pragma once


#include <vector>
#include "../Domain/Question.h"
#include "../Observer.h"

class QuestionRepo: public Subject {
private:
    std::vector<Question> questions;
    std::string fileName;

    void load();
    void save();

public:
    QuestionRepo(const std::string &filename = "Questions.txt");
    ~QuestionRepo(){};

    int getLength();
    std::vector<Question> getAll() const;
    void addQuestion(const Question &question);
    void answerQuestion(int index);

    Question& operator[](int index);
    friend std::ostream& operator<<(std::ostream& stream, const QuestionRepo &repository);

};

inline std::ostream& operator<<(std::ostream& stream, const QuestionRepo &repository) {
    for (auto& it : repository.getAll()) {
        stream << it << "\n";
    }
    return stream;
}