#include "itemlistmemento.h"

ItemListMemento::ItemListMemento()
{
}

QList<QStringList> ItemListMemento::getMemento()
{
    return state;
}

void ItemListMemento::setMemento(QList<QStringList> s)
{
    state = s;
}
