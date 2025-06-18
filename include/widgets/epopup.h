#pragma once

#include <QDialog>
#include <widgets/export.h>

class WD_EXPORT EPopup : public QDialog
{
    Q_OBJECT
public:
    enum MessageTypes
    {
        INFOMESSAGE = 0,
        WARNMESSAGE = 1,
        QUESTMSG = 2,
        ERMESSAGE = 3,
        NEXTMSG = 4,
        WITHOUTANYBUTTONS = 5
    };
    const QStringList c_captions = { "Информация", "Предупреждение", "Вопрос", "Ошибка", "Далее" };

    EPopup(QWidget *parent = nullptr);
    EPopup(MessageTypes type, const QString &msg, QWidget *parent = nullptr);
    EPopup(MessageTypes type, QWidget *w, QWidget *parent = nullptr);

    void aboutToClose();

private:
    void Create(MessageTypes &type, QWidget *w, QWidget *parent = nullptr);

signals:
    void accepted();
    void cancelled();
    void closed();

public slots:
    void acceptSlot();
    void cancelSlot();

protected:
    void showEvent(QShowEvent *e);
    void closeEvent(QCloseEvent *e);
    void keyPressEvent(QKeyEvent *e);
};
