#ifndef BOOK_H
#define BOOK_H

#include "item.h"
#include <QStringList>

class Book : public Item
{
public:
    Book();
    Book(QString n);
    QStringList getDetail() const;
};

#endif // BOOK_H
