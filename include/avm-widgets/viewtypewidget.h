#pragma once

#include <QEvent>
#include <QWidget>
#include <avm-gen/integers.h>
#include <avm-gen/netip.h>

using valueType = std::variant<QString, NetIP, u32>;

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
};

class ViewTypeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ViewTypeWidget(QWidget *parent = nullptr, const QString &name = "", ViewTypes type = String);

    valueType data();
    void setData(const valueType &data);

private:
    ViewTypes m_type;
    valueType m_data;

signals:

protected:
    void changeEvent(QEvent *event);
};
}
