/*
 *
 * Copyright (C) 2015  Dimka Novikov, to@dimkanovikov.pro
 * Copyright (C) 2025  AVM-Energo, support@avmenergo.ru
 *
 */

#pragma once

#include <QTimeLine>
#include <QWidget>

namespace SA
{

/**
 * \brief Класс перекрывающий передний план выкатываемого виджета
 * \note Делается это для того, чтобы скрыть деформации компоновщика, при изменении размера виджета
 */
class SlideForegroundDecorator : public QWidget
{
    Q_OBJECT

public:
    explicit SlideForegroundDecorator(QWidget *_parent);

    // Сохранить изображение родительского виджета
    void grabParent(const QSize &_size);

protected:
    // Переопределяется для прорисовки декорации
    void paintEvent(QPaintEvent *_event);

private:
    QPixmap m_foreground;
};
}
