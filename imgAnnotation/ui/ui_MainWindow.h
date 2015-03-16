/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created: Wed 23. Feb 20:14:31 2011
**      by: Qt User Interface Compiler version 4.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpenDir;
    QAction *actionQuit;
    QAction *actionShortcutHelp;
    QAction *actionCopyMask;
    QAction *actionPasteMask;
    QAction *actionUndo;
    QAction *actionRedo;
    QWidget *centralwidget;
    QMenuBar *menubar;
    QMenu *menuHelp;
    QMenu *menuMenu;
    QMenu *menuEdit;
    QStatusBar *statusbar;
    QDockWidget *imgDockWidget;
    QWidget *imgDockWidgetContents;
    QGridLayout *gridLayout;
    QTreeWidget *imgTreeWidget;
    QDockWidget *zoomDockWidget;
    QWidget *zoomDockWidgetContents;
    QVBoxLayout *vboxLayout;
    QHBoxLayout *hboxLayout;
    QLabel *zoomLabel;
    QDoubleSpinBox *zoomSpinBox;
    QSpacerItem *spacerItem;
    QDockWidget *toolDockWidget;
    QWidget *objDockWidgetContents;
    QVBoxLayout *vboxLayout1;
    QHBoxLayout *hboxLayout1;
    QLabel *label_4;
    QComboBox *brushSizeComboBox;
    QHBoxLayout *hboxLayout2;
    QLabel *label_5;
    QComboBox *maskTypeComboBox;
    QHBoxLayout *hboxLayout3;
    QLabel *label_6;
    QComboBox *drawOnTypeComboBox;
    QHBoxLayout *hboxLayout4;
    QLabel *zoomLabel_2;
    QSlider *transparencySlider;
    QDockWidget *objDockWidget;
    QWidget *objDockWidgetContents1;
    QGridLayout *gridLayout1;
    QListWidget *objListWidget;
    QPushButton *duplicateObjButton;
    QPushButton *delObjButton;
    QPushButton *addObjButton;
    QDockWidget *propDockWidget;
    QWidget *propDockWidgetContents;
    QVBoxLayout *vboxLayout2;
    QHBoxLayout *hboxLayout5;
    QLabel *label_2;
    QComboBox *objTypeComboBox;
    QLabel *label_3;
    QListWidget *tagListWidget;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(747, 590);
        actionOpenDir = new QAction(MainWindow);
        actionOpenDir->setObjectName(QString::fromUtf8("actionOpenDir"));
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        actionShortcutHelp = new QAction(MainWindow);
        actionShortcutHelp->setObjectName(QString::fromUtf8("actionShortcutHelp"));
        actionCopyMask = new QAction(MainWindow);
        actionCopyMask->setObjectName(QString::fromUtf8("actionCopyMask"));
        actionPasteMask = new QAction(MainWindow);
        actionPasteMask->setObjectName(QString::fromUtf8("actionPasteMask"));
        actionUndo = new QAction(MainWindow);
        actionUndo->setObjectName(QString::fromUtf8("actionUndo"));
        actionUndo->setEnabled(false);
        actionRedo = new QAction(MainWindow);
        actionRedo->setObjectName(QString::fromUtf8("actionRedo"));
        actionRedo->setEnabled(false);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setMinimumSize(QSize(0, 0));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 747, 29));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        menuMenu = new QMenu(menubar);
        menuMenu->setObjectName(QString::fromUtf8("menuMenu"));
        menuEdit = new QMenu(menubar);
        menuEdit->setObjectName(QString::fromUtf8("menuEdit"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        imgDockWidget = new QDockWidget(MainWindow);
        imgDockWidget->setObjectName(QString::fromUtf8("imgDockWidget"));
        QSizePolicy sizePolicy(static_cast<QSizePolicy::Policy>(5), static_cast<QSizePolicy::Policy>(5));
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(imgDockWidget->sizePolicy().hasHeightForWidth());
        imgDockWidget->setSizePolicy(sizePolicy);
        imgDockWidget->setFeatures(QDockWidget::NoDockWidgetFeatures);
        imgDockWidgetContents = new QWidget();
        imgDockWidgetContents->setObjectName(QString::fromUtf8("imgDockWidgetContents"));
        gridLayout = new QGridLayout(imgDockWidgetContents);
#ifndef Q_OS_MAC
        gridLayout->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        gridLayout->setContentsMargins(9, 9, 9, 9);
#endif
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        imgTreeWidget = new QTreeWidget(imgDockWidgetContents);
        imgTreeWidget->setObjectName(QString::fromUtf8("imgTreeWidget"));
        QSizePolicy sizePolicy1(static_cast<QSizePolicy::Policy>(13), static_cast<QSizePolicy::Policy>(7));
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(imgTreeWidget->sizePolicy().hasHeightForWidth());
        imgTreeWidget->setSizePolicy(sizePolicy1);
        imgTreeWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
        imgTreeWidget->setIndentation(20);
        imgTreeWidget->setUniformRowHeights(true);
        imgTreeWidget->setSortingEnabled(true);

        gridLayout->addWidget(imgTreeWidget, 0, 0, 1, 2);

        imgDockWidget->setWidget(imgDockWidgetContents);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(1), imgDockWidget);
        zoomDockWidget = new QDockWidget(MainWindow);
        zoomDockWidget->setObjectName(QString::fromUtf8("zoomDockWidget"));
        QSizePolicy sizePolicy2(static_cast<QSizePolicy::Policy>(5), static_cast<QSizePolicy::Policy>(0));
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(zoomDockWidget->sizePolicy().hasHeightForWidth());
        zoomDockWidget->setSizePolicy(sizePolicy2);
        zoomDockWidget->setFeatures(QDockWidget::NoDockWidgetFeatures);
        zoomDockWidgetContents = new QWidget();
        zoomDockWidgetContents->setObjectName(QString::fromUtf8("zoomDockWidgetContents"));
        vboxLayout = new QVBoxLayout(zoomDockWidgetContents);
#ifndef Q_OS_MAC
        vboxLayout->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        vboxLayout->setContentsMargins(9, 9, 9, 9);
#endif
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        hboxLayout = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        hboxLayout->setContentsMargins(0, 0, 0, 0);
#endif
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        zoomLabel = new QLabel(zoomDockWidgetContents);
        zoomLabel->setObjectName(QString::fromUtf8("zoomLabel"));

        hboxLayout->addWidget(zoomLabel);

        zoomSpinBox = new QDoubleSpinBox(zoomDockWidgetContents);
        zoomSpinBox->setObjectName(QString::fromUtf8("zoomSpinBox"));
        zoomSpinBox->setDecimals(1);
        zoomSpinBox->setMaximum(15);
        zoomSpinBox->setMinimum(0.1);
        zoomSpinBox->setSingleStep(0.5);
        zoomSpinBox->setValue(1);

        hboxLayout->addWidget(zoomSpinBox);

        spacerItem = new QSpacerItem(20, 20, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);


        vboxLayout->addLayout(hboxLayout);

        zoomDockWidget->setWidget(zoomDockWidgetContents);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(1), zoomDockWidget);
        toolDockWidget = new QDockWidget(MainWindow);
        toolDockWidget->setObjectName(QString::fromUtf8("toolDockWidget"));
        sizePolicy2.setHeightForWidth(toolDockWidget->sizePolicy().hasHeightForWidth());
        toolDockWidget->setSizePolicy(sizePolicy2);
        toolDockWidget->setFeatures(QDockWidget::NoDockWidgetFeatures);
        objDockWidgetContents = new QWidget();
        objDockWidgetContents->setObjectName(QString::fromUtf8("objDockWidgetContents"));
        sizePolicy.setHeightForWidth(objDockWidgetContents->sizePolicy().hasHeightForWidth());
        objDockWidgetContents->setSizePolicy(sizePolicy);
        vboxLayout1 = new QVBoxLayout(objDockWidgetContents);
