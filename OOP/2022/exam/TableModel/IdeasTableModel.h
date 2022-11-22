//
// Created by Alex Campean on 11.06.2022.
//

#pragma once

#include <QAbstractListModel>
#include <qpixmap.h>
#include "../Domain/Idea.h"

class IdeasTableModel : public QAbstractTableModel {
private:
    std::vector<Idea> inputVector;

public:
    IdeasTableModel(std::vector<Idea> &, QObject *parent = nullptr);

    virtual ~IdeasTableModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
};

