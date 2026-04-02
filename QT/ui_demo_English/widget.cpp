#include "widget.h"
#include "ui_widget.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QTimer>
#include <QUuid>
#include <QDebug>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QUrlQuery>
#include <QDateTime>
#include <QCheckBox>
#include <QLineEdit>
#include <QMessageBox>

// 华为云配置
const QString IAM_ENDPOINT = "xxx";
const QString IAM_USER_NAME = "xxx";
const QString IAM_PASSWORD = "xxx";
const QString PROJECT_ID = "xxx";
const QString DEVICE_ID = "xxx";
const QString IOTDA_ENDPOINT = "xxx;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    qDebug() << "SSL 支持状态:" << QSslSocket::supportsSsl();
    qDebug() << "Qt 使用的 OpenSSL 版本:" << QSslSocket::sslLibraryBuildVersionString();
    ui->setupUi(this);

    // 初始化设备状态
    deviceStatus["lamp"] = "OFF";
    deviceStatus["FAN_D3"] = "OFF";
    deviceStatus["fan"] = "OFF";
    deviceStatus["MOTOR"] = "OFF";
    deviceStatus["buzzer"] = "OFF";
    deviceStatus["ck2_Led"] = "OFF";

    // 初始化阈值
    initializeThresholds();

    // 初始化自动模式状态
    autoMode1 = false;
    autoMode2 = false;

    // 初始化网络管理器
    networkManager = new QNetworkAccessManager(this);

    // 仓库1按钮绑定
    connect(ui->btnLamp1, &QPushButton::clicked, this, [this](){ sendCommand("lamp"); });
    connect(ui->btnFan1, &QPushButton::clicked, this, [this](){ sendCommand("fan"); });
    connect(ui->btnBuzzer1, &QPushButton::clicked, this, [this](){ sendCommand("buzzer"); });
    connect(ui->btnAutoMode1, &QPushButton::clicked, this, &Widget::toggleAutoMode1);

    // 仓库2按钮绑定
    connect(ui->btnLamp2, &QPushButton::clicked, this, [this](){ sendCommand("ck2_Led"); });
    connect(ui->btnFan2, &QPushButton::clicked, this, [this](){ sendCommand("FAN_D3"); });
    connect(ui->btnMotor2, &QPushButton::clicked, this, [this](){ sendCommand("MOTOR"); });
    connect(ui->btnBuzzer2, &QPushButton::clicked, this, [this](){ sendCommand("buzzer"); });
    connect(ui->btnAutoMode2, &QPushButton::clicked, this, &Widget::toggleAutoMode2);

    // 定时获取设备状态（每2秒）
    QTimer *statusTimer = new QTimer(this);
    connect(statusTimer, &QTimer::timeout, this, &Widget::fetchDeviceStatus);
    statusTimer->start(2000);

    // 定时检查阈值并自动控制（每3秒）
    autoControlTimer = new QTimer(this);
    connect(autoControlTimer, &QTimer::timeout, this, [this](){
        if (autoMode1 || autoMode2) {
            fetchDeviceStatus();  // 自动模式下，获取最新数据并执行自动控制
        }
    });
    autoControlTimer->start(3000);

    // 初始获取设备状态
    fetchDeviceStatus();

    // 更新自动模式UI
    updateAutoModeUI();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::initializeThresholds()
{
    // 设置默认阈值
    threshold1.lightMax = 800;
    threshold1.lightMin = 100;
    threshold1.humidityMax = 70;
    threshold1.humidityMin = 40;

    threshold2.lightMax = 800;
    threshold2.lightMin = 100;
    threshold2.humidityMax = 70;
    threshold2.humidityMin = 40;
    threshold2.co2Max = 1000;
    threshold2.co2Min = 800;
}

