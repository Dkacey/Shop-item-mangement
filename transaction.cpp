#include "transaction.h"

Transaction::Transaction(): dateTime{QDateTime::currentDateTime()}
{
}

void Transaction::addLineItem(LineItem item)
{
    lineItems.append(item);
}

QDateTime Transaction::getDateTime() const
{
    return dateTime;
}

QList<LineItem> Transaction::getLineItems() const
{
    return lineItems;
}

