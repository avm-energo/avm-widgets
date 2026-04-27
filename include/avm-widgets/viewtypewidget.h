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
/// \brief Widget with a display representation that depends on the selected ViewType.
namespace ViewType
{
enum ViewTypes
{
    String,       ///< Simple text label
    IpControl,    ///< Four labels separated by dots (e.g. "192.168.1.1")
    SerialNumber, ///< Unsigned integer displayed in hex
    Version,      ///< Version number in "HW.MW-LW" format
    Unknown
};

/// \brief A widget that displays a ValueType variant according to the configured ViewTypes mode.
class WD_EXPORT ViewTypeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ViewTypeWidget(QWidget *parent = nullptr, ViewTypes type = String);

    /// \brief Returns the currently stored data value.
    ValueType data();
    /// \brief Updates the displayed value from \a data, formatting it according to the ViewType.
    void setData(const ValueType &data);

private:
    ViewTypes m_type;
    ValueType m_data;

signals:

protected:
    /// \brief Propagates enabled-state changes to child labels for IpControl mode.
    void changeEvent(QEvent *event) override;
};

/// \brief Factory and accessor helpers for ViewTypeWidget.
class WD_EXPORT ViewTypeFunc
{
public:
    /// \brief Creates a new ViewTypeWidget with the given \a type and object name \a name.
    static ViewTypeWidget *New(QWidget *parent, const QString &name, ViewTypes type = String);
    /// \brief Finds a ViewTypeWidget by \a name inside \a parent.
    static ViewTypeWidget *widget(QWidget *parent, const QString &name);
    /// \brief Returns the widget's data value cast to \a T.
    template <typename T> static T data(QWidget *parent, const QString &name)
    {
        auto vtw = parent->findChild<ViewTypeWidget *>(name);
        if (vtw == nullptr)
            return QString();
        return vtw->data();
    }
    /// \brief Sets the widget's data to \a value; returns false if the widget is not found.
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
