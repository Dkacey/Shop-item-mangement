    #ifndef TRANSACTION_H
#define TRANSACTION_H

#include "lineitem.h"
#include <QDateTime>

class Transaction
{
public:
    Transaction();
    void addLineItem(LineItem item);
    QDateTime getDateTime() const;
    QList<LineItem> getLineItems() const;

private:
    QDateTime dateTime;
    QList<LineItem> lineItems;
};

#endif // TRANSACTION_H