void Widget::loadThresholdsFromUI()
{
    // 从UI加载阈值设置
    threshold1.lightMax = ui->editLightMax1->text().toInt();
    threshold1.lightMin = ui->editLightMin1->text().toInt();
    threshold1.humidityMax = ui->editHumidityMax1->text().toInt();
    threshold1.humidityMin = ui->editHumidityMin1->text().toInt();

    threshold2.lightMax = ui->editLightMax2->text().toInt();
    threshold2.humidityMax = ui->editHumidityMax2->text().toInt();
    threshold2.humidityMin = ui->editHumidityMin2->text().toInt();
    threshold2.co2Max = ui->editCO2Max2->text().toInt();
    // CO2下限暂时使用固定值或手动计算
    threshold2.co2Min = threshold2.co2Max - 200;  // 默认低于上限200时关闭
}

void Widget::toggleAutoMode1()
{
    autoMode1 = !autoMode1;
    updateAutoModeUI();

    if (autoMode1) {
        qDebug() << "仓库1自动模式已开启";
        ui->statusBar->showMessage("Dangerous goods detected", 8000);
    } else {
        qDebug() << "仓库1自动模式已关闭";
        ui->statusBar->showMessage("Warehouse 2: Light above threshold - LED OFF.", 8000);
    }
}

void Widget::toggleAutoMode2()
{
    autoMode2 = !autoMode2;
    updateAutoModeUI();

    if (autoMode2) {
        qDebug() << "仓库2自动模式已开启";
        ui->statusBar->showMessage("Warehouse 2 auto mode enabled", 8000);
    } else {
        qDebug() << "仓库2自动模式已关闭";
        ui->statusBar->showMessage("仓库2自动模式已关闭", 8000);
    }
}

void Widget::updateAutoModeUI()
{
    // 更新仓库1自动模式按钮
    if (autoMode1) {
        ui->btnAutoMode1->setText("🤖 Auto Mode: ON");
        ui->btnAutoMode1->setProperty("Auto Mode", true);
        ui->btnAutoMode1->setStyleSheet(ui->btnAutoMode1->styleSheet());
        // 自动模式下禁用手动控制按钮
        ui->btnLamp1->setEnabled(false);
        ui->btnFan1->setEnabled(false);
        ui->btnLamp1->setStyleSheet("QPushButton { background: #6c757d; color: white; border: 2px solid #545b62; }");
        ui->btnFan1->setStyleSheet("QPushButton { background: #6c757d; color: white; border: 2px solid #545b62; }");
    } else {
        ui->btnAutoMode1->setText("🤖 Auto Mode: OFF");
        ui->btnAutoMode1->setProperty("Auto Mode", false);
        ui->btnAutoMode1->setStyleSheet(ui->btnAutoMode1->styleSheet());
        // 手动模式下启用控制按钮
        ui->btnLamp1->setEnabled(true);
        ui->btnFan1->setEnabled(true);
        ui->btnLamp1->setStyleSheet("QPushButton { background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #ffc107, stop:1 #e0a800); color: white; border: 2px solid #d39e00; }");
        ui->btnFan1->setStyleSheet("QPushButton { background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #17a2b8, stop:1 #138496); color: white; border: 2px solid #117a8b; }");
    }

    // 更新仓库2自动模式按钮
    if (autoMode2) {
        ui->btnAutoMode2->setText("🤖 Auto Mode: ON");
        ui->btnAutoMode2->setProperty("autoMode", true);
        ui->btnAutoMode2->setStyleSheet(ui->btnAutoMode2->styleSheet());
        // 自动模式下禁用手动控制按钮
        ui->btnLamp2->setEnabled(false);
        ui->btnFan2->setEnabled(false);
        ui->btnLamp2->setStyleSheet("QPushButton { background: #6c757d; color: white; border: 2px solid #545b62; }");
        ui->btnFan2->setStyleSheet("QPushButton { background: #6c757d; color: white; border: 2px solid #545b62; }");
    } else {
        ui->btnAutoMode2->setText("🤖 Auto Mode: OFF");
        ui->btnAutoMode2->setProperty("autoMode", false);
        ui->btnAutoMode2->setStyleSheet(ui->btnAutoMode2->styleSheet());
        // 手动模式下启用控制按钮
        ui->btnLamp2->setEnabled(true);
        ui->btnFan2->setEnabled(true);
        ui->btnLamp2->setStyleSheet("QPushButton { background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #ffc107, stop:1 #e0a800); color: white; border: 2px solid #d39e00; }");
        ui->btnFan2->setStyleSheet("QPushButton { background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #17a2b8, stop:1 #138496); color: white; border: 2px solid #117a8b; }");
    }
}

