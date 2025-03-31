#include "widgets/styleloader.h"

#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QKeyEvent>
#include <QMetaEnum>
#include <QSettings>

QMap<QString, QString> Style::themes{
    {"Light", defaultStyleFile},                   //
    {"Dark", ":/styles/darkstyle.qss"},            //
    {"Drakula", ":/styles/dracula.css"},           //
    {"Aqua", ":/styles/Aqua.qss"},                 //
    {"MaterialDark", ":/styles/MaterialDark.qss"}, //
    {"Ubuntu", ":/styles/Ubuntu.qss"}              //
};

StyleLoader::StyleLoader(QObject *parent) : QObject(parent)
{
}

QStringList StyleLoader::availableStyles()
{
    return Style::themes.keys();
}

void StyleLoader::setStyle(const QString &styleName)
{
    m_filename = Style::themes.value(styleName);
    QFile file(m_filename);
    if (!file.open(QIODevice::ReadOnly))
    {
        qWarning() << "Cannot open stylesheet file " << m_filename;
        return;
    }
    QString stylesheet = QString::fromUtf8(file.readAll());
    qApp->setStyleSheet(stylesheet);
}

QString StyleLoader::styleName()
{
    const QString styleName = Style::themes.key(m_filename);
    return styleName;
}
