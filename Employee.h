#ifndef EMPLOYEE_H_INCLUDED
#define EMPLOYEE_H_INCLUDED

#include "Recordset.h"
#include <iostream>
#include <vector>

class Employee
{

public:

    Employee();
    ~Employee();

    void addEmployee(std::string);
    void removeEmployee(std::string);
    void editEmployee(std::string);
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


#endif // EMPLOYEE_H_INCLUDED
