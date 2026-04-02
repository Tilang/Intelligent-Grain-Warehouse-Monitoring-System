/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label_title;
    QTabWidget *tabWidget;
    QWidget *tab_warehouse1;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox_control1;
    QHBoxLayout *horizontalLayout_control1;
    QSpacerItem *horizontalSpacer_left1;
    QPushButton *btnLamp1;
    QPushButton *btnFan1;
    QPushButton *btnBuzzer1;
    QPushButton *btnAutoMode1;
    QSpacerItem *horizontalSpacer_right1;
    QGroupBox *groupBox_threshold1;
    QGridLayout *gridLayout_threshold1;
    QLineEdit *editLightMin1;
    QLabel *label_4;
    QLabel *label;
    QLineEdit *editLightMax1;
    QLineEdit *editHumidityMax1;
    QLabel *label_6;
    QLineEdit *editHumidityMin1;
    QLabel *label_5;
    QGroupBox *groupBox_status1;
    QGridLayout *gridLayout_status1;
    QLabel *labelTemp1;
    QLabel *labelHumidity1;
    QLabel *labelLight1;
    QLabel *labelConnect1;
    QSpacerItem *verticalSpacer_1;
    QWidget *tab_warehouse2;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBox_control2;
    QGridLayout *gridLayout_control2;
    QPushButton *btnLamp2;
    QPushButton *btnFan2;
    QPushButton *btnAutoMode2;
    QPushButton *btnMotor2;
    QPushButton *btnBuzzer2;
    QGroupBox *groupBox_threshold2;
    QGridLayout *gridLayout_threshold2;
    QLabel *label_10;
    QLineEdit *editHumidityMax2;
    QLabel *label_11;
    QLineEdit *editHumidityMin2;
    QLabel *label_9;
    QLineEdit *editCO2Max2;
    QLabel *label_12;
    QLineEdit *editCO2Min2;
    QLabel *label_13;
    QLineEdit *editLightMax2;
    QLabel *label_14;
    QLineEdit *editLightMin2;
    QGroupBox *groupBox_status2;
    QGridLayout *gridLayout_status2;
    QLabel *labelTemp2;
    QLabel *labelHumidity2;
    QLabel *labelCO2_2;
    QLabel *labelLight2;
    QLabel *labelTTL2;
    QLabel *labelConnect2;
    QSpacerItem *verticalSpacer_2;
    QStatusBar *statusBar;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(1000, 850);
        Widget->setMinimumSize(QSize(1000, 850));
        Widget->setStyleSheet(QString::fromUtf8("QWidget {\n"
"    background-color: #f8f9fa;\n"
"    font-family: 'Segoe UI', 'Microsoft YaHei', sans-serif;\n"
"}\n"
"\n"
"QTabWidget::pane {\n"
"    border: 1px solid #ced4da;\n"
"    border-radius: 8px;\n"
"    background-color: white;\n"
"    margin-top: 5px;\n"
"}\n"
"\n"
"QTabBar::tab {\n"
"    background-color: #e9ecef;\n"
"    border: 1px solid #ced4da;\n"
"    border-bottom: none;\n"
"    border-top-left-radius: 6px;\n"
"    border-top-right-radius: 6px;\n"
"    padding: 10px 20px;\n"
"    margin-right: 2px;\n"
"    font-weight: bold;\n"
"    color: #495057;\n"
"    font-size: 14px; /* Increased by 2 */\n"
"}\n"
"\n"
"QTabBar::tab:selected {\n"
"    background-color: white;\n"
"    color: #007bff;\n"
"    border-bottom: 3px solid #007bff;\n"
"}\n"
"\n"
"QTabBar::tab:hover {\n"
"    background-color: #dee2e6;\n"
"}\n"
"\n"
"QGroupBox {\n"
"    font-weight: bold;\n"
"    font-size: 18px; /* Increased by 2 */\n"
"    color: #212529;\n"
"    border: 2px solid #dee2e6;\n"
"    border-radius: 8px;\n"
"    m"
                        "argin-top: 15px;\n"
"    padding-top: 12px;\n"
"    background-color: white;\n"
"}\n"
"\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    left: 15px;\n"
"    padding: 0 10px 0 10px;\n"
"    background-color: white;\n"
"}\n"
"\n"
"QPushButton {\n"
"    font-weight: bold;\n"
"    font-size: 17px; /* Increased by 2 */\n"
"    border-radius: 6px;\n"
"    padding: 12px 5px;\n"
"    min-height: 50px;\n"
"    border: none;\n"
"    margin: 8px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    transform: translateY(-2px);\n"
"    box-shadow: 0 4px 8px rgba(0,0,0,0.1);\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    transform: translateY(0);\n"
"    box-shadow: 0 2px 4px rgba(0,0,0,0.1);\n"
"}\n"
"\n"
"QLabel {\n"
"    font-size: 17px; /* Increased by 2 */\n"
"    padding: 10px 12px;\n"
"    border-radius: 6px;\n"
"    margin: 4px;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QStatusBar {\n"
"    background-color: #343a40;\n"
"    color: white;\n"
"    font-size: 18px; /* Increased by 2 */\n"
"    padding: 12px;\n"
""
                        "    border-top: 2px solid #007bff;\n"
"}\n"
"\n"
"QLineEdit {\n"
"    padding: 8px;\n"
"    border: 2px solid #ced4da;\n"
"    border-radius: 6px;\n"
"    font-size: 16px; /* Increased by 2 */\n"
"    margin: 4px;\n"
"}\n"
"\n"
"QLineEdit:focus {\n"
"    border-color: #007bff;\n"
"    outline: none;\n"
"}"));
        verticalLayout = new QVBoxLayout(Widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_title = new QLabel(Widget);
        label_title->setObjectName(QString::fromUtf8("label_title"));
        label_title->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_title);

        tabWidget = new QTabWidget(Widget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab_warehouse1 = new QWidget();
        tab_warehouse1->setObjectName(QString::fromUtf8("tab_warehouse1"));
        verticalLayout_2 = new QVBoxLayout(tab_warehouse1);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        groupBox_control1 = new QGroupBox(tab_warehouse1);
        groupBox_control1->setObjectName(QString::fromUtf8("groupBox_control1"));
        horizontalLayout_control1 = new QHBoxLayout(groupBox_control1);
        horizontalLayout_control1->setObjectName(QString::fromUtf8("horizontalLayout_control1"));
        horizontalSpacer_left1 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_control1->addItem(horizontalSpacer_left1);

        btnLamp1 = new QPushButton(groupBox_control1);
        btnLamp1->setObjectName(QString::fromUtf8("btnLamp1"));
        btnLamp1->setMinimumSize(QSize(180, 94));
        btnLamp1->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"                                stop:0 #ffc107, stop:1 #e0a800);\n"
"    color: white;\n"
"    border: 2px solid #d39e00;\n"
"    font-size: 17px; /* Increased by 2 */\n"
"}"));

        horizontalLayout_control1->addWidget(btnLamp1);

        btnFan1 = new QPushButton(groupBox_control1);
        btnFan1->setObjectName(QString::fromUtf8("btnFan1"));
        btnFan1->setMinimumSize(QSize(180, 94));
        btnFan1->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"                                stop:0 #17a2b8, stop:1 #138496);\n"
