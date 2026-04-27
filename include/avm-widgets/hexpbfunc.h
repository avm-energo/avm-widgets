#pragma once
#include <export.h>
#include <avm-widgets/hexagonbutton.h>

/// \brief Factory and state-manipulation helpers for HexagonButton widgets.
class WD_EXPORT HexPBFunc
{
public:
    /// \brief Creates a HexagonButton with icon path \a icon, tooltip \a pbtooltip, and click handler \a functor.
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

    /// \brief Sets the button icon to the "processed" visual state (green fill).
    static void setProcessed(QWidget *parent, const QString &name);
    /// \brief Sets the button icon to the "restricted" visual state (red stroke).
    static void setRestricted(QWidget *parent, const QString &name);
    /// \brief Sets the button icon to the default "normal" visual state.
    static void setNormal(QWidget *parent, const QString &name);
    /// \brief Rewrites SVG attributes \a attrs with \a values and reloads the button icon.
    static void setIcon(QWidget *parent, const QString &name, QStringList &attrs, QStringList &values);
};
