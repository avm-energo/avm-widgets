#pragma once

#include "epopup.h"

class EPasswordPopup : public EPopup
{
    Q_OBJECT
public:
    EPasswordPopup(const QString &hash, QWidget *parent);

private:
    QString m_hash;
    bool isAboutToClose;
    bool checkPassword(const QString &psw);

signals:
    void passwordIsCorrect();

protected:
    void keyPressEvent(QKeyEvent *e) override;
    void closeEvent(QCloseEvent *e) override;
};
