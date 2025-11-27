#pragma once

#include <QTableView>
#include <export.h>

class WD_EXPORT TVFunc
{
public:
    [[nodiscard]] static QTableView *tableview(QWidget *parent, const QString &tvname);
    [[nodiscard]] static QTableView *New(QWidget *parent, const QString &tvname, QAbstractItemModel *model);
    [[nodiscard]] static QAbstractItemModel *model(QWidget *parent, const QString &tvname);
    [[nodiscard]] static QString field(QWidget *parent, const QString &tvname, int column, bool isid = false);
    static void autoResize(QWidget *parent, const QString &tvname);
    static void setModel(QWidget *parent, const QString &tvname, QAbstractItemModel *model, bool sortenable = false);

    static void sort(QWidget *parent, const QString &tvname, int column, Qt::SortOrder sortorder);
    [[nodiscard]] static QVariant data(QWidget *parent, const QString &tvname, int column);
};
