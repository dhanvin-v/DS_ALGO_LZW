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

//Function used to compress the output vector and write it into
//a file in LZW format
//Input:
//vector<int> output - the encoded output in a vector
//string fname - file name given by the user
void compression_filewrite(vector<int> output , string fname)
{
//Compression of the output string
    char16_t utf16le[output.size()];

    for(int i = 0 ; i<output.size() ; i++)
    {
        utf16le[i] = output.at(i);
    }

    std::ofstream fout(fname);

    //Writing the output into text file in encoded format
    fout.write( reinterpret_cast<char*>(utf16le), sizeof utf16le);
}

//Function used to encode the input data from the given
//input string
//Input:
//string input - The text from the input file given by the user
//int length - length entered by the user
//string fname - input file name given by the user
void encode(string input , int length , string fname)
{
    //Stores the length of input
    int input_length = input.length();

    //Vector to store the output encoded values
    vector<int> output; 

    //Buffer string to store the current and the next input strings
    string current = "" , next = "";

    //Map to store the ascii values of along with the string value and update
    //the table with new values
    map<string, int> table; 
    map<string, int>::iterator it;


    //Stores the length of the table
    int table_len = 256;
    
    //Storing all the characters from 0-255 along with the corresponding
    //ascii value as the key element
    for (int i = 0; i < 256; i++) 
    { 
        string str = ""; 
        str = str + char(i); 
        table[str] = i; 
    }

    //Initializing the 0th character to be the first string
    current = current + input[0];

    for(int i=0; i<input_length; i++)
    {

        //Base case condition for the last character in the input
        //string
        if(i != input_length - 1)
        {
            next = next + input[i+1];
        }

        //Searching the table for if the current + next string
        //is present or not
        it = table.find(current + next);
        if( it != table.end())
        {
            //If current + next string is present in the table then
            //add the next string to current
            current = current + next;
        }

        else
        {
            //If current + next string is not present in the table then
            //current value is pushed to output vector and the new string
            //and key value is updated to table
            output.push_back(table[current]);
            if(table_len<pow(2 , length))
            {
            table[current+next] = table_len;
            table_len++;
            }
            current = next;
        }
        
        //making next string as NULL
        next = "";

    } 

    //Pushes the value of last string into the output vector
    output.push_back(table[current]); 

    //Removing the txt extension in the filename
    fname = fname.substr(0, fname.size()-4);

    fname = fname + ".lzw";

    compression_filewrite(output , fname);

}

int main(int argc, char* argv[])
{
    string fname;

    //Copying thr filename to a string
	fname = argv[1]; 

    //Copying the bit length to an integer variable
    int length = atoi(argv[2]);
    if(length > 8)
    {
        string input;

        //Reading the contents of the file into a string
        ifstream t(fname.c_str());
        string str((istreambuf_iterator<char>(t)) , istreambuf_iterator<char>());
        input = str;

        //Calling the encode function
        encode(input , length , fname );
    }

    else
    {
        cout<<"Table length is invalid, enter a value above 8";
    }
    
    
}