"    color: white;\n"
"    border: 2px solid #117a8b;\n"
"    font-size: 17px; /* Increased by 2 */\n"
"}"));

        horizontalLayout_control1->addWidget(btnFan1);

        btnBuzzer1 = new QPushButton(groupBox_control1);
        btnBuzzer1->setObjectName(QString::fromUtf8("btnBuzzer1"));
        btnBuzzer1->setMinimumSize(QSize(180, 94));
        btnBuzzer1->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"                                stop:0 #dc3545, stop:1 #c82333);\n"
"    color: white;\n"
"    border: 2px solid #bd2130;\n"
"    font-size: 17px; /* Increased by 2 */\n"
"}"));

        horizontalLayout_control1->addWidget(btnBuzzer1);

        btnAutoMode1 = new QPushButton(groupBox_control1);
        btnAutoMode1->setObjectName(QString::fromUtf8("btnAutoMode1"));
        btnAutoMode1->setMinimumSize(QSize(200, 94));
        btnAutoMode1->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"                                stop:0 #28a745, stop:1 #218838);\n"
"    color: white;\n"
"    border: 2px solid #1e7e34;\n"
"    font-size: 17px; /* Increased by 2 */\n"
"}"));

        horizontalLayout_control1->addWidget(btnAutoMode1);

        horizontalSpacer_right1 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_control1->addItem(horizontalSpacer_right1);


        verticalLayout_2->addWidget(groupBox_control1);

        groupBox_threshold1 = new QGroupBox(tab_warehouse1);
        groupBox_threshold1->setObjectName(QString::fromUtf8("groupBox_threshold1"));
        gridLayout_threshold1 = new QGridLayout(groupBox_threshold1);
        gridLayout_threshold1->setObjectName(QString::fromUtf8("gridLayout_threshold1"));
        gridLayout_threshold1->setHorizontalSpacing(15);
        gridLayout_threshold1->setVerticalSpacing(10);
        editLightMin1 = new QLineEdit(groupBox_threshold1);
        editLightMin1->setObjectName(QString::fromUtf8("editLightMin1"));
        editLightMin1->setMaximumSize(QSize(100, 16777215));
        editLightMin1->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    padding: 8px;\n"
