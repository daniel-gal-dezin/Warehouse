#include "../include/Order.h"



Order::Order(int id, int customerId, int distance) : id(id), customerId(customerId), distance(distance), status(OrderStatus::PENDING), collectorId(-1), driverId(-1)
{
}

Order::~Order()
{
}
int Order::getId() const
{
    return id;
}

int Order::getCustomerId() const
{
    return customerId;
}

OrderStatus Order::getStatus() const
{
    return status;
}

Order *Order::clone() const
{
    return new Order(*this);
}


int Order::getDistance() const
{
    return distance;
}

void Order::setStatus(OrderStatus status)
{
    this->status = status;
}

void Order::setCollectorId(int collectorId)
{
    this->collectorId = collectorId;
}

void Order::setDriverId(int driverId)
{
    this->driverId = driverId;
}

int Order::getCollectorId() const
{
    return collectorId;
}

int Order::getDriverId() const
{
    return driverId;
}

string Order::orderStatusToString()
{
    switch (status)
    {
    case OrderStatus::PENDING:
        return "Pending";
    case OrderStatus::COLLECTING:
        return "Collecting";
    case OrderStatus::DELIVERING:
        return "Delivering";
    case OrderStatus::COMPLETED:
        return "Completed";
    default:
        return "Unknown";
    }
}

const string Order::toString() const
{
      std::string statusString;

    switch (status)
    {
        case OrderStatus::PENDING:
            statusString = "Pending";
            break;
        case OrderStatus::COLLECTING:
            statusString = "Collecting";
            break;
        case OrderStatus::DELIVERING:
            statusString = "Delivering";
            break;
        case OrderStatus::COMPLETED:
            statusString = "Completed";
            break;
        default:
            statusString = "Unknown";
    }

    return "OrderID: " + std::to_string(id) + " , CustomerID: " + std::to_string(customerId) + " , Status: " + statusString;
}
