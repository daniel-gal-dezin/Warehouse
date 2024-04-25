// WareHouse.cpp
#include "../include/WareHouse.h"
#include "../include/Action.h"
using namespace std;
#include <vector> // for std::vector
#include <iostream>

Order erorder(-1, -1, -1);
SoldierCustomer ercustomer(-1, "nir", -1, -1);
DriverVolunteer ervolunteer(-1, "menchik", -1, -1);

WareHouse::WareHouse(const string &configFilePath)
    : isOpen(false),
      actionsLog(),
      volunteers(),
      pendingOrders(),
      inProcessOrders(),
      completedOrders(),
      customers(),
      customerCounter(0),
      volunteerCounter(0),
      orderCounter(0),
      todelete()
{
    string path = "/home/users/bsc/idanaza/Skeleton/configFileExample.txt";
    Parser::parseConfigFile(path, *this);
}

void WareHouse::start()
{
    isOpen = true;
    std::cout << "Warehouse is open!" << std::endl;
    // std::cout << "Enter command (type 'help' for available commands): ";

    std::string inputLine;
    while (isOpen)
    {
        std::getline(std::cin, inputLine);
        std::istringstream iss(inputLine);
        std::string command;
        iss >> command;

        if (command == "help")
        {
            std::cout << "Available commands: help, order<id>, step<num of steps>, customer<customer_name> <customer_type> <customer_distance> <max_orders>, orderStatus<order_id>, volunteerStatus<volunteer_id>, customerStatus<customer_id>, log, close, backup, restore, exit" << std::endl;
        }
        else if (command == "order")
        {
            int customerID;
            if (iss >> customerID)
            {
                AddOrder *order = new AddOrder(customerID);
                order->act(*this);
                addAction(order);
            }
        }
        else if (command == "step")
        {
            int numOfSteps;
            if (iss >> numOfSteps)
            {

                SimulateStep *step = new SimulateStep(numOfSteps);
                step->act(*this);
                addAction(step);
            }
        }
        else if (command == "customer")
        {
            std::string customerName, customerType;
            int customerDistance, maxOrders;
            if (iss >> customerName >> customerType >> customerDistance >> maxOrders)
            {

                AddCustomer *customer = new AddCustomer(customerName, customerType, customerDistance, maxOrders);
                customer->act(*this);
                addAction(customer);
            }
            else
            {
                std::cout << "Error: Invalid customer parameters" << std::endl;
            }
        }
        else if (command == "orderStatus")
        {
            int orderId;
            if (iss >> orderId)
            {

                PrintOrderStatus *orderStatus = new PrintOrderStatus(orderId);
                orderStatus->act(*this);
                addAction(orderStatus);
            }
        }
        else if (command == "volunteerStatus")
        {
            int volunteerId;
            if (iss >> volunteerId)
            {

                PrintVolunteerStatus *volunteerStatus = new PrintVolunteerStatus(volunteerId);
                volunteerStatus->act(*this);
                addAction(volunteerStatus);
            }
        }
        else if (command == "customerStatus")
        {
            int customerId;
            if (iss >> customerId)
            {

                PrintCustomerStatus *customerStatus = new PrintCustomerStatus(customerId);
                customerStatus->act(*this);
                addAction(customerStatus);
            }
        }
        else if (command == "exit")
        {
            isOpen = false;
        }
        else if (command == "log")
        {

            PrintActionsLog *log = new PrintActionsLog();
            log->act(*this);
            addAction(log);
        }
        else if (command == "close")
        {
            Close *close = new Close();
            close->act(*this);
            addAction(close);
            
        }
        else if (command == "backup")
        {

            BackupWareHouse *backup = new BackupWareHouse();
            backup->act(*this);
            addAction(backup);
        }
        else if (command == "restore")
        {

            RestoreWareHouse *restore = new RestoreWareHouse();
            restore->act(*this);
            addAction(restore);
        }
        else if (command == "exit")
        {
            isOpen = false;
        }
        else
        {
            std::cout << "Unknown command. Type 'help' for available commands." << std::endl;
        }
    }
    // Ensure to perform cleanup before exiting, if necessary
}