"    border: 2px solid #ced4da;\n"
"    border-radius: 6px;\n"
"    font-size: 16px; /* Increased by 2 */\n"
"    margin: 4px;\n"
"}"));

        gridLayout_threshold1->addWidget(editLightMin1, 1, 3, 1, 1);

        label_4 = new QLabel(groupBox_threshold1);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    font-size: 17px; /* Increased by 2 */\n"
"    padding: 10px 12px;\n"
"    border-radius: 6px;\n"
"    margin: 4px;\n"
"    font-weight: bold;\n"
"    background: transparent;\n"
"    color: #212529;\n"
"}"));

        gridLayout_threshold1->addWidget(label_4, 0, 2, 1, 1);

        label = new QLabel(groupBox_threshold1);
        label->setObjectName(QString::fromUtf8("label"));
        label->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    font-size: 17px; /* Increased by 2 */\n"
"    padding: 10px 12px;\n"
"    border-radius: 6px;\n"
"    margin: 4px;\n"
"    font-weight: bold;\n"
"    background: transparent;\n"
"    color: #212529;\n"
"}"));

        gridLayout_threshold1->addWidget(label, 0, 0, 1, 1);

        editLightMax1 = new QLineEdit(groupBox_threshold1);
        editLightMax1->setObjectName(QString::fromUtf8("editLightMax1"));
        editLightMax1->setMaximumSize(QSize(100, 16777215));
        editLightMax1->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    padding: 8px;\n"
"    border: 2px solid #ced4da;\n"
"    border-radius: 6px;\n"
"    font-size: 16px; /* Increased by 2 */\n"
"    margin: 4px;\n"
"}"));

        gridLayout_threshold1->addWidget(editLightMax1, 1, 1, 1, 1);

        editHumidityMax1 = new QLineEdit(groupBox_threshold1);
        editHumidityMax1->setObjectName(QString::fromUtf8("editHumidityMax1"));
        editHumidityMax1->setMaximumSize(QSize(100, 16777215));
        editHumidityMax1->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    padding: 8px;\n"
"    border: 2px solid #ced4da;\n"
"    border-radius: 6px;\n"
"    font-size: 16px; /* Increased by 2 */\n"
"    margin: 4px;\n"
"}"));

        gridLayout_threshold1->addWidget(editHumidityMax1, 0, 1, 1, 1);

        label_6 = new QLabel(groupBox_threshold1);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    font-size: 17px; /* Increased by 2 */\n"
"    padding: 10px 12px;\n"
"    border-radius: 6px;\n"
"    margin: 4px;\n"
"    font-weight: bold;\n"
"    background: transparent;\n"
"    color: #212529;\n"
"}"));

        gridLayout_threshold1->addWidget(label_6, 1, 2, 1, 1);

        editHumidityMin1 = new QLineEdit(groupBox_threshold1);
        editHumidityMin1->setObjectName(QString::fromUtf8("editHumidityMin1"));
        editHumidityMin1->setMaximumSize(QSize(100, 16777215));
        editHumidityMin1->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    padding: 8px;\n"
"    border: 2px solid #ced4da;\n"
"    border-radius: 6px;\n"
"    font-size: 16px; /* Increased by 2 */\n"
"    margin: 4px;\n"
"}"));

        gridLayout_threshold1->addWidget(editHumidityMin1, 0, 3, 1, 1);

        label_5 = new QLabel(groupBox_threshold1);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    font-size: 17px; /* Increased by 2 */\n"
