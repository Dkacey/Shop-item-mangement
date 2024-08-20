#ifndef ITEMLISTMEMENTO_H
#define ITEMLISTMEMENTO_H
#include <QStringList>

class ItemList;

class ItemListMemento
{
private:
    friend class ItemList;
    ItemListMemento();

    QList<QStringList> getMemento();
    void setMemento(QList<QStringList> s);

    QList<QStringList> state;
};

#endif // ITEMLISTMEMENTO_H
