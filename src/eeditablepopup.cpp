#include <QKeyEvent>
#include <QVBoxLayout>
#include <avm-widgets/eeditablepopup.h>
#include <avm-widgets/emessagebox.h>
#include <avm-widgets/lblfunc.h>
#include <avm-widgets/lefunc.h>
#include <avm-widgets/pbfunc.h>

EEditablePopup::EEditablePopup(const QString &caption, QWidget *parent) : EPopup(parent)
{
    setAttribute(Qt::WA_DeleteOnClose);
    // Setting default color for editable popup
    setStyleSheet("QDialog {background-color: #c8fcff;}");
    this->caption = caption;
}

void EEditablePopup::addFloatParameter(const QString &name, float *parameter)
{
    m_floatParList[name] = parameter;
}

void EEditablePopup::execPopup()
{
    auto widget = new QWidget(this);
    // widget->setStyleSheet("QWidget {background-color: #c8fcff;}");
    auto layout = new QVBoxLayout;
    layout->addWidget(LBLFunc::New(this, caption));
    for (std::map<QString, float *>::iterator it = m_floatParList.begin(); it != m_floatParList.end(); ++it)
        layout->addWidget(LEFunc::newLBL(this, it->first, it->first, true));
    auto hlyout = new QHBoxLayout;
    hlyout->addStretch(100);
    hlyout->addWidget(PBFunc::New(this, "", "Далее", this, &EEditablePopup::acceptSlot));
    hlyout->addStretch(5);
    hlyout->addWidget(PBFunc::New(this, "", "Отмена", this, &EEditablePopup::cancelSlot));
    hlyout->addStretch(100);
    layout->addLayout(hlyout);
    widget->setLayout(layout);
    auto popupLayout = new QVBoxLayout;
    popupLayout->addWidget(widget);
    setLayout(popupLayout);
    this->adjustSize();
    exec();
}

void EEditablePopup::acceptSlot()
{
    for (std::map<QString, float *>::iterator it = m_floatParList.begin(); it != m_floatParList.end(); ++it)
    {
        bool isOk = false;
        float fl;
        fl = LEFunc::data(this, it->first).toFloat(&isOk);
        float *tmpf = it->second;
        if (isOk)
            *tmpf = fl;
        else
        {
            EMessageBox::warning(this, "Значение " + it->first + "ошибочно, будет принудительно приравнено нулю");
            *tmpf = 0.0;
        }
    }
    emit accepted();
    aboutToClose();
}

void EEditablePopup::cancelSlot()
{
    EPopup::cancelSlot();
}

void EEditablePopup::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Escape)
        cancelSlot();
    if ((e->key() == Qt::Key_Enter) || (e->key() == Qt::Key_Return))
        acceptSlot();
}
