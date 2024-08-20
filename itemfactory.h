#ifndef ITEMFACTORY_H
#define ITEMFACTORY_H
#include <QString>

class Item;

class ItemFactory
{
public:
    ItemFactory();
    Item *createItem(QString type, QString name);
};

#endif // ITEMFACTORY_H
