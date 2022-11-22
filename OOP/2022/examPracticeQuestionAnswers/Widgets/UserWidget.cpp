//
// Created by Alex Campean on 10.06.2022.
//

#include "UserWidget.h"
#include "CustomException.h"

UserWidget::UserWidget(Person &person, QuestionService &questions, AnswerService &answers, QWidget *parent) : person(person),
                                                                                                              questionService(questions),
                                                                                                              answerService(answers),
                                                                                                              QWidget(parent) {
    mapSignalsToSlots();
    setLayout(this->mainLayout);
    setWindowTitle(QString::fromStdString(person.getName()));

    initUI();
    questionService.addObserver(this);
    answerService.addObserver(this);
}

void UserWidget::mapSignalsToSlots() {
    QObject::connect(this, &UserWidget::updateQuestionListSignal, this, &UserWidget::updateQuestionList);
    QObject::connect(this, &UserWidget::updateAnswerListSignal, this, &UserWidget::updateAnswerList);
    QObject::connect(this, SIGNAL(addQuestionSignal(const std::string &, const std::string &)), this,
                     SLOT(addQuestion(const std::string &, const std::string &)));
    QObject::connect(this, SIGNAL(addAnswerSignal(int, const std::string &, const std::string &)), this,
                     SLOT(addAnswer(int, const std::string &, const std::string &)));
    QObject::connect(this, SIGNAL(voteAnswerSignal(int, int)), this,
                     SLOT(voteAnswer(int, int)));
}

int UserWidget::getSelectedIndex(QListWidget *givenList) {
    if (givenList->count() == 0)
        return -1;

    // Getting selected index
    QModelIndexList index = givenList->selectionModel()->selectedIndexes();

    // In case the lost is empty, clear the input fields
    if (index.empty()) {
        return -1;
    }

    int idx = index.at(0).row();
    return idx;;
}

int UserWidget::getSelectedQuestionId() {
    int idx = this->getSelectedIndex(questionsList);
    if (idx == -1)
        return -1;

    if (idx >= questionService.getQuestions().size())
        return -1;

    std::vector<Question> sortedQuestions = questionService.sortQuestionsByNumberOfAnswers();
    return sortedQuestions[idx].getId();
}

Answer UserWidget::getSelectedAnswer() {
    int idx = this->getSelectedIndex(answersList);
    std::vector<Answer> filteredAnswers = answerService.getAnswersByQuestion(getSelectedQuestionId());
    return filteredAnswers[idx];
}

void UserWidget::updateQuestionList() {
    if (questionsList->count() > 0)
        questionsList->clear();

    // Sort the list by score
    std::vector<Question> sortedQuestions = questionService.sortQuestionsByNumberOfAnswers();

    // Populating the list with data from the local vector of dogs
    for (Question &question: sortedQuestions) {
        QListWidgetItem *questionItem = new QListWidgetItem{QString::fromStdString(question.toString())};
        questionItem->setData(Qt::UserRole, QString::fromStdString(question.toString()));
        questionsList->addItem(questionItem);
    }

    // Setting the selection on the first item in the list
    if (!questionService.getQuestions().empty())
        questionsList->setCurrentRow(0);
}

void UserWidget::updateAnswerList(int questionId) {
    if (answersList->count() > 0)
        answersList->clear();

    // Sort the list by score
    std::vector<Answer> filteredAnswers = answerService.getAnswersByQuestion(questionId);

    // Populating the list with data from the local vector of dogs
    for (Answer &answer: filteredAnswers) {
        QListWidgetItem *questionItem = new QListWidgetItem{QString::fromStdString(answer.toString())};
        questionItem->setData(Qt::UserRole, QString::fromStdString(answer.toString()));
        if (answer.getUserName() == person.getName()) {
            questionItem->setBackground(Qt::darkYellow);
        }
        answersList->addItem(questionItem);
    }

    // Setting the selection on the first item in the list
    if (!answerService.getAnswers().empty())
        answersList->setCurrentRow(0);
}

