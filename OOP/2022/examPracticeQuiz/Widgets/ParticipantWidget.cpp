//
// Created by Alex Campean on 08.06.2022.
//

#include "ParticipantWidget.h"

ParticipantWidget::ParticipantWidget(const std::string &name, QuestionRepo &questions, QWidget *parent)
        : name(name), questions(questions), QWidget(parent) {

    mapSignalsToSlots();
    setLayout(this->mainLayout);
    setWindowTitle(QString::fromStdString(name));
    score = 0;

    initUI();
    questions.addObserver(this);
}

void ParticipantWidget::mapSignalsToSlots() {
    QObject::connect(this, &ParticipantWidget::updateListSignal, this, &ParticipantWidget::updateList);
    QObject::connect(this, SIGNAL(answerQuestionSignal(std::string)), this,
                     SLOT(answerQuestion(std::string)));
}

/// Retrieving the index of the selected row
int ParticipantWidget::getSelectedIndex(QListWidget *givenList) {
    if (givenList->count() == 0)
        return -1;

    // Getting selected index
    QModelIndexList index = givenList->selectionModel()->selectedIndexes();

    // In case the lost is empty, clear the input fields
    if (index.empty()) {
        this->questionText->clear();
        return -1;
    }

    int idx = index.at(0).row();
    return idx;
}

void ParticipantWidget::initUI() {
    QWidget * questionsWidget = new QWidget{};
    QVBoxLayout * questionsLayout = new QVBoxLayout{questionsWidget};

    scoreLabel = new QLabel{};
    scoreLabel->setMinimumHeight(35);
    scoreLabel->setText(QString::fromStdString("Score: " + std::to_string(score)));

    questionsList = new QListWidget{};
    // Setting the selection model such that multiple rows cannot be selected at once
    questionsList->setSelectionMode(QAbstractItemView::SingleSelection);
    // Populating the Table
    emit updateListSignal();

    QWidget * answerWidget = new QWidget{};
    QVBoxLayout * answerLayout = new QVBoxLayout{answerWidget};

    questionText = new QLineEdit{};
    questionText->setMinimumHeight(35);
    questionText->setPlaceholderText("Question: ");
    questionText->setDisabled(true);
    QObject::connect(questionsList, &QListWidget::itemSelectionChanged, this, [=]() {
        int idx = this->getSelectedIndex(questionsList);
        if (idx == -1)
            return;

        if (idx >= questions.getAll().size())
            return;

        Question question = questions.getAll()[idx];

        this->questionText->setText(QString::fromStdString(question.getText()));

        if (question.isAnswered()) {
            answerButton->setDisabled(true);
        } else {
            answerButton->setDisabled(false);
        }
    });


    answerText = new QLineEdit{};
    answerText->setMinimumHeight(35);
    answerText->setPlaceholderText("Answer: ");

    answerButton = new QPushButton{"Answer Question"};
    answerButton->setMinimumHeight(35);
    QObject::connect(answerButton, &QPushButton::clicked, this, [=]() {
        emit this->answerQuestionSignal(this->answerText->text().toStdString());
    });

    questionsLayout->addWidget(scoreLabel);
    questionsLayout->addWidget(questionsList);

    answerLayout->addWidget(questionText);
    answerLayout->addWidget(answerText);
    answerLayout->addWidget(answerButton);

    mainLayout->addWidget(questionsWidget);
    mainLayout->addWidget(answerWidget);
}

void ParticipantWidget::updateList() {
    if (questionsList->count() > 0)
        questionsList->clear();

    // Sort the list by score
    std::vector<Question> sortedQuestions = questions.getAll();
    std::sort(sortedQuestions.begin(), sortedQuestions.end(), [](Question &q1, Question &q2) {
        return q1.getScore() > q2.getScore();
    });

    // Populating the list with data from the local vector of dogs
    for (Question &question: sortedQuestions) {
        QListWidgetItem *questionItem = new QListWidgetItem{QString::fromStdString(question.toStringParticipant())};
        questionItem->setData(Qt::UserRole, QString::fromStdString(question.toStringParticipant()));
        if (question.isAnswered()) questionItem->setBackground(Qt::darkGreen);
        questionsList->addItem(questionItem);
    }

    // Setting the selection on the first item in the list
    if (!questions.getAll().empty())
        questionsList->setCurrentRow(0);
}

void ParticipantWidget::update() {
    emit updateListSignal();
}

void ParticipantWidget::answerQuestion(const std::string &answer) {
    int idx = this->getSelectedIndex(questionsList);
    if (idx == -1)
        return;

    if (idx >= questions.getAll().size())
        return;

    Question question = questions.getAll()[idx];

    if (answer == question.getCorrectAnswer()) {
        score += question.getScore();
        scoreLabel->setText(QString::fromStdString("Score: " + std::to_string(score)));
        answerText->setText("");
        questions.answerQuestion(idx);
    }
}


