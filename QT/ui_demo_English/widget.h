#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QMap>
#include <QTimer>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void requestToken();
    void onTokenReceived();
    void sendCommandAPI(const QString &commandName, const QString &value);
    void sendCommandViaToken(const QString &commandName, const QString &value);
    void onCommandSent();
    void fetchDeviceStatus();
    void onDeviceStatusReceived();
    void updateDeviceStatus(const QJsonObject &properties);
    void updateControlButtons();
    void sendCommand(const QString &deviceService);

    // 新添加的自动控制函数
    void toggleAutoMode1();
    void toggleAutoMode2();
    void autoControlWarehouse1(int temp, int humidity, int light);
    void autoControlWarehouse2(int temp, int humidity, int light, int co2);

private:
    Ui::Widget *ui;
    QNetworkAccessManager *networkManager;
    QString m_token;
    QString m_commandName;
    QString m_commandValue;

    // 设备状态映射
    QMap<QString, QString> deviceStatus;

    // 阈值设置
    struct Threshold {
        int lightMax;
        int lightMin;
        int humidityMax;
        int humidityMin;
        int co2Max;
        int co2Min;
    };

    Threshold threshold1;  // 仓库1阈值
    Threshold threshold2;  // 仓库2阈值

    // 自动模式状态
    bool autoMode1 = false;  // 仓库1自动模式
    bool autoMode2 = false;  // 仓库2自动模式

    // 定时器用于自动控制检查
    QTimer *autoControlTimer;

    // 私有函数
    void initializeThresholds();
    void loadThresholdsFromUI();
    void updateAutoModeUI();
};

#endif // WIDGET_H
