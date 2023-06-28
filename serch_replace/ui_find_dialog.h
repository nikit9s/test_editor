/********************************************************************************
** Form generated from reading UI file 'find_dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FIND_DIALOG_H
#define UI_FIND_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QTabWidget *tabWidget;
    QWidget *tab_1;
    QProgressBar *progressBar;
    QLabel *label;
    QLineEdit *lineEdit;
    QPushButton *FindAllButton;
    QPushButton *FindNextButton;
    QCheckBox *WordCheckBox;
    QCheckBox *CaseCheckBox;
    QGroupBox *groupBox;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QPushButton *ChanelSearchButton;
    QWidget *tab_2;
    QLabel *label_3;
    QLineEdit *lineEdit_4;
    QLabel *label_4;
    QPushButton *ReplaceButton;
    QPushButton *FindButton;
    QPushButton *ReplaceAllButton;
    QGroupBox *groupBox_3;
    QRadioButton *radioButton_5;
    QRadioButton *radioButton_6;
    QPushButton *ChanelReplaceButton;
    QCheckBox *checkBox_4;
    QCheckBox *checkBox_5;
    QLineEdit *replaceLine;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(299, 158);
        tabWidget = new QTabWidget(Dialog);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(0, 0, 301, 181));
        tab_1 = new QWidget();
        tab_1->setObjectName(QString::fromUtf8("tab_1"));
        progressBar = new QProgressBar(tab_1);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(10, 110, 281, 21));
        progressBar->setValue(0);
        label = new QLabel(tab_1);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 10, 40, 16));
        lineEdit = new QLineEdit(tab_1);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(60, 10, 133, 20));
        FindAllButton = new QPushButton(tab_1);
        FindAllButton->setObjectName(QString::fromUtf8("FindAllButton"));
        FindAllButton->setGeometry(QRect(200, 40, 80, 25));
        FindNextButton = new QPushButton(tab_1);
        FindNextButton->setObjectName(QString::fromUtf8("FindNextButton"));
        FindNextButton->setGeometry(QRect(200, 10, 80, 25));
        WordCheckBox = new QCheckBox(tab_1);
        WordCheckBox->setObjectName(QString::fromUtf8("WordCheckBox"));
        WordCheckBox->setGeometry(QRect(10, 59, 99, 17));
        CaseCheckBox = new QCheckBox(tab_1);
        CaseCheckBox->setObjectName(QString::fromUtf8("CaseCheckBox"));
        CaseCheckBox->setGeometry(QRect(10, 78, 99, 20));
        groupBox = new QGroupBox(tab_1);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(110, 40, 81, 61));
        radioButton = new QRadioButton(groupBox);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));
        radioButton->setGeometry(QRect(5, 15, 82, 30));
        radioButton->setChecked(false);
        radioButton_2 = new QRadioButton(groupBox);
        radioButton_2->setObjectName(QString::fromUtf8("radioButton_2"));
        radioButton_2->setGeometry(QRect(5, 39, 82, 20));
        radioButton_2->setAcceptDrops(false);
        radioButton_2->setChecked(true);
        ChanelSearchButton = new QPushButton(tab_1);
        ChanelSearchButton->setObjectName(QString::fromUtf8("ChanelSearchButton"));
        ChanelSearchButton->setGeometry(QRect(200, 70, 80, 25));
        tabWidget->addTab(tab_1, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        label_3 = new QLabel(tab_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(21, 10, 40, 16));
        lineEdit_4 = new QLineEdit(tab_2);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));
        lineEdit_4->setGeometry(QRect(68, 10, 133, 20));
        label_4 = new QLabel(tab_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(8, 40, 61, 20));
        ReplaceButton = new QPushButton(tab_2);
        ReplaceButton->setObjectName(QString::fromUtf8("ReplaceButton"));
        ReplaceButton->setGeometry(QRect(206, 40, 80, 25));
        FindButton = new QPushButton(tab_2);
        FindButton->setObjectName(QString::fromUtf8("FindButton"));
        FindButton->setGeometry(QRect(206, 10, 80, 25));
        ReplaceAllButton = new QPushButton(tab_2);
        ReplaceAllButton->setObjectName(QString::fromUtf8("ReplaceAllButton"));
        ReplaceAllButton->setGeometry(QRect(206, 70, 80, 25));
        groupBox_3 = new QGroupBox(tab_2);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(110, 60, 91, 61));
        radioButton_5 = new QRadioButton(groupBox_3);
        radioButton_5->setObjectName(QString::fromUtf8("radioButton_5"));
        radioButton_5->setGeometry(QRect(10, 20, 82, 20));
        radioButton_5->setChecked(false);
        radioButton_6 = new QRadioButton(groupBox_3);
        radioButton_6->setObjectName(QString::fromUtf8("radioButton_6"));
        radioButton_6->setGeometry(QRect(10, 40, 82, 20));
        radioButton_6->setChecked(true);
        ChanelReplaceButton = new QPushButton(tab_2);
        ChanelReplaceButton->setObjectName(QString::fromUtf8("ChanelReplaceButton"));
        ChanelReplaceButton->setGeometry(QRect(206, 100, 80, 25));
        checkBox_4 = new QCheckBox(tab_2);
        checkBox_4->setObjectName(QString::fromUtf8("checkBox_4"));
        checkBox_4->setGeometry(QRect(6, 99, 99, 20));
        checkBox_5 = new QCheckBox(tab_2);
        checkBox_5->setObjectName(QString::fromUtf8("checkBox_5"));
        checkBox_5->setGeometry(QRect(6, 78, 99, 17));
        replaceLine = new QLineEdit(tab_2);
        replaceLine->setObjectName(QString::fromUtf8("replaceLine"));
        replaceLine->setGeometry(QRect(68, 40, 133, 20));
        tabWidget->addTab(tab_2, QString());

        retranslateUi(Dialog);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("Dialog", "Dialog", nullptr));
        progressBar->setFormat(QCoreApplication::translate("Dialog", "%p%", nullptr));
        label->setText(QCoreApplication::translate("Dialog", "\320\230\321\201\320\272\320\260\321\202\321\214:", nullptr));
        FindAllButton->setText(QCoreApplication::translate("Dialog", "\320\235\320\260\320\271\321\202\320\270 \320\262\321\201\320\265", nullptr));
        FindNextButton->setText(QCoreApplication::translate("Dialog", "\320\230\321\201\320\272\320\260\321\202\321\214 \320\264\320\260\320\273\320\265\320\265", nullptr));
        WordCheckBox->setText(QCoreApplication::translate("Dialog", "\320\241\320\273\320\276\320\262\320\276 \321\206\320\265\320\273\320\270\320\272\320\276\320\274", nullptr));
        CaseCheckBox->setText(QCoreApplication::translate("Dialog", "\320\240\320\265\320\263\320\270\321\201\321\202\321\200", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Dialog", "\320\235\320\260\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\265", nullptr));
        radioButton->setText(QCoreApplication::translate("Dialog", "\320\222\320\262\320\265\321\200\321\205", nullptr));
        radioButton_2->setText(QCoreApplication::translate("Dialog", "\320\222\320\275\320\270\320\267", nullptr));
        ChanelSearchButton->setText(QCoreApplication::translate("Dialog", "\320\236\321\202\320\274\320\265\320\275\320\260", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_1), QCoreApplication::translate("Dialog", "\320\235\320\260\320\271\321\202\320\270", nullptr));
        label_3->setText(QCoreApplication::translate("Dialog", "\320\230\321\201\320\272\320\260\321\202\321\214:", nullptr));
        label_4->setText(QCoreApplication::translate("Dialog", "\320\227\320\260\320\274\320\265\320\275\320\270\321\202\321\214:", nullptr));
        ReplaceButton->setText(QCoreApplication::translate("Dialog", "\320\227\320\260\320\274\320\265\320\275\320\270\321\202\321\214", nullptr));
        FindButton->setText(QCoreApplication::translate("Dialog", "\320\235\320\260\320\271\321\202\320\270", nullptr));
        ReplaceAllButton->setText(QCoreApplication::translate("Dialog", "\320\227\320\260\320\274\320\265\320\275\320\270\321\202\321\214 \320\262\321\201\320\265", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("Dialog", "\320\227\320\260\320\274\320\265\320\275\320\270\321\202\321\214", nullptr));
        radioButton_5->setText(QCoreApplication::translate("Dialog", "\320\222\320\272\320\273\320\260\320\264\320\272\320\270", nullptr));
        radioButton_6->setText(QCoreApplication::translate("Dialog", "\320\244\320\260\320\271\320\273\321\213", nullptr));
        ChanelReplaceButton->setText(QCoreApplication::translate("Dialog", "\320\236\321\202\320\274\320\265\320\275\320\260", nullptr));
        checkBox_4->setText(QCoreApplication::translate("Dialog", "\320\240\320\265\320\263\320\270\321\201\321\202\321\200", nullptr));
        checkBox_5->setText(QCoreApplication::translate("Dialog", "\320\241\320\273\320\276\320\262\320\276 \321\206\320\265\320\273\320\270\320\272\320\276\320\274", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("Dialog", "\320\227\320\260\320\274\320\265\320\275\320\270\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FIND_DIALOG_H
