#include "../include/Volunteer.h"

/////////////////////////////// Volunteer implementation ///////////////////////////////////////////////////////

Volunteer::Volunteer(int id, const string &name)
    : completedOrderId(NO_ORDER),
      activeOrderId(NO_ORDER),
      done(false),
      id(id),
      name(name)
{
}

Volunteer::~Volunteer()
{
}
void Volunteer::setdone(bool set)
{
    done = set;
}

void Volunteer::setcompletedOrderId(int id)
{
    completedOrderId = id;
}

void Volunteer::setactiveOrderId(int id)
{
    activeOrderId = id;
}

int Volunteer::getId() const
{
    return id;
}

const string &Volunteer::getName() const
{
    return name;
}

int Volunteer::getActiveOrderId() const
{
    return activeOrderId;
}

int Volunteer::getCompletedOrderId() const
{
    return completedOrderId;
}

bool Volunteer::isBusy() const
{
    return activeOrderId != NO_ORDER; // if activeorder is different from no order the volunteer is busy
}

/////////////////////////////// CollectorVolunteer implementation ///////////////////////////////////////////////////////

CollectorVolunteer::CollectorVolunteer(int id, const string &name, int coolDown)
    : Volunteer(id, name), coolDown(coolDown), timeLeft(0)
{
}

CollectorVolunteer::~CollectorVolunteer()
{
}

CollectorVolunteer *CollectorVolunteer::clone() const
{
    return new CollectorVolunteer(*this); // check with daniel if deep copy needed
}

void CollectorVolunteer::step()
{
    if (isBusy())
    {
        decreaseCoolDown();
    }
}

int CollectorVolunteer::getCoolDown() const
{
    return coolDown;
}

int CollectorVolunteer::getTimeLeft() const
{
    return timeLeft;
}

bool CollectorVolunteer::decreaseCoolDown()
{
    if (timeLeft > 0)
    {
        timeLeft--;
        return true;
    }
    else
    {
        setdone(true);
        return timeLeft == 0;
    }
}

bool CollectorVolunteer::hasOrdersLeft() const
{
    return true; // not limited so always has order left
}

bool CollectorVolunteer::canTakeOrder(const Order &order) const
{
    return !isBusy() && (order.getStatus() == OrderStatus::PENDING); // Collector can take an order if not busy
}

void CollectorVolunteer::acceptOrder(const Order &order)
{
    activeOrderId = order.getId();
    timeLeft = coolDown;
}

bool CollectorVolunteer::getdone()
{
    return timeLeft == 0;
}

string CollectorVolunteer::volenteerType()
{
    return "CollectorVolunteer";
}

string CollectorVolunteer::toString() const
{
    std::string aciveOrderid = (getActiveOrderId() != NO_ORDER ? std::to_string(getActiveOrderId()) : "None");
    std::string timeLeft = (getTimeLeft() != NO_ORDER ? std::to_string(getTimeLeft()) : "None");
    return "VolunteerID: " + std::to_string(getId()) + "\n" +
           "isBusy: " + (isBusy() ? "true" : "false") + "\n" +
           "OrderID: " + aciveOrderid + "\n" +
           "timeLeft: " + timeLeft + "\n" +
           "ordersLeft: No Limit";
}

/////////////////////////////// LimitedCollectorVolunteer implementation ///////////////////////////////////////////////////////

LimitedCollectorVolunteer::LimitedCollectorVolunteer(int id, const string &name, int coolDown, int maxOrders)
    : CollectorVolunteer(id, name, coolDown), maxOrders(maxOrders), ordersLeft(maxOrders)
{
}
LimitedCollectorVolunteer::~LimitedCollectorVolunteer()
{
}
LimitedCollectorVolunteer *LimitedCollectorVolunteer::clone() const
{
    return new LimitedCollectorVolunteer(*this);
}

bool LimitedCollectorVolunteer::hasOrdersLeft() const
{
    return ordersLeft > 0;
}

bool LimitedCollectorVolunteer::canTakeOrder(const Order &order) const
{
    return hasOrdersLeft() && CollectorVolunteer::canTakeOrder(order);
}

void LimitedCollectorVolunteer::acceptOrder(const Order &order)
{
    if (LimitedCollectorVolunteer::canTakeOrder(order))
    { // need to check if needed
        CollectorVolunteer::acceptOrder(order);
        ordersLeft--;
    }
}

int LimitedCollectorVolunteer::getMaxOrders() const
{
    return maxOrders;
}

int LimitedCollectorVolunteer::getNumOrdersLeft() const
{
    return ordersLeft;
}

bool LimitedCollectorVolunteer::getdone()
{
    return getTimeLeft() == 0;
}

string LimitedCollectorVolunteer::volenteerType()
{
    return "LimitedCollectorVolunteer";
}

string LimitedCollectorVolunteer::toString() const
{
    std::string aciveOrderid = (getActiveOrderId() != NO_ORDER ? std::to_string(getActiveOrderId()) : "None");
    std::string timeLeft = (getTimeLeft() != NO_ORDER ? std::to_string(getTimeLeft()) : "None");
    std::string ordersLeft = (getMaxOrders() != NO_ORDER ? std::to_string(getNumOrdersLeft()) : "None");
    return "VolunteerID: " + std::to_string(getId()) + "\n" +
           "isBusy: " + (isBusy() ? "true" : "false") + "\n" +
           "OrderID: " + aciveOrderid + "\n" +
           "timeLeft: " + timeLeft + "\n" +
           "ordersLeft: "+ ordersLeft;
}

