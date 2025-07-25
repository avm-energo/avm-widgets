#include <QLabel>
#include <QLayout>
#include <widgets/prbfunc.h>

QProgressBar *PrbFunc::New(QWidget *parent, const QString &prbname)
{
    auto rb = new QProgressBar(parent);
    rb->setObjectName(prbname);
    return rb;
}

QWidget *PrbFunc::NewLBL(QWidget *parent, const QString &caption, const QString &prbname)
{
    auto widget = new QWidget(parent);
    widget->setContentsMargins(0, 0, 0, 0);
    auto hlyout = new QHBoxLayout;
    auto lbl = new QLabel(caption, widget);
    hlyout->addWidget(lbl, 0);
    auto prb = New(widget, prbname);
    hlyout->addWidget(prb, 10);
    widget->setLayout(hlyout);
    return widget;
}

bool PrbFunc::setRange(QWidget *parent, const QString &prbname, qint64 value)
{
    auto prb = parent->findChild<QProgressBar *>(prbname);
    if (prb == nullptr)
        return false;
    prb->setRange(0, value);
    return true;
}

bool PrbFunc::setValue(QWidget *parent, const QString &prbname, qint64 value)
{
    auto prb = parent->findChild<QProgressBar *>(prbname);
    if (prb == nullptr)
        return false;
    prb->setValue(value);
    return true;
}
