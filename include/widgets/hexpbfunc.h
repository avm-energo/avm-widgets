#pragma once
#include <widgets/export.h>
#include <widgets/hexagonbutton.h>

class WD_EXPORT HexPBFunc
{
public:
    template <typename Functor>
    inline static HexagonButton *New(QWidget *parent, const QString &pbname, Functor &&functor,
        const QString &icon = "", const QString &pbtooltip = "")
    {
        auto pb = new HexagonButton(parent);
        pb->setObjectName(pbname);
        pb->setIcon(QIcon(icon));
        pb->setData(icon);
        pb->setToolTip(pbtooltip);
        pb->setMinimumSize(50, 50);
        pb->setIconSize(QSize(50, 50));
        QObject::connect(pb, &QPushButton::clicked, functor);
        return pb;
    }

    static void SetProcessed(QWidget *parent, const QString &name);
    static void SetRestricted(QWidget *parent, const QString &name);
    static void setNormal(QWidget *parent, const QString &name);
    static void setIcon(QWidget *parent, const QString &name, QStringList &attrs, QStringList &values);
};
