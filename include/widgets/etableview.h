#pragma once

#include <QPaintEvent>
#include <QResizeEvent>
#include <QTableView>
#include <widgets/export.h>

class WD_EXPORT ETableView : public QTableView
{
    Q_OBJECT
public:
    explicit ETableView(QWidget *parent = nullptr);

public slots:
    void dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles);

protected:
    void resizeEvent(QResizeEvent *e);
};
