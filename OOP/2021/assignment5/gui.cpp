// You may need to build the project (run Qt uic code generator) to get "ui_GUI.h" resolved
#include <QApplication>
#include <QDateEdit>
#include <QCompleter>
#include <QGroupBox>
#include <QMessageBox>
#include "gui.h"

GUI::GUI(QWidget *parent) : QWidget(parent) {
    AdminService designated_as;
    UserService designated_us;
    this->as = designated_as;
    this->us = designated_us;

    this->connectSignalsAndSlots();
    this->initGUI();
}

GUI::~GUI() {
}

void GUI::initGUI() {
    setLayout(this->mainLayout);
    this->startMenu();
}

void GUI::populateList() {
    this->moviesVector = this->as.getDataBase();

    if (this->moviesList->count() > 0)
        this->moviesList->clear();

    std::vector<Movie> db = this->moviesVector;
    for (auto it : db) {
        QListWidgetItem* movie = new QListWidgetItem{ QString::fromStdString(it.toString()) };
        movie->setData(Qt::UserRole, QString::fromStdString(it.toString()));
        this->moviesList->addItem(movie);
    }

    // set the selection on the first item in the list
    if (!this->moviesVector.empty())
        this->moviesList->setCurrentRow(0);
}

void GUI::populateUserLists(QListWidget* givenList, const std::vector<Movie>& inputVector) {
    if (givenList->count() > 0)
        givenList->clear();

    for (auto it : inputVector) {
        QListWidgetItem* movie = new QListWidgetItem{ QString::fromStdString(it.toString()) };
        movie->setData(Qt::UserRole, QString::fromStdString(it.toString()));
        givenList->addItem(movie);
    }

    // set the selection on the first item in the list
    if (!inputVector.empty())
        givenList->setCurrentRow(0);
}

void GUI::startMenu() {
    QWidget* optionsWidget = new QWidget{};
    QHBoxLayout* options_layout = new QHBoxLayout{optionsWidget};

    this->admin = new QPushButton{"Admin"};
    this->admin->setMinimumHeight(35);
    this->user = new QPushButton{"User"};
    this->user->setMinimumHeight(35);
    this->close = new QPushButton{ "Close" };
    this->close->setMinimumHeight(35);

    options_layout->addWidget(this->admin);
    options_layout->addWidget(this->user);
    options_layout->addWidget(this->close);

    this->mainLayout->addWidget(optionsWidget);

    QObject::connect(admin, &QPushButton::clicked, this, [=](){
        delete this->admin;
        delete this->user;
        delete this->close;
        delete optionsWidget;
        this->adminMenu();
    });
    QObject::connect(user, &QPushButton::clicked, this, [=](){
        delete this->admin;
        delete this->user;
        delete this->close;
        delete optionsWidget;
        this->userMenuOptions();
    });
    QObject::connect(close, &QPushButton::clicked, this, &QApplication::quit);
}

void GUI::adminMenu() {

    //General layout of the window
    QWidget* windowWidget = new QWidget{};
    QVBoxLayout* windowLayout = new QVBoxLayout{windowWidget};

    // the top layout - a vertical one
    QWidget* topWidget = new QWidget{};
    QHBoxLayout* topLayout = new QHBoxLayout{topWidget};

    // the bottom layout - a grid one
    QWidget* bottomWidget = new QWidget{};
    QGridLayout* bottomLayout = new QGridLayout{bottomWidget};

    // the list of movies - on the left
    this->moviesList = new QListWidget{};
    // set the selection model
    this->moviesList->setSelectionMode(QAbstractItemView::SingleSelection);
    this->populateList();

    std::pair<QWidget*, QLayout*> topWidgetLayout{topWidget, topLayout};

    this->a_add = new QPushButton{ "Add movie" };
    this->a_add->setMinimumHeight(35);
    this->a_delete = new QPushButton{ "Delete movie" };
    this->a_delete->setMinimumHeight(35);
    this->a_update = new QPushButton{ "Update movie" };
    this->a_update->setMinimumHeight(35);
    this->a_close = new QPushButton{ "Close"};
    this->a_close->setMinimumHeight(35);

    QObject::connect(this->a_add, &QPushButton::clicked, this, [=](){
        this->a_add->setDisabled(true);
        this->a_delete->setDisabled(true);
        this->a_update->setDisabled(true);
        this->addFunctionality(topWidgetLayout);
    });

    QObject::connect(this->a_update, &QPushButton::clicked, this, [=](){
        this->a_add->setDisabled(true);
        this->a_delete->setDisabled(true);
        this->a_update->setDisabled(true);
        this->updateFunctionality(topWidgetLayout);
    });

    QObject::connect(this->a_delete, &QPushButton::clicked, this, [=](){
        this->deleteFunctionality();
    });

    QObject::connect(this->a_close, &QPushButton::clicked, this, [=](){
        delete windowWidget;
        this->startMenu();
    });

    topLayout->addWidget(this->moviesList);

    bottomLayout->addWidget(this->a_add, 0, 0);
    bottomLayout->addWidget(this->a_update, 0, 1);
    bottomLayout->addWidget(this->a_delete, 1, 0);
    bottomLayout->addWidget(this->a_close, 1, 1);

    windowLayout->addWidget(topWidget);
    windowLayout->addWidget(bottomWidget);

    this->mainLayout->addWidget(windowWidget);
}

