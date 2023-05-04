#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <numeric>
#include<fstream>
#include <cmath>
#include <climits>
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
    // Constructor for initlizing and filling our set of primes//
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
class decryption:public encryption
{
    public:
    decryption(){
        //Constructor to intialize our prime set//
        primefiller();
    }
    long long int decrypt(int encrpyted_text);
    string decoder(vector<int>encoded);
};
long long int decryption::decrypt(int encrpyted_text){
    int d = private_key;
	long long int decrypted = 1;
    //decrypting the value by the integer that was used to encrypt the corresponding character of a string//
	while (d--)
	{
		decrypted *= encrpyted_text;
		decrypted %= n;
	}
	return decrypted;
}
string decryption::decoder(vector<int>encoded){
string s;
	// calling the decrypting function decoding function
	for (auto &num : encoded)
		s += decrypt(num);
	return s;
}
int main()
{
    string name; 
    name = "123456";
    decryption d;
    d.keys_generator();
    vector<int>coded = d.encoder(name);
    cout<<"The message meant for encryption was :-"<<" "<<name<<endl;
    cout<<"The encrypted message is as follows :-"<<endl;
    for (auto &p : coded)
		cout << p;
   cout<<endl;     
     cout<<"The decrypted text of the above cipher text is :-"<<endl;    
     cout<<d.decoder(coded)<<endl;
    
}