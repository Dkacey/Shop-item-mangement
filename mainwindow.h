#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QPlainTextEdit;
class QAction;
class QUdpSocket;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void listen();
    void processPendingDatagrams();

private:
    QPlainTextEdit *displayfield;
    QAction *listenAction;
    QAction *exitAction;
    QUdpSocket *udpSocket;

    void closeEvent(QCloseEvent *event);
};
#endif // MAINWINDOW_H
