#include "item.h"

Item::Item(): name{"Not set"}
{
}

Item::Item(QString n): name{n}
{
}

QString Item::getName() const
{
    return name;
}

void Item::setName(const QString &newName)
{
    name = newName;
}
