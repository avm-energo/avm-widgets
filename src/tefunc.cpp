#include <widgets/tefunc.h>

bool TEFunc::SetData(QWidget *parent, const QString &tename, const QString &tetext)
{
    auto te = parent->findChild<QTextEdit *>(tename);
    if (te == nullptr)
        return false;
    te->setText(tetext);
    return true;
}

bool TEFunc::AppendData(QWidget *parent, const QString &tename, const QString &tetext)
{
    auto te = parent->findChild<QTextEdit *>(tename);
    if (te == nullptr)
        return false;
    te->append(tetext);
    return true;
}

bool TEFunc::Data(QWidget *parent, const QString &tename, QString &tevalue)
{
    auto te = parent->findChild<QTextEdit *>(tename);
    if (te == nullptr)
        return false;
    tevalue = te->toPlainText();
    return true;
}
