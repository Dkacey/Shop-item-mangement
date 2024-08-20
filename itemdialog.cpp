#include "itemdialog.h"
#include "itemfactory.h"
#include <QtWidgets>

ItemDialog::ItemDialog(QWidget *parent):
    QDialog(parent),
    dataGrid{new QGridLayout(this)},
    itemType{new QComboBox},
    itemName{new QLineEdit},
    message{new QLabel},
    addButton{new QPushButton("Add item")}
{
    itemType->insertItem(0, "");
    itemType->insertItem(1, "Book");
    itemType->insertItem(2, "Magazine");

    dataGrid->addWidget(new QLabel{"Complete the required data"}, 0, 0, 1, 2, Qt::AlignHCenter);
    dataGrid->addWidget(new QLabel{"Item type"}, 1, 0);
    dataGrid->addWidget(itemType, 1, 1);
    dataGrid->addWidget(new QLabel{"Name of item:"}, 2, 0);
    dataGrid->addWidget(itemName, 2, 1);
    dataGrid->addWidget(message, 3, 0, 1, 2);
    dataGrid->addWidget(addButton, 4, 0, 1, 2, Qt::AlignHCenter);

    addButton->setEnabled(false);
    connect(itemType, &QComboBox::currentIndexChanged, this, &ItemDialog::enableButton);
    connect(itemName, &QLineEdit::textChanged, this, &ItemDialog::enableButton);
    connect(addButton, &QPushButton::clicked, this, &ItemDialog::addButtonClicked);
}

void ItemDialog::addButtonClicked()
{
    if (itemName->text().size() == 0)
        message->setText("No item name entered");
    else
    {
        ItemFactory factory;
        emit dataEntered(factory.createItem(itemType->currentText(), itemName->text()));
        accept();
    }
}

void ItemDialog::enableButton()
{
    if ((itemType->currentIndex() > 0) && (itemName->text().size() > 0))
        addButton->setEnabled(true);
    else
        addButton->setEnabled(false);
}
