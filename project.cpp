#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <stdlib.h>
using namespace std;

class bank
{
public:
    int accNo;
    string name;
    int deposit;
    char type;

    void createAcc();
    void viewAcc();
    void accountStatus();
    bank get_data();
    void writeintoFile();
    void readFile();
    void deleteRecord();
    void updateRecord();
};

void bank ::createAcc()
{
    cout << "\nEnter acc number : ";
    cin >> accNo;
    cout << "\nEnter your name : ";
    cin.ignore();
    getline(cin, name);
    cout << "\nEnter Initial Deposit Amount (>=500 Rs. or <=1000 Rs.) : ";
    cin >> deposit;
    cout << "\nType of account (C/S) : ";
    cin >> type;
    type = toupper(type);
    cout << "\n";
}

void bank ::viewAcc()
{
    cout << "\nAccount Number : " << accNo << endl;
    cout << "\nName : " << name << endl;
    cout << "\nBank Balance : " << deposit << endl;
    if (type == 'C')
        cout << "\nType of Bank Account : Current" << endl;
    else
        cout << "\nType of Bank Account : Savings" << endl;
}

int credit(int d)
{
    int amount;
    cout << "\nEnter the amount you want to add in your account : ";
    cin >> amount;
    int x = (d) + amount;
    return x;
}

int debit(int d)
{
    int amount;
    cout << "\nEnter amount you want to draw from the account : ";
    cin >> amount;
    if ((d) >= 500)
    {
        int x = (d)-amount;
        return x;
    }
    if ((d) < 500)
        cout << "No Enough Balance" << endl;
}

int modify_deposit(int de)
{
    int amount;
    char c;
    cout << "\nYou want to credit or debit amount (a/d) ";
    cin >> c;
    if (c == 'A' || c == 'a')
    {
        cout << "\nEnter amount you want to add : ";
        cin >> amount;
        return de + amount;
    }
    if (c == 'd' || c == 'D')
    {
        cout << "\nEnter money you want to withdraw : ";
        cin >> amount;
        if (de - amount < 500)
        {
            cout << "\nInsufficient Balance to withdraw \n";
            return de;
        }
        else
        {
            return de - amount;
        }
    }
}

string modify_name(string n)
{
    string Name;
    cout << "\nEnter your new name for modification : ";
    cin.ignore();
    getline(cin, Name);
    n = Name;
    return n;
}

char modify_type(char t)
{
    char c;
    cout << "\nchoose your account type : ";
    cin.ignore();
    cin >> c;
    c = toupper(c);
    t = c;
    return t;
}

void bank ::accountStatus()
{
    bool found = false;
    bank b2;
    int AccNo;
    ifstream file;
    file.open("Bank.txt");

    cout << "\nEnter your account number : ";
    cin >> AccNo;

    cout << "\n";
    cout << "---------------------------------------------------------------------------------------------------" << endl;
    cout << "Account Number" << setw(15) << " "
         << "Name" << setw(15) << " "
         << "Bank Balance" << setw(15) << " "
         << "Type of Account" << endl;
    cout << "---------------------------------------------------------------------------------------------------" << endl;
    if (file.is_open())
    {
        file >> b2.accNo;
        file.ignore();
        getline(file, b2.name);
        file >> b2.deposit;
        file >> b2.type;
        while (!file.eof())
        {
            if (b2.accNo == AccNo)
            {
                cout << "\n";
                cout << b2.accNo << setw(18) << " " << b2.name << setw(18) << " "
                     << b2.deposit << setw(24) << " " << b2.type << "\n"
                     << endl;
                found = true;
                break;
            }
            else
            {
                file >> b2.accNo;
                file.ignore();
                getline(file, b2.name);
                file >> b2.deposit;
                file >> b2.type;
                found = false;
            }
        }
        if (found == false)
            cout << "\nNo Such Record has been found with account number "
                 << " " << AccNo << endl;
    }
    file.close();
}

void bank ::writeintoFile()
{
    fstream file;
    file.open("Bank.txt", ios ::app);
    if (file.is_open())
    {
        file << accNo << endl;
        file << name << endl;
        file << deposit << endl;
        file << type << endl;
        file.close();
    }
}

void bank ::readFile()
{
    ifstream file;
    bank b1;
    file.open("Bank.txt", ios ::in);
    if (file.is_open())
    {
        file >> b1.accNo;
        file.ignore();
        getline(file, b1.name);
        file >> b1.deposit;
        file >> b1.type;
        cout << "----------------------------------------------------------------------------------------------------------------------------" << endl;
        cout << "Account Number" << setw(20) << " "
             << "Name" << setw(20) << " "
             << "Balance" << setw(20) << " "
             << "Type Of Account" << endl;
        cout << "----------------------------------------------------------------------------------------------------------------------------" << endl;
        while (!file.eof())
        {
            cout << b1.accNo << setw(15) << " " << b1.name << setw(15) << " " << b1.deposit << setw(15) << " " << b1.type << endl;

            file >> b1.accNo;
            file.ignore();
            getline(file, b1.name);
            file >> b1.deposit;
            file >> b1.type;
        }
        cout << "----------------------------------------------------------------------------------------------------------------------------" << endl;
        cout << "----------------------------------------------------------------------------------------------------------------------------" << endl;
    }
}

