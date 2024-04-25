#pragma once
#include "../include/WareHouse.h"
#include <string>
#include <vector>
#include "../include/Volunteer.h"
using std::string;
using std::vector;
#include <iostream>
class WareHouse;
#include <iterator>

enum class ActionStatus
{
    COMPLETED,
    ERROR
};

enum class CustomerType
{
    Soldier,
    Civilian
};

class BaseAction
{
public:
    BaseAction();
    virtual ~BaseAction();
    ActionStatus getStatus() const;
    virtual void act(WareHouse &wareHouse) = 0;
    virtual string toString() const = 0;
    virtual BaseAction *clone() const = 0;
    void setStatus(ActionStatus newStatus); 

    //add function
    string& statustostring(ActionStatus a);

protected:
    void complete();
    void error(string errorMsg);
    string getErrorMsg() const;

private:
    string errorMsg;
    ActionStatus status;
};

class SimulateStep : public BaseAction
{

public:
    SimulateStep(int numOfSteps);
    virtual ~SimulateStep();
    void act(WareHouse &wareHouse) override;
    std::string toString() const override;
    SimulateStep *clone() const override;

private:
    const int numOfSteps;
};

class AddOrder : public BaseAction
{
public:
    AddOrder(int id);
    virtual ~AddOrder();
    void act(WareHouse &wareHouse) override;
    string toString() const override;
    AddOrder *clone() const override;

private:
    const int customerId;
};

class AddCustomer : public BaseAction
{
public:
    AddCustomer(const string &customerName, const string &customerType, int distance, int maxOrders);
    virtual ~AddCustomer();
    void act(WareHouse &wareHouse) override;
    AddCustomer *clone() const override;
    string toString() const override;

private:
    const string customerName;
    const CustomerType customerType;
    const int distance;
    const int maxOrders;
};

class PrintOrderStatus : public BaseAction
{
public:
    PrintOrderStatus(int id);
    virtual ~PrintOrderStatus();
    void act(WareHouse &wareHouse) override;
    PrintOrderStatus *clone() const override;
    string toString() const override;
    

private:
    const int orderId;
};

class PrintCustomerStatus : public BaseAction
{
public:
    PrintCustomerStatus(int customerId);
    virtual ~PrintCustomerStatus();
    void act(WareHouse &wareHouse) override;
    PrintCustomerStatus *clone() const override;
    string toString() const override;

private:
    const int customerId;
};

class PrintVolunteerStatus : public BaseAction
{
public:
    PrintVolunteerStatus(int id);
    virtual ~PrintVolunteerStatus();
    void act(WareHouse &wareHouse) override;
    PrintVolunteerStatus *clone() const override;
    string toString() const override;

private:
    const int volunteerId;
};

class PrintActionsLog : public BaseAction
{
public:
    PrintActionsLog();
    virtual ~PrintActionsLog();
    void act(WareHouse &wareHouse) override;
    PrintActionsLog *clone() const override;
    string toString() const override;

private:
};

class Close : public BaseAction
{
public:
    Close();
    virtual ~Close();
    void act(WareHouse &wareHouse) override;
    Close *clone() const override;
    string toString() const override;

private:
};

class BackupWareHouse : public BaseAction
{
public:
    BackupWareHouse();
    virtual ~BackupWareHouse();
    void act(WareHouse &wareHouse) override;
    BackupWareHouse *clone() const override;
    string toString() const override;

private:
};

class RestoreWareHouse : public BaseAction
{
public:
    RestoreWareHouse();
    virtual ~RestoreWareHouse();
    void act(WareHouse &wareHouse) override;
    RestoreWareHouse *clone() const override;
    string toString() const override;

private:
};