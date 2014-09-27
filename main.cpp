#include <iostream>
#include "Recordset.h"

using namespace std;

int main()
{
    Recordset recordset1;

    recordset1.loadFromfile("test.txt", ";");

    recordset1.moveFirst();

    for ( int i = 0; i < recordset1.getRows() ; i++ ){

        cout << recordset1.fields("FNAME") << " " << recordset1.fields("LNAME") << endl;
        recordset1.moveNext();

    }

    recordset1.addRow();

    recordset1.fields("FNAME") = "Muath";
    recordset1.fields("LNAME") = "Aldhubayb";

    recordset1.writeToFile("test.txt", ";");

    return 0;
}
