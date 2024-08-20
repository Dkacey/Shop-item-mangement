#ifndef LINEITEM_H
#define LINEITEM_H

#include <QString>

class LineItem
{
public:
    LineItem(QString n, QChar t, int q);

    QString getItemName() const;
    void setItemName(const QString newItemName);

    QChar getItemType() const;
    void setItemType(const QChar newItemType);

    int getItemQuantity() const;
    void setItemQuantity(int newItemQuantity);

private:
    QString itemName;
    QChar itemType;
    int itemQuantity;
};

#endif // LINEITEM_H
