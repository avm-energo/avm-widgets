#include <avm-widgets/etabbar.h>

ETabBar::ETabBar(QWidget *parent) : QTabBar(parent)
{
}

QSize ETabBar::tabSizeHint(int index) const
{
    int plusIndex = count() - 1;
    if (index == plusIndex)
    {
        return fontMetrics().boundingRect(tabText(index)).size() + QSize(20, 20);
    }
    else
        return QTabBar::tabSizeHint(index);
}