void GUI::userMenu() {

    //General layout of the window
    QWidget* windowWidget = new QWidget{};
    QVBoxLayout* windowLayout = new QVBoxLayout{windowWidget};

    // the top layout - a vertical one
    QWidget* topWidget = new QWidget{};
    QHBoxLayout* topLayout = new QHBoxLayout{topWidget};

    std::pair<QWidget*, QLayout*> topWidgetLayout{topWidget, topLayout};

    // the bottom layout - a grid one
    QWidget* bottomWidget = new QWidget{};
    QGridLayout* bottomLayout = new QGridLayout{bottomWidget};

    this->moviesListUser = new QListWidget{};
    this->moviesListUser->setSelectionMode(QAbstractItemView::SingleSelection);
    this->populateUserLists(this->moviesListUser, this->moviesVectorUser = this->as.getDataBase());

    this->le_filter = new QLineEdit{};
    this->le_filter->setMinimumHeight(35);
    this->u_filter = new QPushButton{"Filter"};
    this->u_filter->setMinimumHeight(35);
    this->le_filter->setPlaceholderText("Genre: ");

    this->u_watchlist = new QPushButton{"Wishlist"};
    this->u_watchlist->setMinimumHeight(35);
    this->u_close = new QPushButton{"Close"};
    this->u_close->setMinimumHeight(35);

    QObject::connect(this->u_filter, &QPushButton::clicked, this, [=](){
        std::string searchGenre = this->le_filter->text().toStdString();
        emit filterListSignal(searchGenre);
    });

    QObject::connect(this->u_watchlist, &QPushButton::clicked, this, [=](){
        this->u_watchlist->setDisabled(true);
        this->manageWatchList(topWidgetLayout);
    });

    QObject::connect(this->u_close, &QPushButton::clicked, this, [=](){
        delete windowWidget;
        this->startMenu();
    });

    topLayout->addWidget(this->moviesListUser);

    bottomLayout->addWidget(le_filter, 0, 0);
    bottomLayout->addWidget(this->u_filter, 0, 1);
    bottomLayout->addWidget(this->u_watchlist, 1, 0);
    bottomLayout->addWidget(this->u_close, 1, 1);

    windowLayout->addWidget(topWidget);
    windowLayout->addWidget(bottomWidget);
    this->mainLayout->addWidget(windowWidget);
}

void GUI::userMenuOptions() {
    QWidget *windowWidget = new QWidget{};
    QHBoxLayout *windowLayout = new QHBoxLayout{windowWidget};

    this->u_html = new QPushButton{ "HTML" };
    this->u_html->setMinimumHeight(35);
    this->u_csv = new QPushButton{ "CSV" };
    this->u_csv->setMinimumHeight(35);

    windowLayout->addWidget(this->u_html);
    windowLayout->addWidget(this->u_csv);
    this->mainLayout->addWidget(windowWidget);

    QObject::connect(this->u_html, &QPushButton::clicked, this, [=](){
        delete this->u_html;
        delete this->u_csv;
        delete windowLayout;
        delete windowWidget;
        this->us.setRepoType("html");
        this->userMenu();
    });

    QObject::connect(this->u_csv, &QPushButton::clicked, this, [=](){
        delete this->u_html;
        delete this->u_csv;
        delete windowLayout;
        delete windowWidget;
        this->us.setRepoType("csv");
        this->userMenu();
    });
}

