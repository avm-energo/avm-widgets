#pragma once

#include <QKeySequence>
#include <QMap>
#include <QObject>
#include <widgets/export.h>

constexpr char defaultStyleFile[] = ":/lightstyle.qss";

class Style
{
public:
    static QMap<QString, QString> themes;
};

class WD_EXPORT StyleLoader : public QObject
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
