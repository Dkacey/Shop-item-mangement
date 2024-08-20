#ifndef TREEMODELTOXML_H
#define TREEMODELTOXML_H
#include <QByteArray>

class TreeItem;

class TreeModelToXml
{
public:
    TreeModelToXml();
    QByteArray getXml(TreeItem *root);
};

#endif // TREEMODELTOXML_H