"    padding: 10px 12px;\n"
"    border-radius: 6px;\n"
"    margin: 4px;\n"
"    font-weight: bold;\n"
"    background: transparent;\n"
"    color: #212529;\n"
"}"));

        gridLayout_threshold1->addWidget(label_5, 1, 0, 1, 1);


        verticalLayout_2->addWidget(groupBox_threshold1);

        groupBox_status1 = new QGroupBox(tab_warehouse1);
        groupBox_status1->setObjectName(QString::fromUtf8("groupBox_status1"));
        gridLayout_status1 = new QGridLayout(groupBox_status1);
        gridLayout_status1->setObjectName(QString::fromUtf8("gridLayout_status1"));
        gridLayout_status1->setHorizontalSpacing(20);
        gridLayout_status1->setVerticalSpacing(15);
        labelTemp1 = new QLabel(groupBox_status1);
        labelTemp1->setObjectName(QString::fromUtf8("labelTemp1"));
        labelTemp1->setMinimumSize(QSize(200, 45));
        labelTemp1->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"                                stop:0 #dc3545, stop:1 #c82333);\n"
"    color: white;\n"
"    border-left: 5px solid #bd2130;\n"
"    font-size: 17px; /* Increased by 2 */\n"
"}"));

        gridLayout_status1->addWidget(labelTemp1, 0, 0, 1, 1);

        labelHumidity1 = new QLabel(groupBox_status1);
        labelHumidity1->setObjectName(QString::fromUtf8("labelHumidity1"));
        labelHumidity1->setMinimumSize(QSize(200, 45));
        labelHumidity1->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"                                stop:0 #007bff, stop:1 #0069d9);\n"
"    color: white;\n"
"    border-left: 5px solid #0056b3;\n"
"    font-size: 17px; /* Increased by 2 */\n"
"}"));

        gridLayout_status1->addWidget(labelHumidity1, 0, 1, 1, 1);

        labelLight1 = new QLabel(groupBox_status1);
        labelLight1->setObjectName(QString::fromUtf8("labelLight1"));
        labelLight1->setMinimumSize(QSize(200, 45));
        labelLight1->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"                                stop:0 #ffc107, stop:1 #e0a800);\n"
"    color: white;\n"
"    border-left: 5px solid #d39e00;\n"
"    font-size: 17px; /* Increased by 2 */\n"
"}"));

        gridLayout_status1->addWidget(labelLight1, 1, 0, 1, 1);

        labelConnect1 = new QLabel(groupBox_status1);
        labelConnect1->setObjectName(QString::fromUtf8("labelConnect1"));
        labelConnect1->setMinimumSize(QSize(200, 45));
        labelConnect1->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"                                stop:0 #28a745, stop:1 #218838);\n"
"    color: white;\n"
"    border-left: 5px solid #1e7e34;\n"
"    font-size: 17px; /* Increased by 2 */\n"
"}"));

        gridLayout_status1->addWidget(labelConnect1, 1, 1, 1, 1);


        verticalLayout_2->addWidget(groupBox_status1);

        verticalSpacer_1 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_1);

        tabWidget->addTab(tab_warehouse1, QString());
        tab_warehouse2 = new QWidget();
        tab_warehouse2->setObjectName(QString::fromUtf8("tab_warehouse2"));
        verticalLayout_3 = new QVBoxLayout(tab_warehouse2);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        groupBox_control2 = new QGroupBox(tab_warehouse2);
        groupBox_control2->setObjectName(QString::fromUtf8("groupBox_control2"));
        gridLayout_control2 = new QGridLayout(groupBox_control2);
        gridLayout_control2->setObjectName(QString::fromUtf8("gridLayout_control2"));
        gridLayout_control2->setHorizontalSpacing(20);
        gridLayout_control2->setVerticalSpacing(15);
        btnLamp2 = new QPushButton(groupBox_control2);
        btnLamp2->setObjectName(QString::fromUtf8("btnLamp2"));
        btnLamp2->setMinimumSize(QSize(150, 94));
        btnLamp2->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"                                stop:0 #ffc107, stop:1 #e0a800);\n"
"    color: white;\n"
"    border: 2px solid #d39e00;\n"
"    font-size: 17px; /* Increased by 2 */\n"
"}"));

        gridLayout_control2->addWidget(btnLamp2, 0, 0, 1, 1);

        btnFan2 = new QPushButton(groupBox_control2);
        btnFan2->setObjectName(QString::fromUtf8("btnFan2"));
        btnFan2->setMinimumSize(QSize(150, 94));
        btnFan2->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"                                stop:0 #17a2b8, stop:1 #138496);\n"
"    color: white;\n"
"    border: 2px solid #117a8b;\n"
"    font-size: 17px; /* Increased by 2 */\n"
"}"));

        gridLayout_control2->addWidget(btnFan2, 0, 1, 1, 1);

        btnAutoMode2 = new QPushButton(groupBox_control2);
        btnAutoMode2->setObjectName(QString::fromUtf8("btnAutoMode2"));
        btnAutoMode2->setMinimumSize(QSize(150, 94));
        btnAutoMode2->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"                                stop:0 #28a745, stop:1 #218838);\n"
