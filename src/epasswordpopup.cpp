#include <QCryptographicHash>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QPainter>
#include <avm-widgets/emessagebox.h>
#include <avm-widgets/epasswordpopup.h>
#include <avm-widgets/graphfunc.h>
#include <avm-widgets/lblfunc.h>
#include <avm-widgets/lefunc.h>
#include <avm-widgets/styleloader.h>
#include <qpainterpath.h>

EPasswordPopup::EPasswordPopup(const QString &hash, QWidget *parent) : EPopup(parent)
{
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setModal(true);

    isAboutToClose = false;
    m_hash = hash;

    QHBoxLayout *hlyout = new QHBoxLayout;

    auto text = LBLFunc::New(this, "Введите пароль\n\nПодтверждение: клавиша Enter\nОтмена: клавиша Esc", "pswlbl");
    hlyout->addWidget(text);

    QVBoxLayout *vlyout = new QVBoxLayout;
    vlyout->addLayout(hlyout);
    vlyout->addWidget(LEFunc::newPsw(this, "pswle", QLineEdit::Password));

    setLayout(vlyout);
    adjustSize();

    setSizeGripEnabled(false);
}

bool EPasswordPopup::checkPassword(const QString &password)
{
    QCryptographicHash hasher(QCryptographicHash::Sha3_256);
    hasher.addData(password.toUtf8());
    auto buffer = QString::fromUtf8(hasher.result().toHex());
    return (m_hash == buffer);
}

void EPasswordPopup::keyPressEvent(QKeyEvent *e)
{
    if ((e->modifiers() == Qt::AltModifier) || (e->modifiers() == Qt::ControlModifier))
    {
        qCritical("Ошибка при обработке пароля");
        return;
    }

    if ((e->key() == Qt::Key_Enter) || (e->key() == Qt::Key_Return))
    {
        if (checkPassword(LEFunc::data(this, "pswle")))
        {
            emit passwordIsCorrect();
            aboutToClose();
        }
        else
        {
            qCritical("Пароль введён неверно");
            EMessageBox::warning(this, "Пароль неверен");
        }
    }
    if ((e->key() == Qt::Key_Escape) && !isAboutToClose)
    {
        isAboutToClose = true;
        EPopup::cancelSlot();
    }
    QDialog::keyPressEvent(e);
}

void EPasswordPopup::closeEvent(QCloseEvent *e)
{
    EPopup::closeEvent(e);
}

void EPasswordPopup::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int m_borderWidth = 2;
    Qt::Orientation m_gradientOrientation = Qt::Horizontal;
    QColor m_gradientColor1 = QColor(251, 207, 232);
    QColor m_gradientColor2 = QColor(196, 181, 253);

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
