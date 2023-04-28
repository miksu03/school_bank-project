#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H
#include <../pankitinDLL/account.h>
#include <../pankitinDLL/customers.h>
#include <../pankitinDLL/card.h>
#include <../pankitinDLL/events.h>

class CardObject{
public:
    int idCard;
    QString CardNumber;
    QString pinCode;
    QString password;
    int Account_id;
    int Customer_idCustomer;
};

class EventObject{
public:
    int id;
    int idAccount;
    double value;
    QString date;
};

class AccountObject{
public:
    int id;
    double value;
    double maxCredit;
    int idCard;
    int idCustomer;
};

class CustomerObject{
public:
    int idCustomer;
    QString name;
    QString surName;
};

class DatabaseManager : public QObject
{
public:
    DatabaseManager();
    void add (EventObject event, int id);
    void update (AccountObject account);
    QMap<int, CardObject> listOfCards;
    QMap<int, EventObject> listOfEvents;
    QMap<int, AccountObject> listOfAccounts;
    QMap<int, CustomerObject> listOfCustomers;
    int cardFindbyCardNumber(QString cardNumber){
        for(int i = 0; i < listOfCards.count();i++){
            if(listOfCards[i].CardNumber == cardNumber){
                return listOfCards[i].idCard;
            }
        }
        return -1;
    }
private slots:
    void receiveCards (const QJsonArray data);
    void receiveEvents (const QJsonArray data);
    void receiveAccounts (const QJsonArray data);
    void receiveCustomers (const QJsonArray data);
private:
    Account acc;
    Customers cus;
    Events eve;
    Card car;
};

#endif // DATABASEMANAGER_H
