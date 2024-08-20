#include "magazine.h"

Magazine::Magazine(): Item()
{
}

Magazine::Magazine(QString n): Item{n}
{
}

QStringList Magazine::getDetail() const
{
    QStringList s{name, "M"};
    return s;
}
