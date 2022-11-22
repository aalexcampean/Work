//
// Created by Alex Campean on 10.06.2022.
//
#pragma once
#include "AnswerRepo.h"

class AnswerService : public Subject {
private:
    AnswerRepo *answerRepo;
public:
    AnswerService(){};
    AnswerService(AnswerRepo *answerRepo);
    ~AnswerService(){};

    std::vector<Answer> getAnswers();
    std::vector<Answer> getAnswersByQuestion(int questionId);
    void updateNumberOfVotes(int id, int votes);

    void addAnswer(int questionId, const std::string &text, const std::string &userName);
};
