#pragma once

#include <QDoubleSpinBox>
#include <export.h>

class WD_EXPORT EDoubleSpinBox : public QDoubleSpinBox
{
    Q_OBJECT
public:
    EDoubleSpinBox(QWidget *parent = nullptr);

protected:
    virtual void wheelEvent(QWheelEvent *event);
};
