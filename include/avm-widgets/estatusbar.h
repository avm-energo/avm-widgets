#pragma once
#include <QLabel>
#include <QStatusBar>
#include <QWidget>
#include <export.h>

/// \brief Status bar with dedicated labels for queue size, model, serial number, and connection info.
class WD_EXPORT EStatusBar : public QStatusBar
{
    Q_OBJECT
public:
    explicit EStatusBar(QWidget *parent = nullptr);

public slots:
    /// \brief Displays \a sizestr as the current queue size.
    void setQueueSize(const QString &sizestr);
    /// \brief Displays \a str as the device model string.
    void setModelString(const QString &str);
    /// \brief Displays \a number as the device serial number in hex.
    void setSerialNumber(quint32 number);
    /// \brief Displays \a type as the connection type (e.g. "USB", "Ethernet").
    void setConnectionType(const QString &type);
    /// \brief Displays \a state as the connection state text.
    void setConnectionState(const QString &state);
    /// \brief Displays \a pixmap as the connection state icon.
    void setConnectionPixmap(const QPixmap &pixmap);

private:
    QLabel *m_queueSizeLbl, *m_msgModelLbl, *m_msgSNLbl, *m_connStateLbl, *m_connTypeLbl, *m_connImageLbl;
};
