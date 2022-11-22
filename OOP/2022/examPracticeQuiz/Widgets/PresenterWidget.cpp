//
// Created by Alex Campean on 08.06.2022.
//

#include "PresenterWidget.h"
#include "../Exception/CustomException.h"

PresenterWidget::PresenterWidget(QuestionRepo &questions, QWidget *parent) : questions(questions), QWidget(parent) {
    mapSignalsToSlots();
    setLayout(this->mainLayout);
    setWindowTitle(QString::fromStdString("Presenter"));

    initUI();
    questions.addObserver(this);
}

void PresenterWidget::mapSignalsToSlots() {
    QObject::connect(this, &PresenterWidget::updateListSignal, this, &PresenterWidget::updateList);
    QObject::connect(this, SIGNAL(addQuestionSignal(std::string, std::string, std::string, std::string)), this,
                     SLOT(addQuestion(std::string, std::string, std::string, std::string)));
}

void PresenterWidget::initUI() {
    questionsList = new QListWidget{};
    // Setting the selection model such that multiple rows cannot be selected at once
    questionsList->setSelectionMode(QAbstractItemView::SingleSelection);
    // Populating the Table
    emit updateListSignal();

    QWidget * addQuestionWidget = new QWidget{};
    QVBoxLayout * addQuestionLayout = new QVBoxLayout{addQuestionWidget};

    questionId = new QLineEdit{};
    questionId->setMinimumHeight(35);
    questionId->setPlaceholderText("ID: ");

    questionText = new QLineEdit{};
    questionText->setMinimumHeight(35);
    questionText->setPlaceholderText("Text: ");

    questionAnswer = new QLineEdit{};
    questionAnswer->setMinimumHeight(35);
    questionAnswer->setPlaceholderText("Correct Answer: ");

    questionScore = new QLineEdit{};
    questionScore->setMinimumHeight(35);
    questionScore->setPlaceholderText("Score: ");

    addQuestionButton = new QPushButton{"Add Question"};
    addQuestionButton->setMinimumHeight(35);
    QObject::connect(addQuestionButton, &QPushButton::clicked, this, [=]() {
        emit this->addQuestionSignal(questionId->text().toStdString(), questionText->text().toStdString(),
                                     questionAnswer->text().toStdString(), questionScore->text().toStdString());
    });

    errorMessage = new QLabel{};
    errorMessage->setMinimumHeight(35);

    addQuestionLayout->addWidget(questionId);
    addQuestionLayout->addWidget(questionText);
    addQuestionLayout->addWidget(questionAnswer);
    addQuestionLayout->addWidget(questionScore);
    addQuestionLayout->addWidget(addQuestionButton);

    mainLayout->addWidget(questionsList);
    mainLayout->addWidget(addQuestionWidget);
}

void PresenterWidget::updateList() {
    if (questionsList->count() > 0)
        questionsList->clear();

    // Sort the list by id
    std::vector<Question> sortedQuestions = questions.getAll();
    std::sort(sortedQuestions.begin(), sortedQuestions.end(), [](Question &q1, Question &q2) {
        return q1.getId() < q2.getId();
    });

    // Populating the list with data from the local vector of dogs
    for (Question &question: sortedQuestions) {
        QListWidgetItem *questionItem = new QListWidgetItem{QString::fromStdString(question.toStringPresenter())};
        questionItem->setData(Qt::UserRole, QString::fromStdString(question.toStringPresenter()));
        questionsList->addItem(questionItem);
    }

    // Setting the selection on the first item in the list
    if (!questions.getAll().empty())
        questionsList->setCurrentRow(0);
}

void PresenterWidget::update() {
    emit updateListSignal();
}

void PresenterWidget::addQuestion(const std::string &id, const std::string &text, const std::string &correctAnswer,
                                  const std::string &score) {
    bool flag = true;
    try {
        Question newQuestion{std::stoi(id), text, correctAnswer, std::stoi(score)};
        this->questions.addQuestion(newQuestion);
    }
    catch (const CustomException &e) {
        errorMessage->setText(QString::fromStdString(e.what()));
        errorMessage->setStyleSheet("QLabel { color : red; }");
        flag = false;
    }

    if (flag) {
        questionId->setText("");
        questionText->setText("");
        questionAnswer->setText("");
        questionScore->setText("");
    }
}
