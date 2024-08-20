#include "lineitem.h"

LineItem::LineItem(QString n, QChar t, int q): itemName{n}, itemType{t}, itemQuantity{q}
{
}

QString LineItem::getItemName() const
{
    return itemName;
}

void LineItem::setItemName(const QString newItemName)
{
    itemName = newItemName;
}

QChar LineItem::getItemType() const
{
    return itemType;
}

void LineItem::setItemType(const QChar newItemType)
{
    itemType = newItemType;
}

int LineItem::getItemQuantity() const
{
    return itemQuantity;
}

void LineItem::setItemQuantity(int newItemQuantity)
{
    itemQuantity = newItemQuantity;
}
