#pragma once

#include <QTableView>
#include <export.h>

/// \brief Factory and accessor helpers for QTableView widgets.
class WD_EXPORT TVFunc
{
public:
    /// \brief Finds a QTableView by \a tvname inside \a parent.
    [[nodiscard]] static QTableView *tableview(QWidget *parent, const QString &tvname);
    /// \brief Creates a new QTableView and assigns \a model to it.
    [[nodiscard]] static QTableView *New(QWidget *parent, const QString &tvname, QAbstractItemModel *model);
    /// \brief Returns the model currently set on the table view found by \a tvname.
    [[nodiscard]] static QAbstractItemModel *model(QWidget *parent, const QString &tvname);
    /// \brief Returns the data of the selected row's \a column; if \a isid returns the id column.
    [[nodiscard]] static QString field(QWidget *parent, const QString &tvname, int column, bool isid = false);
    /// \brief Calls resizeColumnsToContents() on the table view found by \a tvname.
    static void autoResize(QWidget *parent, const QString &tvname);
    /// \brief Replaces the model; optionally enables column sorting.
    static void setModel(QWidget *parent, const QString &tvname, QAbstractItemModel *model, bool sortenable = false);

    /// \brief Sorts the table by \a column using \a sortorder.
    static void sort(QWidget *parent, const QString &tvname, int column, Qt::SortOrder sortorder);
    /// \brief Returns the data of the currently selected row's \a column as QVariant.
    [[nodiscard]] static QVariant data(QWidget *parent, const QString &tvname, int column);
};
