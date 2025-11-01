#include <avm-widgets/elabel.h>

ELabel::ELabel(QWidget *parent) : QLabel(parent)
{
}

ELabel::ELabel(const QString &caption, QWidget *parent) : QLabel(parent)
{
    setText(caption);
}

void ELabel::setData(const QVariant &data)
{
    m_data = data;
}

void ELabel::setData(const QString &data)
{
    m_data = QVariant::fromValue<QString>(data);
}