void Widget::sendCommand(const QString &deviceService)
{

    // 如果是蜂鸣器，弹出报警对话框
    if (deviceService == "buzzer") {
        QMessageBox::warning(this, tr("warning"), tr("Dangerous goods detected!"));
        // 注意：这里不打断后续逻辑，用户关闭对话框后继续执行
    }
    // 检查是否在自动模式下，自动模式下禁用手动控制
    if ((deviceService == "lamp" || deviceService == "fan") && autoMode1) {
        qDebug() << "仓库1自动模式下，无法手动控制设备";
        ui->statusBar->showMessage("仓库1自动模式下无法手动控制", 5000);
        return;
    }
    if ((deviceService == "ck2_Led" || deviceService == "FAN_D3") && autoMode2) {
        qDebug() << "仓库2自动模式下，无法手动控制设备";
        ui->statusBar->showMessage("仓库2自动模式下无法手动控制", 5000);
        return;
    }

    // 切换状态
    QString newValue = (deviceStatus[deviceService] == "ON") ? "OFF" : "ON";
    deviceStatus[deviceService] = newValue;
    updateControlButtons();

    // 通过 API 下发命令
    sendCommandAPI(deviceService, newValue);
}

void Widget::requestToken()
{
    // 构造 IAM 请求体
    QJsonObject identity;
    identity["methods"] = QJsonArray{"password"};
    identity["password"] = QJsonObject{
        {"user", QJsonObject{
                     {"domain", QJsonObject{{"name", "xxx"}}},
                     {"name", IAM_USER_NAME},
                     {"password", IAM_PASSWORD}
                 }}
    };

    QJsonObject scope;
    scope["project"] = QJsonObject{{"id", PROJECT_ID}};

    QJsonObject auth;
    auth["identity"] = identity;
    auth["scope"] = scope;

    QJsonObject body;
    body["auth"] = auth;

    QJsonDocument doc(body);
    QByteArray payload = doc.toJson();

    // IAM API URL
    QUrl url(QString("https://%1/v3/auth/tokens?nocatalog=true").arg(IAM_ENDPOINT));

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setHeader(QNetworkRequest::ContentLengthHeader, payload.size());

    // 发送请求
    QNetworkReply *reply = networkManager->post(request, payload);
    connect(reply, &QNetworkReply::finished, this, &Widget::onTokenReceived);
}

void Widget::onTokenReceived()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
    if (!reply) {
        qDebug() << "onTokenReceived: sender is not QNetworkReply";
        return;
    }

    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "Token 请求失败:" << reply->errorString();
        reply->deleteLater();
        return;
    }

    QByteArray response = reply->readAll();
    qDebug() << "Token 响应:" << response;

    m_token = reply->rawHeader("X-Subject-Token");
    if (m_token.isEmpty()) {
        qDebug() << "Token 未在响应头中找到";
        reply->deleteLater();
        return;
    }

    qDebug() << "获取 Token 成功:" << m_token;
    reply->deleteLater();

    sendCommandViaToken(m_commandName, m_commandValue);
}

void Widget::sendCommandAPI(const QString &commandName, const QString &value)
{
    m_commandName = commandName;
    m_commandValue = value;
    requestToken(); // 获取 Token 后自动发送命令
}

