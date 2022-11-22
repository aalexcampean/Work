//
// Created by Alex Campean on 10.06.2022.
//
#pragma once

#include <string>
#include <vector>
#include <ostream>

class Question {
private:
    int id;
    static int current_id;

    std::string text;
    std::string userName;
public:
    Question(){};
    Question(const std::string &text, const std::string &userName);
    ~Question(){};

    int getId() const;

    const std::string &getText() const;
    void setText(const std::string &text);

    const std::string &getUserName() const;
    void setUserName(const std::string &userName);

    std::string toString() const;
    friend std::ostream &operator<<(std::ostream &os, const Question &question);
    friend std::istream& operator>>(std::istream& in, Question &question);
};

inline std::ostream &operator<<(std::ostream &os, const Question &question) {
    os << question.id << "," << question.text << "," << question.userName;

    return os;
}

inline std::istream &operator>>(std::istream &in, Question &question) {
    std::vector<std::string> fields;
    std::string field;

    for (int i = 0; i < 3; i++) {
        std::getline(in, field, ',');
        fields.push_back(field);
    }

    question.id = std::stoi(fields[0]);
    question.text = fields[1];
    question.userName = fields[2];

    return in;
}