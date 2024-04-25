// Parser.cpp

#include "../include/Parser.h"

Parser::Parser()
{
}

Parser::~Parser()
{
}

void Parser::parseConfigFile(const std::string &configFilePath, WareHouse &warehouse)
{

    std::ifstream configFile(configFilePath);
    std::string line;
    int customerId = 0;  // Assuming customer IDs start at 0
    int volunteerId = 0; // Assuming volunteer IDs start at 0

    while (getline(configFile, line))
    {
        if (line.empty() || line[0] == '#')
            continue; // Skip empty lines and comments

        std::istringstream iss(line);
        std::string type;
        iss >> type;

        if (type == "customer")
        {
            std::string name, customerType;
            int locationDistance, maxOrders;
            iss >> name >> customerType >> locationDistance >> maxOrders;

            Customer *newCustomer = nullptr;
            if (customerType == "soldier")
            {
                newCustomer = new SoldierCustomer(customerId, name, locationDistance, maxOrders);
            }
            else if (customerType == "civilian")
            {
                newCustomer = new CivilianCustomer(customerId, name, locationDistance, maxOrders);
            }
            if (newCustomer)
            {
                warehouse.addcustomer(newCustomer);
                customerId++;
            }
        }
        else if (type == "volunteer")
        {
            std::string name, volunteerRole;
            int coolDown = 0, maxOrders = -1, maxDistanse = 0, distancePerStep = 0; // Default values
            iss >> name >> volunteerRole;

            if (volunteerRole == "driver")
            {
                iss >> maxDistanse >> distancePerStep; // Only for drivers
            }
            else if (volunteerRole == "limited_driver")
            {
                iss >> maxDistanse >> distancePerStep >> maxOrders;
            }
            else if (volunteerRole == "collector")
            {
                iss >> coolDown;
            }
            else
            {
                iss >> coolDown >> maxOrders;
            }

            if (volunteerRole == "collector")
            {
                CollectorVolunteer *newVolunteer = new CollectorVolunteer(volunteerId, name, coolDown);
                warehouse.addVolunteer(newVolunteer);
                volunteerId++;
            }
            else if (volunteerRole == "limited_collector")
            {
                LimitedCollectorVolunteer *newVolunteer = new LimitedCollectorVolunteer(volunteerId, name, coolDown, maxOrders);
                warehouse.addVolunteer(newVolunteer);
                volunteerId++;
            }
            else if (volunteerRole == "driver")
            {
                DriverVolunteer *newVolunteer = new DriverVolunteer(volunteerId, name, maxDistanse, distancePerStep);
                warehouse.addVolunteer(newVolunteer);
                volunteerId++;
            }
            else if (volunteerRole == "limited_driver")
            {
                LimitedDriverVolunteer *newVolunteer = new LimitedDriverVolunteer(volunteerId, name, maxDistanse, distancePerStep, maxOrders);
                warehouse.addVolunteer(newVolunteer);
                volunteerId++;
            }
        }
    }
}