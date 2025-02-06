#pragma once

#include <QLineEdit>
#include <widgets/export.h>

class WD_EXPORT PasswordLineEdit : public QWidget
{
    Q_OBJECT

public:
    explicit PasswordLineEdit(QWidget *parent = Q_NULLPTR);
    explicit PasswordLineEdit(QLineEdit::EchoMode echostyle = QLineEdit::Password, QWidget *parent = Q_NULLPTR);

private slots:
    void PswLEToggleEchoMode();
};
