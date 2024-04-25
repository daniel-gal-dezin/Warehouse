#pragma once
#include <string>
#include "../include/WareHouse.h"
#include "../include/Action.h"
#include "../include/Customer.h"
#include "../include/Volunteer.h"
#include <fstream>
#include <sstream>
class WareHouse;


class Parser {
public:
    Parser();
    virtual ~Parser();
    static void parseConfigFile(const std::string& configFilePath, WareHouse& warehouse);

};