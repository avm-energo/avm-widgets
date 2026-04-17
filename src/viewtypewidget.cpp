#include <QHBoxLayout>
#include <QtDebug>
#include <avm-gen/std_ext.h>
#include <avm-gen/stdfunc.h>
#include <avm-widgets/lblfunc.h>
#include <avm-widgets/viewtypewidget.h>
#include <avm-widgets/wdfunc.h>
#include <variant>

using namespace ViewType;

ViewTypeWidget::ViewTypeWidget(QWidget *parent, ViewTypes type) : QWidget { parent }, m_type(type)
{
    QHBoxLayout *lyout = new QHBoxLayout(this);
    switch (type)
    {
    case String:
    case SerialNumber:
    case Version:
        lyout->addWidget(LBLFunc::New(this, "", name));
        break;
    case IpControl:
        for (int i = 0; i < 4; ++i)
        {
            lyout->addWidget(LBLFunc::New(this, "", name + QString::number(i)));
            if (i < 3)
                lyout->addWidget(LBLFunc::New(this, "."));
        }
        break;
    default:
        break;
    }
    this->setLayout(lyout);
}

ValueType ViewTypeWidget::data()
{
    return m_data;
}

void ViewTypeWidget::setData(const ValueType &data)
{
    m_data = data;
    switch (m_type)
    {
    case String:
        std::visit(
            overloaded {
                [&](const u32 &number) { LBLFunc::setText(this, name, QString::number(number)); }, //
                [&](const QString &str) { LBLFunc::setText(this, name, str); },                    //
                [&](const NetIP &ip) { LBLFunc::setText(this, name, IP::toString(ip)); }, // default: not a number
            },                                                                            //
            data);
        break;
    case IpControl:
    {
        QStringList sl;
        std::visit(overloaded {
                       [&](const NetIP &IP) { sl = IP::toStringList(IP); }, //
                       [&](const QString &str) { sl = str.split("."); },    //
                       [&](const auto &) { sl = QStringList(); },           // default: not an IP
                   },                                                       //
            data);
        if (sl.size() > 3)
        {
            for (int i = 0; i < 4; ++i)
                LBLFunc::setText(this, name + QString::number(i), sl.at(i));
        }
        else
            qDebug() << "Improper data for IpControl: " << std::get<QString>(data);
        break;
    }
    case SerialNumber:
        std::visit(overloaded {
                       [&](const u32 &number) { LBLFunc::setText(this, name, QString::number(number, 16)); }, //
                       [&](const QString &str) { LBLFunc::setText(this, name, str); },                        //
                       [&](const auto &) {}, // default: not a number
                   },                        //
            data);
        break;
    case Version:
        std::visit(overloaded {
                       [&](const u32 &number) { LBLFunc::setText(this, name, StdFunc::VerToStr(number)); }, //
                       [&](const QString &str) { LBLFunc::setText(this, name, str); },                      //
                       [&](const auto &) {}, // default: not a number
                   },                        //
            data);
        break;
    default:
        break;
    }
}

void ViewTypeWidget::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::EnabledChange)
    {
        if (m_type == IpControl)
        {
            for (int i = 0; i < 4; ++i)
                WDFunc::setEnabled(this, name + QString::number(i), isEnabled());
        }
        else
            setEnabled(isEnabled());
    }
    else
        QWidget::changeEvent(event);
}

ViewTypeWidget *ViewTypeFunc::New(QWidget *parent, const QString &name, ViewTypes type)
{
    auto vtw = new ViewTypeWidget(parent, type);
    vtw->setObjectName(name);
    return vtw;
}

ViewTypeWidget *ViewTypeFunc::widget(QWidget *parent, const QString &name)
{
    auto vtw = parent->findChild<ViewTypeWidget *>(name);
    if (vtw == nullptr)
        return nullptr;
    return vtw;
}
