// Dependecies//
#include <iostream>  //For input/output functionalities//
#include <set>       //For implementation of hash set stores unique keys only//
#include <vector>    //For dynamic allocation and easier functionality//
#include <string>    //For printing and inputing text and using its in-built functions//
#include <numeric>   //For in-built gcd function can be implemented by itself//
#include <fstream>   //File input/output functionality//
#include <cmath>     //Using maths functionalities such as the rand function//
#include <climits>   //Including limits of int_max,int_min//
#include <Windows.h> //Creating message box icon//
#include <tchar.h>   //Converting to unicode from multibyte//
using namespace std;
// Creation of set for the storage of the prime number in the range of 2 to 550 //
set<int> prime_number_arr;
// Creation of variables namely private key and public key private key is initialized using the variables of d ane e
// Public key is initialized using the variables e and n = (p)*(q) where p and q are two randomly picked prime number.
class Primeinitialization
{
public:
    void primefiller();
    // Creation of function to pick up randomly a pair of prime numbers using rand() function //
    int pickrandomprime()
    {
        int k = rand() % prime_number_arr.size();
        // Traversing through the set to select any prime number//
        auto iterator = prime_number_arr.begin();
        while (k--)
            iterator++;
        int ret = *(iterator);
        prime_number_arr.erase(iterator);
        return ret;
    }
};
void Primeinitialization::primefiller()
{
    // Creation of sieve for prime numbers optimized for finding prime numbers
    // Using the idea of seive of erastothenes//
    vector<bool> seive(550, true);
    seive[0] = false;
    seive[1] = false;
    for (int i = 2; i < 550; i++)
    {
        for (int j = i * 2; j < 550; j += i)
        {
            seive[j] = false;
        }
    }
    // Inserting the prime numbers after being seived through the above algorithm and inserting them into set//
    for (int i = 0; i < seive.size(); i++)
    {
        if (seive[i])
            prime_number_arr.insert(i);
    }
}
class encryption : public Primeinitialization
{
protected:
    int private_key;

public:
    int public_key;
    int n;
    void keys_generator();
    long long int encrypt(double);
    vector<int> encoder(string message);
};
vector<int> encryption::encoder(string message)
{
    vector<int> form;
    // calling the encrypting function in encoding function
    for (auto &letter : message)
        form.push_back(encrypt((int)letter));
    return form;
}
// Encrytpion based on the RSA algorithm rule and the use of public key is done by this function to generate
// encrypted text.
long long int encryption::encrypt(double message)
{
    int e = public_key;
    long long int encrpyted_text = 1;
    while (e--)
    {
        encrpyted_text *= message;
        encrpyted_text %= n;
    }
    return encrpyted_text;
}
// Keys generator function to generate both the public key and private key which will be used for encryption and de
// cryption later on.
void encryption::keys_generator()
{
    int prime1 = pickrandomprime();
    int prime2 = pickrandomprime();
    n = prime1 * prime2;
    // Defining euler totient function of the form phi(n) = (p-1)*(q-1).
    int fi = (prime1 - 1) * (prime2 - 1);
    int e = 2;
    // e will be any number satisfying the conditions that phi(n) and e are co primes and e > 1 but e < phi(n).
    while (1)
    {
        if (gcd(e, fi) == 1)
            break;
        e++;
    }
    public_key = e;
    // d = (k*Φ(n) + 1) / e for some integer k
    int d = 2;
    while (1)
    {
        if ((d * e) % fi == 1)
            break;
        d++;
    }
    // d will be the multiplicative inverse of phi(n) //
    private_key = d;
}
class decryption : public encryption
{
public:
    decryption()
    {
        // Constructor to intialize our prime set//
        primefiller();
    }
    long long int decrypt(int encrpyted_text);
    string decoder(vector<int> encoded);
    void print_encrypted_text(vector<int> &coded, string input);
    void print_decrypted_text(vector<int>, decryption &d);
};
// Function for the printing of the decrypted text//
void decryption::print_decrypted_text(vector<int> v, decryption &d)
{
    cout << "The decrypted text of the above cipher text is :-" << endl;
    cout << d.decoder(v) << endl;
}
// Function for printing the encrypted text and storing the input text and encrypted text in a sepearate file//
void decryption::print_encrypted_text(vector<int> &coded, string input)
{
    cout << "The message meant for encryption was :-"
         << " " << input << endl;
    cout << "The encrypted message is as follows :-" << endl;
    fstream fo("Encrypted_text.txt", ios_base::app);
    fo << endl;
    for (auto &p : coded)
    {
        int n = p;
        fo << n;
        cout << p;
    }
    fo << endl;
    fo << "End of encrypted value for :: the input text ==" << input;
    cout << endl;
    fo.close();
}
// Decrypter function that will take the value of the integer assigned to a particular character of the
// input string and will convert it back to the character's ascii value that will be intrinsic typecasting and
// will convert it back to the character form and return a string thorugh the decoder function.
long long int decryption::decrypt(int encrpyted_text)
{
    int d = private_key;
    long long int decrypted = 1;
    // decrypting the value by the integer that was used to encrypt the corresponding character of a string//
    while (d--)
    {
        decrypted *= encrpyted_text;
        decrypted %= n;
    }
    return decrypted;
}
string decryption::decoder(vector<int> encoded)
{
    string s;
    // calling the decrypting function decoding function
    for (auto &num : encoded)
        s += decrypt(num);
    return s;
}
// Function to read any text file provided by the user and to generate a string that will be used as input
// further.
string file_reader(string file_name)
{
    string empty = "";
    fstream fo(file_name, ios_base::in);
    char ch;
    while (fo.good() == true)
    {
        fo >> noskipws >> ch;
        empty.push_back(ch);
    }
    fo.close();
    return empty;
}
bool error(string filepath)
{
    if (filepath.substr(filepath.find_last_of(".") + 1) == "cpp" || filepath.substr(filepath.find_last_of(".") + 1) == "txt" || filepath.substr(filepath.find_last_of(".") + 1) == "py" || filepath.substr(filepath.find_last_of(".") + 1) == "java" || filepath.substr(filepath.find_last_of(".") + 1) == "c")
    {
        return true;
    }
    else
    {
        return false;
    }
    return false;
}
int main()
{
    string path;
    cout << "Enter path of the file you want to encrypt-:" << endl;
    cin >> path;
    cout << "Path is " << path << endl;
    if (error(path) == false)
    {
        cout << "Not a valid extension please enter a valid filetype" << endl;
        MessageBeep(0);
        MessageBox(NULL, _T("Invalid filetype"), _T("Error"), MB_OK);
        return 0;
    }
    string name = file_reader(path);
    decryption d;
    d.keys_generator();
    vector<int> coded = d.encoder(name);
    d.print_encrypted_text(coded, name);
    d.print_decrypted_text(coded, d);
    MessageBox(NULL, _T("File has been encrypted"), _T("INFO"), MB_ICONINFORMATION);
}