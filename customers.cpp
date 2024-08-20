#include "customers.h"

Customers *Customers::onlyInstance = nullptr;

Customers *Customers::getCustomersInstance()
{
    if (onlyInstance == nullptr)
        onlyInstance = new Customers;
    return onlyInstance;
}

void Customers::deleteCustomersInstance()
{
    delete onlyInstance;
}

Customers::Customers()
{
}

bool Customers::addCustomer(QString customerName)
{
    if (!customerList.contains(customerName))
    {
        customerList.append(customerName);
        customerList.sort();
        return true;
    }

    return false;
}

QStringList Customers::getCustomerList() const
{
    return customerList;
}
