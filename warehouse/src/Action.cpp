#include "../include/Action.h"

//////////////////////////////       BaseAction           ////////////////////////////////

BaseAction::BaseAction() : errorMsg(""), status(ActionStatus::COMPLETED)
{
}

BaseAction::~BaseAction()
{
}

ActionStatus BaseAction::getStatus() const
{
    return status;
}

void BaseAction::complete()
{
    status = ActionStatus::COMPLETED;
}

void BaseAction::error(string errorMsg)
{
    status = ActionStatus::ERROR;
    errorMsg = errorMsg;
    cout << "Error: " << errorMsg << endl;
}

string BaseAction::getErrorMsg() const
{
    return errorMsg;
}

void BaseAction::setStatus(ActionStatus newStatus)
{
    status = newStatus;
}

//////////////////////////////       AddOrder           ////////////////////////////////

AddOrder::AddOrder(int id) : customerId(id) {}

AddOrder::~AddOrder()
{
}

void AddOrder::act(WareHouse &wareHouse)
{
    int distance = wareHouse.getCustomer(customerId).getCustomerDistance();
    int id = wareHouse.getCustomer(customerId).getId();
    if (id == -1 || !wareHouse.getCustomer(customerId).canMakeOrder())
    {
        this->setStatus(ActionStatus::ERROR);
        this->error("Cannot place this order");
    }
    else
    {
        int counter = wareHouse.getOrderCounter();
        Order *order = new Order(counter, this->customerId, distance);
        wareHouse.getCustomer(customerId).addOrder(order->getId());
        wareHouse.addOrder(order);
        string username = wareHouse.getCustomer(customerId).getName();
        complete();
    }
}

string AddOrder::toString() const
{
    ActionStatus status = getStatus();
    string status1 = ((status == ActionStatus::COMPLETED) ? "COMPLETED" : "ERROR");
    string ans = "order " + std::to_string(customerId) + " " + status1;
    return ans;
}

AddOrder *AddOrder::clone() const
{
    return new AddOrder(*this);
}

//////////////////////////////       AddCustomer           ////////////////////////////////

AddCustomer::AddCustomer(const string &customerName, const string &customerType, int distance, int maxOrders)

    : customerName(customerName),
      customerType((customerType == "Civilian") ? CustomerType::Civilian : CustomerType::Soldier),
      distance(distance),
      maxOrders(maxOrders)
{
}

AddCustomer::~AddCustomer()
{
}

void AddCustomer::act(WareHouse &wareHouse)
{
    if ((customerType != CustomerType::Civilian && customerType != CustomerType::Soldier) || distance <= 0 || maxOrders <= 0)
    {
        setStatus(ActionStatus::ERROR);
        error("Cannot add this customer");
    }

    if (customerType == CustomerType::Civilian)
    {
        CivilianCustomer *customer = new CivilianCustomer(wareHouse.getcustomercounter(), customerName, distance, maxOrders);
        wareHouse.addcustomer(customer);
        complete();
    }
    else
    {
        SoldierCustomer *customer = new SoldierCustomer(wareHouse.getcustomercounter(), customerName, distance, maxOrders);
        wareHouse.addcustomer(customer);
        complete();
    }
}

AddCustomer *AddCustomer::clone() const
{
    return new AddCustomer(*this);
}

string AddCustomer::toString() const
{
    string status1 = (getStatus() == ActionStatus::COMPLETED) ? "COMPLETED" : "ERROR";
    std::string typeString = (customerType == CustomerType::Civilian) ? "Civilian" : "Soldier";
    return "addCustomer " + customerName + " " + typeString + " " + std::to_string(distance) + " " + std::to_string(maxOrders) + " " + status1;
}

//////////////////////////////       PrintOrderStatus           ////////////////////////////////

PrintOrderStatus::PrintOrderStatus(int id) : orderId(id)
{
}

PrintOrderStatus::~PrintOrderStatus()
{
}

void PrintOrderStatus::act(WareHouse &wareHouse)
{
    Order order = wareHouse.getOrder(orderId);
    if (order.getId() == -1)
    {
        setStatus(ActionStatus::ERROR);
        error("order doesn't exist");
        std::cout << getErrorMsg() << std::endl;
    }
    else
    {
        std::cout << "OrderId: " << order.getId() << std::endl;

        std::string status;
        switch (order.getStatus())
        {
        case OrderStatus::PENDING:
            status = "Pending";
            break;
        case OrderStatus::COLLECTING:
            status = "Collecting";
            break;
        case OrderStatus::DELIVERING:
            status = "Delivering";
            break;
        case OrderStatus::COMPLETED:
            status = "Completed";
            break;
        }
        std::cout << "OrderStatus: " << status << std::endl;

        std::cout << "CustomerID: " << order.getCustomerId() << std::endl;

        int collectorId = order.getCollectorId();
        if (collectorId == NO_VOLUNTEER)
        {
            std::cout << "Collector: None" << std::endl;
        }
        else
        {
            std::cout << "Collector: " << collectorId << std::endl;
        }

        int driverId = order.getDriverId();
        if (driverId == NO_VOLUNTEER)
        {
            std::cout << "Driver: None" << std::endl;
        }
        else
        {
            std::cout << "Driver: " << driverId << std::endl;
        }
        complete();
    }
}

