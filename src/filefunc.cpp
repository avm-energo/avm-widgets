#include <QFileDialog>
#include <QHBoxLayout>
#include <gen/stdfunc.h>
#include <widgets/filefunc.h>
#include <widgets/lefunc.h>
#include <widgets/pbfunc.h>
FileFunc::FileFunc()
{
}

QString FileFunc::ChooseFileForOpen(QWidget *parent, QString mask)
{
    auto workPath = StdFunc::GetHomeDir();
    auto dlg = new QFileDialog(parent);
    dlg->setAttribute(Qt::WA_DeleteOnClose);
    dlg->setFileMode(QFileDialog::AnyFile);
    auto filename = dlg->getOpenFileName(parent, "Открыть файл", workPath, mask, Q_NULLPTR);
    if (!filename.isEmpty())
    {
        QFileInfo info(filename);
        StdFunc::SetHomeDir(info.absolutePath());
    }
    dlg->close();
    return filename;
}

QString FileFunc::ChooseFileForSave(QWidget *parent, const QString &mask, const QString &ext, const QString &filename)
{
    auto workPath = StdFunc::GetHomeDir();
    auto dlg = new QFileDialog(parent);
    dlg->setAttribute(Qt::WA_DeleteOnClose);
    dlg->setFileMode(QFileDialog::AnyFile);
    auto fullpath = workPath + "/" + filename + "." + ext;
    auto filepath = dlg->getSaveFileName(parent, "Сохранить файл", fullpath, mask, Q_NULLPTR);
    if (!filepath.isEmpty())
    {
        QFileInfo info(filepath);
        StdFunc::SetHomeDir(info.absolutePath());
    }
    dlg->close();
    return filepath;
}

QString FileFunc::ChooseDirectoryForOpen(QWidget *parent)
{
    auto workPath = StdFunc::GetHomeDir();
    auto dlg = new QFileDialog(parent);
    dlg->setAttribute(Qt::WA_DeleteOnClose);
    dlg->setFileMode(QFileDialog::Directory);
    dlg->setViewMode(QFileDialog::Detail);
    auto dirPath = dlg->getExistingDirectory(parent, "Выбрать папку с файлами", workPath);
    if (!dirPath.isEmpty())
    {
        QFileInfo info(dirPath);
        StdFunc::SetHomeDir(info.absolutePath());
    }
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