void bank ::deleteRecord()
{
    bank b1;
    int AccNo;
    cout << "\nEnter your account number : ";
    cin >> AccNo;
    ifstream file;
    ofstream tempFile;
    tempFile.open("temp.txt", ios ::app);
    file.open("Bank.txt", ios ::in);
    if (file.is_open() && tempFile.is_open())
    {
        file >> b1.accNo;
        file.ignore();
        getline(file, b1.name);
        file >> b1.deposit;
        file >> b1.type;
        while (!file.eof())
        {
            if (b1.accNo != AccNo)
            {
                tempFile << b1.accNo << endl;
                tempFile << b1.name << endl;
                tempFile << b1.deposit << endl;
                tempFile << b1.type << endl;
            }
            file >> b1.accNo;
            file.ignore();
            getline(file, b1.name);
            file >> b1.deposit;
            file >> b1.type;
        }
    }
    file.close();
    tempFile.close();
    remove("Bank.txt");
    rename("temp.txt", "Bank.txt");
    cout << "Record Successfully Deleted.. " << endl;
}

bank bank ::get_data()
{
    fstream file;
    file.open("Bank.txt", ios::in);
    bank obj;
    file >> obj.accNo;
    file >> obj.name;
    file >> obj.deposit;
    file >> obj.type;
    file.close();
    return obj;
}
void bank ::updateRecord()
{
    ifstream file;
    ofstream tempfile;
    int AccNo;
    cout << "Enter Account number  ";
    cin >> AccNo;
    file.open("Bank.txt", ios ::in);
    tempfile.open("temp.txt", ios ::app);
    bank b1;
    file >> b1.accNo;
    file.ignore();
    getline(file, b1.name);
    file >> b1.deposit;
    file >> b1.type;
    while (!file.eof())
    {
        if (b1.accNo == AccNo)
        {
            cout << "\n a.) For debit/ Credit Money" << endl;
            cout << "\n b.) To Update Name" << endl;
            cout << "\n c.) To update your account type" << endl;
            char ch;
            cout << "\nChoose an option (a/b/c) : ";
            cin.ignore();
            cin >> ch;

            if (ch == 'a' || ch == 'A')
            {
                int dep = modify_deposit(b1.deposit);
                b1.deposit = dep;
            }
            else if (ch == 'b' || ch == 'B')
            {
                string n = modify_name(b1.name);
                b1.name = n;
            }
            else
            {
                char t = modify_type(b1.type);
                b1.type = t;
            }
        }
        tempfile << b1.accNo << endl;
        tempfile << b1.name << endl;
        tempfile << b1.deposit << endl;
        tempfile << b1.type << endl;

        file >> b1.accNo;
        file.ignore();
        getline(file, b1.name);
        file >> b1.deposit;
        file >> b1.type;
    }
    file.close();
    tempfile.close();
    remove("Bank.txt");
    rename("temp.txt", "Bank.txt");
}

void intro()
{
    cout << "            <--------------------------------------------------------->             "
         << "\n"
         << endl;
    cout << "            <------------Welcome to Bank Management System------------>             "
         << "\n"
         << endl;
    cout << "            <--------------------------------------------------------->             "
         << "\n"
         << endl;
}

void projectdoneby()
{
    cout << "                      Name       "
         << "Songala Rohith Kumar" << endl;
    cout << "                      Branch     "
         << "Mining Engineering" << endl;
    cout << "                      Semester   "
         << "VII" << endl;
    cout << "                      College    "
         << "National Institute of Technology, Raipur" << endl;
}

int main()
{
    bank b;
    int c;
    bool done = false;

    do
    {
        system("CLS");
        intro();

        cout << "\n 1.) Create Account" << endl;
        cout << "\n 2.) View Account Status" << endl;
        cout << "\n 3.) Write" << endl;
        cout << "\n 4.) Read" << endl;
        cout << "\n 5.) Delete Record" << endl;
        cout << "\n 6.) Update Record" << endl;
        cout << "\n 7.) Exit" << endl;

        cout << "\n Choose an option : ";
        cin >> c;

        switch (c)
        {
        case 1:
            b.createAcc();
            system("'pause");
            break;
        case 2:
            b.accountStatus();
            system("pause");
            break;
        case 3:
            b.writeintoFile();
            system("pause");
            break;
        case 4:
            b.readFile();
            system("pause");
            break;
        case 5:
            b.deleteRecord();
            system("pause");
            break;
        case 6:
            b.updateRecord();
            system("pause");
            break;
        case 7:
            char temp;
            cout << "\nYou Want to Exit (y/n) : ";
            cin >> temp;
            if (temp == 'y')
                done = true;
            else
                done = false;
            break;
        }
        system("CLS");
    } while (done != true);

    cout << "Project Done By  " << endl;
    projectdoneby();
    cout << "\nThanks For Visiting us. " << endl;
    cout << "\nAll Rights Reserved" << endl;
}