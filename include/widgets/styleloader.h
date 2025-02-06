#pragma once

#include <QKeySequence>
#include <QMap>
#include <QObject>
#include <gen/singleton.h>
#include <widgets/export.h>

constexpr char defaultStyleFile[] = ":/lightstyle.qss";

namespace Style
{
const QMap<QString, QString> themes {
    { "Light", defaultStyleFile },                   //
    { "Dark", ":/styles/darkstyle.qss" },            //
    { "Drakula", ":/styles/dracula.css" },           //
    { "Aqua", ":/styles/Aqua.qss" },                 //
    { "MaterialDark", ":/styles/MaterialDark.qss" }, //
    { "Ubuntu", ":/styles/Ubuntu.qss" }              //
};
}

class WD_EXPORT StyleLoader : public QObject, public Singleton<StyleLoader>
{
    Q_OBJECT

public:
    explicit StyleLoader(QObject *parent);

    static QStringList availableStyles();
    QString styleName();
    void setStyle(const QString &styleName);
    void setStyleFile(const QString &styleFile);

private:
    QString m_filename;
};
