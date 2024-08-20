#include "itemfactory.h"
#include "book.h"
#include "magazine.h"

ItemFactory::ItemFactory()
{
}

Item *ItemFactory::createItem(QString type, QString name)
{
    if (type == "Book")
        return new Book(name);
    if (type == "Magazine")
        return new Magazine(name);
    return nullptr;
}

