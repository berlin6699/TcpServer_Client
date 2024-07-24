#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    socket = new QTcpSocket;    //创建socket对象
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_cancelButton_clicked()
{
    this->close();
}

void Widget::on_connectButton_clicked()
{
    //获取IP地址和端口号
    QString IP = ui->ipLineEdit->text();
    QString port = ui->portLineEdit->text();

    //连接服务器
    socket->connectToHost(QHostAddress(IP), port.toShort());

    //连接服务器成功，socket对象会发出信号
    connect(socket, &QTcpSocket::connected,[this]()
    {
       QMessageBox::information(this,"连接提示","连接服务器成功");
    });

    //连接断开，socket会发出信号
    connect(socket, &QTcpSocket::disconnected,[this]()
    {
        QMessageBox::warning(this, "连接提示", "连接异常 网络断开");
    });

    //socket有数据来了，做处理
    connect(socket,&QTcpSocket::readyRead,this,&Widget::onReadMessage);

}

void Widget::on_sendButton_clicked()
{
    socket->write(ui->sentLineEdit->text().toUtf8());
    socket->flush();
}

void Widget::onReadMessage()   //处理服务端反馈的数据
{
    //服务端将客户发来的数据显示到LineEdit上
    QString bt = QString(socket->readAll());    //socket->readAll返回的是QByteArray类型，而setText接收的时QString类型，需要进行转化
    ui->readMessage->setText(bt);
}

