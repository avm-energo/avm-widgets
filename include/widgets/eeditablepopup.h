#pragma once

#include "epopup.h"

class EEditablePopup : public EPopup
{
    Q_OBJECT
public:
    EEditablePopup(const QString &caption, QWidget *parent = nullptr);
    void addFloatParameter(const QString &name, float *parameter);
    void execPopup();

private:
    std::map<QString, float *> m_floatParList;
    bool m_result;
    QString caption;

private slots:
    void acceptSlot();

protected:
    void keyPressEvent(QKeyEvent *e) override;
};