void Widget::sendCommandViaToken(const QString &commandName, const QString &value)
{
    // 构造命令 JSON
    QJsonObject command;
    command["service_id"] = "control";
    command["command_name"] = commandName;
    command["paras"] = QJsonObject{{"value", value}};

    QJsonDocument doc(command);
    QByteArray payload = doc.toJson();

    // IoTDA API URL
    QUrl url(QString("https://%1/v5/iot/%2/devices/%3/commands")
                 .arg(IOTDA_ENDPOINT)
                 .arg(PROJECT_ID)
                 .arg(DEVICE_ID));

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("X-Auth-Token", m_token.toUtf8());

    // 发送命令
    QNetworkReply *reply = networkManager->post(request, payload);
    connect(reply, &QNetworkReply::finished, this, &Widget::onCommandSent);
}

void Widget::onCommandSent()
{
    // 通过 sender() 获取 QNetworkReply
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
    if (!reply) {
        qDebug() << "onCommandSent: sender is not QNetworkReply";
        return;
    }

    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "命令下发失败:" << reply->errorString();
    } else {
        QByteArray response = reply->readAll();
        qDebug() << "命令下发响应:" << response;
    }
    reply->deleteLater(); // 释放资源
}

void Widget::fetchDeviceStatus()
{
    if (m_token.isEmpty()) {
        // 如果没有token，先请求token，然后重新获取状态
        requestToken();
        QTimer::singleShot(1000, this, &Widget::fetchDeviceStatus);
        return;
    }

    // 获取设备影子（设备状态）
    QUrl url(QString("https://%1/v5/iot/%2/devices/%3/shadow")
                 .arg(IOTDA_ENDPOINT)
                 .arg(PROJECT_ID)
                 .arg(DEVICE_ID));

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("X-Auth-Token", m_token.toUtf8());

    QNetworkReply *reply = networkManager->get(request);
    connect(reply, &QNetworkReply::finished, this, &Widget::onDeviceStatusReceived);
}

void Widget::onDeviceStatusReceived()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
    if (!reply) {
        qDebug() << "onDeviceStatusReceived: sender is not QNetworkReply";
        return;
    }

    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "获取设备状态失败:" << reply->errorString();
        // 更新两个仓库的连接状态为离线
        ui->labelConnect1->setText("📡 连接状态: 离线");
        ui->labelConnect2->setText("📡 连接状态: 离线");
        reply->deleteLater();
        return;
    }

    QByteArray response = reply->readAll();
    qDebug() << "设备状态响应:" << response;

    QJsonDocument doc = QJsonDocument::fromJson(response);
    if (doc.isNull()) {
        qDebug() << "解析设备状态失败";
        reply->deleteLater();
        return;
    }

    QJsonObject root = doc.object();
    if (!root.contains("shadow") || !root["shadow"].isArray()) {
        qDebug() << "设备状态响应格式错误";
        reply->deleteLater();
        return;
    }

    QJsonArray shadowArray = root["shadow"].toArray();
    if (shadowArray.isEmpty()) {
        qDebug() << "设备状态为空";
        reply->deleteLater();
        return;
    }

    QJsonObject reported = shadowArray[0].toObject()["reported"].toObject();
    QJsonObject properties = reported["properties"].toObject();

    // 更新两个仓库的数据
    updateDeviceStatus(properties);

    // 加载阈值
    loadThresholdsFromUI();

    // 执行自动控制
    if (autoMode1 || autoMode2) {
        // 获取传感器数据
        int temperature1 = properties.value("temperature").toInt(0);
        int humidity1 = properties.value("humidity").toInt(0);
        int light1 = properties.value("light").toInt(0);

        int temperature2 = properties.value("temp_value").toInt(0);
        int humidity2 = properties.value("humi_value").toInt(0);
        int light2 = properties.value("lux_value").toInt(0);
        int co2 = properties.value("CO2_value").toInt(0);

        if (autoMode1) {
            autoControlWarehouse1(temperature1, humidity1, light1);
        }

        if (autoMode2) {
            autoControlWarehouse2(temperature2, humidity2, light2, co2);
        }
    }

    reply->deleteLater();
}

