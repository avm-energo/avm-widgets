#pragma once

#include <QComboBox>
#include <export.h>

class WD_EXPORT CBFunc
{
public:
    CBFunc();

    /// \brief Returns ComboBox widget
    /// \param parent - pointer to parent widget
    /// \param cbname - name of combobox to find by objectName
    /// \return QComboBox object
    [[nodiscard]] static QComboBox *comboBox(QWidget *parent, const QString &cbname);
    /// \brief Creates new ComboBox widget
    /// \param parent - pointer to parent widget
    /// \param cbname - name of combobox to find by objectName
    /// \param cbsl - stringlist of combobox members
    /// \return QComboBox object
    [[nodiscard]] static QComboBox *New(QWidget *parent, const QString &cbname, const QStringList &cbsl);
    /// \brief Creates new ComboBox widget
    /// \param parent - pointer to parent widget
    /// \param cbsl - stringlist of combobox members
    /// \return QComboBox object
    [[nodiscard]] static QComboBox *New(QWidget *parent, const QStringList &cbsl);
    /// \brief Creates new ComboBox widget with label before it
    /// \param parent - pointer to parent widget
    /// \param caption - label text
    /// \param cbname - name of combobox to find by objectName
    /// \param cbsl - stringlist of combobox members
    /// \return QComboBox object
    [[nodiscard]] static QWidget *newLBL(
        QWidget *parent, const QString &caption, const QString &cbname, const QStringList &cbsl);
    /// \brief Sets current string in ComboBox
    /// \param parent - pointer to parent widget
    /// \param cbname - combobox objectName to find
    /// \param cbvalue - text to set in combobox
    static bool setData(const QWidget *parent, const QString &cbname, const QString &cbvalue);
    /// \brief Sets current string by its index in ComboBox
    /// \param parent - pointer to parent widget
    /// \param cbname - combobox objectName to find
    /// \param index - index of text to set in combobox
    static bool setIndex(const QObject *parent, const QString &cbname, int index);
    /// \brief Sets current color of text in ComboBox
    /// \param parent - pointer to parent widget
    /// \param cbname - combobox objectName to find
    /// \param color - color of the text in format: #RRGGBB
    static bool setColor(QWidget *parent, const QString &cbname, const QString &color);
    /// \brief Returns current text in ComboBox
    /// \param parent - pointer to parent widget
    /// \param cbname - combobox objectName to find
    /// \return Current text in ComboBox
    static QString data(const QWidget *parent, const QString &cbname);
    /// \brief Returns current index
    /// \param parent - pointer to parent widget
    /// \param cbname - combobox objectName to find
    /// \return Current index
    static int index(const QObject *parent, const QString &cbname);

    /// \brief Returns current text in ComboBox by terms of the type of invoke
    /// \details If the type is float translate number in combobox changing comma to dot
    /// \param parent - pointer to parent widget
    /// \param cbname - combobox objectName to find
    /// \return Current value in ComboBox
    template <typename T> static T data(const QWidget *parent, const QString &cbname)
    {
        auto buffer = data(parent, cbname);
        if constexpr (std::is_floating_point_v<T>)
            buffer.replace(',', '.');
        return QVariant(buffer).value<T>();
    }
};
