//
// Created by Alex Campean on 08.06.2022.
//
#pragma once

#include <string>
#include <vector>
#include <ostream>

class Question {
private:
    int id;
    std::string text;
    std::string correct_answer;
    int score;
    bool answered;
public:
    Question(){};
    Question(int id, const std::string &text, const std::string &correctAnswer, int score);
    ~Question(){};

    int getId() const;
    std::string getText() const;
    std::string getCorrectAnswer() const;
    int getScore() const;
    bool isAnswered() const;
    void setAnswered(bool answered);

    std::string toStringPresenter() const;
    std::string toStringParticipant() const;

    bool operator==(const Question &question) const;
    friend std::ostream &operator<<(std::ostream &os, const Question &question);
    friend std::istream& operator>>(std::istream& in, Question &question);

};

inline std::ostream &operator<<(std::ostream &os, const Question &question) {
    os << question.id << "," << question.text << "," << question.correct_answer
       << "," << question.score;
    return os;
}

inline std::istream &operator>>(std::istream &in, Question &question) {
    std::vector<std::string> fields;
    std::string field;

    for (int i = 0; i < 4; i++) {
        std::getline(in, field, ',');
        fields.push_back(field);
    }

    question.id = std::stoi(fields[0]);
    question.text = fields[1];
    question.correct_answer = fields[2];
    question.score = std::stoi(fields[3]);
    question.answered = false;

    return in;
}