void GUI::addFunctionality(std::pair<QWidget*, QLayout*> receivedWidgetLayout) {
    std::pair<QWidget*, QFormLayout*> fieldsWidgetLayout = this->createFields(receivedWidgetLayout);

    QPushButton* done = new QPushButton{ "Done" };
    done->setMinimumHeight(35);
    QPushButton* close = new QPushButton{ "Close" };
    close->setMinimumHeight(35);
    QLabel* errorMessage = new QLabel{};
    errorMessage->setMinimumHeight(35);
    QLabel* spacing1 = new QLabel{""};
    spacing1->setMinimumHeight(35);
    QLabel* spacing2 = new QLabel{""};
    spacing2->setMinimumHeight(35);
    fieldsWidgetLayout.second->addRow(spacing1);
    fieldsWidgetLayout.second->addRow(done);
    fieldsWidgetLayout.second->addRow(close);
    fieldsWidgetLayout.second->addRow(spacing2);
    fieldsWidgetLayout.second->addRow(errorMessage);


    QObject::connect(done, &QPushButton::clicked, this, [=](){
        errorMessage->setText("");
        std::vector<std::string> receivedFields = this->getFieldsContent();
        emit this->addMovieSignal(receivedFields, errorMessage);
    });

    QObject::connect(close, &QPushButton::clicked, this, [=]() {
        delete done;
        delete close;
        delete errorMessage;
        delete spacing1;
        delete spacing2;

        this->deleteFields(fieldsWidgetLayout);

        this->a_add->setDisabled(false);
        this->a_delete->setDisabled(false);
        this->a_update->setDisabled(false);
    });

}

void GUI::updateFunctionality(std::pair<QWidget*, QLayout*> receivedWidgetLayout) {
    std::pair<QWidget*, QFormLayout*> fieldsWidgetLayout = this->createFields(receivedWidgetLayout);

    QObject::connect(this->moviesList, &QListWidget::itemSelectionChanged, this, &GUI::fieldsChanged);

    QPushButton* done = new QPushButton{ "Done" };
    done->setMinimumHeight(35);
    QPushButton* close = new QPushButton{ "Close" };
    close->setMinimumHeight(35);
    QLabel* errorMessage = new QLabel{};
    errorMessage->setMinimumHeight(35);
    QLabel* spacing1 = new QLabel{""};
    spacing1->setMinimumHeight(35);
    QLabel* spacing2 = new QLabel{""};
    spacing2->setMinimumHeight(35);
    fieldsWidgetLayout.second->addRow(spacing1);
    fieldsWidgetLayout.second->addRow(done);
    fieldsWidgetLayout.second->addRow(close);
    fieldsWidgetLayout.second->addRow(spacing2);
    fieldsWidgetLayout.second->addRow(errorMessage);


    QObject::connect(done, &QPushButton::clicked, this, [=](){
        errorMessage->setText("");

        std::vector<std::string> receivedFields = this->getFieldsContent();
        emit this->updateMovieSignal(receivedFields, errorMessage);
    });

    QObject::connect(close, &QPushButton::clicked, this, [=]() {
        delete done;
        delete close;
        delete errorMessage;
        delete spacing1;
        delete spacing2;

        this->deleteFields(fieldsWidgetLayout);

        this->a_add->setDisabled(false);
        this->a_delete->setDisabled(false);
        this->a_update->setDisabled(false);

        QObject::disconnect(this->moviesList, &QListWidget::itemSelectionChanged, this, &GUI::fieldsChanged);
    });
}

void GUI::deleteFunctionality() {
        int idx = this->getSelectedIndex(this->moviesList);
        if (idx == -1)
            return;

        if (idx >= this->moviesVector.size())
            return;
        std::string receivedTitle = this->moviesVector[idx].getTitle();
        emit this->deleteMovieSignal(receivedTitle);
}

