#pragma once

#include "epopup.h"
#include <export.h>

/// \brief EPopup subclass that auto-generates a form of labelled line edits for float parameters.
class WD_EXPORT EEditablePopup : public EPopup
{
    Q_OBJECT
public:
    /// \brief Constructs the popup with a heading text \a caption.
    EEditablePopup(const QString &caption, QWidget *parent = nullptr);
    /// \brief Registers a float parameter with label \a name backed by \a parameter.
    void addFloatParameter(const QString &name, float *parameter);
    /// \brief Builds the form and runs the dialog modally; writes accepted values back to pointers.
    void execPopup();

private:
    std::map<QString, float *> m_floatParList;
    bool m_result;
    QString caption;

private slots:
    void acceptSlot();
    void cancelSlot();

protected:
    void keyPressEvent(QKeyEvent *e) override;
};
