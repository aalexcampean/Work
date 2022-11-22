//
// Created by Alex Campean on 11.06.2022.
//

#include "IdeasTableModel.h"
#include <qlabel.h>

IdeasTableModel::IdeasTableModel(std::vector<Idea>& vector, QObject *parent): inputVector(vector) {}

IdeasTableModel::~IdeasTableModel() {}

int IdeasTableModel::rowCount(const QModelIndex &parent) const {
    return this->inputVector.size();
}

int IdeasTableModel::columnCount(const QModelIndex &parent) const {
    return 4;
}

QVariant IdeasTableModel::data(const QModelIndex &index, int role) const {
    int row = index.row();
    int column = index.column();

    if (role == Qt::DisplayRole) {
        if (column == 0) {
            std::string description = this->inputVector[row].getDescription();
            return QString::fromStdString(description);
        }
        else if (column == 1) {
            std::string status = this->inputVector[row].getStatus();
            return QString::fromStdString(status);
        }
        else if (column == 2) {
            std::string creator = this->inputVector[row].getCreator();
            return QString::fromStdString(creator);
        }
        else if (column == 3) {
            int act = this->inputVector[row].getAct();
            return QString::number(act);
        }
        else {}
    }
    else {}
    return QVariant();
}


