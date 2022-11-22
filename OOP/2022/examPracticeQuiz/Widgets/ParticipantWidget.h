//
// Created by Alex Campean on 08.06.2022.
//
#pragma once

#include <string>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QListWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include "../Repository/QuestionRepo.h"

class ParticipantWidget: public QWidget, public Observer {
Q_OBJECT

private:
    std::string name;
    int score;
    QuestionRepo& questions;

    /// Layout
    QWidget *mainWidget = new QWidget{};
    QHBoxLayout *mainLayout = new QHBoxLayout{this->mainWidget};

    /// Score Label
    QLabel *scoreLabel;

    /// Questions List
    QListWidget *questionsList;

    /// Answer
    QPushButton* answerButton;
    QLineEdit* questionText;
    QLineEdit* answerText;

public:
    ParticipantWidget(const std::string &name, QuestionRepo &questions, QWidget *parent = Q_NULLPTR);
    ~ParticipantWidget(){};

signals:
    void updateListSignal();
    void answerQuestionSignal(std::string);

public slots:
    void initUI();
    void mapSignalsToSlots();
    int getSelectedIndex(QListWidget *givenList);

    void update() override;
    void updateList();

    void answerQuestion(const std::string &answer);
};

