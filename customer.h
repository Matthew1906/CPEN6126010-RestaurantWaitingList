#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <QString>

struct Customer
{
    int id;
    int numOfPeople;
    QString name, timestamp;
};

#endif // CUSTOMER_H
