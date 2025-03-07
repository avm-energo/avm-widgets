#include <QLabel>
#include <QRegularExpressionValidator>
#include <widgets/lefunc.h>

QLineEdit *LEFunc::New(QWidget *parent, const QString &lename, const QString &letext, const QString &tooltip)
{
    auto le = new QLineEdit(parent);
    le->setObjectName(lename);
    le->setText(letext);
    le->setToolTip(tooltip);
    return le;
}

PasswordLineEdit *LEFunc::NewPsw(QWidget *parent, const QString &lename, QLineEdit::EchoMode echostyle)
{
    auto le = new PasswordLineEdit(echostyle, parent);
    le->setObjectName(lename);
    return le;
}

QString LEFunc::Data(QObject *parent, const QString &lename)
{
    auto le = parent->findChild<QLineEdit *>(lename);
    if (le == nullptr)
        return QString();
    return le->text();
}

bool LEFunc::SetData(QObject *parent, const QString &lename, const QString &levalue, const QString &restring)
{
    auto le = parent->findChild<QLineEdit *>(lename);
    if (le == nullptr)
        return false;
    le->setText(levalue);
    if (!restring.isEmpty())
    {
        auto validator = new QRegularExpressionValidator(QRegularExpression(restring), parent);
        le->setValidator(validator);
    }
    return true;
}

bool LEFunc::SetColor(QWidget *parent, const QString &lename, const QColor &color)
{
    auto le = parent->findChild<QLineEdit *>(lename);
    if (le == nullptr)
        return false;
    // http://forum.sources.ru/index.php?showtopic=313950
    auto pal = le->palette();
    pal.setColor(QPalette::Text, color);
    le->setPalette(pal);
    return true;
}

QWidget *LEFunc::NewLBL(QWidget *parent, QString caption, QString lename, bool enabled)
{
    auto widget = new QWidget(parent);
    widget->setContentsMargins(0, 0, 0, 0);
    auto hlyout = new QHBoxLayout;
    auto lbl = new QLabel(caption, widget);
    hlyout->addWidget(lbl, 0);
    auto le = new QLineEdit("", widget);
    le->setObjectName(lename);
    le->setEnabled(enabled);
    hlyout->addWidget(le, 10);
    widget->setLayout(hlyout);
    return widget;
}
