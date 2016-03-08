/*
 * supervisor.cpp
 * Supervisor class implemented for lab 7.
 *
 * Noah Weiner
 * March 8, 2016
 */

#include "supervisor.h"

Supervisor::Supervisor(string theName,
                       float thePayRate,
                       const string& theDepartment)
    : Employee(theName, thePayRate)
{
  department = theDepartment;
}

const string& Supervisor::getDept() const {
  return department;
}

void Supervisor::setDept(const string& newDepartment) {
  department = newDepartment;
}


float Supervisor::pay(float hoursWorked) const {
  return payRate;
}