void UserWidget::initUI() {
    /// Questions
    QWidget * questionsWidget = new QWidget{};
    QVBoxLayout * questionsLayout = new QVBoxLayout{questionsWidget};

    questionsList = new QListWidget{};
    // Setting the selection model such that multiple rows cannot be selected at once
    questionsList->setSelectionMode(QAbstractItemView::SingleSelection);
    // Populating the Table
    emit updateQuestionListSignal();

    questionText = new QLineEdit{};
    questionText->setMinimumHeight(35);
    questionText->setPlaceholderText("Text: ");

    addQuestionButton = new QPushButton{"Add Question"};
    addQuestionButton->setMinimumHeight(35);
    QObject::connect(addQuestionButton, &QPushButton::clicked, this, [=]() {
        emit this->addQuestionSignal(questionText->text().toStdString(), person.getName());
    });

    questionErrorMessage = new QLabel{};
    questionErrorMessage->setMinimumHeight(35);

    questionsLayout->addWidget(questionsList);
    questionsLayout->addWidget(questionText);
    questionsLayout->addWidget(addQuestionButton);
    questionsLayout->addWidget(questionErrorMessage);

    /// Answers
    QWidget * answersWidget = new QWidget{};
    QVBoxLayout * answersLayout = new QVBoxLayout{answersWidget};

    answersList = new QListWidget{};
    // Setting the selection model such that multiple rows cannot be selected at once
    answersList->setSelectionMode(QAbstractItemView::SingleSelection);

    QWidget * voteWidget = new QWidget{};
    QHBoxLayout * voteLayout = new QHBoxLayout{voteWidget};

    votesSpinBox = new QSpinBox{};
    votesSpinBox->setMinimumHeight(35);
    votesSpinBox->setMinimum(0);

    voteButton = new QPushButton{"Vote"};
    voteButton->setMinimumHeight(35);
    QObject::connect(voteButton, &QPushButton::clicked, this, [=]() {
        int answerId = getSelectedAnswer().getId();
        emit this->voteAnswerSignal(answerId, votesSpinBox->value());
    });

    voteLayout->addWidget(votesSpinBox);
    voteLayout->addWidget(voteButton);

    /// Update votesSpinBox spinner on click question answers
    QObject::connect(answersList, &QListWidget::itemSelectionChanged, this, [=]() {
        if (answersList->count() > 0) {
            if (getSelectedAnswer().getUserName() == person.getName()) {
                votesSpinBox->setDisabled(true);
                voteButton->setDisabled(true);
            } else {
                votesSpinBox->setDisabled(false);
                voteButton->setDisabled(false);
            }
            votesSpinBox->setValue(getSelectedAnswer().getNrVotes());
        }
    });

    answerText = new QLineEdit{};
    answerText->setMinimumHeight(35);
    answerText->setPlaceholderText("Text: ");

    addAnswerButton = new QPushButton{"Add Answer"};
    addAnswerButton->setMinimumHeight(35);
    QObject::connect(addAnswerButton, &QPushButton::clicked, this, [=]() {
        int questionId = getSelectedQuestionId();
        emit this->addAnswerSignal(questionId, answerText->text().toStdString(), person.getName());
    });

    answerErrorMessage = new QLabel{};
    answerErrorMessage->setMinimumHeight(35);

    answersLayout->addWidget(answersList);
    answersLayout->addWidget(voteWidget);
    answersLayout->addWidget(answerText);
    answersLayout->addWidget(addAnswerButton);
    answersLayout->addWidget(answerErrorMessage);

    /// Populate question answers
    QObject::connect(questionsList, &QListWidget::itemSelectionChanged, this, [=]() {
        emit updateAnswerListSignal(getSelectedQuestionId());
    });

    mainLayout->addWidget(questionsWidget);
    mainLayout->addWidget(answersWidget);
}

void UserWidget::update() {
    emit updateQuestionListSignal();
}

void UserWidget::addQuestion(const std::string &text, const std::string &userName) {
    bool flag = true;
    try {
        this->questionService.addQuestion(text, userName);
    }
    catch (const CustomException &e) {
        questionErrorMessage->setText(QString::fromStdString(e.what()));
        questionErrorMessage->setStyleSheet("QLabel { color : red; }");
        flag = false;
    }

    if (flag) {
        questionText->setText("");
    }
}

void UserWidget::addAnswer(int questionId, const std::string &text, const std::string &userName) {
    bool flag = true;
    try {
        this->answerService.addAnswer(questionId, text, userName);
    }
    catch (const CustomException &e) {
        answerErrorMessage->setText(QString::fromStdString(e.what()));
        answerErrorMessage->setStyleSheet("QLabel { color : red; }");
        flag = false;
    }

    if (flag) {
        answerText->setText("");
    }
}

void UserWidget::voteAnswer(int id, int votes) {
    answerService.updateNumberOfVotes(id, votes);
}