void WareHouse::addOrder(Order *order)
{
    pendingOrders.push_back(order);
    order->setStatus(OrderStatus::PENDING);
    orderCounter++;
}

Customer &WareHouse::getCustomer(int customerId) const
{
    for (auto &customer : customers)
    {
        if (customer->getId() == customerId)
        {
            return *customer;
        }
    }
    return ercustomer;
}

Volunteer &WareHouse::getVolunteer(int volunteerId) const
{
    for (auto &volunteer : volunteers)
    {
        if (volunteer->getId() == volunteerId)
        {
            return *volunteer;
        }
    }
    return ervolunteer;
}

Order &WareHouse::getOrder(int orderId) const
{
    for (auto &order : pendingOrders)
    {
        if (order->getId() == orderId)
        {
            return *order;
        }
    }
    for (auto &order : inProcessOrders)
    {
        if (order->getId() == orderId)
        {
            return *order;
        }
    }
    for (auto &order : completedOrders)
    {
        if (order->getId() == orderId)
        {
            return *order;
        }
    }
    return erorder;
}

const vector<BaseAction *> &WareHouse::getActions() const
{
    return actionsLog;
}

void WareHouse::close()
{
    isOpen = false;
}

void WareHouse::open()
{
    isOpen = true;
}

int WareHouse::getOrderCounter() const
{
    return orderCounter;
}

void WareHouse::addordercounter()
{
    orderCounter++;
}

void WareHouse::addcustomercounters()
{
    customerCounter++;
}

void WareHouse::addvolunteercounter()
{
    volunteerCounter++;
}

void WareHouse::addcustomer(Customer *customer)
{
    customers.push_back(customer);
    customerCounter++;
}

void WareHouse::addVolunteer(Volunteer *volunteer)
{
    volunteers.push_back(volunteer);
    volunteerCounter++;
}

void WareHouse::addAction(BaseAction *action)
{
    actionsLog.push_back(action);
}

int WareHouse::getcustomercounter() const
{
    return customerCounter;
}

const vector<Order *> &WareHouse::getPendingOrdervector() const
{
    return pendingOrders;
}

const vector<Order *> &WareHouse::getCompletedOrdersvector() const
{
    return completedOrders;
}

const vector<Order *> &WareHouse::getinProcessOrdersvector() const
{
    return inProcessOrders;
}

const vector<Volunteer *> &WareHouse::getVolunteervector() const
{
    return volunteers;
}

void WareHouse::releasevoulnteer(int volunteerid)
{
    for (auto &volunteer : volunteers)
    {
        if (volunteer->getId() == volunteerid)
        {
            volunteer->setcompletedOrderId(volunteer->getActiveOrderId());
            volunteer->setactiveOrderId(NO_ORDER);
        }
    }
}

void WareHouse::moveFromPendingToinProcess(Order *order)
{
    auto itPending = find(pendingOrders.begin(), pendingOrders.end(), order);

    if (itPending != pendingOrders.end())
    {
        pendingOrders.erase(itPending);

        auto itInProcess = find(inProcessOrders.begin(), inProcessOrders.end(), order);

        if (itInProcess == inProcessOrders.end())
        {
            inProcessOrders.push_back(order);
        }
        else
        {

            std::cerr << "Error: Order already in inProcessOrders (moveFromPendingToinProcess)" << std::endl;
        }
    }
    else
    {

        std::cerr << "Error: Order not found in pendingOrders (moveFromPendingToinProcess)" << std::endl;
    }
}

void WareHouse::moveFrominProcessToCompleted(Order *order)
{
    auto itInProcess = find(inProcessOrders.begin(), inProcessOrders.end(), order);

    if (itInProcess != inProcessOrders.end())
    {
        inProcessOrders.erase(itInProcess);

        auto itCompleted = find(completedOrders.begin(), completedOrders.end(), order);

        if (itCompleted == completedOrders.end())
        {
            completedOrders.push_back(order);
        }
        else
        {

            std::cerr << "Error: Order already in completedOrders (moveFrominProcessToCompleted)" << std::endl;
        }
    }
    else
    {

        std::cerr << "Error: Order not found in inProcessOrders (moveFrominProcessToCompleted)" << std::endl;
    }
}