void GUI::filterList(const std::string& searchGenre) {
    std::vector<Movie> filteredMoviesVector;
    if (searchGenre.empty()){
        std::for_each(this->moviesVectorUser.begin(), this->moviesVectorUser.end(), [&filteredMoviesVector](auto &it){filteredMoviesVector.push_back(it);});
    }
    else {
        std::for_each(this->moviesVectorUser.begin(), this->moviesVectorUser.end(), [&filteredMoviesVector, searchGenre](auto &it){if (it.getGenre() == searchGenre) filteredMoviesVector.push_back(it);});
    }
    emit this->moviesListUpdate(this->moviesListUser, filteredMoviesVector);
}

void GUI::manageWatchList(std::pair<QWidget*, QLayout*> receivedWidgetLayout) {
    QWidget* verticalButtonWidget = new QWidget{};
    QVBoxLayout* verticalButtonLayout = new QVBoxLayout{verticalButtonWidget};

    this->u_add = new QPushButton{"Add"};
    this->u_add->setMinimumHeight(10);
    this->u_delete = new QPushButton{"Delete"};
    this->u_delete->setMinimumHeight(10);
    this->u_done = new QPushButton{"Done"};
    this->u_done->setMinimumHeight(10);

    verticalButtonLayout->addWidget(this->u_add);
    verticalButtonLayout->addWidget(this->u_delete);
    verticalButtonLayout->addWidget(this->u_done);

    this->watchlist = new QListWidget{};
    this->watchlist->setSelectionMode(QAbstractItemView::SingleSelection);
    this->populateUserLists(this->watchlist, this->watchlistVector);

    QObject::connect(this->u_add, &QPushButton::clicked, this, [=](){
        emit this->addToWatchListSignal();
    });
    QObject::connect(this->u_delete, &QPushButton::clicked, this, [=](){
        emit this->deleteFromWatchlistSignal();

    });
    QObject::connect(this->u_done, &QPushButton::clicked, this, [=](){
        delete this->u_add;
        delete this->u_delete;
        delete this->u_done;

        delete this->watchlist;
        delete verticalButtonLayout;
        delete verticalButtonWidget;
        this->us.openFile();
    });

    receivedWidgetLayout.second->addWidget(verticalButtonWidget);
    receivedWidgetLayout.second->addWidget(this->watchlist);
}

std::pair<QWidget*, QFormLayout*> GUI::createFields(std::pair<QWidget*, QLayout*> receivedWidgetLayout) {
    // the fields for add/update - on the right
    QWidget* movieFieldsWidget = new QWidget{};
    QFormLayout* movieFieldsLayout = new QFormLayout{movieFieldsWidget};

    // title
    this->le_title = new QLineEdit{};
    this->le_title->setMinimumHeight(35);
    this->le_title->setPlaceholderText("Title: ");

    // genre
    this->le_genre = new QLineEdit{};
    this->le_genre->setMinimumHeight(35);
    this->le_genre->setPlaceholderText("Genre: ");

    // year of release
    this->le_year_of_release = new QLineEdit{};
    this->le_year_of_release->setMinimumHeight(35);
    this->le_year_of_release->setPlaceholderText("Year of Release: ");

    // nr of likes
    this->le_nr_of_likes = new QLineEdit{};
    this->le_nr_of_likes->setMinimumHeight(35);
    this->le_nr_of_likes->setPlaceholderText("Likes: ");

    // trailer
    this->le_trailer_link = new QLineEdit{};
    this->le_trailer_link->setMinimumHeight(35);
    this->le_trailer_link->setPlaceholderText("Trailer: ");

    movieFieldsLayout->addRow(this->le_title);
    movieFieldsLayout->addRow(this->le_genre);
    movieFieldsLayout->addRow(this->le_year_of_release);
    movieFieldsLayout->addRow(this->le_nr_of_likes);
    movieFieldsLayout->addRow(this->le_trailer_link);

    receivedWidgetLayout.second->addWidget(movieFieldsWidget);

    std::pair<QWidget*, QFormLayout*> returnValue{movieFieldsWidget, movieFieldsLayout};
    return returnValue;
}

