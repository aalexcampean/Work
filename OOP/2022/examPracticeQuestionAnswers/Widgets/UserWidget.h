//
// Created by Alex Campean on 10.06.2022.
//
#pragma once

#include <QWidget>
#include <QHBoxLayout>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QSpinBox>
#include "../Observer.h"
#include "../Repository/QuestionRepo.h"
#include "../Repository/AnswerRepo.h"
#include "Person.h"
#include "Service/QuestionService.h"
#include "Service/AnswerService.h"

class UserWidget : public QWidget, public Observer {
Q_OBJECT

private:
    Person person;
    QuestionService &questionService;
    AnswerService &answerService;

    /// Layout
    QWidget *mainWidget = new QWidget{};
    QHBoxLayout *mainLayout = new QHBoxLayout{this->mainWidget};

    /// Questions List
    QListWidget *questionsList;
    /// Answers List
    QListWidget *answersList;

    /// Questions
    QPushButton *addQuestionButton;
    QLineEdit *questionText;
    QLabel *questionErrorMessage;

    /// Answer
    QPushButton *addAnswerButton;
    QLineEdit *answerText;
    QLabel *answerErrorMessage;
    QSpinBox *votesSpinBox;
    QPushButton *voteButton;

public:
    UserWidget(Person &person, QuestionService &questions, AnswerService &answers, QWidget *parent = Q_NULLPTR);
    ~UserWidget(){};

signals:
    void updateQuestionListSignal();
    void updateAnswerListSignal(int questionId);
    void addQuestionSignal(const std::string &text, const std::string &userName);
    void addAnswerSignal(int questionId, const std::string &text, const std::string &userName);
    void voteAnswerSignal(int id, int votes);

public slots:
    void initUI();
    void mapSignalsToSlots();
    int getSelectedIndex(QListWidget *givenList);
    int getSelectedQuestionId();
    Answer getSelectedAnswer();

    void updateQuestionList();
    void updateAnswerList(int questionId);
    void update() override;

    void addQuestion(const std::string &text, const std::string &userName);
    void addAnswer(int questionId, const std::string &text, const std::string &userName);
    void voteAnswer(int id, int votes);
};
