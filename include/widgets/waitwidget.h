#pragma once

#include <QMovie>
#include <QPaintEvent>
#include <QWidget>
#include <widgets/export.h>

class WD_EXPORT WaitWidget : public QWidget
{
    Q_OBJECT
    QStringList movies = { ":/images/catbeat.gif", ":/images/catlayered.gif", ":/images/catloading.gif",
        ":/images/cuteecat.gif", ":/images/walk-cat.gif", ":/images/walkontwocat.gif" };

public:
    explicit WaitWidget(QWidget *parent = nullptr);
    ~WaitWidget();

    enum ww_format
    {
        WW_TIME,  // format: mm:ss
        WW_SIMPLE // format: ss
    };

    struct ww_struct
    {
        bool isallowedtostop;
        bool isincrement;
        int format;             // ww_format
        quint32 initialseconds; // initial seconds counter
    };

    void Init(ww_struct &ww);
    void Start();
    void Stop();

signals:
    void finished();
    void CountZero(); // signal emits when a number of seconds is down-counted to zero

public slots:
    void SetMessage(QString msg);
    void SetSeconds(quint32 seconds);

private slots:
    void UpdateSeconds();

private:
    QString Message;
    quint32 Seconds;
    QMovie *m_movie;
    bool IsAllowedToStop, IsIncrement;
    int TimeFormat;
    const QString PressAnyKeyString = "Нажмите Esc, если готовы продолжить";
    int PressAnyKeyStringWidth;

protected:
    void paintEvent(QPaintEvent *e);
    void keyPressEvent(QKeyEvent *e);
    void closeEvent(QCloseEvent *e);
};
