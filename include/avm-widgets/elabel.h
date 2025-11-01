#pragma once

#include <QLabel>
#include <QWidget>
#include <export.h>

class WD_EXPORT ELabel : public QLabel
{
    Q_OBJECT
public:
    ELabel(QWidget *parent = nullptr);
    ELabel(const QString &caption, QWidget *parent = nullptr);

    void setData(const QVariant &data);
    void setData(const QString &data);
    template <typename T> T data()
    {
        return qvariant_cast<T>(m_data);
    }

private:
    QVariant m_data;
};
