#pragma once

#include <QMovie>
#include <QPaintEvent>
#include <QWidget>
#include <export.h>

/// \brief A frameless, always-on-top widget that shows an animated GIF and an optional countdown timer.
class WD_EXPORT WaitWidget : public QWidget
{
    Q_OBJECT

public:
    /// \brief Constructs the widget; \a movie is a path to a GIF file (uses a default cat GIF if empty).
    explicit WaitWidget(const QString &movie = "", QWidget *parent = nullptr);
    ~WaitWidget();

    enum ww_format
    {
        WW_TIME,  ///< Counter displayed as mm:ss
        WW_SIMPLE ///< Counter displayed as total seconds
    };

    /// \brief Configuration structure passed to init().
    struct ww_struct
    {
        bool isallowedtostop;   ///< Whether the user can stop the widget by pressing Escape
        bool isincrement;       ///< true = count up, false = count down
        int format;             ///< One of ww_format values
        quint32 initialseconds; ///< Initial value of the seconds counter
    };

    /// \brief Applies configuration from \a ww and pre-computes the "press Esc" string width.
    void init(ww_struct &ww);
    /// \brief Shows the widget, starts the animation and the timer.
    void start();
    /// \brief Stops the animation and timer, emits finished(), and closes the widget.
    void stop();

signals:
    void finished();
    void countZero(); // signal emits when a number of seconds is down-counted to zero

public slots:
    /// \brief Sets the message text displayed at the bottom of the widget.
    void setMessage(QString msg);
    /// \brief Overrides the current seconds counter value.
    void setSeconds(quint32 seconds);

private slots:
    void updateSeconds();

private:
    QString Message;
    quint32 Seconds;
    QMovie *m_movie;
    QTimer *m_timer;
    bool IsAllowedToStop, IsIncrement;
    int TimeFormat;
    const QString PressAnyKeyString = "Нажмите Esc, если готовы продолжить";
    int PressAnyKeyStringWidth = 0;

protected:
    void paintEvent(QPaintEvent *e) override;
    void keyPressEvent(QKeyEvent *e) override;
    void closeEvent(QCloseEvent *e) override;
};
