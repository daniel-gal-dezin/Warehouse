#pragma once
#include <string>
#include <vector>
#include "../include/Order.h"
#include "../include/Customer.h"
#include "../include/Volunteer.h"
#include "../include/Parser.h"
#include "../include/Action.h"
#include <iterator>
class BaseAction;


using namespace std;
#include <algorithm> // for std::find
#include <iostream>
class WareHouse;

extern WareHouse* backup;

// Warehouse responsible for Volunteers, Customers Actions, and Orders.


class WareHouse {

    public:
        WareHouse(const string &configFilePath);//constructor
        void start();
        void addOrder(Order* order);
        void addAction(BaseAction* action);
        Customer &getCustomer(int customerId) const;
        Volunteer &getVolunteer(int volunteerId) const;
        Order &getOrder(int orderId) const;
        const vector<BaseAction*> &getActions() const;
        void close();
        void open();
        

        //our function
        void initializeFromConfig(const string &configFilePath);
        int getOrderCounter() const; // add const
        void addordercounter();
        void addcustomercounters();
        void addvolunteercounter();
        void addcustomer(Customer* customer);
        void addVolunteer(Volunteer* volunteer);
        int getcustomercounter() const;//add const
        const vector<Order*>& getPendingOrdervector() const;
        const vector<Order*>& getinProcessOrdersvector() const;
        const vector<Order*>& getCompletedOrdersvector() const;
        const vector<Volunteer*>& getVolunteervector() const;
        vector<Volunteer*>& getdeletevector() ;
        void moveFromPendingToinProcess(Order* order);
        void moveFrominProcessToCompleted(Order* order);
        void moveFrominProcessToPending(Order* order);
        void moveftomvolunteerstodelet(Volunteer* volunteer);
        void releasevoulnteer(int volunteerid);
        bool getIsOpen() const;//add here function
        int getVolunteerCounter() const; //add function
        void backupHelp();
        void restoreHelp();






        
        //role of 5 function adder
        WareHouse(const WareHouse& other);//copy constructor
        WareHouse& operator=(const WareHouse& other); //Copy assigement oprator
        WareHouse(WareHouse&& other);//Move Counstructor
        WareHouse& operator=(const WareHouse&& other); //Move assigement oprator
        ~WareHouse();//distructor










    private:
        bool isOpen;
        vector<BaseAction*> actionsLog;
        vector<Volunteer*> volunteers;
        vector<Order*> pendingOrders;
        vector<Order*> inProcessOrders;
        vector<Order*> completedOrders;
        vector<Customer*> customers;
        int customerCounter; //For assigning unique customer IDs
        int volunteerCounter; //For assigning unique volunteer IDs
        int orderCounter;// addad by us
        vector<Volunteer*> todelete;
        
};