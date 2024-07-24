#include "widget.h"
#include "ui_widget.h"


//定义曲线全局变量
QLineSeries *series1 = new QLineSeries();
QLineSeries *series2 = new QLineSeries();

//创建接收数据字符串
QString bt;
int savecounter = 1;


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    server = new QTcpServer;
    socket = new QTcpSocket;

    server->listen(QHostAddress::AnyIPv4, PORT);

    //客户端发起连接，server发出信号
    connect(server, &QTcpServer::newConnection, this, &Widget::newClientHandler);

    setWindowTitle("上位机"); //修改页面左上角的字

    CreateChartFunc();  //调用此函数实现图表绘制功能

    //初始时wifi显示断连,移动工程的时候记得把这段绝对路径改一下
    QPixmap pix("C:\\Users\\berlin\\Desktop\\TcpServer\\WiFi_disconnect.png");
    ui->wifi->setPixmap(pix);

}

Widget::~Widget()
{
    delete ui;
}


void Widget::newClientHandler()
{
    //建立TCP连接
    socket = server->nextPendingConnection();//通过nextpendingconnection连接，连接的信息都保存在socket，包含地址、端口号
    socket->peerAddress();//获取客户端地址
    socket->peerPort();//获取客户端端口号

    ui->ipLineEdit->setText(socket->peerAddress().toString());
    ui->portLineEdit->setText(QString::number(socket->peerPort()));

    //WiFi图表变化,移动工程的时候记得把这段绝对路径改一下
    QPixmap pix("C:\\Users\\berlin\\Desktop\\TcpServer\\WiFi_connect.png");
    ui->wifi->setPixmap(pix);

    //socket有数据时会发送readyRead信号，放在连接函数里应该是为了让有连接时才触发这个连接
    connect(socket, &QTcpSocket::readyRead, this, &Widget::onReadMsg);

    //这里写connect连接“建立连接”button的函数
}

void Widget::onReadMsg()
{
    //服务端将客户发来的数据显示到LineEdit上
    bt = QString(socket->readAll());    //socket->readAll返回的是QByteArray类型，而setText接收的时QString类型，需要进行转化
    ui->dataLineEdit->setText(bt);

    //发了数据才通过序列添加数值
    qreal start=0,y1,y2,intv = 1;

    //以下代码用来清除图标上的所有点，确保每次只有一个光谱被画上去
    const QList<QAbstractSeries*> &seriesList = chart->series();

    // 遍历图表上的所有系列
    for (QAbstractSeries *series : seriesList)
    {
        // 确认系列是QLineSeries类型
        QLineSeries *lineSeries = qobject_cast<QLineSeries*>(series);
        if (lineSeries)
        {
            // 清除这个系列上的所有数据点
            lineSeries->clear();
        }
    }


    QVector<qreal> qrealArray = stringToQRealArray(bt);
    int length = qrealArray.size();//length的长度为发来的数据有多少

//    //将接收数据写入txt文件
//    saveToTxt(qrealArray, "C:\\Users\\berlin\\Desktop\\test.txt");


    //对TCP发送过来的数据类型进行转换
//    QVariant variant(bt);
//    qreal value = variant.toReal();

    for(int i=0; i<length; i++)
    {
        y1 = qrealArray.at(i);
        series1->append(start,y1);

        y2 = qrealArray.at(i)+1;
        series2->append(start,y2);

        start = start+intv;
    }

}


void Widget::CreateChartFunc()     //创建图表函数
{
    //创建图表
    chartview = new QChartView(this);
    chart = new QChart();

    // 调整为合适的大小
    chartview->setMinimumSize(1500, 1000);

    // 设置 chartView 的位置（左上角坐标为 (x, y)）
    int x = 200;
    int y = 200;
    chartview->move(x, y);

    chart->setTitle("光谱图像");

    chartview->setChart(chart); //chart添加到chartview


    //创建曲线序列操作，创建变量使用了全局定义，这样才可以在多个函数里使用
    series1->setName("光谱曲线1");
    series2->setName("光谱曲线2");
    chart->addSeries(series1);
    chart->addSeries(series2);

    //创建坐标轴
    QValueAxis *axisX = new QValueAxis; //X轴
    axisX->setRange(0,400);  //设置坐标范围
    axisX->setTitleText("波长/nm");  //标题


    QValueAxis *axisY = new QValueAxis; //Y轴
    axisY->setRange(0,200);  //设置坐标范围
    axisY->setTitleText("相对强度");  //标题

    chart->setAxisX(axisX,series1);
    chart->setAxisY(axisY,series1);

    chart->setAxisX(axisX,series2);
    chart->setAxisY(axisY,series2);


//以下注释是由于把代码转移到了当接收到客户端发来的数据的时候的代码，这时候有数据才画图
//    //通过序列添加数值
//    qreal t=400,y1,y2,intv = 0.1;
//    int icount = 100;
//    for(int i=0; i<icount; i++)
//    {
//        y1 = qSin(t);
//        series1->append(t,y1);

//        y2 = qSin(t+20);
//        series2->append(t,y2);

//        t = t+intv;
//    }

}

QVector<qreal> Widget::stringToQRealArray(const QString &dataString)
{
    QVector<qreal> qrealArray;
    QStringList stringList = dataString.split(" "); // 使用空格分割字符串

    foreach (const QString &str, stringList) {
        bool ok;
        qreal value = str.toDouble(&ok);
        if (ok) {
            qrealArray.append(value); // 将转换后的qreal值添加到数组中
        } else {
            qWarning() << "Failed to convert" << str << "to qreal";
        }
    }

    return qrealArray;
}

void Widget::on_saveButton_clicked()
{
//    QString str="你好，客户端！";
//    socket->write(str.toUtf8());

    //拼接新地址
    // 获取当前的日期和时间
    QDateTime currentDateTime = QDateTime::currentDateTime();

    // 将日期和时间格式化为字符串，例如："20240716_123456"
    QString formattedTime = currentDateTime.toString("yyyyMMdd_hh_mm_ss");

    // 构建完整的文件路径和文件名
    QString path = "C:\\Users\\berlin\\Desktop\\" +QString::number(savecounter)+"_"+formattedTime + ".txt";

    //创建新txt并写入数据
    writeDataToFile(path, bt);
    savecounter++;
}

void Widget::on_connectButton_clicked()
{
//    //连接到stm32
//    writeDataToFile("C:\\Users\\berlin\\Desktop\\test.txt", "Hello, world!");
        QString str="A";
        socket->write(str.toUtf8());

}

void Widget::on_photoButton_clicked()
{
    QString str="B";
    socket->write(str.toUtf8());
}


//将数据存入已有txt
void Widget::saveToTxt(const QVector<qreal>& data, const QString& filePath)
{
    // 打开文件以写入模式
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "Failed to open file:" << filePath;
        return;
    }

    // 创建一个文本流来写入文件
    QTextStream out(&file);

    // 遍历数组并写入每一项
    for (const qreal& value : data)
    {
        out << value << '\n'; // 每个值后面加一个换行符
    }

    // 关闭文件
    file.close();
}

//新建txt并写入数据
void Widget::writeDataToFile(const QString& filePath, const QString& content)
{
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
    {
        qDebug() << "Failed to open file:" << filePath;
        return;
    }

    QTextStream out(&file);
    out << content;

    file.close();
}