#ifndef Q_OS_MAC
        vboxLayout1->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        vboxLayout1->setContentsMargins(9, 9, 9, 9);
#endif
        vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
        hboxLayout1 = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout1->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        hboxLayout1->setContentsMargins(0, 0, 0, 0);
#endif
        hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
        label_4 = new QLabel(objDockWidgetContents);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        hboxLayout1->addWidget(label_4);

        brushSizeComboBox = new QComboBox(objDockWidgetContents);
        brushSizeComboBox->setObjectName(QString::fromUtf8("brushSizeComboBox"));
        QSizePolicy sizePolicy3(static_cast<QSizePolicy::Policy>(3), static_cast<QSizePolicy::Policy>(0));
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(brushSizeComboBox->sizePolicy().hasHeightForWidth());
        brushSizeComboBox->setSizePolicy(sizePolicy3);
        brushSizeComboBox->setEditable(true);
        brushSizeComboBox->setInsertPolicy(QComboBox::NoInsert);

        hboxLayout1->addWidget(brushSizeComboBox);


        vboxLayout1->addLayout(hboxLayout1);

        hboxLayout2 = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout2->setSpacing(6);
#endif
        hboxLayout2->setContentsMargins(0, 0, 0, 0);
        hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
        label_5 = new QLabel(objDockWidgetContents);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        hboxLayout2->addWidget(label_5);

        maskTypeComboBox = new QComboBox(objDockWidgetContents);
        maskTypeComboBox->setObjectName(QString::fromUtf8("maskTypeComboBox"));
        sizePolicy3.setHeightForWidth(maskTypeComboBox->sizePolicy().hasHeightForWidth());
        maskTypeComboBox->setSizePolicy(sizePolicy3);
        maskTypeComboBox->setEditable(true);
        maskTypeComboBox->setInsertPolicy(QComboBox::NoInsert);

        hboxLayout2->addWidget(maskTypeComboBox);


        vboxLayout1->addLayout(hboxLayout2);

        hboxLayout3 = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout3->setSpacing(6);
