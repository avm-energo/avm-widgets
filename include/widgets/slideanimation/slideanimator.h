/*
 *
 * Copyright (C) 2015  Dimka Novikov, to@dimkanovikov.pro
 * Copyright (C) 2025  AVM-Energo, support@avmenergo.ru
 *
 */

#pragma once
#include <QSize>
#include <widgets/slideanimation/abstractanimator.h>
#include <widgets/slideanimation/sa.h>
#include <widgets/slideanimation/slideforegrounddecorator.h>

class QPropertyAnimation;

namespace SA
{
class SlideAnimator : public AbstractAnimator
{
    Q_OBJECT

public:
    explicit SlideAnimator(QWidget *_widgetForSlide);

    void setAnimationDirection(AnimationDirection _direction);
    void setFixBackground(bool _fix);
    void setFixStartSize(bool _fix);
    int animationDuration() const;
    void animateForward();
    void slideIn();
    void animateBackward();
    void slideOut();

protected:
    // Переопределяется, чтобы корректировать позицию перекрывающего виджета
    bool eventFilter(QObject *_object, QEvent *_event);

private:
    // Зависит ли от анимации ширина (true) или высота (false) анимируемого виджета
    bool isWidth() const;

    // Зафиксировать размер в направлении изменяемой анимацией стороны
    void fixSize(const QSize &_sourceSize, QSize &_targetSize) const;
    void fixSizeOfWidgetForSlide(const QSize &_sourceSize) const;

    QWidget *widgetForSlide() const;

private:
    AnimationDirection m_direction;
    bool m_isFixBackground;
    // Необходимо ли запоминать стартовый размер виджета
    bool m_isFixStartSize;
    QSize m_startMinSize, m_startMaxSize, m_startSize;
    QPropertyAnimation *m_animation;
    // Помошник перекрывающий анимируемый виджет
    SlideForegroundDecorator *m_decorator;
};
}
