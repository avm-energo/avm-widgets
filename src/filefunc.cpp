#include <QFileDialog>
#include <QHBoxLayout>
#include <avm-widgets/filefunc.h>
#include <avm-widgets/lblfunc.h>
#include <avm-widgets/lefunc.h>
#include <avm-widgets/pbfunc.h>
#include <avm-gen/settings.h>
FileFunc::FileFunc()
{
}

QString FileFunc::chooseFileForOpen(QWidget *parent, QString mask)
{
    auto workPath = Settings::workDir();
    auto dlg = new QFileDialog(parent);
    dlg->setAttribute(Qt::WA_DeleteOnClose);
    dlg->setFileMode(QFileDialog::AnyFile);
    auto filename = dlg->getOpenFileName(parent, "Открыть файл", workPath, mask, Q_NULLPTR);
    setWorkDir(filename);
    dlg->close();
    return filename;
}

QString FileFunc::chooseFileForSave(QWidget *parent, const QString &mask, const QString &ext, const QString &filename)
{
    auto workPath = Settings::workDir();
    auto dlg = new QFileDialog(parent);
    dlg->setAttribute(Qt::WA_DeleteOnClose);
    dlg->setFileMode(QFileDialog::AnyFile);
    auto fullpath = workPath + "/" + filename + "." + ext;
    auto filepath = dlg->getSaveFileName(parent, "Сохранить файл", fullpath, mask, Q_NULLPTR);
    if (!filepath.isEmpty())
        setWorkDir(filepath);
    dlg->close();
    return filepath;
}

QString FileFunc::chooseDirectoryForOpen(QWidget *parent)
{
    auto workPath = Settings::workDir();
    auto dlg = new QFileDialog(parent);
    dlg->setAttribute(Qt::WA_DeleteOnClose);
    dlg->setFileMode(QFileDialog::Directory);
    dlg->setViewMode(QFileDialog::Detail);
    auto dirPath = dlg->getExistingDirectory(parent, "Выбрать папку с файлами", workPath);
    if (!dirPath.isEmpty())
        setWorkDir(dirPath);
    dlg->close();
    return dirPath;
}

QWidget *FileFunc::New(
    QWidget *parent, const QString &wname, WidgetTypes type, const QString &mask, const QString &path)
{
    QWidget *w = new QWidget;
    QHBoxLayout *hlyout = new QHBoxLayout;
    hlyout->addWidget(LEFunc::newLBL(parent, (type == WidgetTypes::FILE) ? "Файл: " : "Каталог: ", wname));
    hlyout->addWidget(PBFunc::New(parent, "", "...", [=] {
        if (type == WidgetTypes::FILE)
            LEFunc::setData(parent, wname, chooseFileForOpen(parent, mask));
        else
            LEFunc::setData(parent, wname, chooseDirectoryForOpen(parent));
    }));
    LEFunc::setData(parent, wname, path);
    w->setLayout(hlyout);
    return w;
}

QWidget *FileFunc::newLBL(QWidget *parent, const QString &lbltext, const QString &wname, WidgetTypes type,
    const QString &mask, const QString &path)
{
    QWidget *w = new QWidget;
    QHBoxLayout *hlyout = new QHBoxLayout;
    hlyout->addWidget(LBLFunc::New(parent, lbltext));
    hlyout->addWidget(New(parent, wname, type, mask, path));
    w->setLayout(hlyout);
    return w;
}

void FileFunc::setWorkDir(const QString &dir)
{
    if (!dir.isEmpty())
    {
        QFileInfo info(dir);
        Settings::setWorkDir(info.absolutePath());
    }
}