#endif
        hboxLayout3->setContentsMargins(0, 0, 0, 0);
        hboxLayout3->setObjectName(QString::fromUtf8("hboxLayout3"));
        label_6 = new QLabel(objDockWidgetContents);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        hboxLayout3->addWidget(label_6);

        drawOnTypeComboBox = new QComboBox(objDockWidgetContents);
        drawOnTypeComboBox->setObjectName(QString::fromUtf8("drawOnTypeComboBox"));
        sizePolicy3.setHeightForWidth(drawOnTypeComboBox->sizePolicy().hasHeightForWidth());
        drawOnTypeComboBox->setSizePolicy(sizePolicy3);
        drawOnTypeComboBox->setEditable(true);
        drawOnTypeComboBox->setInsertPolicy(QComboBox::NoInsert);

        hboxLayout3->addWidget(drawOnTypeComboBox);


        vboxLayout1->addLayout(hboxLayout3);

        hboxLayout4 = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout4->setSpacing(6);
#endif
        hboxLayout4->setContentsMargins(0, 0, 0, 0);
        hboxLayout4->setObjectName(QString::fromUtf8("hboxLayout4"));
        zoomLabel_2 = new QLabel(objDockWidgetContents);
        zoomLabel_2->setObjectName(QString::fromUtf8("zoomLabel_2"));

        hboxLayout4->addWidget(zoomLabel_2);

        transparencySlider = new QSlider(objDockWidgetContents);
        transparencySlider->setObjectName(QString::fromUtf8("transparencySlider"));
        transparencySlider->setMaximum(10);
        transparencySlider->setPageStep(2);
        transparencySlider->setValue(5);
        transparencySlider->setSliderPosition(5);
        transparencySlider->setOrientation(Qt::Horizontal);

        hboxLayout4->addWidget(transparencySlider);


        vboxLayout1->addLayout(hboxLayout4);

        toolDockWidget->setWidget(objDockWidgetContents);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(2), toolDockWidget);
        objDockWidget = new QDockWidget(MainWindow);
        objDockWidget->setObjectName(QString::fromUtf8("objDockWidget"));
        sizePolicy.setHeightForWidth(objDockWidget->sizePolicy().hasHeightForWidth());
        objDockWidget->setSizePolicy(sizePolicy);
        objDockWidget->setFeatures(QDockWidget::NoDockWidgetFeatures);
        objDockWidgetContents1 = new QWidget();
        objDockWidgetContents1->setObjectName(QString::fromUtf8("objDockWidgetContents1"));
        gridLayout1 = new QGridLayout(objDockWidgetContents1);
