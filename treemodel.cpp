// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

/*
    treemodel.cpp

    Provides a simple tree model to show how to create and use hierarchical
    models.
*/

#include "treemodel.h"
#include "treeitem.h"
#include "transaction.h"
#include <QStringList>

//! [0]
TreeModel::TreeModel(QObject *parent)
    : QAbstractItemModel(parent)
{
    rootItem = new TreeItem({"Transaction", "Type", "Quantity"});
    //setupModelData(data, rootItem);
}
//! [0]

//! [1]
TreeModel::~TreeModel()
{
    delete rootItem;
}
//! [1]

//! [2]
int TreeModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return static_cast<TreeItem*>(parent.internalPointer())->columnCount();
    return rootItem->columnCount();
}
//! [2]

//! [3]
QVariant TreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    TreeItem *item = static_cast<TreeItem*>(index.internalPointer());

    return item->data(index.column());
}
//! [3]

//! [4]
Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index);
}
//! [4]

//! [5]
QVariant TreeModel::headerData(int section, Qt::Orientation orientation,
                               int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem->data(section);

    return QVariant();
}
//! [5]

//! [6]
QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    TreeItem *parentItem;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    TreeItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    return QModelIndex();
}
//! [6]

//! [7]
QModelIndex TreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    TreeItem *childItem = static_cast<TreeItem*>(index.internalPointer());
    TreeItem *parentItem = childItem->parentItem();

    if (parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}
//! [7]

//! [8]
int TreeModel::rowCount(const QModelIndex &parent) const
{
    TreeItem *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    return parentItem->childCount();
}
//! [8]

void TreeModel::addData(QString customer, Transaction transaction)
{
    if (rootItem->childCount() == 0)  // add first child
    {
        TreeItem *customerParent{new TreeItem({customer, "", ""}, rootItem)};
        rootItem->appendChild(customerParent);

        TreeItem *dateParent = new TreeItem({transaction.getDateTime(), "", ""}, customerParent);
        customerParent->appendChild(dateParent);

        foreach(LineItem item, transaction.getLineItems())
        {
            QList<QVariant> itemData{item.getItemName(), item.getItemType(), item.getItemQuantity()};
            TreeItem *itemParent = new TreeItem(itemData, dateParent);
            dateParent->appendChild(itemParent);
        }
    }
    else // check that customer does not already exist among children
    {
        bool found{false};
        int loop{0};
        do
        {
            TreeItem *item{rootItem->child(loop)};
            if(item->data(0).toString() == customer)  // does customer already exist?
            {
                found = true;
                TreeItem *dateParent = new TreeItem({transaction.getDateTime(), "", ""}, item);
                item->appendChild(dateParent);

                foreach(LineItem item, transaction.getLineItems())
                {
                    QList<QVariant> itemData{item.getItemName(), item.getItemType(), item.getItemQuantity()};
                    TreeItem *itemParent = new TreeItem(itemData, dateParent);
                    dateParent->appendChild(itemParent);
                }
            }
            loop++;
        } while (!found && (loop < rootItem->childCount()));

        if (!found)  // did not find customer
        {
            TreeItem *customerParent{new TreeItem({customer, "", ""}, rootItem)};
            rootItem->appendChild(customerParent);

            TreeItem *dateParent = new TreeItem({transaction.getDateTime(), "", ""}, customerParent);
            customerParent->appendChild(dateParent);

            foreach(LineItem item, transaction.getLineItems())
            {
                QList<QVariant> itemData{item.getItemName(), item.getItemType(), item.getItemQuantity()};
                TreeItem *itemParent = new TreeItem(itemData, dateParent);
                dateParent->appendChild(itemParent);
            }
        }
    }
}

TreeItem *TreeModel::getRootItem()
{
    return rootItem;
}

