#include <iostream>
#include "Recordset.h"

using namespace std;

int main()
{
    Recordset recordset1;


    // Adding fields to the recordset
    recordset1.addField("FNAME");
    recordset1.addField("LNAME");
    //////////////////////////////////


    // adding rows to recordset and setting values
    recordset1.addRow();

    recordset1.fields("FNAME") = "Chris";
    recordset1.fields("LNAME") = "Tiller";

    recordset1.addRow();

    recordset1.fields("FNAME") = "Muath";
    recordset1.fields("LNAME") = "Aldhubayb";

    recordset1.addRow();

    recordset1.fields("FNAME") = "Dhiraj";
    recordset1.fields("LNAME") = "Ranjit";
    //////////////////////////////////////////////

    //printing out the recordset

    recordset1.moveFirst(); // make sure you are at the beginning so that everything gets printed out

    while ( recordset1.getRow() <= recordset1.getRows() )
    {

        cout << recordset1.fields("FNAME") << " " << recordset1.fields("LNAME") << endl;
        recordset1.moveNext(); // must have this line to increment to the next row or else you will get an infinite loop

    }
    //////////////////////////////////////////////

    // deleting a specific row

    recordset1.moveFirst();

    while ( recordset1.fields("FNAME") != "Dhiraj" )
    {
        recordset1.moveNext(); // increment to the next row
    }

    recordset1.removeRow();
    ////////////////////////////////////////////////

    cout << endl;

    recordset1.moveFirst();

    while ( recordset1.getRow() <= recordset1.getRows() )
    {

        cout << recordset1.fields("FNAME") << " " << recordset1.fields("LNAME") << endl;
        recordset1.moveNext();

    }

    return 0;
}
