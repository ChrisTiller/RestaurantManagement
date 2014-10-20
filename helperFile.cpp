#include "helperFile.h"
#include <cmath>



void parseCommand(Command& com, string rawInput)
{

    rawInput = trim(rawInput);

    int position = 0;

    if ( ( position = rawInput.find(" ")) == std::string::npos )
    {
        com.mainCommand = rawInput;
    }
    else
    {
        com.mainCommand = trim(rawInput.substr(0, position));
        rawInput.erase(0, position + 1 );
        com.commandArguments = trim(rawInput.substr(0, rawInput.length()));
    }

}

// Returns a trimmed string so that there are no beginning or ending spaces
std::string trim(std::string stringToTrim)
{
    if ( stringToTrim.length() == 0 )
	{
		return "";
	}

    int position = 0;

    while ( ( position < stringToTrim.length() ) && ( stringToTrim[position] == ' ' ) )
    {
        position++;
    }

    stringToTrim = stringToTrim.erase(0, position);

    position = stringToTrim.length();

    while ( ( position >= 0 ) && ( stringToTrim[position-1] == ' ' ) )
    {
        position--;
    }

    stringToTrim = stringToTrim.erase(position, stringToTrim.length());

    return stringToTrim;
}

int stringToInt(std::string stringValue)
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

std::string intToString(int rhs)
{
    int length = 0;
    std::string invertedValue = "";
    std::string value = "";

    if ( rhs == 0 )
    {
        return "0";
    }

    while ( ( rhs / (int)pow(10, length) ) > 0 )
    {
        length++;
    }

    length--;
    int currentvalue = rhs;
    int numberToCompare = 0;

    while ( length >= 0)
    {
        numberToCompare = currentvalue%10;

        switch ( numberToCompare )
        {
        case 0:
            {
                invertedValue += "0";
                break;
            }
        case 1:
            {
                invertedValue += "1";
                break;
            }
        case 2:
            {
                invertedValue += "2";
                break;
            }
        case 3:
            {
                invertedValue += "3";
                break;
            }
        case 4:
            {
                invertedValue += "4";
                break;
            }
        case 5:
            {
                invertedValue += "5";
                break;
            }
        case 6:
            {
                invertedValue += "6";
                break;
            }
        case 7:
            {
                invertedValue += "7";
                break;
            }
        case 8:
            {
                invertedValue += "8";
                break;
            }
        case 9:
            {
                invertedValue += "9";
                break;
            }
        }

        currentvalue = currentvalue/10;
        length--;
    }

    // string value of the integer is reversed so we need to get the
    // original value back
    for ( int i = invertedValue.length() - 1 ; i >= 0 ; i-- )
    {
        value += invertedValue[i];
    }
    return value;
}
