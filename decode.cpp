//Name         :   Dhanvin Athray
//Email        :   dathray@uncc.edu
//Student id   :   8001167002 

#include<iostream>
#include <string>
#include <iterator>
#include <map>
#include <vector>
#include <bits/stdc++.h>
#include <bits/stdc++.h> 
#include <stdlib.h>
#include <locale>
#include <codecvt>
using namespace std;

//Function used to decompress the compressed data
//Input : 
//string fname - file name passed by the user
//int length - length of the table passed by the user
//Output :
//vector<int> input - return the decompressed input

vector<int> initiate(string fname , int length)
{
    vector<int> input; 
    std::wifstream fin(fname, std::ios::binary);

    // Converts the data from UTF16LE format
    fin.imbue(std::locale(fin.getloc(),
       new std::codecvt_utf16<wchar_t, 0x10ffff, std::little_endian>));

    for (wchar_t c; fin.get(c); )
    {
        if (int(c)<pow(2,length)){
            input.push_back(int(c));
        }
    }

    return input;

}

//Function used to decode the encoded data
//Input:
//int length - Length given by the user
//string fname - File name given by the user
void decode (int length , string fname)
{
    map<int, string> table; 
    map<int, string>::iterator it;


    //Stores the length of the table
    int table_len = 256;
    
    //Calling the decode function used to decompressthe data 
    //in lzw file and return the input vector
    vector<int> input = initiate(fname , length);
    vector<string> output;
    
    string current = "" , next = "";

    int next_num = 0, current_num = input[0];
        
    //Storing all the ascii values from 0-255 along with the corresponding
    //string as the key element
    for (int i = 0; i < 256; i++) 
    { 
        string str = ""; 
        str += char(i); 
        table[i] = str; 
    }

    //Stores the first string into the output vactor
    current = current + char(input.at(0));

    output.push_back(current);

    for(int i = 0; i < (input.size() - 1) ; i++)
    {
        next_num = input.at(i+1);

        //Checks if the value is present in the table and pushes
        //it into the output vector
        it = table.find(next_num);
        if( it != table.end())
        {
            next = table[next_num];
            output.push_back(next);
        }

        else
        {
            next = table[current_num] + current;
            output.push_back(next);
        }

        current = "";

        //Checks if the table length is within the
        //limit
        if(table_len<pow(2 , length))
        {
        table[table_len] = table[current_num] + next[0];
        table_len++;
        }
        current = current + next[0];
        current_num = next_num;
    }

    fname = fname.substr(0, fname.size()-4);
    fname = fname + "_decoded.txt"; 

    //Writes the decoded output to a text file
    ofstream myfile;
    myfile.open (fname);

    for(int i = 0; i< output.size() ; i++)
    {
        myfile<<output.at(i);
    }
    myfile.close();
}

int main(int argc, char* argv[])
{
    string fname;

    //Copying thr filename to a string
	fname = argv[1]; 

    //Copying the bit length to an integer variable
    int length = atoi(argv[2]);

    //Calling the decode function
    decode(length , fname);
    return 0;
}