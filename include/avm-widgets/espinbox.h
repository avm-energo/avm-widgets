#pragma once

#include <QSpinBox>
#include <QWheelEvent>
#include <export.h>

/// \brief QSpinBox that ignores wheel events unless the widget has keyboard focus,
///        preventing accidental value changes while scrolling a parent widget.
class WD_EXPORT ESpinBox : public QSpinBox
{
    Q_OBJECT
public:
    explicit ESpinBox(QWidget *parent = nullptr);

protected:
    /// \brief Ignores wheel events when the widget does not have focus.
    void wheelEvent(QWheelEvent *event) override;
};
