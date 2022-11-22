//
// Created by Alex Campean on 10.06.2022.
//

#include "Question.h"

Question::Question(const std::string &text, const std::string &userName) : id(current_id++), text(text),
                                                                           userName(userName) {}

int Question::getId() const {
    return id;
}

const std::string &Question::getText() const {
    return text;
}

void Question::setText(const std::string &text) {
    Question::text = text;
}

const std::string &Question::getUserName() const {
    return userName;
}

void Question::setUserName(const std::string &userName) {
    Question::userName = userName;
}

std::string Question::toString() const {
    return "ID: " + std::to_string(id) + "  |  " + "Text: " + text + "  |  " + "User Name: " + userName;
}
