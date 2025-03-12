/*
 *
 * Copyright (C) 2015  Dimka Novikov, to@dimkanovikov.pro
 * Copyright (C) 2025  AVM-Energo, support@avmenergo.ru
 *
 */

#include <QHBoxLayout>
#include <QLabel>
#include <QTimer>
#include <QToolButton>
#include <widgets/slideanimation/animation.h>
#include <widgets/slideanimation/slideanimator.h>

using namespace SA;

Message::Message(const QString &_message, int type, QWidget *parent) : QFrame(parent)
{
    setProperty("notifyMessage", true);
    QLabel *message = new QLabel(_message, this);
    message->setProperty("notifyMessage", true);
    message->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    message->setWordWrap(true);
    QToolButton *typeIcon = new QToolButton(this);
    if (type == MessageTypes::ERROR)
        typeIcon->setIcon(QIcon(":/images/err-hex.svg"));
    else if (type == MessageTypes::INFORMATION)
        typeIcon->setIcon(QIcon(":/images/info-hex.svg"));
    else if (type == MessageTypes::WARNING)
        typeIcon->setIcon(QIcon(":/images/warn-hex.svg"));
    QToolButton *close = new QToolButton(this);
    close->setIcon(QIcon(":/close.png"));

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(typeIcon);
    layout->addWidget(message);
    layout->addWidget(close);

    QObject::connect(close, &QToolButton::clicked, this, &Message::hideMessage);

    setMaximumHeight(0);
    m_lastHeight = 0;

    QTimer *timer = new QTimer(this);
    QObject::connect(timer, &QTimer::timeout, [=] {
        if (m_lastHeight != maximumHeight())
        {
            int delta = maximumHeight() - m_lastHeight;
            m_lastHeight = maximumHeight();
            parentWidget()->resize(parentWidget()->width(), parentWidget()->height() + delta);
            parentWidget()->move(parentWidget()->pos().x(), parentWidget()->pos().y() - delta);
        }
    });
    timer->start(10);
}

Animation::Animation(QWidget *parent)
{
    m_widget = parent;
    m_animator = new SlideAnimator(parent);
}

int Animation::slideIn(bool _fixBackground, bool _fixStartSize)
{
    const bool IN = true;
    return slide(_fixBackground, _fixStartSize, IN);
}

int Animation::slideOut(bool _fixBackground, bool _fixStartSize)
{
    const bool OUT = false;
    return slide(_fixBackground, _fixStartSize, OUT);
}

int Animation::slide(bool _fixBackground, bool _fixStartSize, bool _in)
{
    m_animator->setAnimationDirection(FromBottomToTop);
    m_animator->setFixBackground(_fixBackground);
    m_animator->setFixStartSize(_fixStartSize);

    return runAnimation(_in);
}

void Animation::showMessage(QWidget *parent, int msgType, const QString &msg)
{
    Animation *animation = new Animation(parent);
    Message *message = new Message(msg, msgType, parent);
    animation->slideIn(message, false);
    QTimer::singleShot(5000, message, [=] { animation->slideOut(message, false); });
}

void Animation::error(QWidget *parent, const QString &msg)
{
    showMessage(parent, ERROR, msg);
}

void Animation::warning(QWidget *parent, const QString &msg)
{
    showMessage(parent, WARNING, msg);
}

void Animation::information(QWidget *parent, const QString &msg)
{
    showMessage(parent, INFORMATION, msg);
}

int Animation::runAnimation(bool _in)
{
    if (_in)
    {
        m_animator->animateForward();
    }
    else
    {
        m_animator->animateBackward();
    }

    return m_animator->animationDuration();
}
