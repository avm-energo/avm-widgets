#pragma once

#include <QComboBox>
#include <export.h>

/// \brief A QComboBox with an internal key→value mapping.
class WD_EXPORT EComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit EComboBox(QWidget *parent = nullptr);

    /// \brief Populates the combo box from \a map (display text → integer value).
    void setItems(const QMap<QString, int> &map);
    /// \brief Selects the item whose mapped integer equals \a value.
    void setIndexByValue(const int value);
    /// \brief Selects the item whose display text equals \a key.
    void setIndexByKey(const QString &key);
    /// \brief Returns the mapped integer value for the currently selected item.
    int getValueByCurrentIndex() const;

private:
    QMap<QString, int> m_comboMap;
};
