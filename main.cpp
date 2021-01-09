#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstring>
#include <sstream>

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
    ~myAddress ()
    {
        street="";
        house_number=0;
        apartment_number=0;
    }
};

template<typename T> string toString(const T &t)
{
    stringstream ss;
    ss << t;
    return ss.str();
}

std::ifstream & operator>> (std::ifstream& is , string& str)
{
    //char ch[255];
    string tmp;
    std::getline(is, tmp);
    str = tmp;
    //
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
    ~myFullname()
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
    ~myResident()
    {
        sex = "";
        age = 0;
        Fullname.firstname = "";
        Fullname.midlename = "";
        Fullname.lastname = "" ;
    }
};

std::ofstream & operator<< (std::ofstream& os , const myResident & rsdnt)
{
    os << rsdnt.Fullname;
    //os << " ";
    os << rsdnt.address;
    //os << " ";
    os << rsdnt.sex.c_str();
    os << endl;
    os << rsdnt.age <<endl;
    return os;
}

std::ifstream & operator>> (std::ifstream& is , myResident & rsdnt)
{
    is >> rsdnt.Fullname;
    //os << " ";
    is >> rsdnt.address;
    //os << " ";
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
    /* int size = 0;
    for (myResident i: arr)
    {
        size++;
    }
    return size;*/
    return arr.size();
}

void sort(std::vector<myResident>& arr)// сортировка
{
    myResident tmp;
    int dbSize = getDatabaseSize(arr);
    
    for (int i = 0; i < dbSize - 1; i++)
    {
        for (int j = i + 1; j < dbSize; j++) {
            const char* d1 = arr[i].Fullname.firstname.c_str();
            const char* d2 = arr[j].Fullname.firstname.c_str();
            if (strcmp(d1, d2) > 0)
            {
                tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            }
        }
    }
}

void sortByStreet(std::vector<myResident>& arr)// сортировка по улице
{
    myResident tmp;
    int dbSize = getDatabaseSize(arr);
    
    for (int i = 0; i < dbSize - 1; i++)
    {
        for (int j = i + 1; j < dbSize; j++) {
            const char* s1 = arr[i].address.street.c_str();
            const char* s2 = arr[j].address.street.c_str();
            if (strcmp(s1, s2) > 0)
            {
                tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            }
        }
    }
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
        //delete &rsdnt;
    }
    
    text_database.close();
    tmp.pop_back();
    return tmp;
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
            
        }
    }
}


void saveDatadaseInBinaryFormat (std::vector<myResident>& arr, string fileName)// для бинарного
{
    std::ofstream output (fileName, std::ios::binary);
    if (!output)
    {
       cout << "Error to open file in write mode: " << fileName;
        return;
    }
    for (int i = 0; i< arr.size(); i++)
    {
        output << arr[i];
    }
    
    output.close();
    
}

std::vector<myResident> loadDatabaseFromBinary (string fileName)// для бинарного
{
    std::vector<myResident> tmp;
    
    std::ifstream text_database;
    text_database.open(fileName, std::ios::binary);
    while (!text_database.eof())
    {
        myResident rsdnt;
        text_database >> rsdnt;
        tmp.push_back(rsdnt);
        //delete &rsdnt;
    }
    
    text_database.close();
    tmp.pop_back();
    return tmp;
}

void printUnderage(std::vector<myResident>& arr)// вывод несовершеннолетних
{
    int databaseSize = getDatabaseSize(arr);
    for (int i = 0; i < databaseSize; i++)
    {
        if (arr[i].age < 18)
        {
          cout << arr[i].address.street << ": " << arr[i].Fullname << endl;
        }
    }
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
    int databaseSize = 5;
    std::vector<myResident> people;
    //people[0] = {{"Mark", "Jordan", "Smith"},        {"Dover Road"  , 10, 4},   "Male", 30};
    //people[1] = {{"Curtis", "Merritt", "Black"},     {"Walden Road" ,11,5},     "Female", 20};
     //people[2] = {{"Donald", "Horton", "Garcia"},     {"Stroude Road",12,6},     "Male", 9};
    //people[3] = {{"Donald", "Tramp", "Jhohn"},       {"Rowland Rd"  ,13,7},     "Other", 8};
    //people[4] = {{"Thomas", "McCoy", "Miller"},      {"Stuart Street",11,7},    "Male", 17};
    
    people = loadDatabaseFromText("text_database.txt");
    printAll (people);
    
    cout << "sort" << endl;
    sort(people);
    printAll (people);
    saveDatadaseInTextFormat(people,"Text.txt");
    
    cout << "save and load from binary format" << endl;
    printAll (people);
    
    saveDatadaseInBinaryFormat (people, "bin_database.bin");
    people.clear();
    
    people = loadDatabaseFromBinary ("bin_database.bin");
    printAll (people);
    
    cout << "print underage by street" << endl;
    sortByStreet(people);
    PrintUnderageCountsForStreets (people);
    printUnderage(people);
}
