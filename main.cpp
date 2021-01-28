#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

using std::endl;
using std::cout;
using std::string;
using std::cin;

struct myAddress{
    string street;
    int house_number;
    int apartment_number;
    myAddress ()
    {
        street="";
        house_number=0;
        apartment_number=0;
    }
    bool operator<(const myAddress & My)
    {
        if (this->street< My.street) { return true;}
        
        return false;
    }
    
    bool operator>(const myAddress & My)
    {
        if (this->street> My.street) { return true;}
        
        return false;
    }
};

std::ifstream & operator>> (std::ifstream& is , string& str)
{
    string tmp;
    std::getline(is, tmp);
    str = tmp;
    return is;
}

std::ofstream & operator<< (std::ofstream& os , const myAddress& addr)
{
    os << addr.street.c_str() << endl << addr.house_number << endl << addr.apartment_number << endl;
    return os;
}

std::ostream & operator<< (std::ostream& os , const myAddress& addr)
{
    os << addr.street.c_str()  << ", " << addr.house_number  << ", apt. " << addr.apartment_number;
    return os;
}

std::ifstream& operator>> (std::ifstream& is , myAddress& addr)
{
    string s1, s2;
    
    std::getline(is, addr.street);
    std::getline(is, s1);
    std::getline(is, s2);
    
    addr.apartment_number = s2=="" ? 0 : std::stoi(s2);
    addr.house_number = s1 == "" ? 0 : std::stoi(s1);
    
    return is;
}

struct myFullname
{
    string firstname;
    string midlename;
    string lastname;
    
    myFullname()
    {
        firstname = "";
        midlename = "";
        lastname = "";
    }
};

std::ofstream & operator<< (std::ofstream& os , const myFullname & Fullname)
{
    os << Fullname.firstname.c_str() << endl << Fullname.midlename.c_str() << endl << Fullname.lastname.c_str() << endl;
    return os;
}

std::ifstream & operator>> (std::ifstream& is , myFullname & Fullname)
{
    std::getline(is, Fullname.firstname);
    std::getline(is, Fullname.midlename);
    std::getline(is, Fullname.lastname);
    
    return is;
}

std::ostream & operator<< (std::ostream& os , const myFullname & Fullname)
{
    os << Fullname.firstname.c_str() << " " << Fullname.midlename.c_str() << " " << Fullname.lastname.c_str();
    return os;
}

struct myResident{
    myFullname Fullname;
    myAddress address;
    string sex;
    int age;
    
    myResident()
    {
        sex = "";
        age = 0;
        Fullname.firstname = "";
        Fullname.midlename = "";
        Fullname.lastname = "" ;
    }
    bool operator<(const myResident & My)
    {
        if (this->Fullname.firstname < My.Fullname.firstname) { return true;}
        
        return false;
    }
    
    bool operator>(const myResident & My)
    {
        if (this->Fullname.firstname < My.Fullname.firstname) { return true;}
        
        return false;
    }
};

std::ofstream & operator<< (std::ofstream& os , const myResident & rsdnt)
{
    os << rsdnt.Fullname;
    os << rsdnt.address;
    os << rsdnt.sex.c_str();
    os << endl;
    os << rsdnt.age <<endl;
    return os;
}

std::ifstream & operator>> (std::ifstream& is , myResident & rsdnt)
{
    is >> rsdnt.Fullname;
    is >> rsdnt.address;
    std::getline(is, rsdnt.sex);
    
    string s1;
    std::getline(is, s1);
    rsdnt.age = s1=="" ? 0 : std::stoi(s1);
    
    return is;
}

std::ostream & operator<< (std::ostream& os , const myResident & rsdnt)
{
    os << "Fullname: " << rsdnt.Fullname  <<  endl << "sex: " <<rsdnt.sex.c_str() << "; age: "  << rsdnt.age << endl << "Address: " << rsdnt.address;
    return os;
}

int getDatabaseSize (std::vector<myResident>& arr)
{
    return arr.size();
}

void saveDatadaseInTextFormat (std::vector<myResident>& arr, string fileName)// сохранение в текстовом формате
{
    std::ofstream text_database;
    text_database.open(fileName);
    
    int databaseSize = getDatabaseSize(arr);
    for (int i = 0; i < databaseSize; i++) {
        text_database << arr[i] << endl;
    }
    text_database.close();
}

std::vector<myResident> loadDatabaseFromText (string fileName)// загрузка в текстовом формате
{
    std::vector<myResident> tmp;
    
    std::ifstream text_database;
    text_database.open(fileName);
    if (!text_database)
    {
        cout << "Error open file " << fileName;
        std::vector<myResident> arr;
        return arr;
    }
    
    while (!text_database.eof())
    {
        myResident rsdnt;
        text_database >> rsdnt;
        tmp.push_back(rsdnt);
    }
    
    text_database.close();
    tmp.pop_back();
    return tmp;
}

void printUnderageByStreet(std::vector<myResident>& arr, std::string streetName)// вывод несовершеннолетних
{
    for (myResident person : arr )
    {
        if (person.age < 18 && person.address.street == streetName)
        {
            cout << person.Fullname << " age: " << person.age << endl;
        }
    }
}

