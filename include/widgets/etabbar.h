#pragma once

#include <QTabBar>
#include <QWidget>
#include <widgets/export.h>

class WD_EXPORT ETabBar : public QTabBar
{
    Q_OBJECT
public:
    ETabBar(QWidget *parent = nullptr);

protected:
    QSize tabSizeHint(int index) const;

private slots:
};
