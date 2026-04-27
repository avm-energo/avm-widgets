#pragma once

#include <avm-widgets/elabel.h>
#include <export.h>

/// \brief Factory and accessor helpers for ELabel widgets.
class WD_EXPORT LBLFunc
{
public:
    LBLFunc();

    /// \brief Finds an ELabel by \a lblname inside \a parent.
    [[nodiscard]] static ELabel *label(QWidget *parent, const QString &lblname);
    /// \brief Creates a new ELabel with text \a text, optional pixmap \a pm and tooltip \a lbltip.
    [[nodiscard]] static ELabel *New(QWidget *parent, const QString &text, const QString &lblname = "",
        const QPixmap *pm = nullptr, const QString &lbltip = "");
    /// \brief Creates a new transparent-background ELabel; set \a fixed for a fixed-size policy.
    [[nodiscard]] static ELabel *newT(QWidget *parent, const QString &text, const QString &lblname = "",
        const QString &lbltip = "", bool fixed = false);
    /// \brief Creates a label+value pair widget: a read-only label with a caption label beside it.
    [[nodiscard]] static QWidget *newLBL(QWidget *parent, QString lblname, QString caption, bool enabled = false);

    /// \brief Sets the pixmap of a label found by \a lblname.
    static bool setImage(QWidget *parent, const QString &lblname, QPixmap *pm);
    /// \brief Sets the foreground text color (hex string) of a label found by \a lblname.
    static bool setColor(QWidget *parent, const QString &lblname, const QString &lblcolor);
    /// \brief Sets the background color (hex string) of a label found by \a lblname via stylesheet.
    static bool setBGColor(QWidget *parent, const QString &lblname, const QString &color);
    /// \brief Sets the text of a label found by \a lblname and optionally enables/disables it.
    static bool setText(QWidget *parent, const QString &lblname, const QString &lbltext = "", bool enabled = true);
    /// \brief Returns the displayed text of a label found by \a lblname.
    [[nodiscard]] static QString text(QWidget *parent, const QString &lblname);
    /// \brief Stores \a data as the ELabel payload (does not change displayed text).
    static bool setData(QWidget *parent, const QString &lblname, const QString &data);
    /// \brief Returns the ELabel payload string for the label found by \a lblname.
    [[nodiscard]] static QString data(QWidget *parent, const QString &lblname);
};
