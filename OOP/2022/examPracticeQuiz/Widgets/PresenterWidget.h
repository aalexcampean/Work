//
// Created by Alex Campean on 08.06.2022.
//



#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include "../Observer.h"
#include "../Repository/QuestionRepo.h"

class PresenterWidget: public QWidget, public Observer {
    Q_OBJECT

private:
    QuestionRepo& questions;

    /// Layout
    QWidget *mainWidget = new QWidget{};
    QHBoxLayout *mainLayout = new QHBoxLayout{this->mainWidget};

    /// Questions List
    QListWidget *questionsList;

    /// Answer
    QPushButton* addQuestionButton;
    QLineEdit* questionId;
    QLineEdit* questionText;
    QLineEdit* questionAnswer;
    QLineEdit* questionScore;
    QLabel* errorMessage;

public:
    PresenterWidget(QuestionRepo &questions, QWidget *parent = Q_NULLPTR);
    ~PresenterWidget(){};

signals:
    void updateListSignal();
    void addQuestionSignal(const std::string &id, const std::string &text, const std::string &correctAnswer, const std::string &score);

public slots:
    void initUI();
    void mapSignalsToSlots();

    void update() override;
    void updateList();

    void addQuestion(const std::string &id, const std::string &text, const std::string &correctAnswer, const std::string &score);
};


