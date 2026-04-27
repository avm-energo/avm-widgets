#pragma once

#include <QLabel>
#include <QMouseEvent>
#include <QScrollArea>
#include <export.h>

/// \brief A scroll area showing a list of checkboxes and labels for signal selection.
class WD_EXPORT SignalChooseWidget : public QScrollArea
{
    Q_OBJECT
public:
    /// \brief Constructs the widget; \a snames are signal identifiers, \a discr are tooltip descriptions.
    explicit SignalChooseWidget(const QStringList &snames, const QStringList &discr, QWidget *parent = nullptr);

signals:
    /// \brief Emitted when the user clicks a signal label (requests trend highlight in oscilloscope).
    void signalChoosed(QString signame);
    /// \brief Emitted when the user toggles a signal checkbox.
    void signalToggled(QString signame, bool isChecked);

public slots:
    /// \brief Programmatically sets the checked state of the checkbox for \a signame.
    void setChecked(QString signame, bool checked);
};

/// \brief A clickable QLabel used inside SignalChooseWidget to represent a single signal.
class MarkSignalWidget : public QLabel
{
    Q_OBJECT
public:
    explicit MarkSignalWidget(const QString &text, QWidget *parent = nullptr);

signals:
    /// \brief Emitted when the user clicks the label.
    void clicked();

protected:
    void mousePressEvent(QMouseEvent *e) override;
};
