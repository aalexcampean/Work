//
// Created by Alex Campean on 08.06.2022.
//

#include "Question.h"

Question::Question(int id, const std::string &text, const std::string &correctAnswer, int score) : id(id), text(text),
                                                                                                   correct_answer(
                                                                                                           correctAnswer),
                                                                                                   score(score) {
    this->answered = false;
}

int Question::getId() const {
    return id;
}

std::string Question::getText() const {
    return text;
}

std::string Question::getCorrectAnswer() const {
    return correct_answer;
}

int Question::getScore() const {
    return score;
}

std::string Question::toStringPresenter() const {
    return "ID: " + std::to_string(id) + " -  Text: " + text + " -  Correct Answer: " + correct_answer + " -  Score: " + std::to_string(score);
}

std::string Question::toStringParticipant() const {
    return "ID: " + std::to_string(id) + " -  Text: " + text + " -  Score: " + std::to_string(score);
}

bool Question::operator==(const Question &question) const {
    return this->id == question.id;
}

bool Question::isAnswered() const {
    return answered;
}

void Question::setAnswered(bool answered) {
    Question::answered = answered;
}