PrintOrderStatus *PrintOrderStatus::clone() const
{
    return new PrintOrderStatus(*this);
}

string PrintOrderStatus::toString() const
{
    string status1;
    (getStatus() == ActionStatus::COMPLETED) ? status1 = "COMPLETED" : status1 = "ERROR";
    return "orderStatus " + std::to_string(orderId) + " " + status1;
}

//////////////////////////////       PrintCustomerStatus           ////////////////////////////////

PrintCustomerStatus::PrintCustomerStatus(int id) : customerId(id)
{
}

PrintCustomerStatus::~PrintCustomerStatus()
{
}

void PrintCustomerStatus::act(WareHouse &wareHouse)
{
    Customer *customer = &wareHouse.getCustomer(customerId);
    if (customer->getId() == -1)
    {
        setStatus(ActionStatus::ERROR);
        error("Customer doesn't exist");
        std::cout << getErrorMsg() << std::endl;
    }
    else
    {
        std::cout << "CustomerID: " << customer->getId() << std::endl;

        for (auto &order : wareHouse.getCustomer(customerId).getOrdersIds())
        {
            cout << "OrderId: " << order << endl;
            cout << "OrderStatus: " << wareHouse.getOrder(order).orderStatusToString() << endl;
        }

        int numOrdersLeft = customer->getMaxOrders() - customer->getOrdersIds().size();
        std::cout << "numOrdersLeft: " << numOrdersLeft << std::endl;

        complete();
    }
}

PrintCustomerStatus *PrintCustomerStatus::clone() const
{
    return new PrintCustomerStatus(*this);
}

string PrintCustomerStatus::toString() const
{
    std::string statusString = (getStatus() == ActionStatus::COMPLETED) ? "COMPLETED" : "ERROR";
    return "customerStatus " + std::to_string(customerId) + " " + statusString;
}

//////////////////////////////       PrintVolunteerStatus           ////////////////////////////////

PrintVolunteerStatus::PrintVolunteerStatus(int id) : volunteerId(id)
{
}

PrintVolunteerStatus::~PrintVolunteerStatus()
{
}

void PrintVolunteerStatus::act(WareHouse &wareHouse)
{
    Volunteer *volunteer = &wareHouse.getVolunteer(volunteerId);
    if (volunteer->getId() == -1)
    {
        setStatus(ActionStatus::ERROR);
        error("Volunteer doesn't exist");
        std::cout << getErrorMsg() << std::endl;
    }
    else
    {
        std::cout << volunteer->toString() << std::endl;
        complete();
    }
}

PrintVolunteerStatus *PrintVolunteerStatus::clone() const
{
    return new PrintVolunteerStatus(*this);
}

string PrintVolunteerStatus::toString() const
{
    std::string statusString = (getStatus() == ActionStatus::COMPLETED) ? "COMPLETED" : "ERROR";
    return "volunteerStatus " + std::to_string(volunteerId) + " " + statusString;
}

//////////////////////////////       PrintActionsLog           ////////////////////////////////

PrintActionsLog::PrintActionsLog() {}

PrintActionsLog::~PrintActionsLog()
{
}

PrintActionsLog *PrintActionsLog::clone() const
{
    return new PrintActionsLog(*this);
}

void PrintActionsLog::act(WareHouse &wareHouse)
{
    for (auto &action : wareHouse.getActions())
    {
        std::cout << action->toString() << std::endl;
    }

    complete();
}

string PrintActionsLog::toString() const
{
    std::string statusString = (getStatus() == ActionStatus::COMPLETED) ? "COMPLETED" : "ERROR";
    return "PrintActionsLog " + statusString;
}

//////////////////////////////       SimulateStep           ////////////////////////////////

SimulateStep::SimulateStep(int numOfSteps) : numOfSteps(numOfSteps)
{
}

SimulateStep::~SimulateStep()
{
}