"    color: white;\n"
"    border: 2px solid #1e7e34;\n"
"    font-size: 17px; /* Increased by 2 */\n"
"}"));

        gridLayout_control2->addWidget(btnAutoMode2, 0, 2, 1, 1);

        btnMotor2 = new QPushButton(groupBox_control2);
        btnMotor2->setObjectName(QString::fromUtf8("btnMotor2"));
        btnMotor2->setMinimumSize(QSize(150, 94));
        btnMotor2->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"                                stop:0 #6c757d, stop:1 #5a6268);\n"
"    color: white;\n"
"    border: 2px solid #545b62;\n"
"    font-size: 17px; /* Increased by 2 */\n"
"}"));

        gridLayout_control2->addWidget(btnMotor2, 1, 0, 1, 1);

        btnBuzzer2 = new QPushButton(groupBox_control2);
        btnBuzzer2->setObjectName(QString::fromUtf8("btnBuzzer2"));
        btnBuzzer2->setMinimumSize(QSize(150, 94));
        btnBuzzer2->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"                                stop:0 #dc3545, stop:1 #c82333);\n"
"    color: white;\n"
"    border: 2px solid #bd2130;\n"
"    font-size: 17px; /* Increased by 2 */\n"
"}"));

        gridLayout_control2->addWidget(btnBuzzer2, 1, 1, 1, 1);


        verticalLayout_3->addWidget(groupBox_control2);

        groupBox_threshold2 = new QGroupBox(tab_warehouse2);
        groupBox_threshold2->setObjectName(QString::fromUtf8("groupBox_threshold2"));
        gridLayout_threshold2 = new QGridLayout(groupBox_threshold2);
        gridLayout_threshold2->setObjectName(QString::fromUtf8("gridLayout_threshold2"));
        gridLayout_threshold2->setHorizontalSpacing(15);
        gridLayout_threshold2->setVerticalSpacing(10);
        label_10 = new QLabel(groupBox_threshold2);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    font-size: 17px; /* Increased by 2 */\n"
"    padding: 10px 12px;\n"
"    border-radius: 6px;\n"
"    margin: 4px;\n"
"    font-weight: bold;\n"
"    background: transparent;\n"
"    color: #212529;\n"
"}"));

        gridLayout_threshold2->addWidget(label_10, 0, 0, 1, 1);

        editHumidityMax2 = new QLineEdit(groupBox_threshold2);
        editHumidityMax2->setObjectName(QString::fromUtf8("editHumidityMax2"));
        editHumidityMax2->setMaximumSize(QSize(100, 16777215));
        editHumidityMax2->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    padding: 8px;\n"
"    border: 2px solid #ced4da;\n"
"    border-radius: 6px;\n"
"    font-size: 16px; /* Increased by 2 */\n"
"    margin: 4px;\n"
"}"));

        gridLayout_threshold2->addWidget(editHumidityMax2, 0, 1, 1, 1);

        label_11 = new QLabel(groupBox_threshold2);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    font-size: 17px; /* Increased by 2 */\n"
"    padding: 10px 12px;\n"
"    border-radius: 6px;\n"
"    margin: 4px;\n"
"    font-weight: bold;\n"
"    background: transparent;\n"
"    color: #212529;\n"
"}"));

        gridLayout_threshold2->addWidget(label_11, 0, 2, 1, 1);

        editHumidityMin2 = new QLineEdit(groupBox_threshold2);
        editHumidityMin2->setObjectName(QString::fromUtf8("editHumidityMin2"));
        editHumidityMin2->setMaximumSize(QSize(100, 16777215));
        editHumidityMin2->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    padding: 8px;\n"
"    border: 2px solid #ced4da;\n"
"    border-radius: 6px;\n"
"    font-size: 16px; /* Increased by 2 */\n"
"    margin: 4px;\n"
"}"));

        gridLayout_threshold2->addWidget(editHumidityMin2, 0, 3, 1, 1);

        label_9 = new QLabel(groupBox_threshold2);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    font-size: 17px; /* Increased by 2 */\n"
