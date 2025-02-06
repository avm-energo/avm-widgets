#include "widgets/waitwidget.h"

#include <QApplication>
#include <QFontMetrics>
#include <QLabel>
#include <QPainter>
#include <QRandomGenerator>
#include <QTimer>

WaitWidget::WaitWidget(QWidget *parent) : QWidget(parent)
{
    //    setAttribute(Qt::WA_TranslucentBackground);
    setStyleSheet("QWidget {background: rgb(0, 186, 144);}");
    setAttribute(Qt::WA_DeleteOnClose);
    QRandomGenerator random;
    quint8 gifNumber = random.bounded(movies.size());
    QLabel *lbl = new QLabel;
    m_movie = new QMovie(movies.at(gifNumber));
    lbl->setMovie(m_movie);
    Message = "";
    resize(320, 380);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    IsAllowedToStop = false;
    IsIncrement = true;
    TimeFormat = WW_SIMPLE;
    Seconds = 0;
}

WaitWidget::~WaitWidget()
{
}

void WaitWidget::Init(WaitWidget::ww_struct &ww)
{
    this->IsAllowedToStop = ww.isallowedtostop;
    this->IsIncrement = ww.isincrement;
    this->TimeFormat = ww.format;
    this->Seconds = ww.initialseconds;
    QFont font;
    QFontMetrics fm(font);
    PressAnyKeyStringWidth = fm.horizontalAdvance(PressAnyKeyString); //+10;
}

void WaitWidget::Start()
{
    show();
    m_movie->start();
    QTimer *tmrs = new QTimer(this);
    tmrs->setInterval(1000);
    connect(tmrs, &QTimer::timeout, this, &WaitWidget::UpdateSeconds);
    tmrs->start();
}

void WaitWidget::Stop()
{
    emit finished();
    m_movie->stop();
    close();
}

void WaitWidget::SetMessage(QString msg)
{
    Message = msg;
}

void WaitWidget::SetSeconds(quint32 seconds)
{
    Seconds = seconds;
}

void WaitWidget::UpdateSeconds()
{
    if (IsIncrement)
        ++Seconds;
    else
    {
        --Seconds;
        if (Seconds == 0)
        {
            emit CountZero();
            Stop();
        }
    }
}

void WaitWidget::paintEvent(QPaintEvent *e)
{
    QSize size = QSize(320, 240);
    QSize wsize = QSize(310, 380);
    int left = wsize.width() / 2 - size.width() / 2;
    QPainter p(this);
    QFont font;
    QFontMetrics fm(font);
    int center = wsize.width() / 2;
    int msgwidth = fm.horizontalAdvance(Message); //+10;
    left = center - msgwidth / 2;
    QRect mrect = QRect(left, height() - 20, msgwidth, 20);
    p.setPen(Qt::black);
    p.drawText(mrect, Qt::AlignCenter, Message);
    if (IsAllowedToStop)
    {
        left = center - PressAnyKeyStringWidth / 2;
        mrect = QRect(left, height() - 40, PressAnyKeyStringWidth, 20);
        p.drawText(mrect, Qt::AlignCenter, PressAnyKeyString);
    }
    p.end();
    QPainter ps(this);
    QPen pen(Qt::darkGreen, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    ps.setPen(pen);
    font.setFamily("Helvetica");
    font.setPointSize(20);
    ps.setFont(font);
    QRect srect = QRect(0, height() - 65, width(), 24);
    QString SecondsString = (TimeFormat == WW_TIME)
        ? (QString::number(Seconds / 60) + ":" + QString::number(Seconds % 60))
        : QString::number(Seconds);
    ps.drawText(srect, Qt::AlignCenter, SecondsString);
    ps.end();
    e->accept();
}

void WaitWidget::keyPressEvent(QKeyEvent *e)
{
    if ((e->key() == Qt::Key_Escape) && IsAllowedToStop)
    {
        Stop();
        emit CountZero();
    }
    QWidget::keyPressEvent(e);
}

void WaitWidget::closeEvent(QCloseEvent *e)
{
    emit CountZero();
    e->accept();
}
