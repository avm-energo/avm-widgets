#pragma once

#include <QString>
#include <QWidget>
#include <export.h>

/// \brief Factory functions for file/directory chooser widgets.
class WD_EXPORT FileFunc
{
public:
    enum WidgetTypes
    {
        DIR,  ///< Selects a directory
        FILE  ///< Selects a file
    };
    FileFunc();

    /// \brief Opens a file-open dialog filtered by \a mask; returns the selected path or empty string.
    [[nodiscard]] static QString chooseFileForOpen(QWidget *parent, const QString &mask);
    /// \brief Opens a file-save dialog; \a mask is the file description (e.g. "Log files (*.swj)"),
    ///        \a ext is the default extension, \a filename is the suggested name.
    [[nodiscard]] static QString chooseFileForSave(
        QWidget *parent, const QString &mask, const QString &ext, const QString &filename = "");
    /// \brief Opens a directory chooser dialog; returns the selected path or empty string.
    [[nodiscard]] static QString chooseDirectoryForOpen(QWidget *parent);
    /// \brief Creates a line edit + browse button widget of the given \a type.
    static QWidget *New(QWidget *parent, const QString &wname, WidgetTypes type = WidgetTypes::FILE,
        const QString &mask = "Все файлы (*.*)", const QString &path = "");
    /// \brief Creates a caption label + file chooser widget pair.
    static QWidget *newLBL(QWidget *parent, const QString &lbltext, const QString &wname,
        WidgetTypes type = WidgetTypes::FILE, const QString &mask = "Все файлы (*.*)", const QString &path = "");

private:
    static void setWorkDir(const QString &dir);
};
