/*
 *
 * Copyright (C) 2015  Dimka Novikov, to@dimkanovikov.pro
 * Copyright (C) 2025  AVM-Energo, support@avmenergo.ru
 *
 */

#include <QPainter>
#include <widgets/slideanimation/slideforegrounddecorator.h>

using namespace SA;

SlideForegroundDecorator::SlideForegroundDecorator(QWidget *_parent) : QWidget(_parent)
{
}

void SlideForegroundDecorator::grabParent(const QSize &_size)
{
    resize(_size);
    m_foreground = QPixmap(_size);
    parentWidget()->render(&m_foreground, QPoint(), QRegion(QRect(QPoint(), _size)));
}

void SlideForegroundDecorator::paintEvent(QPaintEvent *_event)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, m_foreground);

    QWidget::paintEvent(_event);
}
