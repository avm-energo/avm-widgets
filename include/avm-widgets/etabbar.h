#pragma once

#include <QTabBar>
#include <QWidget>
#include <export.h>

/// \brief QTabBar that shrinks the "+" (new-tab) tab to fit its text content.
class WD_EXPORT ETabBar : public QTabBar
{
    Q_OBJECT
public:
    explicit ETabBar(QWidget *parent = nullptr);

protected:
    /// \brief Returns a compact size for the last tab (the "+" button); delegates to base for others.
    QSize tabSizeHint(int index) const override;
};
