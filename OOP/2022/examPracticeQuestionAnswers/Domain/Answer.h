//
// Created by Alex Campean on 10.06.2022.
//
#pragma once

#include <string>
#include <vector>
#include <ostream>

class Answer {
private:
    int id;
    static int current_id;

    int questionId;
    std::string userName;
    std::string text;
    int nrVotes;
public:
    Answer(){};
    Answer(int questionId, const std::string &text, const std::string &userName);
    ~Answer(){};

    int getId() const;
    int getQuestionId() const;
    const std::string &getUserName() const;

    const std::string &getText() const;
    void setText(const std::string &text);

    int getNrVotes() const;
    void setNrVotes(int nrVotes);

    std::string toString() const;
    bool operator==(int inputId) const;
    friend std::ostream &operator<<(std::ostream &os, const Answer &answer);
    friend std::istream& operator>>(std::istream& in, Answer &answer);
};

inline std::ostream &operator<<(std::ostream &os, const Answer &answer) {
    os << answer.id << "," << answer.questionId << "," << answer.userName << "," << answer.text << "," << answer.nrVotes;

    return os;
}

inline std::istream &operator>>(std::istream &in, Answer &answer) {
    std::vector<std::string> fields;
    std::string field;

    for (int i = 0; i < 5; i++) {
        std::getline(in, field, ',');
        fields.push_back(field);
    }

    answer.id = std::stoi(fields[0]);
    answer.questionId = std::stoi(fields[1]);
    answer.userName = fields[2];
    answer.text = fields[3];
    answer.nrVotes = std::stoi(fields[4]);

    return in;
}