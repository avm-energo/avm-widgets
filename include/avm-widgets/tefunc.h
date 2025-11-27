#pragma once

#include <QTextEdit>
#include <export.h>

class WD_EXPORT TEFunc
{
public:
    static QTextEdit *textedit(QWidget *parent, const QString &tename);
    static QTextEdit *New(QWidget *parent, const QString &tename);
    static bool appendData(QWidget *parent, const QString &tename, const QString &tetext);
    static bool setData(QWidget *parent, const QString &tename, const QString &tetext);
    static bool data(QWidget *parent, const QString &tename, QString &tevalue);
};