void WareHouse::moveFrominProcessToPending(Order *order)
{
    auto itInProcess = find(inProcessOrders.begin(), inProcessOrders.end(), order);

    if (itInProcess != inProcessOrders.end())
    {
        inProcessOrders.erase(itInProcess);

        auto itPending = find(pendingOrders.begin(), pendingOrders.end(), order);

        if (itPending == pendingOrders.end())
        {
            pendingOrders.push_back(order);
        }
        else
        {

            std::cerr << "Error: Order already in pendingOrders (moveFrominProcessToPending)" << std::endl;
        }
    }
    else
    {

        std::cerr << "Error: Order not found in inProcessOrders (moveFrominProcessToPending)" << std::endl;
    }
}

bool WareHouse::getIsOpen() const
{
    return isOpen;
}

int WareHouse::getVolunteerCounter() const
{
    return volunteerCounter;
}

void WareHouse::backupHelp()
{
    if (backup != nullptr)
    {
        *backup = *this;
    }
    else
        backup = new WareHouse(*this);
}

void WareHouse::restoreHelp()
{

    *this = *backup;
}

vector<Volunteer *> &WareHouse::getdeletevector()
{
    return todelete;
}
void WareHouse::moveftomvolunteerstodelet(Volunteer *volunteer)
{
    auto todel = find(volunteers.begin(), volunteers.end(), volunteer);
    volunteers.erase(todel);
    todelete.push_back(volunteer);
}

//////////////////////////////////////////////////////role of 5//////////////////////////////////////////////////////////////////////

WareHouse::WareHouse(const WareHouse &other)
    : isOpen(other.getIsOpen()),
      actionsLog(),      // Initializing the vector
      volunteers(),      // Initializing the vector
      pendingOrders(),   // Initializing the vector
      inProcessOrders(), // Initializing the vector
      completedOrders(), // Initializing the vector
      customers(),       // Initializing the vector
      customerCounter(other.getcustomercounter()),
      volunteerCounter(other.getVolunteerCounter()),
      orderCounter(other.getOrderCounter()),
      todelete()
{
    for (auto action : other.actionsLog)
        actionsLog.push_back(action->clone());
    for (auto orderpending : other.pendingOrders)
        pendingOrders.push_back(orderpending->clone());
    for (auto inprocess : other.inProcessOrders)
        inProcessOrders.push_back(inprocess->clone());
    for (auto completeOrders : other.completedOrders)
        completedOrders.push_back(completeOrders->clone());
    for (auto customer : other.customers)
        customers.push_back(customer->clone());
    for (auto volunteer : other.volunteers)
        volunteers.push_back(volunteer->clone());
    for (auto todel : other.todelete)
        todelete.push_back(todel->clone());
}

