#pragma once
#include "../Service/AdminService.h"
#include "../Service/UserService.h"
#include "../Operation/OperationExecution.h"
#include "MoviesTableModel.h"
#include <QWidget>
#include <QListWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QShortcut>
#include <QTableView>


class GUI : public QWidget {
    Q_OBJECT

public:
    GUI(QWidget *parent = Q_NULLPTR);
    ~GUI();

private:
    AdminService as;
    OperationExecution* op;
    UserService us;

    std::vector<Movie> moviesVector;
    QListWidget* moviesList;
    std::vector<int> moviesTableRows;


    std::vector<Movie> moviesVectorUser;
    MoviesTableModel* moviesTableModelUser;
    QTableView*  moviesTableViewUser;
    std::vector<int> moviesTableUserRows;

    std::vector<Movie> watchlistVector;
    MoviesTableModel* watchlistModel;
    QTableView* watchlistView;
    std::vector<int> watchlistRows;

    QPushButton* admin;
    QPushButton* user;
    QPushButton* close;

    QPushButton* a_add;
    QPushButton* a_delete;
    QPushButton* a_update;
    QPushButton* a_undo;
    QPushButton* a_redo;
    QShortcut* shortcutUndo = new QShortcut(QKeySequence("Command + Z"), this);
    QShortcut* shortcutRedo = new QShortcut(QKeySequence("Command + Shift + Z"), this);
    QPushButton* a_close;

    QLineEdit* le_title;
    QLineEdit* le_genre;
    QLineEdit* le_year_of_release;
    QLineEdit* le_nr_of_likes;
    QLineEdit* le_trailer_link;

    QPushButton* u_html;
    QPushButton* u_csv;
    QLineEdit* le_filter;
    QPushButton* u_filter;
    QPushButton* u_add;
    QPushButton* u_delete;
    QPushButton* u_close;
    QPushButton* u_done;
    QPushButton* u_watchlist;

    QWidget* mainWidget = new QWidget{};
    QVBoxLayout* mainLayout = new QVBoxLayout{this->mainWidget};

    // methods
    void initGUI();

    void connectSignalsAndSlots();

    void startMenu();
    void adminMenu();
    void userMenu();
    void userMenuOptions();


    void addFunctionality(std::pair<QWidget*, QLayout*>);
    void updateFunctionality(std::pair<QWidget*, QLayout*>);
    void deleteFunctionality();
    void manageWatchList(std::pair<QWidget*, QLayout*>);


    std::pair<QWidget*, QFormLayout*> createFields(std::pair<QWidget*, QLayout*>);
    void deleteFields(std::pair<QWidget*, QLayout*>);
    std::vector<std::string> getFieldsContent();

    void fieldsChanged();
    int getSelectedIndex(QListWidget*);



signals:
    void addMovieSignal(std::vector<std::string>, QLabel*);
    void updateMovieSignal(std::vector<std::string>, QLabel*);
    void deleteMovieSignal(const std::string&);
    void undoSignal();
    void redoSignal();
    void filterListSignal(const std::string&);
    void addToWatchListSignal();
    void deleteFromWatchlistSignal();
    void dataBaseUpdate();
    void moviesListUpdate(std::vector<Movie>);
    void watchListUpdate(std::vector<Movie>);

public slots:
    void populateList();
    void populateUserList(std::vector<Movie>);
    void populateWatchlist(std::vector<Movie>);
    void addMovie(std::vector<std::string>, QLabel*);
    void deleteMovie(const std::string&);
    void undo();
    void redo();
    void updateMovie(std::vector<std::string>, QLabel*);
    void filterList(const std::string&);
    void addToWatchList();
    void deleteFromWatchlist();
};