void SimulateStep::act(WareHouse &wareHouse)
{
    if (numOfSteps <= 0)
    {
        setStatus(ActionStatus::ERROR);
        error("num of steps must be positive");
        std::cout << getErrorMsg() << std::endl;
    }

    for (int step = 0; step < numOfSteps; ++step)
    {
        // Retrieve the vectors once for the iteration
        vector<Order *> pendings = wareHouse.getPendingOrdervector();
        vector<Volunteer *> voulnteers = wareHouse.getVolunteervector();

        // Iterate through pending orders
        for (std::size_t i = 0; i < wareHouse.getPendingOrdervector().size() && wareHouse.getPendingOrdervector().size() > 0;)
        {
            Order *order = wareHouse.getPendingOrdervector()[i];
            bool findVolenteer = false;

            // Iterate through volunteers to find one for the order
            for (auto &volunteer : voulnteers)
            {
                if (volunteer->canTakeOrder(*order))
                {
                    findVolenteer = true;
                    volunteer->acceptOrder(*order);

                    // Transfer the order to in progress
                    wareHouse.moveFromPendingToinProcess(order);

                    string type = volunteer->volenteerType();

                    // Update status based on whether a driver is assigned
                    if (type == ("LimitedCollectorVolunteer") || type == ("CollectorVolunteer"))
                    {
                        order->setStatus(OrderStatus::COLLECTING);
                        order->setCollectorId(volunteer->getId());
                        break;
                    }
                    else
                    {
                        order->setStatus(OrderStatus::DELIVERING);
                        order->setDriverId(volunteer->getId());
                        break;
                    }
                }
            }

            // Increment 'i' only if no volunteer can take the order
            if (!findVolenteer)
                i++;
        }

        // Simulate a step for each volunteer
        for (auto &voulnteer : voulnteers)
        {
            voulnteer->step();
        }

        // Check completed orders and move them to the appropriate vectors
        for (auto &volunteer : voulnteers)
        {
            if (volunteer->isBusy())
            {
                if (volunteer->getdone())
                {
                    int orderid = volunteer->getActiveOrderId();

                    // Use a pointer to the order to avoid accessing a deleted order
                    Order *order = &wareHouse.getOrder(orderid);

                    if (order->getStatus() == OrderStatus::COLLECTING)
                    {
                        wareHouse.moveFrominProcessToPending(order);
                        wareHouse.releasevoulnteer(order->getCollectorId());
                    }
                    else
                    {
                        wareHouse.moveFrominProcessToCompleted(order);
                        wareHouse.releasevoulnteer(order->getDriverId());
                        order->setStatus(OrderStatus::COMPLETED);
                    }
                }
            }
        }

        // Delete volunteers with no orders left
        for (std::size_t j = 0; j < wareHouse.getVolunteervector().size() && wareHouse.getVolunteervector().size() > 0;)
        {
            Volunteer *volunteer = wareHouse.getVolunteervector()[j];
            if (!volunteer->hasOrdersLeft() && !volunteer->isBusy())
            {
                wareHouse.moveftomvolunteerstodelet(volunteer);
            }
            else
                j++;
        }
    }
}

SimulateStep *SimulateStep::clone() const
{
    return new SimulateStep(*this);
}

string SimulateStep::toString() const
{
    std::string statusString = (getStatus() == ActionStatus::COMPLETED) ? "COMPLETED" : "ERROR";
    return "simulateStep " + std::to_string(numOfSteps) + " " + statusString;
}

//////////////////////////////       Close           ////////////////////////////////

Close::Close()
{
}

Close::~Close()
{
}

void Close::act(WareHouse &wareHouse)
{
    for (auto &order : wareHouse.getPendingOrdervector())
    {
        std::cout << order->toString() << std::endl;
    }

    for (auto &order : wareHouse.getinProcessOrdersvector())
    {
        std::cout << order->toString() << std::endl;
    }

    for (auto &order : wareHouse.getCompletedOrdersvector())
    {
        std::cout << order->toString() << std::endl;
    }

    wareHouse.close();
}

Close *Close::clone() const
{
    return new Close(*this);
}

string Close::toString() const
{
    return "close";
}

//////////////////////////////       BackupWareHouse           ////////////////////////////////

BackupWareHouse::BackupWareHouse()
{
}

BackupWareHouse::~BackupWareHouse()
{
}

void BackupWareHouse::act(WareHouse &wareHouse)
{
    wareHouse.backupHelp();
    complete();
}

BackupWareHouse *BackupWareHouse::clone() const
{
    return new BackupWareHouse(*this);
}

string BackupWareHouse::toString() const
{
    std::string statusString = (getStatus() == ActionStatus::COMPLETED) ? "COMPLETED" : "ERROR";
    return "backup " + statusString;
}

//////////////////////////////       RestoreWareHouse           ////////////////////////////////

RestoreWareHouse::RestoreWareHouse()
{
}

RestoreWareHouse::~RestoreWareHouse()
{
}
void RestoreWareHouse::act(WareHouse &wareHouse)
{
    if (backup == nullptr)
    {
        setStatus(ActionStatus::ERROR);
        error("No backup available");
        return;
    }

    wareHouse.restoreHelp();
    complete();
}

RestoreWareHouse *RestoreWareHouse::clone() const
{
    return new RestoreWareHouse(*this);
}

string RestoreWareHouse::toString() const
{
    std::string statusString = (getStatus() == ActionStatus::COMPLETED) ? "COMPLETED" : "ERROR";
    return "restore " + statusString;
}