#include <QHBoxLayout>
#include <QLabel>
#include <QStringListModel>
#include <avm-widgets/cbfunc.h>

CBFunc::CBFunc()
{
}

QComboBox *CBFunc::New(QWidget *parent, const QString &cbname, const QStringList &cbsl)
{
    auto cb = New(parent, cbsl);
    cb->setObjectName(cbname);
    return cb;
}

QComboBox *CBFunc::New(QWidget *parent, const QStringList &cbsl)
{
    auto cb = new QComboBox(parent);
    auto cblm = new QStringListModel(cbsl, cb);
    cb->setModel(cblm);
    return cb;
}

QWidget *CBFunc::newLBL(QWidget *parent, const QString &caption, const QString &cbname, const QStringList &cbsl)
{
    QWidget *w = new QWidget(parent);
    w->setContentsMargins(0, 0, 0, 0);
    auto hlyout = new QHBoxLayout;
    auto lbl = new QLabel(caption, w);
    hlyout->addWidget(lbl, 0);
    QComboBox *cb = New(w, cbname, cbsl);
    hlyout->addWidget(cb, 10);
    w->setLayout(hlyout);
    return w;
}

QString CBFunc::data(const QWidget *parent, const QString &cbname)
{
    auto cb = parent->findChild<QComboBox *>(cbname);
    if (cb == nullptr)
        return QString();
    return cb->currentText();
}

int CBFunc::index(const QObject *parent, const QString &cbname)
{
    auto cb = parent->findChild<QComboBox *>(cbname);
    if (cb == nullptr)
        return -1;
    return cb->currentIndex();
}

bool CBFunc::setData(const QWidget *parent, const QString &cbname, const QString &cbvalue)
{
    auto cb = parent->findChild<QComboBox *>(cbname);
    if (cb == nullptr)
        return false;
    cb->setCurrentText(cbvalue);
    return true;
}

bool CBFunc::setIndex(const QObject *parent, const QString &cbname, int index)
{
    auto cb = parent->findChild<QComboBox *>(cbname);
    if (cb == nullptr)
        return false;
    if (index < cb->count())
    {
        cb->setCurrentIndex(index);
        return true;
    }

    return false;
}

bool CBFunc::setColor(QWidget *parent, const QString &cbname, const QString &color)
{
    auto cb = parent->findChild<QComboBox *>(cbname);
    if (cb == nullptr)
        return false;
    // http://forum.sources.ru/index.php?showtopic=313950
    auto pal = cb->palette();
    pal.setColor(QPalette::Text, QColor(color));
    cb->setPalette(pal);
    return true;
}
