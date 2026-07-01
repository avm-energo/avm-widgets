#include <QKeyEvent>
#include <QVBoxLayout>
#include <avm-widgets/epopup.h>
#include <avm-widgets/graphfunc.h>
#include <avm-widgets/lblfunc.h>
#include <avm-widgets/lefunc.h>
#include <avm-widgets/passwordlineedit.h>
#include <avm-widgets/pbfunc.h>
#include <avm-widgets/styleloader.h>
#include <qpainter.h>
#include <qpainterpath.h>

EPopup::EPopup(QWidget *parent) : QDialog(parent)
{
}

EPopup::EPopup(MessageTypes type, const QString &msg, QWidget *parent) : QDialog(parent)
{
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setModal(true);
    this->m_type = type;
    create(type, LBLFunc::New(parent, msg), parent);
}

EPopup::EPopup(MessageTypes type, QWidget *w, QWidget *parent) : QDialog(parent)
{
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setModal(true);
    this->m_type = type;
    create(type, w, parent);
}

void EPopup::create(MessageTypes &type, QWidget *w, QWidget *parent)
{
    setAttribute(Qt::WA_DeleteOnClose);

    QVBoxLayout *lyout = new QVBoxLayout;
    QHBoxLayout *hlyout = new QHBoxLayout;

    // auto icon = GraphFunc::newIcon(parent, map[type].pxFile);
    // hlyout->addWidget(icon);

    hlyout->addWidget(w);
    lyout->addLayout(hlyout);

    hlyout = new QHBoxLayout;
    hlyout->addStretch(100);

    if (type == EPopup::QUESTMSG)
    {
        hlyout->addWidget(PBFunc::New(parent, "", "Да", this, &EPopup::acceptSlot));
        hlyout->addStretch(5);
        hlyout->addWidget(PBFunc::New(parent, "", "Нет", this, &EPopup::cancelSlot));
    }
    else if (type == EPopup::NEXTMSG)
    {
        hlyout->addWidget(PBFunc::New(parent, "", "Далее", this, &EPopup::acceptSlot));
        hlyout->addStretch(5);
        hlyout->addWidget(PBFunc::New(parent, "", "Отмена", this, &EPopup::cancelSlot));
    }
    else if (type != EPopup::WITHOUTANYBUTTONS)
        hlyout->addWidget(PBFunc::New(parent, "", "Далее", [&] { this->aboutToClose(); }));

    hlyout->addStretch(100);
    lyout->addLayout(hlyout);
    setLayout(lyout);
    this->adjustSize();

    setSizeGripEnabled(false);
}

void EPopup::aboutToClose()
{
    close();
}

void EPopup::showEvent(QShowEvent *e)
{
    QDialog::showEvent(e);
}

void EPopup::closeEvent(QCloseEvent *e)
{
    emit closed();
    QDialog::closeEvent(e);
}

void EPopup::keyPressEvent(QKeyEvent *e)
{

    if (e->key() == Qt::Key_Escape)
        cancelSlot();
    if ((e->key() == Qt::Key_Enter) || (e->key() == Qt::Key_Return))
        acceptSlot();
}

void EPopup::acceptSlot()
{
    emit accepted();
    aboutToClose();
}

void EPopup::cancelSlot()
{
    emit cancelled();
    aboutToClose();
}

void EPopup::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int m_borderWidth = 2;
    Qt::Orientation m_gradientOrientation = Qt::Horizontal;
    QColor m_gradientColor1 = map[m_type].firstColor;
    QColor m_gradientColor2 = map[m_type].secondColor;

    // Создаем внешний путь с закругленными углами
    QPainterPath outerPath;
    outerPath.addRoundedRect(rect(), 12, 12);

    // Создаем внутренний путь (меньше на толщину рамки)
    QRectF innerRect = rect().adjusted(m_borderWidth, m_borderWidth, -m_borderWidth, -m_borderWidth);
    QPainterPath innerPath;
    innerPath.addRoundedRect(innerRect, 12 - m_borderWidth, 12 - m_borderWidth);

    // Создаем путь для рамки (разница между внешним и внутренним путями)
    QPainterPath borderPath = outerPath - innerPath;

    // Создаем градиент
    QLinearGradient gradient;
    if (m_gradientOrientation == Qt::Horizontal)
    {
        gradient.setStart(0, 0);
        gradient.setFinalStop(width(), 0);
    }
    else
    {
        gradient.setStart(0, 0);
        gradient.setFinalStop(0, height());
    }
    gradient.setColorAt(0, m_gradientColor1);
    gradient.setColorAt(1, m_gradientColor2);

    // Рисуем градиентную рамку
    painter.fillPath(borderPath, gradient);
}
