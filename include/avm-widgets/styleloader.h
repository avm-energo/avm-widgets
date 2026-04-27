#pragma once

#include <QMap>
#include <QObject>
#include <export.h>

constexpr char defaultStyleFile[] = ":/styles/lightstyle.qss";

/// \brief Manages application-wide Qt stylesheets with named theme support (Light / Dark).
class WD_EXPORT StyleLoader : public QObject
{
    Q_OBJECT

public:
    /// \brief Map of theme name → QSS resource path; can be extended at runtime.
    static QMap<QString, QString> s_themes;

    explicit StyleLoader(QObject *parent);
    /// \brief Returns the list of registered theme names.
    static QStringList availableStyles();
    /// \brief Returns the currently active theme name.
    static QString styleName();
    /// \brief Activates the theme named \a styleName and applies its QSS to the application.
    static void setStyle(const QString &styleName);
    /// \brief Loads and applies the QSS file at \a styleFile directly, bypassing theme lookup.
    static void setStyleFile(const QString &styleFile);

private:
    static QString s_filename;
};
