#include "mainwindow.h"
#include <QMessageBox>
#include <QCloseEvent>
#include <QTreeView>
#include <QMenuBar>
#include <QStatusBar>
#include <QInputDialog>
#include <QLineEdit>
#include <QThreadPool>
#include "treemodel.h"
#include "customers.h"
#include "itemdialog.h"
#include "item.h"
#include "itemlist.h"
#include "transactiondialog.h"
#include "itemlistmemento.h"
#include "broadcast.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      treeview{new QTreeView},
      treemodel{new TreeModel(this)},
      customerList{Customers::getCustomersInstance()},
      itemList{ItemList::getItemListInstance()},
      memento{nullptr},
      broadcastAction{new QAction("&Broadcast", this)},
      exitAction{new QAction("&Exit", this)},
      addCustomerAction{new QAction("Add &customer", this)},
      addItemAction{new QAction("Add &item", this)},
      addTransactionAction{new QAction("Add &transaction", this)},
      restoreItemListAction{new QAction("Restore item list from backup", this)}
{
    setupGui();
}

MainWindow::~MainWindow()
{
    customerList->deleteCustomersInstance();
    itemList->deleteItemListInstance();
    if (memento != nullptr)
        delete memento;
}

void MainWindow::broadcastModelAsXml()
{
    Broadcast *broadcast{new Broadcast(treemodel->getRootItem())};
    QThreadPool::globalInstance()->start(broadcast);
}

void MainWindow::addCustomer()
{
    bool ok;
    QString text = QInputDialog::getText(this, "Add customer", "Customer name:", QLineEdit::Normal, "", &ok);
    if (ok && !text.isEmpty())
    {
        if (customerList->addCustomer(text))
            QMessageBox::information(this, "Adding customer", "Customer added successfully", QMessageBox::Ok);
        else
            QMessageBox::information(this, "Adding customer", "Customer already exists", QMessageBox::Ok);
    }
    else if (!ok)
        QMessageBox::information(this, "Adding customer", "Task cancelled", QMessageBox::Ok);
    else if (text.isEmpty())
        QMessageBox::information(this, "Adding customer", "No name added", QMessageBox::Ok);

    statusBar()->showMessage("Customer added");
}

void MainWindow::callItemAddDialog()
{
    ItemDialog *getItem{new ItemDialog(this)};
    connect(getItem, &ItemDialog::dataEntered, this, &MainWindow::addItemToList);
    getItem->exec();
    getItem->deleteLater();
}

void MainWindow::addItemToList(Item *i)
{
    itemList->addItem(i);
    memento = itemList->createMemento();
    restoreItemListAction->setEnabled(true);

    statusBar()->showMessage("Item added; list backed up");
}

void MainWindow::addTransaction()
{
    TransactionDialog *getTransaction{new TransactionDialog(customerList->getCustomerList(), itemList->getItemList(), this)};
    connect(getTransaction, &TransactionDialog::dataEntered, this, &MainWindow::addTransactionToModel);
    getTransaction->exec();
    getTransaction->deleteLater();
}

void MainWindow::addTransactionToModel(QString c, Transaction t)
{
    treemodel->addData(c, t);
    treeview->reset();

    statusBar()->showMessage("Transaction added and view updated");
}

void MainWindow::restoreItemList()
{
    itemList->setMemento(memento);
}

void MainWindow::setupGui()
{
    setCentralWidget(treeview);
    treeview->setModel(treemodel);

    // File menu
    QMenu *fileMenu{menuBar()->addMenu("&File")};

    fileMenu->addAction(broadcastAction);
    broadcastAction->setStatusTip("Broadcast the model in XML format");
    connect(broadcastAction, &QAction::triggered, this, &MainWindow::broadcastModelAsXml);

    fileMenu->addAction(exitAction);
    exitAction->setStatusTip("Close the application");
    connect(exitAction, &QAction::triggered, this, &QWidget::close);

    // Add menu
    QMenu *addMenu{menuBar()->addMenu("&Add")};

    addMenu->addAction(addCustomerAction);
    addCustomerAction->setStatusTip("Add a new customer");
    connect(addCustomerAction, &QAction::triggered, this, &MainWindow::addCustomer);

    addMenu->addAction(addItemAction);
    addItemAction->setStatusTip("Add a new item");
    connect(addItemAction, &QAction::triggered, this, &MainWindow::callItemAddDialog);

    addMenu->addAction(addTransactionAction);
    addTransactionAction->setStatusTip("Add a new transaction for a customer");
    connect(addTransactionAction, &QAction::triggered, this, &MainWindow::addTransaction);

    // Restore menu
    QMenu *restoreMenu{menuBar()->addMenu("&Restore")};

    restoreMenu->addAction(restoreItemListAction);
    restoreItemListAction->setEnabled(false);
    restoreItemListAction->setStatusTip("Restore the item list from the auto-saved backup");
    connect(restoreItemListAction, &QAction::triggered, this, &MainWindow::restoreItemList);

    // other setup
    statusBar()->showMessage("Ready");

    this->resize(500, 300);
    treeview->setColumnWidth(0, 200);

    // some data for testing
//    LineItem i1{"book1", 'B', 1};
//    LineItem i2{"book2", 'B', 2};
//    LineItem i3{"book3", 'B', 3};
//    LineItem i4{"book4", 'B', 4};
//    LineItem i5{"magazine1", 'M', 5};
//    LineItem i6{"magazine2", 'M', 6};
//    LineItem i7{"magazine3", 'M', 7};

//    Transaction t1;
//    t1.addLineItem(i1);
//    t1.addLineItem(i2);
//    t1.addLineItem(i5);

//    Transaction t2;
//    t2.addLineItem(i3);
//    t2.addLineItem(i6);

//    Transaction t3;
//    t3.addLineItem(i4);
//    t3.addLineItem(i7);

//    treemodel->addData("Customer1", t1);
//    treemodel->addData("Customer2", t2);
//    treemodel->addData("Customer1", t3);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    int answer{QMessageBox::warning(this, "Exit", "Are you sure you want to exit?", QMessageBox::Yes | QMessageBox::No)};
    if (answer == QMessageBox::Yes)
        event->accept();
    else
        event->ignore();
}

