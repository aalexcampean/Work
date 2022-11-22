//
// Created by Alex Campean on 10.06.2022.
//

#include "Answer.h"

Answer::Answer(int questionId, const std::string &text, const std::string &userName) : id(current_id++),
                                                                                       questionId(questionId),
                                                                                       text(text),
                                                                                       userName(userName) {
    nrVotes = 0;
}

int Answer::getId() const {
    return id;
}

int Answer::getQuestionId() const {
    return questionId;
}

const std::string &Answer::getUserName() const {
    return userName;
}

const std::string &Answer::getText() const {
    return text;
}

void Answer::setText(const std::string &text) {
    Answer::text = text;
}

int Answer::getNrVotes() const {
    return nrVotes;
}

void Answer::setNrVotes(int nrVotes) {
    Answer::nrVotes = nrVotes;
}

std::string Answer::toString() const {
    return "ID: " + std::to_string(id) + "  |  " + "Text: " + text + "  |  " + "User Name: " + userName + "  |  " +
           "Number of votesSpinBox: " + std::to_string(nrVotes);
}

bool Answer::operator==(int inputId) const {
    return id == inputId;
}
