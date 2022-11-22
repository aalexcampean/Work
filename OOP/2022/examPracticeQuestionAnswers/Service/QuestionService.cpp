//
// Created by Alex Campean on 10.06.2022.
//

#include "QuestionService.h"
#include "CustomException.h"

QuestionService::QuestionService(QuestionRepo *questionRepo, AnswerRepo *answerRepo) : questionRepo(questionRepo),
                                                                                       answerRepo(answerRepo) {}

std::vector<Question> QuestionService::getQuestions() {
    return questionRepo->getAll();
}

int QuestionService::getNumberOfAnswers(Question &question) {
    std::vector<Answer> answers = answerRepo->getAll();
    int answerCount = 0;
    std::for_each(answers.begin(), answers.end(), [&answerCount, &question](auto& it){
        if (it.getQuestionId() == question.getId()) {
            answerCount += 1;
        }
    });
    return answerCount;
}

std::vector<Question> QuestionService::sortQuestionsByNumberOfAnswers() {
    std::vector<Question> sortedQuestions = questionRepo->getAll();
    std::sort(sortedQuestions.begin(), sortedQuestions.end(), [this](Question &q1, Question &q2){
        return this->getNumberOfAnswers(q1) > this->getNumberOfAnswers(q2);
    });
    return sortedQuestions;
}

void QuestionService::addQuestion(const std::string &text, const std::string &userName) {
    if (text.empty()) {
        throw CustomException(ExceptionTypes::EmptyFieldException);
    }
    Question question(text, userName);
    questionRepo->addQuestion(question);
    this->notify();
}
