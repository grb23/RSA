/***
compile and run (in linux):
g++ sha256.cpp main.cpp -o sha256_example && ./sha256_example
Output:
sha256('grape'): 0f78fcc486f5315418fbf095e71c0675ee07d318e5ac4d150050cd8e57966496
**/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "sha256.h"
#include "BigIntegerLibrary.hh"


using std::string;
using std::cout;
using std::endl;

using namespace std;
 
int main(int argc, char *argv[])
{
    //string input = "grape    sha256('grape'):0f78fcc486f5315418fbf095e71c0675ee07d318e5ac4d150050cd8e57966496";
    //string output1 = sha256(input);
 
    //cout << "sha256('"<< input << "'):" << output1 << endl;
    
    ifstream message;
    message.open("message.txt");

    stringstream ss;
    ss << message.rdbuf();
    std::string s = ss.str();
    cout << s << '\n';
    
    message.close();
    
    string sha = sha256(s);
    cout << sha << '\n';
    
    ifstream d_n;
    d_n.open("d_n.txt");
    
    //get d from Private Key
    string line;
    getline(d_n, line);
    string d = line;
    cout << "d: " << d << endl << endl;
    
    //get n from Private Key
    getline(d_n, line);
    string n = line;
    cout << "n: " << n << endl << endl;
    
    d_n.close();
    
    ifstream e_n;
    e_n.open("e_n.txt");
    
    //get e from Private Key
    getline(e_n, line);
    string e = line;
    cout << "e: " << e << endl << endl;
    
    ifstream p_q;
    p_q.open("p_q.txt");
    
    //get p from Public Key
    getline(p_q, line);
    string p = line;
    cout << "p: " << p << endl << endl;
    
    //get q from Public Key
    getline(p_q, line);
    string q = line;
    cout << "q: " << q << endl << endl;
    
    p_q.close();
    
    //BigInteger sha_BigInteger = stringToBigInteger(sha);
    
    //BigUnsigned d_BigUnsigned = stringToBigUnsigned(d);
    //BigUnsigned e_BigUnsigned = stringToBigUnsigned(e);
    //BigUnsigned n_BigUnsigned = stringToBigUnsigned(n);
    
    //BigUnsigned p_BigUnsigned = stringToBigUnsigned(p);
    //BigUnsigned q_BigUnsigned = stringToBigUnsigned(q);
    
    //decrypt message
    //BigUnsigned M = modexp(sha_BigInteger, d_BigUnsigned, n_BigUnsigned);
    
    //cout << "M: " << M << endl << endl;
    
    //Compare the SHA-256 hash value and the “encrypted” signature
    //s.compareTo(message.txt.signature);

    std::string filename = "message.txt";
    std::ifstream myfile (filename.c_str(), std::ios::binary);
    std::streampos begin,end;
    begin = myfile.tellg();
    myfile.seekg (0, std::ios::end);
    end = myfile.tellg();
    std::streampos size = end-begin; //size of the file in bytes   
    myfile.seekg (0, std::ios::beg);
    
    char * memblock = new char[size];
    myfile.read (memblock, size); //read the entire file
    memblock[size]='\0'; //add a terminator
    myfile.close();
   
    //check what's in the block
    string str(memblock);
    std::cout << str; 
    std::cout << "\nthe content ";
   
    //----------------------- add signature to the content and save
    std::string filename2 = filename+".signed";
    std::ofstream myfile2 (filename2.c_str(), std::ios::binary);
    myfile2.write (memblock, size);
    int sigLength = 1024;
    char * signature = new char[sigLength];
    string sig = "Gwendolyn";
    strcpy(signature, sig.c_str());
    myfile2.write (signature, sigLength); //write sig in a block of 1024 bytes
    
    myfile2.close();
    std::cout << "signed at the end of the doc!\n";
    
    return 0;
}