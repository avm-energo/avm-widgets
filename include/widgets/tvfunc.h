#pragma once

#include <QTableView>
#include <widgets/export.h>

class WD_EXPORT TVFunc
{
public:
    [[nodiscard]] static QString Field(QWidget *parent, const QString &tvname, int column, bool isid = false);
    static void AutoResize(QWidget *parent, const QString &tvname);
    static void SetModel(QWidget *parent, const QString &tvname, QAbstractItemModel *model, bool sortenable = false);
    [[nodiscard]] static QTableView *New(QWidget *parent, const QString &tvname, QAbstractItemModel *model);
    [[nodiscard]] static QAbstractItemModel *Model(QWidget *parent, const QString &tvname);

    static void Sort(QWidget *parent, const QString &tvname, int column, Qt::SortOrder sortorder);
    [[nodiscard]] static QVariant Data(QWidget *parent, const QString &tvname, int column);
};
