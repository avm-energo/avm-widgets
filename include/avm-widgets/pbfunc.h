#pragma once

#include <QPushButton>
#include <export.h>

class WD_EXPORT PBFunc
{
public:
    template <typename Func>
    inline static QPushButton *New(QWidget *parent, const QString &pbname, const QString &text, const Func *receiver,
        void (Func::*method)(), const QString &icon = "", const QString &pbtooltip = "")
    {
        auto pb = newCommon(parent, pbname, text, icon, pbtooltip);
        QObject::connect(pb, &QPushButton::clicked, receiver, method);
        return pb;
    }

    template <typename Functor>
    inline static QPushButton *New(QWidget *parent, const QString &pbname, const QString &text, Functor &&functor,
        const QString &icon = "", const QString &pbtooltip = "")
    {
        auto pb = newCommon(parent, pbname, text, icon, pbtooltip);
        QObject::connect(pb, &QPushButton::clicked, functor);
        return pb;
    }

    template <typename Functor>
    inline static QPushButton *New(QWidget *parent, const QString &pbname, const QString &text, QObject *context,
        Functor &&functor, const QString &icon = "", const QString &pbtooltip = "")
    {
        auto pb = newCommon(parent, pbname, text, icon, pbtooltip);
        QObject::connect(pb, &QPushButton::clicked, context, functor);
        return pb;
    }

    template <typename Functor>
    inline static void Connect(QWidget *parent, const QString &pbname, QObject *context, Functor &&functor)
    {
        auto pb = parent->findChild<QPushButton *>(pbname);
        if (pb != nullptr)
            QObject::connect(pb, &QPushButton::clicked, context, functor);
    }

    template <typename Object>
    inline static void Connect(QWidget *parent, const QString &pbname, const Object *receiver, void (Object::*method)())
    {
        auto pb = parent->findChild<QPushButton *>(pbname);
        if (pb != nullptr)
            QObject::connect(pb, &QPushButton::clicked, receiver, method);
    }

private:
    [[nodiscard]] static QPushButton *newCommon(QWidget *parent, const QString &pbname, const QString &text,
        const QString &icon = "", const QString &pbtooltip = "");
};