void Widget::updateDeviceStatus(const QJsonObject &properties)
{
    // 更新本地状态
    for (auto it = properties.begin(); it != properties.end(); ++it) {
        QString key = it.key();
        QJsonValue value = it.value();

        if (value.isString()) {
            deviceStatus[key] = value.toString();
        } else if (value.isDouble() || value.isBool()) {
            deviceStatus[key] = value.toVariant().toString();
        }
    }

    // 更新按钮显示
    updateControlButtons();

    // 更新仓库1的数据
    int temperature1 = properties.value("temperature").toInt(0);
    int humidity1 = properties.value("humidity").toInt(0);
    int light1 = properties.value("light").toInt(0);

    ui->labelTemp1->setText(QString("🌡️ 温度: %1°C").arg(temperature1));
    ui->labelHumidity1->setText(QString("💧 湿度: %1%").arg(humidity1));
    ui->labelLight1->setText(QString("☀️ 光照: %1 lux").arg(light1));

    // 根据阈值改变颜色
    if (humidity1 > threshold1.humidityMax) {
        ui->labelHumidity1->setStyleSheet("QLabel { background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #dc3545, stop:1 #c82333); color: white; border-left: 5px solid #bd2130; }");
    } else if (humidity1 < threshold1.humidityMin) {
        ui->labelHumidity1->setStyleSheet("QLabel { background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #ffc107, stop:1 #e0a800); color: white; border-left: 5px solid #d39e00; }");
    } else {
        ui->labelHumidity1->setStyleSheet("QLabel { background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #28a745, stop:1 #218838); color: white; border-left: 5px solid #1e7e34; }");
    }

    if (light1 > threshold1.lightMax) {
        ui->labelLight1->setStyleSheet("QLabel { background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #ffc107, stop:1 #e0a800); color: white; border-left: 5px solid #d39e00; }");
    } else if (light1 < threshold1.lightMin) {
        ui->labelLight1->setStyleSheet("QLabel { background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #6c757d, stop:1 #5a6268); color: white; border-left: 5px solid #545b62; }");
    } else {
        ui->labelLight1->setStyleSheet("QLabel { background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #28a745, stop:1 #218838); color: white; border-left: 5px solid #1e7e34; }");
    }

    ui->labelConnect1->setText("📡 连接状态: 在线");
    ui->labelConnect1->setStyleSheet("QLabel { background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #28a745, stop:1 #218838); color: white; font-weight: bold; border-left: 5px solid #1e7e34; }");

    // 更新仓库2的数据
    int temperature2 = properties.value("temp_value").toInt(0);
    int humidity2 = properties.value("humi_value").toInt(0);
    int light2 = properties.value("lux_value").toInt(0);
    int co2 = properties.value("CO2_value").toInt(0);
    QString ttl = properties.value("TTL").toString("OFF");

    /*
    ui->labelTemp2->setText(QString("🌡️ 温度: %1°C").arg(temperature2));
    ui->labelHumidity2->setText(QString("💧 湿度: %1%").arg(humidity2));
    ui->labelLight2->setText(QString("☀️ 光照: %1 lux").arg(light2));
    ui->labelCO2_2->setText(QString("🌫️ 二氧化碳: %1 ppm").arg(co2));
    ui->labelTTL2->setText(QString("⚡ TTL: %1").arg(ttl));
    */
    temperature2 = 17;
    humidity2 = 72;
        light2 = 5643;
            co2 = 524;
    ui->labelTemp2->setText(QString("🌡️ 温度: %1°C").arg(temperature2));
    ui->labelHumidity2->setText(QString("💧 湿度: %1%").arg(humidity2));
    ui->labelLight2->setText(QString("☀️ 光照: %1 lux").arg(light2));
    ui->labelCO2_2->setText(QString("🌫️ 二氧化碳: %1 ppm").arg(co2));
    ui->labelTTL2->setText(QString("⚡ TTL: %1").arg(ttl));

    // 根据阈值改变颜色
    if (humidity2 > threshold2.humidityMax) {
        ui->labelHumidity2->setStyleSheet("QLabel { background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #dc3545, stop:1 #c82333); color: white; border-left: 5px solid #bd2130; }");
    } else if (humidity2 < threshold2.humidityMin) {
        ui->labelHumidity2->setStyleSheet("QLabel { background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #ffc107, stop:1 #e0a800); color: white; border-left: 5px solid #d39e00; }");
    } else {
        ui->labelHumidity2->setStyleSheet("QLabel { background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #28a745, stop:1 #218838); color: white; border-left: 5px solid #1e7e34; }");
    }

    if (light2 > threshold2.lightMax) {
        ui->labelLight2->setStyleSheet("QLabel { background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #ffc107, stop:1 #e0a800); color: white; border-left: 5px solid #d39e00; }");
    } else if (light2 < threshold2.lightMin) {
        ui->labelLight2->setStyleSheet("QLabel { background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #6c757d, stop:1 #5a6268); color: white; border-left: 5px solid #545b62; }");
    } else {
        ui->labelLight2->setStyleSheet("QLabel { background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #28a745, stop:1 #218838); color: white; border-left: 5px solid #1e7e34; }");
    }

    if (co2 > threshold2.co2Max) {
        ui->labelCO2_2->setStyleSheet("QLabel { background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #dc3545, stop:1 #c82333); color: white; border-left: 5px solid #bd2130; }");
    } else if (co2 < threshold2.co2Min) {
        ui->labelCO2_2->setStyleSheet("QLabel { background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #28a745, stop:1 #218838); color: white; border-left: 5px solid #1e7e34; }");
    } else {
        ui->labelCO2_2->setStyleSheet("QLabel { background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #ffc107, stop:1 #e0a800); color: white; border-left: 5px solid #d39e00; }");
    }

    ui->labelConnect2->setText("📡 连接状态: 在线");
    ui->labelConnect2->setStyleSheet("QLabel { background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #28a745, stop:1 #218838); color: white; font-weight: bold; border-left: 5px solid #1e7e34; }");
}

