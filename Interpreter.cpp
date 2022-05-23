// Najm Aldeen Hamid 
// CISC 3160 project 

#include <iostream>
#include <map>
#include <string>
#include "INTERPRTER_H.h"

using namespace std;
int main ()
{
     map <string, Table_Row> symbolTable;
     string fileName;
    
        cout<<"Enter the file text file name: ";
        cin>>fileName;
      interpreter (fileName, &symbolTable);
     
     return 0;	
}
