#include <avm-widgets/tefunc.h>

bool TEFunc::setData(QWidget *parent, const QString &tename, const QString &tetext)
{
    auto te = parent->findChild<QTextEdit *>(tename);
    if (te == nullptr)
        return false;
    te->setText(tetext);
    return true;
}

QTextEdit *TEFunc::textedit(QWidget *parent, const QString &tename)
{
    return parent->findChild<QTextEdit *>(tename);
}

QTextEdit *TEFunc::New(QWidget *parent, const QString &tename)
{
    QTextEdit *te = new QTextEdit(parent);
    te->setObjectName(tename);
    return te;
}

bool TEFunc::appendData(QWidget *parent, const QString &tename, const QString &tetext)
{
    auto te = parent->findChild<QTextEdit *>(tename);
    if (te == nullptr)
        return false;
    te->append(tetext);
    return true;
}

bool TEFunc::data(QWidget *parent, const QString &tename, QString &tevalue)
{
    auto te = parent->findChild<QTextEdit *>(tename);
    if (te == nullptr)
        return false;
    tevalue = te->toPlainText();
    return true;
}
