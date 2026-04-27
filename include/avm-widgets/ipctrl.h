#pragma once

#include <QFrame>
#include <array>
#include <export.h>
#include <avm-gen/netip.h>

/// \brief IP address entry widget composed of four validated QLineEdits separated by dots.
/// Thanx to https://stackoverflow.com/a/11358560/8524139
class QLineEdit;
class WD_EXPORT IPCtrl : public QFrame
{
    Q_OBJECT
public:
    static constexpr auto MAX_DIGITS = 3; ///< Maximum digits per octet

    explicit IPCtrl(QWidget *parent = nullptr);
    ~IPCtrl();

    /// \brief Intercepts key events to auto-advance focus between octets.
    bool eventFilter(QObject *obj, QEvent *event) override;

    /// \brief Returns the current IP address as a NetIP array.
    NetIP getIP() const;
    /// \brief Sets each octet from \a ipAddr.
    void setIP(const NetIP ipAddr);

    /// \brief Creates a standalone IPCtrl or a label+IPCtrl pair if \a caption is non-empty.
    static QWidget *New(QWidget *parent, const QString &name = "", const QString &caption = "");
    /// \brief Sets the IP address of the IPCtrl found by \a name inside \a parent.
    static bool setData(const QObject *parent, const QString &name, const NetIP &value);
    /// \brief Returns the IP address from the IPCtrl found by \a name inside \a parent.
    static NetIP data(const QObject *parent, const QString &name);

signals:
    void signalTextChanged(QLineEdit *pEdit);

private:
    std::array<QLineEdit *, NET_IP_SIZE> m_pLineEdit;
    void slotTextChanged(QLineEdit *pEdit);
    void moveNextLineEdit(int i);
    void movePrevLineEdit(int i);
};
