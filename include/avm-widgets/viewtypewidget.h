#pragma once

#include <QEvent>
#include <QWidget>
#include <avm-gen/integers.h>
#include <avm-gen/netip.h>
#include <export.h>

using ValueType = std::variant<QString, NetIP, u32>;

namespace
{
constexpr auto name = "name";
}
// Widget with representation depending of ViewType
namespace ViewType
{
enum ViewTypes
{
    String,       // simple string
    IpControl,    // four lineedits with dots
    SerialNumber, // serial in hex format
    Version,      // version like HW.MW-LW
    Unknown
};

class WD_EXPORT ViewTypeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ViewTypeWidget(QWidget *parent = nullptr, ViewTypes type = String);

    ValueType data();
    void setData(const ValueType &data);

private:
    ViewTypes m_type;
    ValueType m_data;

signals:

protected:
    void changeEvent(QEvent *event);
};

class WD_EXPORT ViewTypeFunc
{
public:
    static ViewTypeWidget *New(QWidget *parent, const QString &name, ViewTypes type = String);
    static ViewTypeWidget *widget(QWidget *parent, const QString &name);
    template <typename T> static T data(QWidget *parent, const QString &name)
    {
        auto vtw = parent->findChild<ViewTypeWidget *>(name);
        if (vtw == nullptr)
            return QString();
        return vtw->data();
    }
    template <typename T> static bool setData(QWidget *parent, const QString &name, const T &value)
    {
        auto vtw = parent->findChild<ViewTypeWidget *>(name);
        if (vtw == nullptr)
            return false;
        vtw->setData(value);
        return true;
    }
};
}
