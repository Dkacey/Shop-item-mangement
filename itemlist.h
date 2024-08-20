#ifndef ITEMLIST_H
#define ITEMLIST_H

#include <QList>

class Item;
class ItemListMemento;

class ItemList
{
public:
    static ItemList *getItemListInstance();
    static void deleteItemListInstance();

    void addItem(Item *i);
    QList<Item*> * getItemList();

    ItemListMemento *createMemento();
    void setMemento(ItemListMemento *menento);

    void clearItemList();

private:
    ItemList();
    ~ItemList();
    static ItemList *onlyInstance;
    QList<Item*> *items;
};

#endif // ITEMLIST_H
