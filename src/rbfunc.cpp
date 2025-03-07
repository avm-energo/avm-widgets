#include <QHBoxLayout>
#include <QLabel>
#include <widgets/rbfunc.h>

QRadioButton *RBFunc::New(QWidget *parent, const QString &rbtext, const QString &rbname)
{
    auto rb = new QRadioButton(parent);
    rb->setObjectName(rbname);
    rb->setText(rbtext);
    return rb;
}

QWidget *RBFunc::NewLBL(QWidget *parent, const QString &caption, const QString &rbtext, const QString &rbname)
{
    auto widget = new QWidget(parent);
    widget->setContentsMargins(0, 0, 0, 0);
    auto hlyout = new QHBoxLayout;
    auto lbl = new QLabel(caption, widget);
    hlyout->addWidget(lbl, 0);
    auto rb = New(widget, rbtext, rbname);
    hlyout->addWidget(rb, 10);
    widget->setLayout(hlyout);
    return widget;
}

bool RBFunc::Data(QWidget *parent, const QString &rbname, bool &data)
{
    auto rb = parent->findChild<QRadioButton *>(rbname);
    if (rb == nullptr)
        return false;
    data = rb->isChecked();
    return true;
}

bool RBFunc::SetData(QWidget *parent, const QString &rbname, bool data)
{
    auto rb = parent->findChild<QRadioButton *>(rbname);
    if (rb == nullptr)
        return false;
    rb->setChecked(data);
    return true;
}
