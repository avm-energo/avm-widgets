#ifndef HEXAGONBUTTON_H
#define HEXAGONBUTTON_H

#include <QPushButton>
#include <QWidget>
#include <widgets/export.h>

class WD_EXPORT HexagonButton : public QPushButton
{
    Q_OBJECT
public:
    HexagonButton(QWidget *parent = nullptr);
    void setData(const QString &data);
    QString data();

private:
    QString m_data;
};

#endif // HEXAGONBUTTON_H
