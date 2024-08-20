#ifndef ITEM_H
#define ITEM_H

#include <QString>

class Item
{
public:
    Item();
    Item(QString n);

    QString getName() const;
    void setName(const QString &newName);

    virtual QStringList getDetail() const = 0;

protected:
    QString name;
};

#endif // ITEM_H