void GUI::deleteFields(std::pair<QWidget*, QLayout*> receivedWidgetLayout) {
    // title
    delete this->le_title;

    // genre
    delete this->le_genre;

    // year of release
    delete this->le_year_of_release;

    // nr of likes
    delete this->le_nr_of_likes;

    // trailer
    delete this->le_trailer_link;

    delete receivedWidgetLayout.second;
    delete receivedWidgetLayout.first;
}



void GUI::connectSignalsAndSlots() {
    QObject::connect(this, SIGNAL(dataBaseUpdate()), this, SLOT(populateList()));
    QObject::connect(this, SIGNAL(addMovieSignal(std::vector<std::string>, QLabel*)),this, SLOT(addMovie(std::vector<std::string>, QLabel*)));
    QObject::connect(this, SIGNAL(updateMovieSignal(std::vector<std::string>, QLabel*)),this, SLOT(updateMovie(std::vector<std::string>, QLabel*)));
    QObject::connect(this, SIGNAL(deleteMovieSignal(const std::string&)),this, SLOT(deleteMovie(const std::string&)));

    QObject::connect(this, SIGNAL(moviesListUpdate(QListWidget*, const std::vector<Movie>&)),this, SLOT(populateUserLists(QListWidget*, const std::vector<Movie>&)));
    QObject::connect(this, SIGNAL(watchListUpdate(QListWidget*, const std::vector<Movie>&)), this, SLOT(populateUserLists(QListWidget*, const std::vector<Movie>&)));
    ;
    QObject::connect(this, SIGNAL(filterListSignal(const std::string&)),this, SLOT(filterList(const std::string&)));
    QObject::connect(this, SIGNAL(addToWatchListSignal()), this, SLOT(addToWatchList()));
    QObject::connect(this, SIGNAL(deleteFromWatchlistSignal()), this, SLOT(deleteFromWatchlist()));
}

void GUI::fieldsChanged() {
    int idx = this->getSelectedIndex(this->moviesList);
    if (idx == -1)
        return;

    if (idx >= this->moviesVector.size())
        return;

    Movie m = this->moviesVector[idx];

    this->le_title->setText(QString::fromStdString(m.getTitle()));
    this->le_title->setReadOnly(true);
    this->le_genre->setText(QString::fromStdString(m.getGenre()));
    this->le_year_of_release->setText(QString::fromStdString(std::to_string(m.getYearOfRelease())));
    this->le_nr_of_likes->setText(QString::fromStdString(std::to_string(m.getNrOfLikes())));
    this->le_trailer_link->setText(QString::fromStdString(m.getTrailer()));
}

int GUI::getSelectedIndex(QListWidget* givenList) {
    if (givenList->count() == 0)
        return -1;

    // get selected index
    QModelIndexList index = givenList->selectionModel()->selectedIndexes();
    if (index.size() == 0) {
        this->le_title->clear();
        this->le_genre->clear();
        this->le_year_of_release->clear();
        this->le_nr_of_likes->clear();
        this->le_trailer_link->clear();
        return -1;
    }

    int idx = index.at(0).row();
    return idx;
}

void GUI::addMovie(std::vector<std::string> receivedFields, QLabel* errorMessage) {
    bool flag = true;
    try {
        this->as.addElement(receivedFields[0], receivedFields[1], receivedFields[2], receivedFields[3], receivedFields[4]);
    }
    catch (const CustomException& e) {
        errorMessage->setText(QString::fromStdString(e.what()));
        errorMessage->setStyleSheet("QLabel { color : red; }");
        flag = false;
    }

    if (flag)
        emit this->dataBaseUpdate();
}

void GUI::updateMovie(std::vector<std::string> receivedFields, QLabel* errorMessage) {
    bool flag = true;
    try {
        this->as.updateElement(receivedFields[0], receivedFields[1], receivedFields[2], receivedFields[3], receivedFields[4]);
    }
    catch (const CustomException& e) {
        errorMessage->setText(e.what());
        errorMessage->setStyleSheet("QLabel { color : red; }");
        flag = false;
    }

    if (flag)
        emit this->dataBaseUpdate();
}

void GUI::deleteMovie(const std::string& receivedTitle) {
    try {
        this->as.deleteElement(receivedTitle);
    }
    catch (const CustomException& e) {
    }
    emit this->dataBaseUpdate();
}

