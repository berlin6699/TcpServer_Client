#ifndef WIDGET_H
#define WIDGET_H

//TCP头文件
#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>

//图表头文件
#include <QWidget>
#include <QtCharts>
#include <QValueAxis>
#include <QChartView>

//接收拆分字符头文件
#include <QVector>
#include <QDebug>

//文件读写头文件
#include <QFile>
#include <QTextStream>

//获取时间头文件
#include <QDateTime>

//复选框头文件
#include <QCheckBox>
QT_CHARTS_USE_NAMESPACE

#define PORT 8000

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    QVector<qreal> stringToQRealArray(const QString &dataString);   //拆分字符函数

    void saveToTxt(const QVector<qreal>& data, const QString& filePath);    //文件处理函数（写入已有txt文件）
    void writeDataToFile(const QString& filePath, const QString& content);  //文件处理函数（新建txt文件并写入）





private slots:
    void newClientHandler();    //客户端新的连接请求处理
    void onReadMsg();           //服务端读取客户端发来的数据


    void on_saveButton_clicked();

    void on_connectButton_clicked();

    void on_photoButton_clicked();

private:
    Ui::Widget *ui;
    QTcpServer *server;
    QTcpSocket *socket;


    QChartView *chartview;
    QChart *chart;
    void CreateChartFunc();     //创建图表函数

};
#endif // WIDGET_H
