#pragma once

#include <QLineEdit>
#include <export.h>

class WD_EXPORT PasswordLineEdit : public QWidget
{
    Q_OBJECT

public:
    explicit PasswordLineEdit(QWidget *parent = Q_NULLPTR,
                              const QString &lename = "",
                              QLineEdit::EchoMode echostyle = QLineEdit::Password);

private slots:
    void pswLEToggleEchoMode(const QString &lename);
};
