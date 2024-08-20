#ifndef TRANSACTIONDIALOG_H
#define TRANSACTIONDIALOG_H

#include "item.h"
#include "lineitem.h"
#include "transaction.h"
#include <QDialog>

class QComboBox;
class QLabel;
class QSpinBox;
class QPushButton;
class QPlainTextEdit;
class QGridLayout;

class TransactionDialog : public QDialog
{
    Q_OBJECT
public:
    TransactionDialog(QStringList customers, QList<Item*> *items, QWidget *parent = nullptr);

signals:
    void dataEntered(QString, Transaction);

private slots:
    void addButtonClicked();
    void doneButtonClicked();
    void itemIndexChanged(int);
    void enableButtonAdd();

private:
    QGridLayout *dataGrid;
    QComboBox *customerSelect;
    QComboBox *itemSelect;
    QLabel *typeLabel;
    QSpinBox *quantity;
    QPushButton *addButton;
    QPlainTextEdit *display;
    QPushButton *doneButton;

    QList<Item*> *itemList;
    QList<LineItem> lineItems;
};

#endif // TRANSACTIONDIALOG_H
