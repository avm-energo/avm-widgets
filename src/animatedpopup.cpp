#include "avm-widgets/animatedpopup.h"

#include <QGraphicsOpacityEffect>
#include <QParallelAnimationGroup>
#include <QScreen>
#include <algorithm>

AnimatedPopup::AnimatedPopup(QWidget *parent) : QWidget(parent), m_parent(parent)
{
    setupUI();
    setupGlobalTimer();
}

AnimatedPopup::~AnimatedPopup()
{
    if (m_instance == this)
    {
        m_instance = nullptr;
    }
}

void AnimatedPopup::setupUI()
{
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_ShowWithoutActivating);
    setWindowFlags(Qt::ToolTip | Qt::FramelessWindowHint);
    setFocusPolicy(Qt::NoFocus);
}

void AnimatedPopup::setupGlobalTimer()
{
    m_globalTimer = new QTimer(this);
    m_globalTimer->setSingleShot(true);
    connect(m_globalTimer, &QTimer::timeout, this, &AnimatedPopup::processNextPopup);
}

void AnimatedPopup::showPopup(const QString &message, const Level l, int msec)
{
    m_messageQueue.enqueue({ message, l, msec });

    if (!m_globalTimer->isActive() && hasFreeSlotForPopup())
    {
        m_globalTimer->start(m_delayBeforeNextPopup);
    }
}

void AnimatedPopup::processNextPopup()
{
    if (m_messageQueue.isEmpty())
    {
        return;
    }

    PopupMessage msg = m_messageQueue.dequeue();

    QWidget *popup = createPopupWidget(msg.text, msg.l);
    animatePopup(popup, msg.duration);


    if (!m_globalTimer->isActive() && hasFreeSlotForPopup())
    {
        m_globalTimer->start(m_delayBeforeNextPopup);
    }
}