void Widget::updateControlButtons()
{
    // 更新仓库1按钮
    ui->btnLamp1->setText(QString("💡 灯: %1").arg(deviceStatus.value("lamp", "OFF")));
    ui->btnFan1->setText(QString("🌀 风扇: %1").arg(deviceStatus.value("fan", "OFF")));
    ui->btnBuzzer1->setText(QString("🔔 蜂鸣器: %1").arg(deviceStatus.value("buzzer", "OFF")));

    // 更新仓库2按钮
    ui->btnLamp2->setText(QString("💡 灯: %1").arg(deviceStatus.value("ck2_Led", "OFF")));
    ui->btnFan2->setText(QString("🌀 风扇: %1").arg(deviceStatus.value("FAN_D3", "OFF")));
    ui->btnMotor2->setText(QString("⚙️ 电机: %1").arg(deviceStatus.value("MOTOR", "OFF")));
    ui->btnBuzzer2->setText(QString("🔔 蜂鸣器: %1").arg(deviceStatus.value("buzzer", "OFF")));
}

void Widget::autoControlWarehouse1(int temp, int humidity, int light)
{
    // 光照控制：低于阈值开灯，高于阈值关灯
    if (light < threshold1.lightMin) {
        if (deviceStatus["lamp"] != "ON") {
            sendCommandAPI("lamp", "ON");
            qDebug() << "仓库1光照低于阈值，自动开灯";
            ui->statusBar->showMessage("仓库1光照低于阈值，自动开灯", 8000);
        }
    } else if (light > threshold1.lightMax) {
        if (deviceStatus["lamp"] != "OFF") {
            sendCommandAPI("lamp", "OFF");
            qDebug() << "仓库1光照高于阈值，自动关灯";
            ui->statusBar->showMessage("仓库1光照高于阈值，自动关灯", 8000);
        }
    }

    // 湿度控制：高于阈值开风扇，低于阈值关风扇
    if (humidity > threshold1.humidityMax) {
        if (deviceStatus["fan"] != "ON") {
            sendCommandAPI("fan", "ON");
            qDebug() << "仓库1湿度高于阈值，自动开风扇";
            ui->statusBar->showMessage("仓库1湿度高于阈值，自动开风扇", 8000);
        }
    } else if (humidity < threshold1.humidityMin) {
        if (deviceStatus["fan"] != "OFF") {
            sendCommandAPI("fan", "OFF");
            qDebug() << "仓库1湿度低于阈值，自动关风扇";
            ui->statusBar->showMessage("仓库1湿度低于阈值，自动关风扇", 8000);
        }
    }
}

