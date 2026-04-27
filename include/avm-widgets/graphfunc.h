#pragma once

#include <QLabel>
#include <export.h>

/// \brief Factory functions for graphical elements: icons, circles, LED indicators, and separator lines.
class WD_EXPORT GraphFunc
{
public:
    GraphFunc();

    /// \brief Creates a QLabel displaying the pixmap loaded from \a iconpath (empty = blank label).
    [[nodiscard]] static QLabel *newIcon(QWidget *parent, const QString &iconpath = "");
    /// \brief Returns a \a radius × \a radius pixmap of a circle with a radial gradient from \a color to black.
    [[nodiscard]] static QPixmap newCircle(QColor color, int radius);
    /// \brief Returns a square pixmap of a realistic LED indicator of the given \a color and \a height.
    [[nodiscard]] static QPixmap newLedIndicator(QColor color, float height);
    /// \brief Renders the SVG document in \a str at \a size and returns the resulting pixmap.
    [[nodiscard]] static QPixmap newSVG(QString &str, QSize size);
    /// \brief Creates a horizontal separator line (QFrame::HLine | Sunken).
    [[nodiscard]] static QFrame *newHLine(QWidget *parent);
    /// \brief Creates a vertical separator line (QFrame::VLine | Sunken).
    [[nodiscard]] static QFrame *newVLine(QWidget *parent);
};
