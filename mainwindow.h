#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "transaction.h"
#include <QMainWindow>

class QTreeView;
class TreeModel;
class Customers;
class Item;
class ItemList;
class ItemListMemento;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void broadcastModelAsXml();
    void addCustomer();
    void callItemAddDialog();
    void addItemToList(Item *);
    void addTransaction();
    void addTransactionToModel(QString c, Transaction t);
    void restoreItemList();

private:
    QAction *broadcastAction;
    QAction *exitAction;
    QAction *addCustomerAction;
    QAction *addItemAction;
    QAction *addTransactionAction;
    QAction *restoreItemListAction;

    QTreeView *treeview;
    TreeModel *treemodel;
    Customers *customerList;
    ItemList *itemList;
    ItemListMemento *memento;

    void setupGui();
    void closeEvent(QCloseEvent *event);
};
#endif // MAINWINDOW_H