#ifndef Q_OS_MAC
        gridLayout1->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        gridLayout1->setContentsMargins(9, 9, 9, 9);
#endif
        gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
        objListWidget = new QListWidget(objDockWidgetContents1);
        objListWidget->setObjectName(QString::fromUtf8("objListWidget"));
        sizePolicy1.setHeightForWidth(objListWidget->sizePolicy().hasHeightForWidth());
        objListWidget->setSizePolicy(sizePolicy1);
        objListWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);

        gridLayout1->addWidget(objListWidget, 0, 0, 1, 3);

        duplicateObjButton = new QPushButton(objDockWidgetContents1);
        duplicateObjButton->setObjectName(QString::fromUtf8("duplicateObjButton"));

        gridLayout1->addWidget(duplicateObjButton, 1, 1, 1, 1);

        delObjButton = new QPushButton(objDockWidgetContents1);
        delObjButton->setObjectName(QString::fromUtf8("delObjButton"));

        gridLayout1->addWidget(delObjButton, 1, 2, 1, 1);

        addObjButton = new QPushButton(objDockWidgetContents1);
        addObjButton->setObjectName(QString::fromUtf8("addObjButton"));

        gridLayout1->addWidget(addObjButton, 1, 0, 1, 1);

        objDockWidget->setWidget(objDockWidgetContents1);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(2), objDockWidget);
        propDockWidget = new QDockWidget(MainWindow);
        propDockWidget->setObjectName(QString::fromUtf8("propDockWidget"));
        sizePolicy.setHeightForWidth(propDockWidget->sizePolicy().hasHeightForWidth());
        propDockWidget->setSizePolicy(sizePolicy);
        propDockWidget->setFeatures(QDockWidget::NoDockWidgetFeatures);
        propDockWidgetContents = new QWidget();
        propDockWidgetContents->setObjectName(QString::fromUtf8("propDockWidgetContents"));
        vboxLayout2 = new QVBoxLayout(propDockWidgetContents);
#ifndef Q_OS_MAC
        vboxLayout2->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        vboxLayout2->setContentsMargins(9, 9, 9, 9);
#endif
        vboxLayout2->setObjectName(QString::fromUtf8("vboxLayout2"));
        hboxLayout5 = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout5->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        hboxLayout5->setContentsMargins(0, 0, 0, 0);
#endif
        hboxLayout5->setObjectName(QString::fromUtf8("hboxLayout5"));
        label_2 = new QLabel(propDockWidgetContents);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        hboxLayout5->addWidget(label_2);

        objTypeComboBox = new QComboBox(propDockWidgetContents);
        objTypeComboBox->setObjectName(QString::fromUtf8("objTypeComboBox"));
        sizePolicy3.setHeightForWidth(objTypeComboBox->sizePolicy().hasHeightForWidth());
        objTypeComboBox->setSizePolicy(sizePolicy3);
        objTypeComboBox->setEditable(true);
        objTypeComboBox->setInsertPolicy(QComboBox::InsertAlphabetically);

        hboxLayout5->addWidget(objTypeComboBox);


        vboxLayout2->addLayout(hboxLayout5);

        label_3 = new QLabel(propDockWidgetContents);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        vboxLayout2->addWidget(label_3);

        tagListWidget = new QListWidget(propDockWidgetContents);
        tagListWidget->setObjectName(QString::fromUtf8("tagListWidget"));
        sizePolicy1.setHeightForWidth(tagListWidget->sizePolicy().hasHeightForWidth());
        tagListWidget->setSizePolicy(sizePolicy1);
        tagListWidget->setSelectionMode(QAbstractItemView::MultiSelection);

        vboxLayout2->addWidget(tagListWidget);

        propDockWidget->setWidget(propDockWidgetContents);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(2), propDockWidget);
#ifndef QT_NO_SHORTCUT
        label_4->setBuddy(brushSizeComboBox);
        label_5->setBuddy(brushSizeComboBox);
        label_6->setBuddy(brushSizeComboBox);
        label_2->setBuddy(brushSizeComboBox);
        label_3->setBuddy(tagListWidget);
