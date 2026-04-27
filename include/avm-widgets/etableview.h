#pragma once

#include <QPaintEvent>
#include <QResizeEvent>
#include <QTableView>
#include <export.h>

/// \brief QTableView with transparent background that auto-resizes columns on data changes.
class WD_EXPORT ETableView : public QTableView
{
    Q_OBJECT
public:
    explicit ETableView(QWidget *parent = nullptr);

public slots:
    /// \brief Auto-resizes all columns to content whenever the model data changes.
    void dataChanged(
        const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles) override;

protected:
    /// \brief Auto-resizes all columns to content on widget resize.
    void resizeEvent(QResizeEvent *e) override;
};
