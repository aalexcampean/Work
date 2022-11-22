//
// Created by Alex Campean on 10.06.2022.
//

#include "AnswerService.h"
#include "CustomException.h"

AnswerService::AnswerService(AnswerRepo *answerRepo) : answerRepo(answerRepo) {

}

std::vector<Answer> AnswerService::getAnswers() {
    return answerRepo->getAll();
}

std::vector<Answer> AnswerService::getAnswersByQuestion(int questionId) {
    std::vector<Answer> allAnswers = answerRepo->getAll();
    std::vector<Answer> filteredAnswers;
    std::copy_if(allAnswers.begin(), allAnswers.end(), std::back_inserter(filteredAnswers),
                 [&questionId](const Answer &answer) {
        return answer.getQuestionId() == questionId;
    });
    return filteredAnswers;
}

void AnswerService::updateNumberOfVotes(int id, int votes) {
    answerRepo->updateNumberOfVotes(id, votes);
    this->notify();
}

void AnswerService::addAnswer(int questionId, const std::string &text, const std::string &userName) {
    if (text.empty()) {
        throw CustomException(ExceptionTypes::EmptyFieldException);
    }
    Answer answer(questionId, text, userName);
    answerRepo->addAnswer(answer);
    this->notify();
}

