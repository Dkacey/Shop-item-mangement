#include "broadcast.h"
#include "treeitem.h"
#include "treemodeltoxml.h"
#include <QUdpSocket>

Broadcast::Broadcast(TreeItem *root): modelRoot{root}
{
}

void Broadcast::run()
{
    // get XML
    TreeModelToXml xml;
    QByteArray xmlStr{xml.getXml(modelRoot)};

    // broadcast XML
    QUdpSocket *socket{new QUdpSocket};
    socket->writeDatagram(xmlStr, QHostAddress::Broadcast, 45454);

    socket->deleteLater();
}
