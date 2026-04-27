#pragma once

#include <QDialog>
#include <export.h>

/// \brief Frameless modal dialog used for information, warning, error, question, and "next" messages.
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

    /// \brief Constructs an empty popup (used as a base for subclasses).
    EPopup(QWidget *parent = nullptr);
    /// \brief Constructs a popup of \a type with a text message \a msg.
    EPopup(MessageTypes type, const QString &msg, QWidget *parent = nullptr);
    /// \brief Constructs a popup of \a type embedding an arbitrary widget \a w.
    EPopup(MessageTypes type, QWidget *w, QWidget *parent = nullptr);

    /// \brief Closes the dialog programmatically.
    void aboutToClose();

private:
    /// \brief Builds the dialog layout for the given \a type and content widget \a w.
    void create(MessageTypes &type, QWidget *w, QWidget *parent = nullptr);

signals:
    void accepted();
    void cancelled();
    void closed();

public slots:
    /// \brief Emits accepted() and closes the dialog.
    void acceptSlot();
    /// \brief Emits cancelled() and closes the dialog.
    void cancelSlot();

protected:
    void showEvent(QShowEvent *e) override;
    void closeEvent(QCloseEvent *e) override;
    void keyPressEvent(QKeyEvent *e) override;
};
