#pragma once

#include <QString>
#include <QWidget>
#include <export.h>

class WD_EXPORT FileFunc
{
public:
    enum WidgetTypes
    {
        DIR,
        FILE
    };
    FileFunc();

    [[nodiscard]] static QString chooseFileForOpen(QWidget *parent, QString mask);
    /// Input: QString mask: описание файлов, например: "Файлы журналов (*.swj)";
    /// QString ext - расширение по умолчанию Output: QString filename
    [[nodiscard]] static QString chooseFileForSave(
        QWidget *parent, const QString &mask, const QString &ext, const QString &filename = "");
    [[nodiscard]] static QString chooseDirectoryForOpen(QWidget *parent);
    static QWidget *New(QWidget *parent, const QString &wname, WidgetTypes type = WidgetTypes::FILE,
        const QString &mask = "Все файлы (*.*)", const QString &path = "");
    static QWidget *newLBL(QWidget *parent, const QString &lbltext, const QString &wname,
        WidgetTypes type = WidgetTypes::FILE, const QString &mask = "Все файлы (*.*)", const QString &path = "");

private:
    static void setWorkDir(const QString &dir);
};
