#pragma once

#include <QApplication>
#include <QLabel>
#include <QPropertyAnimation>
#include <QQueue>
#include <QTimer>
#include <QVBoxLayout>
#include <QWidget>

class AnimatedPopup : public QWidget
{

public:
    explicit AnimatedPopup(QWidget *parent = nullptr);
    ~AnimatedPopup() override = default;

    enum Level
    {
        Info,
        Warning,
        Error
    };

    void showPopup(const QString &message, const Level l, const int msec);

private:
    static constexpr int m_animationDuration = 500;
    static constexpr int m_activePopupLimit = 3;
    static constexpr int m_delayBeforeNextPopup = 500;
    static constexpr int rightMargin = 20;
    static constexpr int bottomMargin = 20;

    static constexpr const char *infoStyle = "#PopupBackground {"
                                             "  background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 "
                                             "rgba(15, 110, 15, 230), stop:1 rgba(5, 65, 5, 245));"
                                             "  border-radius: 8px;"
                                             "}";

    static constexpr const char *warnStyle = "#PopupBackground {"
                                             "  background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 "
                                             "rgba(130, 110, 10, 230), stop:1 rgba(75, 60, 5, 245));"
                                             "  border-radius: 8px;"
                                             "}";

    static constexpr const char *errStyle = "#PopupBackground {"
                                            "  background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 "
                                            "rgba(120, 10, 10, 220), stop:1 rgba(70, 5, 5, 240));"
                                            "  border-radius: 8px;"
                                            "}";

    struct PopupMessage
    {
        QString text;
        Level l;
        int duration;
    };

    QWidget *m_parent;
    QQueue<PopupMessage> m_messageQueue;
    QTimer *m_globalTimer;
    QList<QWidget *> m_activePopups;

    void setupUI();
    void setupGlobalTimer();

    void processNextPopup();
    QWidget *createPopupWidget(const QString &message, const Level l);
    void animatePopup(QWidget *popup, const int duration);
    void startAnimation(QWidget *popup);
    void positionPopup(QWidget *popup);
    void repositionActivePopups();
    void cleanupFinishedPopup(QWidget *popup);

    void addActivePopup(QWidget *popup);
    void removeActivePopup(QWidget *popup);
    std::optional<qsizetype> findFreeSlot();
    bool hasFreeSlotForPopup();

    QPixmap getIconForLevel(const Level l) const;
    QString getLevelStyleSheet(const Level l) const;
};
