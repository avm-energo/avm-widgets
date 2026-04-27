#pragma once

#include <QLabel>
#include <QWidget>
#include <export.h>

/// \brief QLabel that also stores an arbitrary QVariant payload alongside the displayed text.
class WD_EXPORT ELabel : public QLabel
{
    Q_OBJECT
public:
    explicit ELabel(QWidget *parent = nullptr);
    /// \brief Constructs a label with visible text \a caption.
    explicit ELabel(const QString &caption, QWidget *parent = nullptr);

    /// \brief Stores \a data as the label's payload (does not change the displayed text).
    void setData(const QVariant &data);
    /// \brief Stores \a data as a QString payload (does not change the displayed text).
    void setData(const QString &data);
    /// \brief Returns the stored payload cast to \a T.
    template <typename T> T data()
    {
        return qvariant_cast<T>(m_data);
    }

private:
    QVariant m_data;
};