std::vector<std::string> GUI::getFieldsContent() {
    std::vector<std::string> receivedFields;
    QString movieTile = this->le_title->text();
    QString movieGenre = this->le_genre->text();
    QString movieYearOfRelease = this->le_year_of_release->text();
    QString movieNrOfLikes = this->le_nr_of_likes->text();
    QString movieTrailer = this->le_trailer_link->text();

    receivedFields.push_back(movieTile.toStdString());
    receivedFields.push_back(movieGenre.toStdString());
    receivedFields.push_back(movieYearOfRelease.toStdString());
    receivedFields.push_back(movieNrOfLikes.toStdString());
    receivedFields.push_back(movieTrailer.toStdString());

    return receivedFields;
}

void GUI::addToWatchList() {
    int idx = this->getSelectedIndex(this->moviesListUser);
    Movie* addMovie = &this->moviesVectorUser[idx];

    auto it = std::find(this->moviesVectorUser.begin(), this->moviesVectorUser.end(), addMovie->getTitle());
    if (it == this->moviesVectorUser.end()) {
        return;
    }

    this->us.addElement(addMovie->getTitle(), addMovie->getGenre(), addMovie->getYearOfRelease(), addMovie->getNrOfLikes(), addMovie->getTrailer());

    this->watchlistVector.push_back(*addMovie);
    this->moviesVectorUser.erase(it);


    emit this->moviesListUpdate(this->moviesListUser, this->moviesVectorUser);
    emit this->watchListUpdate(this->watchlist, this->watchlistVector);
//    std::string url = std::string("open ").append(addMovie->getTrailer());
//    system(url.c_str());
}

void GUI::deleteFromWatchlist() {
    int idx = this->getSelectedIndex(this->watchlist);
    if (idx != -1) {
        Movie* deleteMovie = &this->watchlistVector[idx];
        auto it = std::find(this->watchlistVector.begin(), this->watchlistVector.end(),
                            deleteMovie->getTitle());
        if (it == this->watchlistVector.end()) {
            return;
        }

        QWidget *popup = new QWidget;
        QVBoxLayout *popup_layout = new QVBoxLayout{popup};

        QPushButton *like = new QPushButton("Like");
        QPushButton *dislike = new QPushButton("Dislike");

        popup->resize(300, 300);
        popup_layout->addWidget(like);
        popup_layout->addWidget(dislike);
        popup->show();

        this->u_add->setDisabled(true);
        this->u_delete->setDisabled(true);
        this->u_done->setDisabled(true);
        this->u_close->setDisabled(true);

        QObject::connect(like, &QPushButton::clicked, this, [=]() {
            this->u_add->setDisabled(false);
            this->u_delete->setDisabled(false);
            this->u_done->setDisabled(false);
            this->u_close->setDisabled(false);
            delete like;
            delete dislike;
            delete popup_layout;
            delete popup;
            int new_number_of_likes = deleteMovie->getNrOfLikes() + 1;
            deleteMovie->setNrOfLikes(new_number_of_likes);
            this->as.updateElement(deleteMovie->getTitle(), deleteMovie->getGenre(),
                                       std::to_string(deleteMovie->getYearOfRelease()),
                                       std::to_string(deleteMovie->getNrOfLikes()), deleteMovie->getTrailer());

            this->us.deleteElement(this->watchlistVector[idx].getTitle());

            this->moviesVectorUser.push_back(this->watchlistVector[idx]);
            this->watchlistVector.erase(it);

            emit this->moviesListUpdate(this->moviesListUser, this->moviesVectorUser);
            emit this->watchListUpdate(this->watchlist, this->watchlistVector);

        });

        QObject::connect(dislike, &QPushButton::clicked, this, [=]() {
            this->u_add->setDisabled(false);
            this->u_delete->setDisabled(false);
            this->u_done->setDisabled(false);
            this->u_close->setDisabled(false);
            delete like;
            delete dislike;
            delete popup_layout;
            delete popup;

            this->us.deleteElement(this->watchlistVector[idx].getTitle());

            this->moviesVectorUser.push_back(this->watchlistVector[idx]);
            this->watchlistVector.erase(it);

            emit this->moviesListUpdate(this->moviesListUser, this->moviesVectorUser);
            emit this->watchListUpdate(this->watchlist, this->watchlistVector);

        });

    }
}













