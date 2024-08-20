#include "transactiondialog.h"
#include "transaction.h"
#include <QtWidgets>

TransactionDialog::TransactionDialog(QStringList customers, QList<Item*> *items, QWidget *parent):
     QDialog(parent),
     dataGrid{new QGridLayout(this)},
     customerSelect{new QComboBox},
     itemSelect{new QComboBox},
     typeLabel{new QLabel},
     quantity{new QSpinBox},
     addButton{new QPushButton("Add item")},
     display{new QPlainTextEdit},
     doneButton{new QPushButton("Done")},
     itemList{items}
{
    quantity->setMinimum(0);
    quantity->setMaximum(1000);

    customerSelect->insertItem(0, "");
    customerSelect->insertItems(1, customers);

    QStringList itemNames;
    foreach (Item *i, *itemList)
        itemNames.append(i->getName());
    itemNames.sort();
    itemSelect->insertItem(0, "");
    itemSelect->insertItems(1, itemNames);

    dataGrid->addWidget(new QLabel{"Complete the required data"}, 0, 0, 1, 2, Qt::AlignHCenter);
    dataGrid->addWidget(new QLabel{"Select the customer:"}, 1, 0);
    dataGrid->addWidget(customerSelect, 1, 1);
    dataGrid->addWidget(new QLabel{"Select the item:"}, 2, 0);
    dataGrid->addWidget(itemSelect, 2, 1);
    dataGrid->addWidget(new QLabel{"Item type:"}, 3, 0);
    dataGrid->addWidget(typeLabel, 3, 1);
    dataGrid->addWidget(new QLabel{"Item quantity:"}, 4, 0);
    dataGrid->addWidget(quantity, 4, 1);
    dataGrid->addWidget(addButton, 4, 2);
    dataGrid->addWidget(display, 5, 0, 1, 3);
    dataGrid->addWidget(doneButton, 6, 0, 1, 3, Qt::AlignHCenter);

    addButton->setEnabled(false);
    doneButton->setEnabled(false);

    connect(itemSelect, &QComboBox::currentIndexChanged, this, &TransactionDialog::itemIndexChanged);
    connect(customerSelect, &QComboBox::currentIndexChanged, this, &TransactionDialog::enableButtonAdd);
    connect(quantity, &QSpinBox::valueChanged, this, &TransactionDialog::enableButtonAdd);
    connect(itemSelect, &QComboBox::currentIndexChanged, this, &TransactionDialog::enableButtonAdd);
    connect(addButton, &QPushButton::clicked, this, &TransactionDialog::addButtonClicked);
    connect(doneButton, &QPushButton::clicked, this, &TransactionDialog::doneButtonClicked);
}

void TransactionDialog::addButtonClicked()
{
    LineItem lineItem{itemSelect->currentText(), typeLabel->text().at(0), quantity->value()};
    lineItems.append(lineItem);
    display->appendPlainText(QString{itemSelect->currentText() + " - " + typeLabel->text().at(0) + " - " + QString::number(quantity->value())});
    itemSelect->setCurrentIndex(0);
    typeLabel->clear();
    quantity->setValue(0);
    itemSelect->setFocus();
    doneButton->setEnabled(true);
}

void TransactionDialog::doneButtonClicked()
{
    Transaction transaction;
    foreach (LineItem lineitem, lineItems)
        transaction.addLineItem(lineitem);
    emit dataEntered(customerSelect->currentText(), transaction);
    accept();
}

void TransactionDialog::itemIndexChanged(int i)
{
    QString itemName{itemSelect->itemText(i)};
    foreach (Item *item, *itemList)
    {
        if (item->getName() == itemName)
        {
            typeLabel->setText(item->getDetail().at(1));
            return;
        }
    }
}

void TransactionDialog::enableButtonAdd()
{
    if (customerSelect->currentIndex()>0 && itemSelect->currentIndex()>0 && quantity->value()>0)
        addButton->setEnabled(true);
    else
        addButton->setEnabled(false);
}
