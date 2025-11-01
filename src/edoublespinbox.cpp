#include <QWheelEvent>
#include <avm-widgets/edoublespinbox.h>

EDoubleSpinBox::EDoubleSpinBox(QWidget *parent) : QDoubleSpinBox(parent)
{
    setFocusPolicy(Qt::StrongFocus);
}

void EDoubleSpinBox::wheelEvent(QWheelEvent *event)
{
    if (!hasFocus())
    {
        event->ignore();
    }
    else
    {
        QDoubleSpinBox::wheelEvent(event);
    }
}
