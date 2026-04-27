#pragma once

#include <QObject>
#include <QStyledItemDelegate>
#include <export.h>

/// \brief Item delegate that renders table cells as push buttons and emits clicked() on mouse release.
class WD_EXPORT PushButtonDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit PushButtonDelegate(QObject *parent = nullptr);
    /// \brief Paints the cell as a QPushButton using the model's DisplayRole text or DecorationRole icon.
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    /// \brief Handles mouse press/release to toggle the button visual state and emit clicked().
    bool editorEvent(
        QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);

signals:
    void clicked(const QModelIndex &index);

private:
    QStyle::State _state;

private slots:
};
