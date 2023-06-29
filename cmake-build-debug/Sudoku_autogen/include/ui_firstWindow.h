/********************************************************************************
** Form generated from reading UI file 'firstWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FIRSTWINDOW_H
#define UI_FIRSTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *verticalLayout_2;
    QLabel *playerAmountLabel;
    QComboBox *playerAmountcomboBox;
    QLabel *gridSizeLabel;
    QComboBox *gridSizeComboBox;
    QPushButton *startButton;
    QLabel *errorLabel;

    void setupUi(QMainWindow *mainWindow)
    {
        if (mainWindow->objectName().isEmpty())
            mainWindow->setObjectName(QString::fromUtf8("mainWindow"));
        mainWindow->resize(1370, 929);
        mainWindow->setIconSize(QSize(10, 10));
        centralwidget = new QWidget(mainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        playerAmountLabel = new QLabel(centralwidget);
        playerAmountLabel->setObjectName(QString::fromUtf8("playerAmountLabel"));
        playerAmountLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(playerAmountLabel);

        playerAmountcomboBox = new QComboBox(centralwidget);
        playerAmountcomboBox->addItem(QString());
        playerAmountcomboBox->addItem(QString());
        playerAmountcomboBox->addItem(QString());
        playerAmountcomboBox->addItem(QString());
        playerAmountcomboBox->setObjectName(QString::fromUtf8("playerAmountcomboBox"));

        verticalLayout_2->addWidget(playerAmountcomboBox);

        gridSizeLabel = new QLabel(centralwidget);
        gridSizeLabel->setObjectName(QString::fromUtf8("gridSizeLabel"));
        gridSizeLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(gridSizeLabel);

        gridSizeComboBox = new QComboBox(centralwidget);
        gridSizeComboBox->addItem(QString());
        gridSizeComboBox->addItem(QString());
        gridSizeComboBox->addItem(QString());
        gridSizeComboBox->setObjectName(QString::fromUtf8("gridSizeComboBox"));
        gridSizeComboBox->setEditable(false);
        gridSizeComboBox->setIconSize(QSize(11, 11));

        verticalLayout_2->addWidget(gridSizeComboBox);

        startButton = new QPushButton(centralwidget);
        startButton->setObjectName(QString::fromUtf8("startButton"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(startButton->sizePolicy().hasHeightForWidth());
        startButton->setSizePolicy(sizePolicy);

        verticalLayout_2->addWidget(startButton);

        errorLabel = new QLabel(centralwidget);
        errorLabel->setObjectName(QString::fromUtf8("errorLabel"));
        errorLabel->setStyleSheet(QString::fromUtf8("color=rgb(239, 41, 41)"));

        verticalLayout_2->addWidget(errorLabel);


        verticalLayout->addLayout(verticalLayout_2);

        mainWindow->setCentralWidget(centralwidget);

        retranslateUi(mainWindow);

        gridSizeComboBox->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(mainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *mainWindow)
    {
        mainWindow->setWindowTitle(QApplication::translate("mainWindow", "startScreen", nullptr));
        playerAmountLabel->setText(QApplication::translate("mainWindow", "How many players?", nullptr));
        playerAmountcomboBox->setItemText(0, QApplication::translate("mainWindow", "1", nullptr));
        playerAmountcomboBox->setItemText(1, QApplication::translate("mainWindow", "2", nullptr));
        playerAmountcomboBox->setItemText(2, QApplication::translate("mainWindow", "3", nullptr));
        playerAmountcomboBox->setItemText(3, QApplication::translate("mainWindow", "4", nullptr));

        gridSizeLabel->setText(QApplication::translate("mainWindow", "Which size?", nullptr));
        gridSizeComboBox->setItemText(0, QApplication::translate("mainWindow", "9x9", nullptr));
        gridSizeComboBox->setItemText(1, QApplication::translate("mainWindow", "16x16", nullptr));
        gridSizeComboBox->setItemText(2, QApplication::translate("mainWindow", "25x25", nullptr));

        startButton->setText(QApplication::translate("mainWindow", "Create Game", nullptr));
        errorLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class mainWindow: public Ui_mainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FIRSTWINDOW_H