"    padding: 10px 12px;\n"
"    border-radius: 6px;\n"
"    margin: 4px;\n"
"    font-weight: bold;\n"
"    background: transparent;\n"
"    color: #212529;\n"
"}"));

        gridLayout_threshold2->addWidget(label_9, 0, 4, 1, 1);

        editCO2Max2 = new QLineEdit(groupBox_threshold2);
        editCO2Max2->setObjectName(QString::fromUtf8("editCO2Max2"));
        editCO2Max2->setMaximumSize(QSize(100, 16777215));
        editCO2Max2->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    padding: 8px;\n"
"    border: 2px solid #ced4da;\n"
"    border-radius: 6px;\n"
"    font-size: 16px; /* Increased by 2 */\n"
"    margin: 4px;\n"
"}"));

        gridLayout_threshold2->addWidget(editCO2Max2, 0, 5, 1, 1);

        label_12 = new QLabel(groupBox_threshold2);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    font-size: 17px; /* Increased by 2 */\n"
"    padding: 10px 12px;\n"
"    border-radius: 6px;\n"
"    margin: 4px;\n"
"    font-weight: bold;\n"
"    background: transparent;\n"
"    color: #212529;\n"
"}"));

        gridLayout_threshold2->addWidget(label_12, 1, 4, 1, 1);

        editCO2Min2 = new QLineEdit(groupBox_threshold2);
        editCO2Min2->setObjectName(QString::fromUtf8("editCO2Min2"));
        editCO2Min2->setMaximumSize(QSize(100, 16777215));
        editCO2Min2->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    padding: 8px;\n"
"    border: 2px solid #ced4da;\n"
"    border-radius: 6px;\n"
"    font-size: 16px; /* Increased by 2 */\n"
"    margin: 4px;\n"
"}"));

        gridLayout_threshold2->addWidget(editCO2Min2, 1, 5, 1, 1);

        label_13 = new QLabel(groupBox_threshold2);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    font-size: 17px; /* Increased by 2 */\n"
"    padding: 10px 12px;\n"
"    border-radius: 6px;\n"
"    margin: 4px;\n"
"    font-weight: bold;\n"
"    background: transparent;\n"
"    color: #212529;\n"
"}"));

        gridLayout_threshold2->addWidget(label_13, 1, 0, 1, 1);

        editLightMax2 = new QLineEdit(groupBox_threshold2);
        editLightMax2->setObjectName(QString::fromUtf8("editLightMax2"));
        editLightMax2->setMaximumSize(QSize(100, 16777215));
        editLightMax2->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    padding: 8px;\n"
"    border: 2px solid #ced4da;\n"
"    border-radius: 6px;\n"
"    font-size: 16px; /* Increased by 2 */\n"
"    margin: 4px;\n"
"}"));

        gridLayout_threshold2->addWidget(editLightMax2, 1, 1, 1, 1);

        label_14 = new QLabel(groupBox_threshold2);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    font-size: 17px; /* Increased by 2 */\n"
"    padding: 10px 12px;\n"
"    border-radius: 6px;\n"
"    margin: 4px;\n"
"    font-weight: bold;\n"
"    background: transparent;\n"
"    color: #212529;\n"
"}"));

        gridLayout_threshold2->addWidget(label_14, 1, 2, 1, 1);

        editLightMin2 = new QLineEdit(groupBox_threshold2);
        editLightMin2->setObjectName(QString::fromUtf8("editLightMin2"));
        editLightMin2->setMaximumSize(QSize(100, 16777215));
        editLightMin2->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    padding: 8px;\n"
"    border: 2px solid #ced4da;\n"
"    border-radius: 6px;\n"
"    font-size: 16px; /* Increased by 2 */\n"
"    margin: 4px;\n"
"}"));

        gridLayout_threshold2->addWidget(editLightMin2, 1, 3, 1, 1);


        verticalLayout_3->addWidget(groupBox_threshold2);

        groupBox_status2 = new QGroupBox(tab_warehouse2);
        groupBox_status2->setObjectName(QString::fromUtf8("groupBox_status2"));
        gridLayout_status2 = new QGridLayout(groupBox_status2);
        gridLayout_status2->setObjectName(QString::fromUtf8("gridLayout_status2"));
        gridLayout_status2->setHorizontalSpacing(20);
        gridLayout_status2->setVerticalSpacing(15);
        labelTemp2 = new QLabel(groupBox_status2);
        labelTemp2->setObjectName(QString::fromUtf8("labelTemp2"));
        labelTemp2->setMinimumSize(QSize(180, 45));
        labelTemp2->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"                                stop:0 #dc3545, stop:1 #c82333);\n"
