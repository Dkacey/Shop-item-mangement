#include "mainwindow.h"
#include <QPlainTextEdit>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QUdpSocket>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      displayfield{new QPlainTextEdit},
      listenAction{new QAction("&Listen", this)},
      exitAction{new QAction("&Exit", this)},
      udpSocket{nullptr}
{
    setCentralWidget(displayfield);
    displayfield->setEnabled(false);

    QMenu *fileMenu{menuBar()->addMenu("&File")};

    fileMenu->addAction(listenAction);
    listenAction->setStatusTip("Close the application");
    connect(listenAction, &QAction::triggered, this, &MainWindow::listen);

    fileMenu->addAction(exitAction);
    exitAction->setStatusTip("Close the application");
    connect(exitAction, &QAction::triggered, this, &QWidget::close);
}

MainWindow::~MainWindow()
{
}

void MainWindow::listen()
{
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(45454, QUdpSocket::ShareAddress);
    connect(udpSocket, &QUdpSocket::readyRead, this, &MainWindow::processPendingDatagrams);
}

void MainWindow::processPendingDatagrams()
{
    QByteArray datagram;
    while (udpSocket->hasPendingDatagrams())
    {
        datagram.resize(int(udpSocket->pendingDatagramSize()));
        udpSocket->readDatagram(datagram.data(), datagram.size());
        displayfield->appendPlainText(datagram.constData());
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    int answer{QMessageBox::warning(this, "Exit", "Are you sure you want to exit?", QMessageBox::Yes | QMessageBox::No)};
    if (answer == QMessageBox::Yes)
        event->accept();
    else
        event->ignore();
}