WareHouse &WareHouse::operator=(const WareHouse &other) {
    // Guard against self-assignment
    if (this != &other) {
        // Clean up existing resources
        for (auto* action : actionsLog) {
            delete action;
        }
        actionsLog.clear();

        for (auto* order : pendingOrders) {
            delete order;
        }
        pendingOrders.clear();

        for (auto* order : inProcessOrders) {
            delete order;
        }
        inProcessOrders.clear();

        for (auto* order : completedOrders) {
            delete order;
        }
        completedOrders.clear();

        for (auto* customer : customers) {
            delete customer;
        }
        customers.clear();

        for (auto* volunteer : volunteers) {
            delete volunteer;
        }
        volunteers.clear();

        for (auto* todel : todelete) {
            delete todel;
        }
        todelete.clear();

        // Copy from other
        isOpen = other.isOpen;
        customerCounter = other.customerCounter;
        volunteerCounter = other.volunteerCounter;
        orderCounter = other.orderCounter;

        for (auto* action : other.actionsLog) {
            actionsLog.push_back(action->clone()); 
        }

        for (auto* order : other.pendingOrders) {
            pendingOrders.push_back(order->clone()); 
        }

        for (auto* order : other.inProcessOrders) {
            inProcessOrders.push_back(order->clone());
        }

        for (auto* order : other.completedOrders) {
            completedOrders.push_back(order->clone());
        }

        for (auto* customer : other.customers) {
            customers.push_back(customer->clone()); 
        }

        for (auto* volunteer : other.volunteers) {
            volunteers.push_back(volunteer->clone()); 
        }

        for (auto* todel : other.todelete) {
            todelete.push_back(todel->clone()); 
        }
    }
    
    return *this;
}
WareHouse::WareHouse(WareHouse &&other)
    : isOpen(other.getIsOpen()),
      actionsLog(std::move(other.actionsLog)),
      volunteers(std::move(other.volunteers)),
      pendingOrders(std::move(other.pendingOrders)),
      inProcessOrders(std::move(other.inProcessOrders)),
      completedOrders(std::move(other.completedOrders)),
      customers(std::move(other.customers)),
      customerCounter(other.getcustomercounter()),
      volunteerCounter(other.getVolunteerCounter()),
      orderCounter(other.getOrderCounter()),
      todelete(other.getdeletevector())
{
    // Set the moved-from object's pointers to nullptr
    other.actionsLog.clear();
    other.volunteers.clear();
    other.pendingOrders.clear();
    other.inProcessOrders.clear();
    other.completedOrders.clear();
    other.customers.clear();
    todelete.clear();
}

WareHouse &WareHouse::operator=(const WareHouse &&other) // Move assign operator
{
    if (this != &other)
    {
        // delete current resources
       for (auto* action : actionsLog) {
            delete action;
        }
        actionsLog.clear();

        for (auto* order : pendingOrders) {
            delete order;
        }
        pendingOrders.clear();

        for (auto* order : inProcessOrders) {
            delete order;
        }
        inProcessOrders.clear();

        for (auto* order : completedOrders) {
            delete order;
        }
        completedOrders.clear();

        for (auto* customer : customers) {
            delete customer;
        }
        customers.clear();

        for (auto* volunteer : volunteers) {
            delete volunteer;
        }
        volunteers.clear();

        for (auto* todel : todelete) {
            delete todel;
        }
        todelete.clear();

        // Transfer the ownership of resources from 'other'
        isOpen = other.isOpen;
        customerCounter = other.customerCounter;
        volunteerCounter = other.volunteerCounter;
        orderCounter = other.orderCounter;
        actionsLog = std::move(other.actionsLog);
        pendingOrders = std::move(other.pendingOrders);
        inProcessOrders = std::move(other.inProcessOrders);
        completedOrders = std::move(other.completedOrders);
        customers = std::move(other.customers);
        volunteers = std::move(other.volunteers);
        todelete = std::move(other.todelete);
    }

    return *this;
}

WareHouse::~WareHouse()
{
    for (BaseAction *action : actionsLog)
    {
        if (action != nullptr)
        {
            delete action;
        }
    }
    actionsLog.clear();

    for (Volunteer *volunteer : volunteers)
    {
        if (volunteer != nullptr)
        {
            delete volunteer;
        }
    }
    volunteers.clear();

    for (Order *order : pendingOrders)
    {
        if (order != nullptr)
        {
            delete order;
        }
    }
    pendingOrders.clear();

    for (Order *order : inProcessOrders)
    {
        if (order != nullptr)
        {
            delete order;
        }
    }
    inProcessOrders.clear();

    for (Order *order : completedOrders)
    {
        if (order != nullptr)
        {
            delete order;
        }
    }
    completedOrders.clear();

    for (Customer *customer : customers)
    {
        if (customer != nullptr)
        {
            delete customer;
        }
    }
    customers.clear();
    for (Volunteer *todel : todelete)
    {
        if (todel != nullptr)
        {
            delete todel;
        }
    }
    todelete.clear();
}