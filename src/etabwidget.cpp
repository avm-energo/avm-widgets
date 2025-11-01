#include <avm-widgets/etabwidget.h>
#include <avm-widgets/etabbar.h>

ETabWidget::ETabWidget(bool editable, const QString &widgetName, QWidget *parent) : QTabWidget(parent)
{
    ETabBar *bar = new ETabBar;
    setTabBar(bar);
    setObjectName(widgetName);
    m_isEditable = editable;
    setTabsClosable(m_isEditable);
    if (m_isEditable)
    {
        connect(this, &ETabWidget::tabCloseRequested, this, &ETabWidget::closeTab);
        insertTab(0, new QWidget, "+");
        tabBar()->setTabButton(0, QTabBar::RightSide, nullptr);
        tabBar()->connect(tabBar(), &QTabBar::tabBarClicked, this, &ETabWidget::tabClicked);
    }
}

int ETabWidget::addTab(QWidget *widget, const QString &caption)
{
    if (m_isEditable)
    {
        int newTabIndex = count() - 1;
        insertTab(newTabIndex, widget, caption);
        setCurrentIndex(newTabIndex);
        return newTabIndex;
    }
    else
        return QTabWidget::addTab(widget, caption);
}

void ETabWidget::setTabWidget(int tabIndex, QWidget *widget, const QString &caption)
{
    int currentindex = currentIndex();
    removeTab(tabIndex);
    insertTab(tabIndex, widget, caption);
    setCurrentIndex(currentindex);
}

void ETabWidget::closeTab(int index)
{
    int plusTabIndex = count() - 1;
    if ((tabBar()->count() > 1) && (index != plusTabIndex))
    {
        removeTab(index);
        if (count() > 1)
            setCurrentIndex(0);
    }
}

void ETabWidget::tabClicked(int index)
{
    int plusTabIndex = count() - 1;
    if (index == plusTabIndex)
    {
        insertTab(plusTabIndex, new QWidget, "@");
        emit newTabCreated(plusTabIndex);
        setCurrentIndex(plusTabIndex);
    }
}
