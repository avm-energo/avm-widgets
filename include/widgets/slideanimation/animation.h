/*
 *
 * Copyright (C) 2015  Dimka Novikov, to@dimkanovikov.pro
 * Copyright (C) 2025  AVM-Energo, support@avmenergo.ru
 *
 */

#pragma once

#include <QFrame>
#include <gen/error.h>
#include <widgets/slideanimation/sa.h>
#include <widgets/slideanimation/slideanimator.h>

namespace SA
{
enum MessageTypes
{
    ERROR,
    WARNING,
    INFORMATION
};

class Message : public QFrame
{
public:
    explicit Message(const QString &_message, int type, QWidget *parent = 0);

signals:
    void hideMessage();

private:
    int m_lastHeight;
};

class Animation
{
public:
    Animation(QWidget *parent = nullptr);
    int slideIn(bool _fixBackground = true, bool _fixStartSize = false);
    int slideOut(bool _fixBackground = true, bool _fixStartSize = false);
    int slide(bool _fixBackground = true, bool _fixStartSize = false, bool _in = true);

    static void showMessage(QWidget *parent, int msgType, const QString &msg);
    static void error(QWidget *parent, const QString &msg);
    static void warning(QWidget *parent, const QString &msg);
    static void information(QWidget *parent, const QString &msg);

private:
    int runAnimation(bool _in);

private:
    SlideAnimator *m_animator;
    QWidget *m_widget;
};
}