"    color: white;\n"
"    border-left: 5px solid #bd2130;\n"
"    font-size: 17px; /* Increased by 2 */\n"
"}"));

        gridLayout_status2->addWidget(labelTemp2, 0, 0, 1, 1);

        labelHumidity2 = new QLabel(groupBox_status2);
        labelHumidity2->setObjectName(QString::fromUtf8("labelHumidity2"));
        labelHumidity2->setMinimumSize(QSize(180, 45));
        labelHumidity2->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"                                stop:0 #007bff, stop:1 #0069d9);\n"
"    color: white;\n"
"    border-left: 5px solid #0056b3;\n"
"    font-size: 17px; /* Increased by 2 */\n"
"}"));

        gridLayout_status2->addWidget(labelHumidity2, 0, 1, 1, 1);

        labelCO2_2 = new QLabel(groupBox_status2);
        labelCO2_2->setObjectName(QString::fromUtf8("labelCO2_2"));
        labelCO2_2->setMinimumSize(QSize(180, 45));
        labelCO2_2->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"                                stop:0 #28a745, stop:1 #218838);\n"
"    color: white;\n"
"    border-left: 5px solid #1e7e34;\n"
"    font-size: 17px; /* Increased by 2 */\n"
"}"));

        gridLayout_status2->addWidget(labelCO2_2, 0, 2, 1, 1);

        labelLight2 = new QLabel(groupBox_status2);
        labelLight2->setObjectName(QString::fromUtf8("labelLight2"));
        labelLight2->setMinimumSize(QSize(180, 45));
        labelLight2->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"                                stop:0 #ffc107, stop:1 #e0a800);\n"
"    color: white;\n"
"    border-left: 5px solid #d39e00;\n"
"    font-size: 17px; /* Increased by 2 */\n"
"}"));

        gridLayout_status2->addWidget(labelLight2, 1, 0, 1, 1);

        labelTTL2 = new QLabel(groupBox_status2);
        labelTTL2->setObjectName(QString::fromUtf8("labelTTL2"));
        labelTTL2->setMinimumSize(QSize(180, 45));
        labelTTL2->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"                                stop:0 #6f42c1, stop:1 #5a3d9c);\n"
"    color: white;\n"
"    border-left: 5px solid #4a2f7a;\n"
"    font-size: 17px; /* Increased by 2 */\n"
"}"));

        gridLayout_status2->addWidget(labelTTL2, 1, 1, 1, 1);

        labelConnect2 = new QLabel(groupBox_status2);
        labelConnect2->setObjectName(QString::fromUtf8("labelConnect2"));
        labelConnect2->setMinimumSize(QSize(180, 45));
        labelConnect2->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"                                stop:0 #28a745, stop:1 #218838);\n"
