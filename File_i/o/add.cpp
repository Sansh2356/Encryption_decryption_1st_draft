#include <iostream>
#include <cstring>
#include<ostream>
#include<istream>
#include <fstream>
#include <string>
using namespace std;
class stu{
    public:
    int age;
    string name;
};
int main()
{
stu so[5];
for(int m=0;m<5;m++){
    cin>>so[m].age;
    cin>>so[m].name;
}
fstream fo("random.txt",ios_base::out);
for(int x=0;x<5;x++){
    stu so2 = so[x];
    fo<<so2;
}

}