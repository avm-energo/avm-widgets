#pragma once

#include <QTextEdit>
#include <widgets/export.h>

class WD_EXPORT TEFunc
{
public:
    static QTextEdit *New(QWidget *parent, const QString &tename);
    static bool AppendData(QWidget *parent, const QString &tename, const QString &tetext);
    static bool SetData(QWidget *parent, const QString &tename, const QString &tetext);
    static bool Data(QWidget *parent, const QString &tename, QString &tevalue);
};