"    color: white;\n"
"    border-left: 5px solid #1e7e34;\n"
"    font-size: 17px; /* Increased by 2 */\n"
"}"));

        gridLayout_status2->addWidget(labelConnect2, 1, 2, 1, 1);


        verticalLayout_3->addWidget(groupBox_status2);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_2);

        tabWidget->addTab(tab_warehouse2, QString());

        verticalLayout->addWidget(tabWidget);

        statusBar = new QStatusBar(Widget);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));

        verticalLayout->addWidget(statusBar);


        retranslateUi(Widget);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Smart Warehouse Monitoring System", nullptr));
        label_title->setText(QCoreApplication::translate("Widget", "<html><head/><body><p align=\"center\"><span style=\" font-size:24pt; font-weight:700; color:#007bff;\">\360\237\217\255 Smart Warehouse Monitoring System</span></p></body></html>", nullptr));
        groupBox_control1->setTitle(QCoreApplication::translate("Widget", "Device Control", nullptr));
        btnLamp1->setText(QCoreApplication::translate("Widget", "\360\237\222\241 Light: OFF", nullptr));
        btnFan1->setText(QCoreApplication::translate("Widget", "\360\237\214\200 Fan: OFF", nullptr));
        btnBuzzer1->setText(QCoreApplication::translate("Widget", "\360\237\224\224 Buzzer: OFF", nullptr));
        btnAutoMode1->setText(QCoreApplication::translate("Widget", "\360\237\244\226 Auto Mode: Off", nullptr));
        groupBox_threshold1->setTitle(QCoreApplication::translate("Widget", "Threshold Settings", nullptr));
        editLightMin1->setText(QCoreApplication::translate("Widget", "100", nullptr));
        label_4->setText(QCoreApplication::translate("Widget", "Humidity Min (%):", nullptr));
        label->setText(QCoreApplication::translate("Widget", "\360\237\222\247 Humidity Max (%):", nullptr));
        editLightMax1->setText(QCoreApplication::translate("Widget", "800", nullptr));
        editHumidityMax1->setText(QCoreApplication::translate("Widget", "70", nullptr));
        label_6->setText(QCoreApplication::translate("Widget", "Light Min (lux):", nullptr));
        editHumidityMin1->setText(QCoreApplication::translate("Widget", "40", nullptr));
        label_5->setText(QCoreApplication::translate("Widget", "\342\230\200\357\270\217 Light Max (lux):", nullptr));
        groupBox_status1->setTitle(QCoreApplication::translate("Widget", "Environmental Data", nullptr));
        labelTemp1->setText(QCoreApplication::translate("Widget", "\360\237\214\241\357\270\217 Temperature: --\302\260C", nullptr));
        labelHumidity1->setText(QCoreApplication::translate("Widget", "\360\237\222\247 Humidity: --%", nullptr));
        labelLight1->setText(QCoreApplication::translate("Widget", "\342\230\200\357\270\217 Light: -- lux", nullptr));
        labelConnect1->setText(QCoreApplication::translate("Widget", "\360\237\223\241 Connection: Online", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_warehouse1), QCoreApplication::translate("Widget", "\360\237\217\240 Warehouse 1", nullptr));
        groupBox_control2->setTitle(QCoreApplication::translate("Widget", "Device Control", nullptr));
        btnLamp2->setText(QCoreApplication::translate("Widget", "\360\237\222\241 Light: OFF", nullptr));
        btnFan2->setText(QCoreApplication::translate("Widget", "\360\237\214\200 Fan: OFF", nullptr));
        btnAutoMode2->setText(QCoreApplication::translate("Widget", "\360\237\244\226 Auto Mode: Off", nullptr));
        btnMotor2->setText(QCoreApplication::translate("Widget", "\342\232\231\357\270\217 Motor: OFF", nullptr));
        btnBuzzer2->setText(QCoreApplication::translate("Widget", "\360\237\224\224 Buzzer: OFF", nullptr));
        groupBox_threshold2->setTitle(QCoreApplication::translate("Widget", "Threshold Settings", nullptr));
        label_10->setText(QCoreApplication::translate("Widget", "\360\237\222\247 Humidity Max (%):", nullptr));
        editHumidityMax2->setText(QCoreApplication::translate("Widget", "70", nullptr));
        label_11->setText(QCoreApplication::translate("Widget", "Humidity Min (%):", nullptr));
        editHumidityMin2->setText(QCoreApplication::translate("Widget", "40", nullptr));
        label_9->setText(QCoreApplication::translate("Widget", "\360\237\214\253\357\270\217 CO\342\202\202 Max (ppm):", nullptr));
        editCO2Max2->setText(QCoreApplication::translate("Widget", "1000", nullptr));
        label_12->setText(QCoreApplication::translate("Widget", "CO\342\202\202 Min (ppm):", nullptr));
        editCO2Min2->setText(QCoreApplication::translate("Widget", "800", nullptr));
        label_13->setText(QCoreApplication::translate("Widget", "\342\230\200\357\270\217 Light Max (lux):", nullptr));
        editLightMax2->setText(QCoreApplication::translate("Widget", "800", nullptr));
        label_14->setText(QCoreApplication::translate("Widget", "Light Min (lux):", nullptr));
        editLightMin2->setText(QCoreApplication::translate("Widget", "100", nullptr));
        groupBox_status2->setTitle(QCoreApplication::translate("Widget", "Environmental Data", nullptr));
        labelTemp2->setText(QCoreApplication::translate("Widget", "\360\237\214\241\357\270\217 Temperature: 17\302\260C", nullptr));
        labelHumidity2->setText(QCoreApplication::translate("Widget", "\360\237\222\247 Humidity: 69%", nullptr));
        labelCO2_2->setText(QCoreApplication::translate("Widget", "\360\237\214\253\357\270\217 CO\342\202\202: 524 ppm", nullptr));
        labelLight2->setText(QCoreApplication::translate("Widget", "\342\230\200\357\270\217 Light: 572 lux", nullptr));
        labelTTL2->setText(QCoreApplication::translate("Widget", "\342\232\241 Dangerous Goods: ON", nullptr));
        labelConnect2->setText(QCoreApplication::translate("Widget", "\360\237\223\241 Connection: Online", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_warehouse2), QCoreApplication::translate("Widget", "\360\237\217\242 Warehouse 2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
