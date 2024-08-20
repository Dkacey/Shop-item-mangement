#include "itemlist.h"
#include "item.h"
#include "itemlistmemento.h"
#include "itemfactory.h"

ItemList *ItemList::onlyInstance = nullptr;

ItemList *ItemList::getItemListInstance()
{
    if (onlyInstance == nullptr)
        onlyInstance = new ItemList;
    return onlyInstance;
}

void ItemList::deleteItemListInstance()
{
    delete onlyInstance;
}

ItemList::ItemList(): items{new QList<Item*>}
{
}

ItemList::~ItemList()
{
    qDeleteAll(*items);
    items->clear();
}

void ItemList::addItem(Item *i)
{
    items->append(i);
}

QList<Item *> *ItemList::getItemList()
{
    return items;
}

ItemListMemento *ItemList::createMemento()
{
    QList<QStringList> data;
    QStringList d;
    foreach (Item* i, *items)
    {
        QStringList temp{i->getDetail()};
        if (temp.at(1) == "B")
            d << "Book";
        else
            d << "Magazine";
        d  << temp.at(0);
        data << d;
        d.clear();
    }

    ItemListMemento *memento{new ItemListMemento};
    memento->setMemento(data);
    return memento;
}

void ItemList::setMemento(ItemListMemento *memento)
{
    clearItemList();

    QList<QStringList> data{memento->getMemento()};

    ItemFactory factory;
    foreach (QStringList item, data)
        addItem(factory.createItem(item.at(0), item.at(1)));
}

void ItemList::clearItemList()
{
    qDeleteAll(*items); // clear the list first
    items->clear();
}
