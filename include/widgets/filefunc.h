#pragma once

#include <QString>
#include <QWidget>
#include <widgets/export.h>

class WD_EXPORT FileFunc
{
public:
    FileFunc();

    [[nodiscard]] static QString ChooseFileForOpen(QWidget *parent, QString mask);
    /// Input: QString mask: описание файлов, например: "Файлы журналов (*.swj)";
    /// QString ext - расширение по умолчанию Output: QString filename
    [[nodiscard]] static QString ChooseFileForSave(
        QWidget *parent, const QString &mask, const QString &ext, const QString &filename = "");
    [[nodiscard]] static QString ChooseDirectoryForOpen(QWidget *parent);
};
