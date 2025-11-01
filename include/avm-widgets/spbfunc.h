#pragma once

#include <avm-widgets/basespinboxgroup.h>
#include <avm-widgets/edoublespinbox.h>
#include <export.h>

class WD_EXPORT SPBFunc
{
public:
    SPBFunc();

    [[nodiscard]] static EDoubleSpinBox *New(
        QWidget *parent, const QString &spbname, const double min, const double max, const int decimals);
    [[nodiscard]] static QWidget *newLBL(QWidget *parent, const QString &caption, const QString &spbname,
        const double min, const double max, const int decimals);
    [[nodiscard]] static DoubleSpinBoxGroup *newGroup(
        QWidget *parent, const QString &spbname, int count, const double min, const double max, const int decimals);
    [[nodiscard]] static DoubleSpinBoxGroup *newGroup(QWidget *parent, const QString &spbname, const QStringList &list,
        const double min, const double max, const int decimals);
    static bool setData(const QObject *parent, const QString &spbname, const double &spbvalue);

    template <size_t N, typename T>
    static bool setGroupData(const QWidget *parent, const QString &spbname, const std::array<T, N> spbvalue)
    {
        auto spbg = static_cast<DoubleSpinBoxGroup *>(parent->findChild<QWidget *>(spbname));
        if (spbg == nullptr)
            return false;
        spbg->setValue(std::vector<float>(spbvalue.cbegin(), spbvalue.cend()));
        return true;
    }

    template <typename T>
    static bool setGroupData(const QWidget *parent, const QString &spbname, const std::vector<T> &spbvalue)
    {
        auto spbg = dynamic_cast<DoubleSpinBoxGroup *>(parent->findChild<QWidget *>(spbname));
        if (spbg == nullptr)
            return false;
        spbg->setValue(spbvalue);
        return true;
    }

    template <typename T>
    static bool setGroupData(const QWidget *parent, const QString &spbname, const QList<T> &spbvalue)
    {
        auto spbg = dynamic_cast<DoubleSpinBoxGroup *>(parent->findChild<QWidget *>(spbname));
        if (spbg == nullptr)
            return false;
        spbg->setValue(spbvalue.toVector().toStdVector());
        return true;
    }

    template <typename T> static bool data(const QObject *parent, const QString &spbname, T &spbvalue)
    {
        auto spb = parent->findChild<EDoubleSpinBox *>(spbname);
        if (spb == nullptr)
        {
            spbvalue = 0;
            return false;
        }
        spbvalue = spb->value();
        return true;
    }

    template <typename T> static T data(const QObject *parent, const QString &spbname)
    {
        auto spb = parent->findChild<EDoubleSpinBox *>(spbname);
        if (spb == nullptr)
        {
            qWarning() << "No spinbox " << spbname;
            return 0;
        }
        return T(spb->value());
    }

    template <size_t N, typename T>
    static bool groupData(const QWidget *parent, const QString &spbname, std::array<T, N> &spbvalue)
    {
        auto spbg = dynamic_cast<DoubleSpinBoxGroup *>(parent->findChild<QWidget *>(spbname));
        if (spbg == nullptr)
        {
            spbvalue = {};
            return false;
        }
        auto vector = spbg->value();
        std::copy_n(vector.cbegin(), std::min(N, vector.size()), spbvalue.begin());
        // spbvalue = spbg->value();
        return true;
    }
};
