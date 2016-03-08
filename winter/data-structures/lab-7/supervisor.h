/*
 * supervisor.h
 * Supervisor class implemented for lab 7.
 *
 * Noah Weiner
 * March 8, 2016
 */

#ifndef _SUPERVISOR_H
#define _SUPERVISOR_H

#include "employee.h"

using namespace std;

class Supervisor : public Employee {
public:
  Supervisor(string theName,
          float thePayRate,
          const string& theDepartment);

  const string& getDept() const;
  void setDept(const string& newDepartment);

  float pay(float hoursWorked) const;

protected:
  string department;
};

#endif /* not defined _SUPERVISOR_H */
