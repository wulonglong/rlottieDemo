/********************************************************************************
** Form generated from reading UI file 'AnimationForm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ANIMATIONFORM_H
#define UI_ANIMATIONFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AnimationForm
{
public:

    void setupUi(QWidget *AnimationForm)
    {
        if (AnimationForm->objectName().isEmpty())
            AnimationForm->setObjectName(QString::fromUtf8("AnimationForm"));
        AnimationForm->resize(400, 300);

        retranslateUi(AnimationForm);

        QMetaObject::connectSlotsByName(AnimationForm);
    } // setupUi

    void retranslateUi(QWidget *AnimationForm)
    {
        AnimationForm->setWindowTitle(QCoreApplication::translate("AnimationForm", "AnimationForm", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AnimationForm: public Ui_AnimationForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ANIMATIONFORM_H
