//
// Created by Alex Campean on 10.06.2022.
//
#pragma once

#include "QuestionRepo.h"
#include "AnswerRepo.h"

class QuestionService : public Subject {
private:
    QuestionRepo *questionRepo;
    AnswerRepo *answerRepo;
public:
    QuestionService(){};
    QuestionService(QuestionRepo *questionRepo, AnswerRepo *answerRepo);
    ~QuestionService(){};

    std::vector<Question> getQuestions();
    int getNumberOfAnswers(Question &question);
    std::vector<Question> sortQuestionsByNumberOfAnswers();

    void addQuestion(const std::string &text, const std::string &userName);
};


