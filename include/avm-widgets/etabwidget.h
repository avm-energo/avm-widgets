/* class ETabWidget is the editable tab widget with closable tabs and always live tab "plus" to create
 * new tab each time the user clicked it. To use this class one should implement the following:
 * 1) create ETabWidget with true argument:
 *       ETabWidget *etw = new ETabWidget(true);
 * 2) connect the signal newTabCreated of etw to the slot that creates new tab widget:
 *       connect(etw, &ETabWidget::newTabCreated, this, &MainWindow::setNewWidget);
 * 3) call setTabWidget to newly created tab in the slot:
 *       ETabWidget *etw = qobject_cast<ETabWidget *>(sender());
 *           if (etw != nullptr)
 *           {
 *               ... create new widget w ...
 *               etw->setTabWidget(index, w, "New tab");
 *           }
 */

#pragma once

#include <QTabBar>
#include <QTabWidget>
#include <export.h>

class WD_EXPORT ETabWidget : public QTabWidget
{
    Q_OBJECT
public:
     ETabWidget(bool editable = false, const QString &widgetName = "", QWidget *parent = nullptr);

    /// \brief Method adds tabs as it does the default QTabBar while initially creating
    int addTab(QWidget *widget, const QString &caption);
    /// \brief Sets widget to tab newly created (must be called when receiving signal newTabCreated)
    void setTabWidget(int tabIndex, QWidget *widget = nullptr, const QString &caption = "");

signals:
    /// \brief Signal when new tab has been created to set the widget
    void newTabCreated(int index);

private:
    bool m_isEditable;

private slots:
    void closeTab(int index);
    void tabClicked(int index);
};