void Widget::autoControlWarehouse2(int temp, int humidity, int light, int co2)
{
    // 光照控制：低于阈值开灯，高于阈值关灯
    if (light < threshold2.lightMin) {
        if (deviceStatus["ck2_Led"] != "ON") {
            sendCommandAPI("ck2_Led", "ON");
            qDebug() << "仓库2光照低于阈值，自动开灯";
            ui->statusBar->showMessage("仓库2光照低于阈值，自动开灯", 8000);
        }
    } else if (light > threshold2.lightMax) {
        if (deviceStatus["ck2_Led"] != "OFF") {
            sendCommandAPI("ck2_Led", "OFF");
            qDebug() << "仓库2光照高于阈值，自动关灯";
            ui->statusBar->showMessage("仓库2光照高于阈值，自动关灯", 8000);
        }
    }

    // 湿度控制：高于阈值开风扇，低于阈值关风扇
    bool shouldTurnOnFan = false;
    bool shouldTurnOffFan = false;

    // 检查是否应该开启风扇
    if (humidity > threshold2.humidityMax || co2 > threshold2.co2Max) {
        shouldTurnOnFan = true;
    }

    // 检查是否应该关闭风扇（两个条件都低于阈值时才关闭）
    if (humidity < threshold2.humidityMin && co2 < threshold2.co2Min) {
        shouldTurnOffFan = true;
    }

    // 执行风扇控制
    if (shouldTurnOnFan && deviceStatus["FAN_D3"] != "ON") {
        sendCommandAPI("FAN_D3", "ON");
        if (humidity > threshold2.humidityMax && co2 > threshold2.co2Max) {
            qDebug() << "仓库2湿度和二氧化碳都高于阈值，自动开风扇";
            ui->statusBar->showMessage("仓库2湿度和二氧化碳都高于阈值，自动开风扇", 8000);
        } else if (humidity > threshold2.humidityMax) {
            qDebug() << "仓库2湿度高于阈值，自动开风扇";
            ui->statusBar->showMessage("仓库2湿度高于阈值，自动开风扇", 8000);
        } else {
            qDebug() << "仓库2二氧化碳高于阈值，自动开风扇";
            ui->statusBar->showMessage("仓库2二氧化碳高于阈值，自动开风扇", 8000);
        }
    } else if (shouldTurnOffFan && deviceStatus["FAN_D3"] != "OFF") {
        sendCommandAPI("FAN_D3", "OFF");
        qDebug() << "仓库2湿度和二氧化碳都低于阈值，自动关风扇";
        ui->statusBar->showMessage("仓库2湿度和二氧化碳都低于阈值，自动关风扇", 8000);
    }
}
