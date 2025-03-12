/*
 *
 * Copyright (C) 2015  Dimka Novikov, to@dimkanovikov.pro
 * Copyright (C) 2025  AVM-Energo, support@avmenergo.ru
 *
 */

#pragma once

#include <QObject>

namespace SA
{

class AbstractAnimator : public QObject
{
    Q_OBJECT

public:
    explicit AbstractAnimator(QObject *_parent = 0) : QObject(_parent)
    {
    }

    virtual int animationDuration() const = 0;
    virtual void animateForward() = 0;
    virtual void animateBackward() = 0;

protected:
    void setAnimationForward()
    {
        m_isAnimationInProcess = true;
        m_isAnimationForward = true;
    }
    void setAnimationBackward()
    {
        m_isAnimationInProcess = true;
        m_isAnimationForward = false;
    }
    void setAnimationStopped()
    {
        m_isAnimationInProcess = false;
    }
    bool isAnimationInProcess() const
    {
        return m_isAnimationInProcess;
    }
    bool isAnimationForward() const
    {
        return m_isAnimationForward;
    }
    bool isAnimationBackward() const
    {
        return !isAnimationForward();
    }

private:
    bool m_isAnimationInProcess = false;
    // Направление последней анимации
    bool m_isAnimationForward = true;
};
} // namespace SA
