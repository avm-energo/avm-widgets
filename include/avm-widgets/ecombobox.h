#pragma once

#include <QComboBox>
#include <export.h>

class WD_EXPORT EComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit EComboBox(QWidget *parent = nullptr);

    void setItems(const QMap<QString, int> &map);
    void setIndexByValue(const int value);
    void setIndexByKey(const QString &key);
    int getValueByCurrentIndex() const;

private:
    QMap<QString, int> m_comboMap;
};
