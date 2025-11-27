#include <QLabel>
#include <QLayout>
#include <avm-widgets/prbfunc.h>

QProgressBar *PrbFunc::progressBar(QWidget *parent, const QString &prbname)
{
    return parent->findChild<QProgressBar *>(prbname);
}

QProgressBar *PrbFunc::New(QWidget *parent, const QString &prbname)
{
    auto prb = new QProgressBar(parent);
    prb->setObjectName(prbname);
    return prb;
}

QWidget *PrbFunc::newLBL(QWidget *parent, const QString &caption, const QString &prbname, const QString &format)
{
    auto widget = new QWidget(parent);
    widget->setContentsMargins(0, 0, 0, 0);
    auto hlyout = new QHBoxLayout;
    auto lbl = new QLabel(caption, widget);
    hlyout->addWidget(lbl, 0);
    auto prb = New(widget, prbname);
    prb->setFormat(format);
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