#endif // QT_NO_SHORTCUT

        menubar->addAction(menuMenu->menuAction());
        menubar->addAction(menuEdit->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menuHelp->addAction(actionShortcutHelp);
        menuMenu->addAction(actionOpenDir);
        menuMenu->addSeparator();
        menuMenu->addAction(actionQuit);
        menuEdit->addAction(actionUndo);
        menuEdit->addAction(actionRedo);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "ImageAnnotation", 0));
        actionOpenDir->setText(QApplication::translate("MainWindow", "&Open Directory Structure", 0));
        actionOpenDir->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", 0));
        actionQuit->setText(QApplication::translate("MainWindow", "&Quit", 0));
        actionQuit->setShortcut(QApplication::translate("MainWindow", "Ctrl+Q", 0));
        actionShortcutHelp->setText(QApplication::translate("MainWindow", "&Shortcuts", 0));
        actionCopyMask->setText(QApplication::translate("MainWindow", "&Copy Mask", 0));
        actionCopyMask->setShortcut(QApplication::translate("MainWindow", "Ctrl+C", 0));
        actionPasteMask->setText(QApplication::translate("MainWindow", "&Paste Mask", 0));
        actionPasteMask->setShortcut(QApplication::translate("MainWindow", "Ctrl+V", 0));
        actionUndo->setText(QApplication::translate("MainWindow", "Undo", 0));
        actionUndo->setShortcut(QApplication::translate("MainWindow", "Ctrl+Z", 0));
        actionRedo->setText(QApplication::translate("MainWindow", "Redo", 0));
        actionRedo->setShortcut(QApplication::translate("MainWindow", "Ctrl+Shift+Z", 0));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", 0));
        menuMenu->setTitle(QApplication::translate("MainWindow", "Database", 0));
        menuEdit->setTitle(QApplication::translate("MainWindow", "Edit", 0));
        imgDockWidget->setWindowTitle(QApplication::translate("MainWindow", "Images in Directory", 0));
        QTreeWidgetItem *___qtreewidgetitem = imgTreeWidget->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("MainWindow", "File/Directory", 0));
        zoomDockWidget->setWindowTitle(QApplication::translate("MainWindow", "Image Zoom", 0));
        zoomLabel->setText(QApplication::translate("MainWindow", "Zoom Factor:", 0));
        toolDockWidget->setWindowTitle(QApplication::translate("MainWindow", "Mask Tool Properties", 0));
        label_4->setText(QApplication::translate("MainWindow", "Brush:", 0));
        label_5->setText(QApplication::translate("MainWindow", "Mask Type:", 0));
        label_6->setText(QApplication::translate("MainWindow", "Draw on:", 0));
        zoomLabel_2->setText(QApplication::translate("MainWindow", "Mask Transparency:", 0));
        objDockWidget->setWindowTitle(QApplication::translate("MainWindow", "Objects for Image", 0));
#ifndef QT_NO_TOOLTIP
        duplicateObjButton->setToolTip(QApplication::translate("MainWindow", "Duplicates the current object mask.", 0));
#endif // QT_NO_TOOLTIP
        duplicateObjButton->setText(QApplication::translate("MainWindow", "&Duplicate", 0));
#ifndef QT_NO_TOOLTIP
        delObjButton->setToolTip(QApplication::translate("MainWindow", "Removes all selected object masks.", 0));
#endif // QT_NO_TOOLTIP
        delObjButton->setText(QApplication::translate("MainWindow", "&Remove", 0));
#ifndef QT_NO_TOOLTIP
        addObjButton->setToolTip(QApplication::translate("MainWindow", "Adds a new and empty object mask to the current image.", 0));
#endif // QT_NO_TOOLTIP
        addObjButton->setText(QApplication::translate("MainWindow", "&Add", 0));
        propDockWidget->setWindowTitle(QApplication::translate("MainWindow", "Object Properties", 0));
        label_2->setText(QApplication::translate("MainWindow", "Type:", 0));
        label_3->setText(QApplication::translate("MainWindow", "Labels:", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
