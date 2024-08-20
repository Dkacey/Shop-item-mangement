#include "treemodeltoxml.h"
#include "treeitem.h"
#include <QXmlStreamWriter>
#include <QXmlStreamAttribute>
#include <QBuffer>

TreeModelToXml::TreeModelToXml()
{
}

QByteArray TreeModelToXml::getXml(TreeItem *root)
{
    QXmlStreamWriter writer;
    QBuffer buffer;
    buffer.open(QBuffer::WriteOnly);
    writer.setDevice(&buffer);
    writer.setAutoFormatting(true);
    writer.writeStartDocument();
    writer.writeStartElement("ModelData");                                  // root element

    for (int i=0; i<root->childCount(); i++)                // loop through all customers
    {
        TreeItem *itemCustomer = root->child(i);
        writer.writeStartElement("customer");                               // customer element
        QXmlStreamAttribute attrName("name", itemCustomer->data(0).toString());
        writer.writeAttribute(attrName);

        for (int j=0; j<itemCustomer->childCount(); j++)    // loop through all dates for this customer
        {
            TreeItem *itemDate = itemCustomer->child(j);
            writer.writeStartElement("transaction");                        // transaction element
            QXmlStreamAttribute attrTrans("date", itemDate->data(0).toString());
            writer.writeAttribute(attrTrans);

            for (int k=0; k<itemDate->childCount(); k++)    // loop through each line item for this transaction
            {
                TreeItem *itemLineitem = itemDate->child(k);
                writer.writeStartElement("lineitem");                       // lineitem element

                QXmlStreamAttribute nameAttr("name", itemLineitem->data(0).toString());
                writer.writeAttribute(nameAttr);

                QXmlStreamAttribute typeAttr("type", itemLineitem->data(1).toString());
                writer.writeAttribute(typeAttr);

                QXmlStreamAttribute quantityAttr("quantity", itemLineitem->data(2).toString());
                writer.writeAttribute(quantityAttr);

                writer.writeEndElement();                                   // end of lineitem element
            }

            writer.writeEndElement();                                       // end of transaction element
        }
        writer.writeEndElement();                                           // end of customer element

    }

    writer.writeEndElement();                                               // end of root element

    writer.writeEndDocument();

    buffer.close();
    return buffer.buffer();
}
