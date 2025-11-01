#pragma once

#include <QMovie>
#include <QPaintEvent>
#include <QWidget>
#include <export.h>

class WD_EXPORT WaitWidget : public QWidget
{
    Q_OBJECT

public:
    explicit WaitWidget(const QString &movie = "", QWidget *parent = nullptr);
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

    void init(ww_struct &ww);
    void start();
    void stop();

signals:
    void finished();
    void countZero(); // signal emits when a number of seconds is down-counted to zero

public slots:
    void setMessage(QString msg);
    void setSeconds(quint32 seconds);

private slots:
    void updateSeconds();

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
