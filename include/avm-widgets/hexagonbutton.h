#ifndef HEXAGONBUTTON_H
#define HEXAGONBUTTON_H

#include <QPushButton>
#include <QWidget>
#include <export.h>

/// \brief QPushButton that stores an associated data string (e.g. an SVG resource path).
class WD_EXPORT HexagonButton : public QPushButton
{
    Q_OBJECT
public:
    explicit HexagonButton(QWidget *parent = nullptr);
    /// \brief Stores \a data as the button's payload (e.g. icon resource path).
    void setData(const QString &data);
    /// \brief Returns the stored payload string.
    QString data();

private:
    QString m_data;
};

#endif // HEXAGONBUTTON_H