void PrintUnderageCountsForStreets (std::vector<myResident>& arr)// подсчитываем кол-во несовершеннолетних
{
    struct searchPair
    {
        string street;
        int count;
        searchPair ()
        {
            street = "";
            count = 0;
        }
    };
    
    int databaseSize = getDatabaseSize(arr);
    searchPair * sp = new searchPair [databaseSize];
    
    for (myResident i : arr)
    {
        if (i.age< 18)
        {
            for (int pairNum = 0; pairNum < databaseSize; pairNum++)
            {
                if (sp[pairNum].street == "")
                {
                    sp[pairNum].street = i.address.street;
                    sp[pairNum].count++;
                    break;
                }
                else
                if (sp[pairNum].street == i.address.street)
                {
                    sp[pairNum].count++;
                    break;
                }
            }
        }
    }
    
    for (int i = 0; i < databaseSize; i++)
    {
        if (sp[i].street  != "" )
        {
            cout << sp[i].street << ": " << sp[i].count << endl;
            printUnderageByStreet(arr, sp[i].street );
            
        }
    }
    delete[] sp;
}

void saveDatadaseInBinaryFormat (std::vector<myResident>& arr, string fileName)
{
    std::ofstream out(fileName, std::ios::binary);
    unsigned char buf;
    unsigned char data_size = sizeof(unsigned char);
    
    for (myResident person : arr)
    {
        buf = person.Fullname.firstname.length();
        out.write(reinterpret_cast<const char*> (&buf), data_size);
        out.write(person.Fullname.firstname.data(), buf);
        
        buf = person.Fullname.midlename.length();
        out.write(reinterpret_cast<const char*> (&buf), data_size);
        out.write(person.Fullname.midlename.data(), buf);
        
        buf = person.Fullname.lastname.length();
        out.write(reinterpret_cast<const char*> (&buf), data_size);
        out.write(person.Fullname.lastname.data(), buf);
        
        buf = person.address.street.length();
        out.write(reinterpret_cast<const char*> (&buf), data_size);
        out.write(person.address.street.data(), buf);
        
        
        out.write(reinterpret_cast<const char*> (&person.address.house_number), data_size);
        out.write(reinterpret_cast<const char*> (&person.address.apartment_number), data_size);
        out.write(reinterpret_cast<const char*> (&person.age), data_size);
        
        
        buf = person.sex.length();
        out.write(reinterpret_cast<const char*> (&buf), data_size);
        out.write(person.sex.data(), buf);
    }
    out.close();
}

std::vector<myResident> loadDatabaseFromBinary (string fileName)
{
    std::vector<myResident> tmp;
    
    std::ifstream in(fileName, std::ios::binary);
    myResident person;
    unsigned char buf;
    unsigned char data_size = sizeof(unsigned char);
    while (!in.eof())
    {
        in.read(reinterpret_cast<char*> (&buf), data_size);
        in.read(const_cast<char *>(person.Fullname.firstname.data()), buf);
        
        in.read(reinterpret_cast<char*> (&buf), data_size);
        person.Fullname.midlename.resize(buf);
        in.read(const_cast<char *>(person.Fullname.midlename.data()), buf);
        
        in.read(reinterpret_cast<char*> (&buf), data_size);
        person.Fullname.lastname.resize(buf);
        in.read(const_cast<char *>(person.Fullname.lastname.data()), buf);
        
        in.read(reinterpret_cast<char*> (&buf), data_size);
        person.address.street.resize(buf);
        in.read(const_cast<char *>(person.address.street.data()), buf);
        
        in.read(reinterpret_cast<char*> (&person.address.house_number), data_size);
        in.read(reinterpret_cast<char*> (&person.address.apartment_number), data_size);
        in.read(reinterpret_cast<char*> (&person.age), data_size);
        
        in.read(reinterpret_cast<char*> (&buf), data_size);
        person.sex.resize(buf);
        in.read(const_cast<char *>(person.sex.data()), buf);
        
        tmp.push_back(person);
    }
    in.close();
    
    tmp.pop_back();
    return tmp;
}

void printAll (std::vector<myResident>& arr)// функция печати
{
    int databawseSize = getDatabaseSize(arr);
    for (int i = 0; i < databawseSize; i++)
    {
        cout << arr[i] << endl;
    }
}



int main()
{
    std::vector<myResident> people;
    
    people = loadDatabaseFromText("text_database.txt");
    printAll (people);
    
    cout << "------------sort---------------" << endl;
    std::sort(people.begin(),people.end());
    printAll (people);
    saveDatadaseInTextFormat(people,"Text.txt");
    
    cout << "------------save and load from binary format---------------" << endl;
    printAll (people);
    
    saveDatadaseInBinaryFormat (people, "bin_database.txt");
    people.clear();
    
    people = loadDatabaseFromBinary ("bin_database.bin");
    printAll (people);
    
    cout << "-----------print underage by street--------------" << endl;
    std::sort(people.begin(),people.end());
    PrintUnderageCountsForStreets (people);
}
