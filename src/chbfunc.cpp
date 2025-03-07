#include <QHBoxLayout>
#include <QLabel>
#include <gen/error.h>
#include <widgets/chbfunc.h>

QCheckBox *ChBFunc::New(QWidget *parent, const QString &chbname, const QString &chbtext)
{
    auto chb = new QCheckBox(parent);
    chb->setObjectName(chbname);
    chb->setText(chbtext);
    return chb;
}

QWidget *ChBFunc::NewLBL(QWidget *parent, const QString &caption, const QString &chbname, const QString &chbtext)
{
    QWidget *w = new QWidget(parent);
    w->setContentsMargins(0, 0, 0, 0);
    auto hlyout = new QHBoxLayout;
    auto lbl = new QLabel(caption, w);
    hlyout->addWidget(lbl, 0);
    QCheckBox *chb = New(w, chbname, chbtext);
    hlyout->addWidget(chb, 10);
    w->setLayout(hlyout);
    return w;
}

bool ChBFunc::Data(const QWidget *parent, const QString &chbname, bool &data)
{
    auto chb = parent->findChild<QCheckBox *>(chbname);
    if (chb == nullptr)
        return false;
    data = chb->isChecked();
    return true;
}

bool ChBFunc::Data(const QWidget *parent, const QString &chbname)
{
    auto chb = parent->findChild<QCheckBox *>(chbname);
    if (chb == nullptr)
    {
        qDebug() << Error::NullDataError;
        return false;
    }
    return chb->isChecked();
}

bool ChBFunc::SetData(QWidget *parent, const QString &chbname, bool data)
{
    auto chb = parent->findChild<QCheckBox *>(chbname);
    if (chb == nullptr)
        return false;
    chb->setChecked(data);
    return true;
}
