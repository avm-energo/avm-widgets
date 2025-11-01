#pragma once

#include <QFrame>
#include <array>
#include <export.h>
#include <gen/netip.h>

/// Thanx to https://stackoverflow.com/a/11358560/8524139
class QLineEdit;
class WD_EXPORT IPCtrl : public QFrame
{
    Q_OBJECT
public:
    static constexpr auto MAX_DIGITS = 3; ///< число символов в LineEdit

    IPCtrl(QWidget *parent = nullptr);
    ~IPCtrl();

    virtual bool eventFilter(QObject *obj, QEvent *event);

    NetIP getIP() const;
    void setIP(const NetIP ipAddr);

    static QWidget *New(QWidget *parent, const QString &name = "", const QString &caption = "");
    static bool setData(const QObject *parent, const QString &name, const NetIP &value);
    static NetIP data(const QObject *parent, const QString &name);

signals:
    void signalTextChanged(QLineEdit *pEdit);

private:
    std::array<QLineEdit *, NET_IP_SIZE> m_pLineEdit;
    void slotTextChanged(QLineEdit *pEdit);
    void moveNextLineEdit(int i);
    void movePrevLineEdit(int i);
};
