###### Name      :   Dhanvin Athray
###### Email id  :   dathray@uncc.edu
###### Student id : 801167002

# LZW Compression in C++

The Lempel–Ziv–Welch  (LZW)  algorithm is  a  lossless  data  compression  algorithm.
  - Adaptive  compression  algorithm  that  does  not  assume  prior  knowledge  of  the  input  data  distribution. 
  - Works well when the input data is sufficiently large and there is redundancy in data.
  - Suitable  for  compressing  text files, and is the algorithm in the compress Unix file compression utility.

## Steps

  1) Encoding
  2) Compression
  3) Decoding
  4) Decompression
  
### Contents 
- encode.cpp
- decode.cpp


### Working of LZW Algorithm in the code

##### Encoding:
###### void encode(string input , int length , string fname) 

* Reads the data from an input text file and stores it in a string.
* Creates a table with [0-255] ascii characters.
* Reads the string one by one and checks if the character is present in the table .
* If present in the table, appends the current string with next string .
* If not present in the table, adds the current string key value of the table to the output vector and adds the string into the table .

##### Compression:
###### void compression_filewrite(vector<int> output , string fname)
* Stores the output string vector in an array of char16_t format.
* The array is then converted to UTF16 format and is written into the file in .lzw format.

##### Decompression:
###### vector<int> initiate(string fname , int length)
* Reads the .lzw file and stores into a wchar array.
* The wchar array is then written into an integer vector.

##### Decoding:
###### void decode (int length , string fname)
* Gets the umcompressed data in an integer vector.
* Creates a table with [0-255] ascii characters.
* Reads the input integer vector and checks if the value is present in the table.
* If present in the table, adds the string to the output string vector and appends the current and ext string to the table.
* If not present, adds the previous string to the output string vector.
* The output string vector is then added to a text file.

### Compilation 

##### Was run on Linux Platform and C++ 11 version

 Command for Encoding:
```sh
$ g++ -o encode encode.cpp
$ ./encode filename.txt length
```
Command for Decoding

```sh
$ g++ -o decode decode.cpp
$ ./decode filename.lzw length
```

### Example

###### Text Input
```sh
abbbab
```
###### Encoded output
```sh
abāĀ
```
###### Decoded output
```sh
abbbab
```
