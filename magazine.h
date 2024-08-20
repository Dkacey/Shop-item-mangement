#ifndef MAGAZINE_H
#define MAGAZINE_H
#include <QStringList>

#include "item.h"

class Magazine : public Item
{
public:
    Magazine();
    Magazine(QString n);
    QStringList getDetail() const;
};

#endif // MAGAZINE_H
