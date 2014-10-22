#include "Calendar.h"
#include "Recordset.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>


void Calendar::printCalendar(std::string args)
{

    std::string monthName[] = {"January","February","March","April","May","June","July",
                                "August","September","October","November","December"};
    Date date;

    date = parseDateFromString(args);

    int days = getDaysInMonth(date.month, date.year );
    int startingDayOfMonth = getStartingDayOfMonth(date.month, date.year);

    std::string daysOfWeek = " Sun Mon Tue Wed Thu Fri Sat";

    std::cout << std::string (daysOfWeek.length()/2, ' ' ) << monthName[date.month-1] << std::endl;
    std::cout << daysOfWeek << std::endl;
    std::cout << " --- --- --- --- --- --- ---" << std::endl << " ";
    for( int day = 0 ; day < startingDayOfMonth ; day++ )
    {
        std::cout << "    ";
    }
    for(int day=1; day<=days; day++)
    {
        std::cout << std::setw(3) << day << " ";

        if (++startingDayOfMonth>6)
        {
            startingDayOfMonth = 0; std::cout << std::endl << " ";
        }
   }

   std::cout << std::endl;

}

int Calendar::getDaysInMonth(int month, int year)
{
     switch (month)
     {
	  case 2:
	      {
	          if ( isLeapYear(year) )
              {
                  return 29;
              }
              else
              {
                  return 28;
              }
	      }
	  case 4:
	  case 6:
	  case 9:
	  case 11:
	      {
	          return 30;
	      }
	  default:
	      {
	          return 31;
	      }
    }
}

bool Calendar::isLeapYear(int year)
{
   return ((year%400==0) || (year%4==0 && year%100!=0));
}

int Calendar::getStartingDayOfMonth(int month, int year)
{
    int d = 1; // finding the first day of the month
    int y = year - (month < 3);
    int t[] = {0,3,2,5,0,3,5,1,4,6,2,4};
    return (y + y/4 - y/100 + y/400 + t[month-1] + d) % 7;
}

Date Calendar::parseDateFromString(std::string dateString)
{
    //date string must be int the form m/yyyy
    Date date;

    dateString = trim(dateString);

    int position = 0;

    if ( ( position = dateString.find("/") ) == std::string::npos )
    {
        std::cout << "Can't parse date given" << std::endl;
        return date;
    }
    else
    {
        date.month = stringToInt(trim(dateString.substr(0, position)));
        dateString.erase(0, position+1);
        date.year = stringToInt((trim(dateString.substr(0, dateString.length()))));
    }

}

int Calendar::stringToInt(std::string stringValue)
{
    int value = 0;

    for ( int i = 0 ; i < stringValue.length() ; i++ )
    {

        switch ( stringValue[i] )
        {
            case '0':
            {
                value = (value*10) + 0;
                break;
            }
            case '1':
            {
                value = (value*10) + 1;
                break;
            }
            case '2':
            {
                value = (value*10) + 2;
                break;
            }
            case '3':
            {
                value = (value*10) + 3;
                break;
            }
            case '4':
            {
                value = (value*10) + 4;
                break;
            }
            case '5':
            {
                value = (value*10) + 5;
                break;
            }
            case '6':
            {
                value = (value*10) + 6;
                break;
            }
            case '7':
            {
                value = (value*10) + 7;
                break;
            }
            case '8':
            {
                value = (value*10) + 8;
                break;
            }
            case '9':
            {
                value = (value*10) + 9;
                break;
            }
            default:
                {
                    return value;
                }
        }

    }

    return value;
}
