#include "MoviesListModel.h"

MoviesTableModel::MoviesTableModel(AdminService& provided_as, QObject *parent): as(provided_as){}

MoviesTableModel::~MoviesTableModel() {}

int MoviesTableModel::rowCount(const QModelIndex &parent) const {
    return this->as.getLength();
}
QVariant MoviesTableModel::data(const QModelIndex &index, int role) const {
    std::vector<Movie> dataBase = this->as.getDataBase();
}