#pragma once

#include <QLabel>
#include <export.h>

class WD_EXPORT GraphFunc
{
public:
    GraphFunc();

    [[nodiscard]] static QLabel *newIcon(QWidget *parent, const QString &iconpath = "");
    [[nodiscard]] static QPixmap newCircle(QColor color, int radius);
    [[nodiscard]] static QPixmap newLedIndicator(QColor color, float height);
    [[nodiscard]] static QPixmap newSVG(QString &str, QSize size);
    [[nodiscard]] static QFrame *newHLine(QWidget *parent);
    [[nodiscard]] static QFrame *newVLine(QWidget *parent);
};
