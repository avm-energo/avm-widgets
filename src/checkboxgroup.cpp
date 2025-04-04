#include "widgets/checkboxgroup.h"

#include <QDebug>
#include <QVBoxLayout>
#include <widgets/checkboxgroup_p.h>
#include <widgets/flowlayout.h>

CheckBoxGroup::CheckBoxGroup(const QStringList &desc, const QList<int> &ignorePos, QWidget *parent)
    : QWidget(parent), d_ptr(new CheckBoxGroupPrivate(desc.size()))
{
    Q_D(CheckBoxGroup);
    d->q_ptr = this;
    d->setDescription(desc);
    d->setHiddenPositions(ignorePos);
    FlowLayout *flowLayout = new FlowLayout;
    flowLayout->setObjectName(desc.at(0));
    for (auto i = 0; i != d->description().size(); ++i)
    {
        const QString name = d->description().at(i);
        if (d->ignorePositions().contains(i))
            continue;
        QCheckBox *checkBox = new QCheckBox(name, this);
        checkBox->setObjectName(QString::number(i));
        flowLayout->addWidget(checkBox);
#if QT_VERSION < QT_VERSION_CHECK(6, 8, 2)
        connect(checkBox, &QCheckBox::stateChanged, this, [=](const int value) {
            Qt::CheckState state = Qt::CheckState(value);
            if (!(state == Qt::Checked && d->test(i)) && !(state == Qt::Unchecked && !d->test(i)))
                d->flip(i);
        });
#else
        connect(checkBox, &QCheckBox::checkStateChanged, this, [=](Qt::CheckState value) {
            if (!(value == Qt::Checked && d->test(i)) && !(value == Qt::Unchecked && !d->test(i)))
                d->flip(i);
        });
#endif
    }
    setLayout(flowLayout);
}

CheckBoxGroup::CheckBoxGroup(const QStringList &desc, QWidget *parent)
    : QWidget(parent), d_ptr(new CheckBoxGroupPrivate(desc.size()))
{
    Q_D(CheckBoxGroup);
    d->q_ptr = this;
    d->setDescription(desc);
    FlowLayout *flowLayout = new FlowLayout;
    flowLayout->setObjectName(desc.at(0));
    for (auto i = 0; i != d->description().size(); ++i)
    {
        const QString name = d->description().at(i);
        QCheckBox *checkBox = new QCheckBox(name, this);
        checkBox->setObjectName(QString::number(i));
        flowLayout->addWidget(checkBox);
#if QT_VERSION < QT_VERSION_CHECK(6, 8, 2)
        connect(checkBox, &QCheckBox::stateChanged, this, [=](const int value) {
            Qt::CheckState state = Qt::CheckState(value);
            if (!(state == Qt::Checked && d->test(i)) && !(state == Qt::Unchecked && !d->test(i)))
                d->flip(i);
        });
#else
        connect(checkBox, &QCheckBox::checkStateChanged, this, [=](Qt::CheckState value) {
            if (!(value == Qt::Checked && d->test(i)) && !(value == Qt::Unchecked && !d->test(i)))
                d->flip(i);
        });
#endif
    }
    setLayout(flowLayout);
}

CheckBoxGroup::CheckBoxGroup(const QStringList &desc, int count, QWidget *parent)
    : QWidget(parent), d_ptr(new CheckBoxGroupPrivate(count))
{
    if (desc.size() != count)
    {
        qWarning() << "CheckBoxGroup: desc.size not equals count";
        return;
    }
    Q_D(CheckBoxGroup);
    d->q_ptr = this;
    d->setDescription(desc);
    FlowLayout *flowLayout = new FlowLayout;
    flowLayout->setObjectName(desc.at(0));

    for (auto i = 0; i != std::min(int(d->description().size()), count); ++i)
    {
        const QString name = d->description().at(i);
        QCheckBox *checkBox = new QCheckBox(name, this);
        checkBox->setObjectName(QString::number(i));
        flowLayout->addWidget(checkBox);
#if QT_VERSION < QT_VERSION_CHECK(6, 8, 2)
        connect(checkBox, &QCheckBox::stateChanged, this, [=](const int value) {
            Qt::CheckState state = Qt::CheckState(value);
            if (!(state == Qt::Checked && d->test(i)) && !(state == Qt::Unchecked && !d->test(i)))
                d->flip(i);
        });
#else
        connect(checkBox, &QCheckBox::checkStateChanged, this, [=](Qt::CheckState value) {
            if (!(value == Qt::Checked && d->test(i)) && !(value == Qt::Unchecked && !d->test(i)))
                d->flip(i);
        });
#endif
    }
    setLayout(flowLayout);
}

CheckBoxGroup::~CheckBoxGroup()
{
    delete d_ptr;
}

template <typename T, std::enable_if_t<std::is_unsigned_v<T>, bool>> void CheckBoxGroup::setBits(const T value)
{
    Q_D(CheckBoxGroup);
    d->setBits(value);
}

template <typename T, std::enable_if_t<std::is_unsigned_v<T>, bool>> T CheckBoxGroup::bits()
{
    Q_D(CheckBoxGroup);
    return d->bits<T>();
}

template void CheckBoxGroup::setBits(const quint64 value);
template void CheckBoxGroup::setBits(const quint32 value);
template void CheckBoxGroup::setBits(const quint16 value);
template void CheckBoxGroup::setBits(const quint8 value);

template quint64 CheckBoxGroup::bits();
template quint32 CheckBoxGroup::bits();
template quint16 CheckBoxGroup::bits();
template quint8 CheckBoxGroup::bits();
