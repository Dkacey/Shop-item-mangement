#include "book.h"

Book::Book(): Item()
{
}

Book::Book(QString n): Item{n}
{
}

QStringList Book::getDetail() const
{
    QStringList s{name, "B"};
    return s;
}
