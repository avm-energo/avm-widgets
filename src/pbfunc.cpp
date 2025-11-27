#include <avm-widgets/pbfunc.h>

QPushButton *PBFunc::pushButton(QWidget *parent, const QString &pbname)
{
    return parent->findChild<QPushButton *>(pbname);
}

QPushButton *PBFunc::newCommon(
    QWidget *parent, const QString &pbname, const QString &text, const QString &icon, const QString &pbtooltip)
{
    auto pb = new QPushButton(text, parent);
    pb->setObjectName(pbname);
    if (!icon.isEmpty())
        pb->setIcon(QIcon(icon));
    pb->setToolTip(pbtooltip);
    return pb;
}