QWidget *AnimatedPopup::createPopupWidget(const QString &message, const Level l)
{
    QWidget *popup = new QWidget(this, Qt::FramelessWindowHint | Qt::ToolTip);
    popup->setAttribute(Qt::WA_TranslucentBackground, true);

    QGraphicsOpacityEffect *opacityEffect = new QGraphicsOpacityEffect(popup);
    opacityEffect->setOpacity(0.0);
    popup->setGraphicsEffect(opacityEffect);

    QVBoxLayout *mainLayout = new QVBoxLayout(popup);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    QFrame *backgroundFrame = new QFrame(popup);
    backgroundFrame->setObjectName("PopupBackground");
    backgroundFrame->setStyleSheet(getLevelStyleSheet(l));

    QHBoxLayout *contentLayout = new QHBoxLayout(backgroundFrame);
    contentLayout->setContentsMargins(15, 12, 15, 12);
    contentLayout->setSpacing(10);

    QLabel *iconLabel = new QLabel(backgroundFrame);
    iconLabel->setStyleSheet("background: transparent; border: none; padding: 0;");
    QPixmap icon = getIconForLevel(l);
    if (!icon.isNull())
    {
        iconLabel->setPixmap(icon.scaled(22, 22, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
    iconLabel->setFixedSize(22, 22);
    contentLayout->addWidget(iconLabel, 0, Qt::AlignVCenter);

    QLabel *textLabel = new QLabel(message, backgroundFrame);
    textLabel->setStyleSheet("color: white; font-size: 14px; font-family: system-ui; background: transparent;");
    textLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    textLabel->setWordWrap(true);
    textLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    contentLayout->addWidget(textLabel, 1);

    mainLayout->addWidget(backgroundFrame);

    popup->setMaximumWidth(350);
    popup->ensurePolished();

    int availableTextWidth = 350 - (15 + 12 + 15) - 22 - 10;
    int textHeight = textLabel->heightForWidth(availableTextWidth);
    int finalHeight = std::max(22, textHeight) + 12 + 12;

    popup->resize(350, finalHeight);
    addActivePopup(popup);
    positionPopup(popup);

    return popup;
}

void AnimatedPopup::positionPopup(QWidget *popup)
{
    QRect parentGeometry = m_parent ? m_parent->geometry() : QGuiApplication::primaryScreen()->availableGeometry();

    // Считаем общий отступ снизу на основе всех живых попапов
    int accumulatedHeight = 0;

    for (const QWidget *activePopup : std::as_const(m_activePopups))
    {
        // Пропускаем пустые слоты и сам текущий попап, если он уже в списке
        if (activePopup && activePopup != popup)
        {
            // Высота попапа + расстояние между ними (10px)
            accumulatedHeight += activePopup->height() + 10;
        }
    }

    int x = parentGeometry.x() + parentGeometry.width() - popup->width() - rightMargin;

    // Стартовая позиция (до анимации появления)
    int y = parentGeometry.y() + parentGeometry.height() - bottomMargin - accumulatedHeight;

    popup->move(x, y);
}

void AnimatedPopup::animatePopup(QWidget *popup, const int duration)
{
    startAnimation(popup);

    QTimer *timer = new QTimer(popup);
    timer->setSingleShot(true);

    connect(timer, &QTimer::timeout, this, [this, popup]() {
        if (!popup)
            return;

        // Перед закрытием останавливаем любые анимации пересчета позиций
        QList<QPropertyAnimation *> oldAnims = popup->findChildren<QPropertyAnimation *>("repositionAnim");
        for (auto *oldAnim : std::as_const(oldAnims))
        {
            oldAnim->stop();
            delete oldAnim;
        }

        removeActivePopup(popup);

        // Создаем анимацию перемещения вниз
        QPropertyAnimation *posAnimation = new QPropertyAnimation(popup, "pos", popup);
        posAnimation->setDuration(m_animationDuration);
        posAnimation->setStartValue(popup->pos());
        posAnimation->setEndValue(QPoint(popup->x(), popup->y() + popup->height()));
        posAnimation->setEasingCurve(QEasingCurve::InCubic);

        // Создаем анимацию прозрачности
        QPropertyAnimation *opacityAnimation = new QPropertyAnimation(popup->graphicsEffect(), "opacity", popup);
        opacityAnimation->setStartValue(1.0);
        opacityAnimation->setEndValue(0.0);
        opacityAnimation->setDuration(m_animationDuration);
        opacityAnimation->setEasingCurve(QEasingCurve::OutCubic);

        // Используем счетчик завершения вместо QParallelAnimationGroup,
        // так как группы часто вызывают утечки "визуальных" окон в Qt при ToolTip
        auto *animationCounter = new int(2);
        auto checkAndCleanup = [this, popup, animationCounter]() {
            (*animationCounter)--;
            if (*animationCounter == 0)
            {
                delete animationCounter;
                cleanupFinishedPopup(popup);
            }
        };

        connect(posAnimation, &QPropertyAnimation::finished, this, checkAndCleanup);
        connect(opacityAnimation, &QPropertyAnimation::finished, this, checkAndCleanup);

        posAnimation->start(QAbstractAnimation::DeleteWhenStopped);
        opacityAnimation->start(QAbstractAnimation::DeleteWhenStopped);
    });

    timer->start(duration);
}

void AnimatedPopup::startAnimation(QWidget *popup)
{
    // Show the popup
    popup->show();

    int startx = popup->x();
    int starty = popup->y();

    QRect finalPos(startx, starty - popup->height(), popup->width(), popup->height());

    QPropertyAnimation *opacityAnimation = new QPropertyAnimation(popup->graphicsEffect(), "opacity");
    opacityAnimation->setStartValue(0.0);
    opacityAnimation->setEndValue(1.0);
    opacityAnimation->setDuration(m_animationDuration);
    opacityAnimation->setEasingCurve(QEasingCurve::OutCubic);

    QPropertyAnimation *posAnimation = new QPropertyAnimation(popup, "pos");
    posAnimation->setDuration(m_animationDuration);
    posAnimation->setStartValue(QPoint(startx, starty));
    posAnimation->setEndValue(QPoint(finalPos.topLeft()));
    posAnimation->setEasingCurve(QEasingCurve::OutCubic);

    QParallelAnimationGroup *group = new QParallelAnimationGroup(popup);
    group->addAnimation(opacityAnimation);
    group->addAnimation(posAnimation);

    group->start(QAbstractAnimation::DeleteWhenStopped);
}

void AnimatedPopup::cleanupFinishedPopup(QWidget *popup)
{
    if (!popup)
        return;

    popup->deleteLater();

    repositionActivePopups();

    if (!m_globalTimer->isActive() && hasFreeSlotForPopup())
    {
        processNextPopup();
    }
}

void AnimatedPopup::addActivePopup(QWidget *popup)
{
    m_activePopups.append(popup);
}

void AnimatedPopup::removeActivePopup(QWidget *popup)
{
    m_activePopups.removeAll(popup);
}

bool AnimatedPopup::hasFreeSlotForPopup()
{
    return m_activePopups.size() < m_activePopupLimit;
}

std::optional<qsizetype> AnimatedPopup::findFreeSlot()
{
    auto it = std::find(m_activePopups.begin(), m_activePopups.end(), nullptr);
    if (it != m_activePopups.end())
    {
        return it - m_activePopups.begin();
    }

    return std::nullopt;
}

QPixmap AnimatedPopup::getIconForLevel(const Level l) const
{
    static const QHash<Level, QString> iconMap = { { Level::Info, ":/icons/info-hex.svg" },
        { Level::Warning, ":/icons/warn-hex.svg" }, { Level::Error, ":/icons/err-hex.svg" } };

    if (iconMap.contains(l))
    {
        return QPixmap(iconMap.value(l));
    }

    return QPixmap("");
}

QString AnimatedPopup::getLevelStyleSheet(const Level l) const
{
    switch (l)
    {
    case Level::Info:
        return infoStyle;
        break;
    case Level::Warning:
        return warnStyle;
        break;
    case Level::Error:
        return errStyle;
        break;
    default:
        return "";
    }
}

void AnimatedPopup::repositionActivePopups()
{
    QRect parentGeometry = m_parent ? m_parent->geometry() : QGuiApplication::primaryScreen()->availableGeometry();

    int accumulatedHeight = 0;

    for (QWidget *activePopup : std::as_const(m_activePopups))
    {
        // Безопасная проверка: если виджет удаляется или скрывается, пропускаем его
        if (!activePopup)
            continue;

        int x = parentGeometry.x() + parentGeometry.width() - activePopup->width() - rightMargin;
        int targetY = parentGeometry.y() + parentGeometry.height() - bottomMargin - accumulatedHeight;

        QPoint targetPos(x, targetY - activePopup->height());

        if (activePopup->pos() != targetPos)
        {
            // Удаляем старые анимации repositionAnim
            QList<QPropertyAnimation *> oldAnims = activePopup->findChildren<QPropertyAnimation *>("repositionAnim");
            for (auto *oldAnim : std::as_const(oldAnims))
            {
                oldAnim->stop();
                delete oldAnim;
            }

            QPropertyAnimation *moveAnim = new QPropertyAnimation(activePopup, "pos", activePopup);
            moveAnim->setObjectName("repositionAnim");
            moveAnim->setDuration(m_animationDuration);
            moveAnim->setStartValue(activePopup->pos());
            moveAnim->setEndValue(targetPos);
            moveAnim->setEasingCurve(QEasingCurve::OutCubic);
            moveAnim->start(QAbstractAnimation::DeleteWhenStopped);
        }

        accumulatedHeight += activePopup->height() + 10;
    }
}

AnimatedPopup *AnimatedPopup::m_instance = nullptr;

void AnimatedPopup::setParent(QWidget *parent)
{
    if (!m_instance)
    {
        m_instance = new AnimatedPopup(parent);
    }
    else
    {
        m_instance->QWidget::setParent(parent);
    }

    m_instance->m_parent = parent;
}

AnimatedPopup *AnimatedPopup::instance()
{
    if (!m_instance)
    {
        m_instance = new AnimatedPopup(nullptr);
    }
    return m_instance;
}
