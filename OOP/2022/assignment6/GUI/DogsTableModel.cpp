#include "DogsTableModel.h"
#include <qlabel.h>

DogsTableModel::DogsTableModel(std::vector<Dog>& designatedVector, QObject *parent): inputVector(designatedVector) {}

DogsTableModel::~DogsTableModel() {}

int DogsTableModel::rowCount(const QModelIndex &parent) const {
    return this->inputVector.size();
}

int DogsTableModel::columnCount(const QModelIndex &parent) const {
    return 6;
}

QVariant DogsTableModel::data(const QModelIndex &index, int role) const {
    int row = index.row();
    int column = index.column();

    if (role == Qt::DisplayRole) {
        if (column == 0) {
            std::string title = this->inputVector[row].getBreed();
            return QString::fromStdString(title);
        }
        else if (column == 1) {
            std::string genre = this->inputVector[row].getName();
            return QString::fromStdString(genre);
        }
        else if (column == 2) {
            int yearOfRelease = this->inputVector[row].getAge();
            return QString::number(yearOfRelease);
        }
        else if (column == 3) {
            std::string imageLink = this->inputVector[row].getImage();
            return QString::fromStdString(imageLink);
        }
        else {}
    }
    else if (role == Qt::DecorationRole && column == 4) {
        QPixmap pic("play-button-overlay.png");
        return pic;
    }
    else {}
    return QVariant();
}