////////////////////////////////////////// DriverVolunteer implementation ///////////////////////////////////////////////////////

DriverVolunteer::DriverVolunteer(int id, const string &name, int maxDistance, int distancePerStep)
    : Volunteer(id, name), maxDistance(maxDistance), distancePerStep(distancePerStep), distanceLeft(0)
{
}

DriverVolunteer::~DriverVolunteer()
{
}

DriverVolunteer *DriverVolunteer::clone() const
{
    return new DriverVolunteer(*this);
}

int DriverVolunteer::getDistanceLeft() const
{
    return distanceLeft;
}

int DriverVolunteer::getMaxDistance() const
{
    return maxDistance;
}

int DriverVolunteer::getDistancePerStep() const
{
    return distancePerStep;
}

bool DriverVolunteer::decreaseDistanceLeft()
{
    if (distanceLeft > 0)
    {
        if (distanceLeft - distancePerStep <= 0)
        {
            distanceLeft = 0;
            setdone(true);
            return true;
        }
        else
        {
            distanceLeft -= distancePerStep;
            return true;
        }
    }

    return false; // Add a return statement for all cases
}

bool DriverVolunteer::hasOrdersLeft() const
{
    return true; // Drivers always have orders left
}

bool DriverVolunteer::canTakeOrder(const Order &order) const
{
    return !isBusy() && (order.getDistance() <= maxDistance && order.getStatus() == OrderStatus::COLLECTING);
}

void DriverVolunteer::acceptOrder(const Order &order)
{
    if (canTakeOrder(order)) // to check later if it should be here or in thr vec
    {
        activeOrderId = order.getId();
        distanceLeft = order.getDistance();
    }
}

void DriverVolunteer::step()
{
    if (isBusy())
    {
        decreaseDistanceLeft();
    }
}

bool DriverVolunteer::getdone()
{
    return distanceLeft == 0;
}

string DriverVolunteer::volenteerType()
{
    return "DriverVolunteer";
}

string DriverVolunteer::toString() const
{
    std::string aciveOrderid = (getActiveOrderId() != NO_ORDER ? std::to_string(getActiveOrderId()) : "None");
    std::string distanceLeft = (getDistanceLeft() != NO_ORDER ? std::to_string(getDistanceLeft()) : "None");
    return "VolunteerID: " + std::to_string(getId()) + "\n" +
           "isBusy: " + (isBusy() ? "true" : "false") + "\n" +
           "OrderID: " + aciveOrderid + "\n" +
           "distanceLeft: " + distanceLeft + "\n" +
           "ordersLeft: No Limit";
}

/////////////////////////////// LimitedDriverVolunteer implementation ///////////////////////////////////////////////////////

LimitedDriverVolunteer::LimitedDriverVolunteer(int id, const string &name, int maxDistance, int distancePerStep, int maxOrders)
    : DriverVolunteer(id, name, maxDistance, distancePerStep),
      maxOrders(maxOrders),
      ordersLeft(maxOrders)
{
}

LimitedDriverVolunteer::~LimitedDriverVolunteer()
{
}

LimitedDriverVolunteer *LimitedDriverVolunteer::clone() const
{
    return new LimitedDriverVolunteer(*this);
}

int LimitedDriverVolunteer::getMaxOrders() const
{
    return maxOrders;
}

int LimitedDriverVolunteer::getNumOrdersLeft() const
{
    return ordersLeft;
}

bool LimitedDriverVolunteer::hasOrdersLeft() const
{
    return ordersLeft > 0;
}

bool LimitedDriverVolunteer::canTakeOrder(const Order &order) const
{
    return hasOrdersLeft() && DriverVolunteer::canTakeOrder(order);
}

void LimitedDriverVolunteer::acceptOrder(const Order &order)
{
    DriverVolunteer::acceptOrder(order);
    ordersLeft--;
}

string LimitedDriverVolunteer::toString() const
{
    std::string aciveOrderid1 = (getActiveOrderId() != NO_ORDER ? std::to_string(getActiveOrderId()) : "None");
    std::string distanceLeft1 = (getDistanceLeft() != NO_ORDER ? std::to_string(getDistanceLeft()) : "None");
    std::string ordersLeft1 = (getMaxOrders() != NO_ORDER ? std::to_string(getNumOrdersLeft()) : "None");
    return "VolunteerID: " + std::to_string(getId()) + "\n" +
           "isBusy: " + (isBusy() ? "true" : "false") + "\n" +
           "OrderID: " + aciveOrderid1 + "\n" +
           "timeLeft: " + distanceLeft1 + "\n" +
           "ordersLeft: "+ ordersLeft1;
}

bool LimitedDriverVolunteer::getdone()
{
    return getDistanceLeft() == 0;
}

string LimitedDriverVolunteer::volenteerType()
{
    return "LimitedDriverVolunteer";
}
