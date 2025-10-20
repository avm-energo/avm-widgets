#include <QFileDialog>
#include <QHBoxLayout>
#include <gen/settings.h>
#include <widgets/filefunc.h>
#include <widgets/lblfunc.h>
#include <widgets/lefunc.h>
#include <widgets/pbfunc.h>
FileFunc::FileFunc()
{
}

QString FileFunc::ChooseFileForOpen(QWidget *parent, QString mask)
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

QString FileFunc::ChooseFileForSave(QWidget *parent, const QString &mask, const QString &ext, const QString &filename)
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

QString FileFunc::ChooseDirectoryForOpen(QWidget *parent)
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
    hlyout->addWidget(LEFunc::NewLBL(parent, (type == WidgetTypes::FILE) ? "Файл: " : "Каталог: ", wname));
    hlyout->addWidget(PBFunc::New(parent, "", "...", [=] {
        if (type == WidgetTypes::FILE)
            LEFunc::SetData(parent, wname, ChooseFileForOpen(parent, mask));
        else
            LEFunc::SetData(parent, wname, ChooseDirectoryForOpen(parent));
    }));
    LEFunc::SetData(parent, wname, path);
    w->setLayout(hlyout);
    return w;
}

QWidget *FileFunc::NewLBL(QWidget *parent, const QString &lbltext, const QString &wname, WidgetTypes type,
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
