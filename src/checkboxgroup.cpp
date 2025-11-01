#include <QDebug>
#include <QVBoxLayout>
#include <avm-widgets/checkboxgroup.h>
#include <avm-widgets/flowlayout.h>

CheckBoxGroup::CheckBoxGroup(const QStringList &desc, const QList<int> &ignorePos, QWidget *parent) : QWidget(parent)
{
    setDescription(desc);
    setHiddenPositions(ignorePos);
    FlowLayout *flowLayout = new FlowLayout;
    flowLayout->setObjectName(desc.at(0));
    for (auto i = 0; i != description().size(); ++i)
    {
        const QString name = description().at(i);
        if (ignorePositions().contains(i))
            continue;
        QCheckBox *checkBox = new QCheckBox(name, this);
        checkBox->setObjectName(QString::number(i));
        flowLayout->addWidget(checkBox);
#if QT_VERSION < QT_VERSION_CHECK(6, 7, 0)
        connect(checkBox, &QCheckBox::stateChanged, this, [=](const int value) {
            Qt::CheckState state = Qt::CheckState(value);
            if (!(state == Qt::Checked && test(i)) && !(state == Qt::Unchecked && !test(i)))
                flip(i);
        });
#else
        connect(checkBox, &QCheckBox::checkStateChanged, this, [=](Qt::CheckState value) {
            if (!(value == Qt::Checked && test(i)) && !(value == Qt::Unchecked && !test(i)))
                flip(i);
        });
#endif
    }
    setLayout(flowLayout);
}

CheckBoxGroup::CheckBoxGroup(const QStringList &desc, QWidget *parent) : QWidget(parent)
{
    setDescription(desc);
    FlowLayout *flowLayout = new FlowLayout;
    flowLayout->setObjectName(desc.at(0));
    for (auto i = 0; i != description().size(); ++i)
    {
        const QString name = description().at(i);
        QCheckBox *checkBox = new QCheckBox(name, this);
        checkBox->setObjectName(QString::number(i));
        flowLayout->addWidget(checkBox);
#if QT_VERSION < QT_VERSION_CHECK(6, 7, 0)
        connect(checkBox, &QCheckBox::stateChanged, this, [=](const int value) {
            Qt::CheckState state = Qt::CheckState(value);
            if (!(state == Qt::Checked && test(i)) && !(state == Qt::Unchecked && !test(i)))
                flip(i);
        });
#else
        connect(checkBox, &QCheckBox::checkStateChanged, this, [=](Qt::CheckState value) {
            if (!(value == Qt::Checked && test(i)) && !(value == Qt::Unchecked && !test(i)))
                flip(i);
        });
#endif
    }
    setLayout(flowLayout);
}

CheckBoxGroup::CheckBoxGroup(const QStringList &desc, int count, QWidget *parent) : QWidget(parent)
{
    if (desc.size() != count)
    {
        qWarning() << "CheckBoxGroup: desc.size not equals count";
        return;
    }
    setDescription(desc);
    FlowLayout *flowLayout = new FlowLayout;
    flowLayout->setObjectName(desc.at(0));

    for (auto i = 0; i != std::min(int(description().size()), count); ++i)
    {
        const QString name = description().at(i);
        QCheckBox *checkBox = new QCheckBox(name, this);
        checkBox->setObjectName(QString::number(i));
        flowLayout->addWidget(checkBox);
#if QT_VERSION < QT_VERSION_CHECK(6, 7, 0)
        connect(checkBox, &QCheckBox::stateChanged, this, [=](const int value) {
            Qt::CheckState state = Qt::CheckState(value);
            if (!(state == Qt::Checked && test(i)) && !(state == Qt::Unchecked && !test(i)))
                flip(i);
        });
#else
        connect(checkBox, &QCheckBox::checkStateChanged, this, [=](Qt::CheckState value) {
            if (!(value == Qt::Checked && test(i)) && !(value == Qt::Unchecked && !test(i)))
                flip(i);
        });
#endif
    }
    setLayout(flowLayout);
}

CheckBoxGroup::~CheckBoxGroup()
{
}
