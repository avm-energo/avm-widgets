#pragma once

#include "epopup.h"
#include <export.h>

/// \brief EPopup subclass that prompts for a password and validates it against a SHA3-256 hash.
class WD_EXPORT EPasswordPopup : public EPopup
{
    Q_OBJECT
public:
    /// \brief Constructs the password dialog; \a hash is the expected SHA3-256 hex digest.
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
