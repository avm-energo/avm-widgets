#pragma once

#include <QDoubleSpinBox>
#include <export.h>

/// \brief QDoubleSpinBox that ignores wheel events unless the widget has keyboard focus,
///        preventing accidental value changes while scrolling a parent widget.
class WD_EXPORT EDoubleSpinBox : public QDoubleSpinBox
{
    Q_OBJECT
public:
    explicit EDoubleSpinBox(QWidget *parent = nullptr);

protected:
    /// \brief Ignores wheel events when the widget does not have focus.
    void wheelEvent(QWheelEvent *event) override;
};
