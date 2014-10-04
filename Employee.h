#ifndef EMPLOYEE_H_INCLUDED
#define EMPLOYEE_H_INCLUDED

#include "Recordset.h"
#include <iostream>
#include <vector>

enum EmployeeInfoFlags
{

    EI_FNAME    = 0x01,
    EI_LNAME    = 0x02,
    EI_FULLNAME = 0x04,
    EI_PHONE    = 0x08,
    EI_ADDRESS  = 0x10,
    EI_WAGE     = 0x20,
    EI_ALL      = 0x40

};

struct EmployeeInfo
{
    std::string name = "";
    std::string firstName = "";
    std::string lastName = "";
    std::string phone = "";
    std::string address = "";
    std::string wage = "";
};

class Employee
{

public:

    Employee();
    ~Employee();

    void addEmployee(std::string);
    void removeEmployee(std::string, std::string);
    void editEmployee(std::string, std::string, std::string, std::string, std::string, std::string, std::string);
    void viewEmployees(std::string);

    bool employeeExists(std::string, std::string);

    std::string getEmployeeName(std::string, std::string);
    std::string getEmployeePhone(std::string, std::string);
    std::string getEmployeeAddress(std::string, std::string);
    std::string getEmployeeWageStr(std::string, std::string);

    std::string getEmployeeInfo(int);

    int getEmployeeWageInt(std::string, std::string);

private:

    Recordset m_employeeRecordset;

    std::string m_employeeSourceFile;
};

std::string trim(std::string);

#endif // EMPLOYEE_H_INCLUDED
