//
// Created by Alex Campean on 10.06.2022.
//
#include <QApplication>
#include "QuestionRepo.h"
#include "AnswerRepo.h"
#include "PersonRepo.h"
#include "Service/QuestionService.h"
#include "Service/AnswerService.h"
#include "UserWidget.h"

int Question::current_id;
int Answer::current_id;

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    QuestionRepo questionRepo{};
    AnswerRepo answersRepo{};
    PersonRepo persons{};

    QuestionService questionService{&questionRepo, &answersRepo};
    AnswerService answerService{&answersRepo};


    std::vector <UserWidget*> users;
    for (auto &person: persons.getAll()) {
        users.push_back(new UserWidget(person, questionService, answerService));
    }

    for (auto &participant: users) {
        participant->show();
    }

    return a.exec();
}
