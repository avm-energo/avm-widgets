#pragma once

#include <QMap>
#include <QObject>
#include <widgets/export.h>

constexpr char defaultStyleFile[] = ":/styles/lightstyle.qss";

class WD_EXPORT StyleLoader : public QObject
{
    Q_OBJECT

public:
    static QMap<QString, QString> s_themes;

    explicit StyleLoader(QObject *parent);
    static QStringList availableStyles();
    static QString styleName();
    static void setStyle(const QString &styleName);
    static void setStyleFile(const QString &styleFile);

private:
    static QString s_filename;
};
