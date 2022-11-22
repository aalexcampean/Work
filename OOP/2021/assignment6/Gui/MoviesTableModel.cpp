#include "MoviesTableModel.h"
#include <qlabel.h>

MoviesTableModel::MoviesTableModel(std::vector<Movie>& designatedVector, QObject *parent): inputVector(designatedVector) {}

MoviesTableModel::~MoviesTableModel() {}

int MoviesTableModel::rowCount(const QModelIndex &parent) const {
    return this->inputVector.size();
}

int MoviesTableModel::columnCount(const QModelIndex &parent) const {
    return 6;
}

QVariant MoviesTableModel::data(const QModelIndex &index, int role) const {
    int row = index.row();
    int column = index.column();

    if (role == Qt::DisplayRole) {
        if (column == 0) {
            std::string title = this->inputVector[row].getTitle();
            return QString::fromStdString(title);
        }
        else if (column == 1) {
            std::string genre = this->inputVector[row].getGenre();
            return QString::fromStdString(genre);
        }
        else if (column == 2) {
            int yearOfRelease = this->inputVector[row].getYearOfRelease();
            return QString::number(yearOfRelease);
        }
        else if (column == 3) {
            int numberOfLikes = this->inputVector[row].getNrOfLikes();
            return QString::number(numberOfLikes);
        }
        else if (column == 4) {
            std::string trailer = this->inputVector[row].getTrailer();
            return QString::fromStdString(trailer);
        }
        else {}
    }
    else if (role == Qt::DecorationRole && column == 5) {
        QPixmap pic("play-button-overlay.png");
        return pic;
    }
    else {}
    return QVariant();
}


