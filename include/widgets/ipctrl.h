#pragma once

#include <QFrame>
#include <array>
#include <gen/netip.h>
#include <widgets/export.h>

/// Thanx to https://stackoverflow.com/a/11358560/8524139
class QLineEdit;
class WD_EXPORT IPCtrl : public QFrame
{
    Q_OBJECT
public:
    static constexpr auto MAX_DIGITS = 3; ///< число символов в LineEdit

    IPCtrl(QWidget *parent = nullptr, const QString &name = "", const QString &caption = "");
    ~IPCtrl();

    virtual bool eventFilter(QObject *obj, QEvent *event);

    NetIP getIP() const;
    void setIP(const NetIP ipAddr);

    static bool SetIPCtrlData(const QObject *parent, const QString &name, const std::array<quint8, 4> &value);
    static std::array<quint8, 4> IPCtrlData(const QObject *parent, const QString &name);

signals:
    void signalTextChanged(QLineEdit *pEdit);

private:
    std::array<QLineEdit *, NET_IP_SIZE> m_pLineEdit;
    void slotTextChanged(QLineEdit *pEdit);
    void moveNextLineEdit(int i);
    void movePrevLineEdit(int i);
};
