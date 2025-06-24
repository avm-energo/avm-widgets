#include "widgets/styleloader.h"

#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QKeyEvent>
#include <QMetaEnum>
#include <QSettings>

QMap<QString, QString> StyleLoader::s_themes {
    { "Light", defaultStyleFile },        //
    { "Dark", ":/styles/darkstyle.qss" }, //
};
QString StyleLoader::s_filename = defaultStyleFile;

StyleLoader::StyleLoader(QObject *parent) : QObject(parent)
{
}

QStringList StyleLoader::availableStyles()
{
    return s_themes.keys();
}

void StyleLoader::setStyle(const QString &styleName)
{
    s_filename = s_themes.value(styleName);
    QFile file(s_filename);
    if (!file.open(QIODevice::ReadOnly))
    {
        qWarning() << "Cannot open stylesheet file " << s_filename;
        return;
    }
    QString stylesheet = QString::fromUtf8(file.readAll());
    qApp->setStyleSheet(stylesheet);
}

QString StyleLoader::styleName()
{
    const QString styleName = s_themes.key(s_filename);
    return styleName;
}
