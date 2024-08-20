#ifndef CUSTOMERS_H
#define CUSTOMERS_H

#include <QStringList>

class Customers
{
public:
    static Customers *getCustomersInstance();
    static void deleteCustomersInstance();
    bool addCustomer(QString customerName);
    QStringList getCustomerList() const;

private:
    Customers();
    static Customers *onlyInstance;
    QStringList customerList;
};

#endif // CUSTOMERS_H
