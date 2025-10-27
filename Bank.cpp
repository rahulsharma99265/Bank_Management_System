/*
MINI PROJECT
R K PUBLIC BANK

 */


#include <iostream>
#include <cstring>
#include <fstream>
#include <conio.h>
using namespace std;
class RKBANK
{
    char Acc_no[15],Name[20],Address[25],Pin[5],BusOcc[20];
    string Date,Time;
    char Type;
    double Bal;
    public :
    bool Create();             // function to get data from user
    void Modify();	           // function to add new data
    void Display();            // function to display account details
    void Delete(char[]);       // function to delete account
    void Display_All();        // function to display all account holders
    void Dep(int x)            // function to deposit amount
    {
        Bal += x;
        Update();
    }
    bool Draw(int x)           // function to withdraw amount
    {
        if(x <= Bal)
        {
            Bal -= x;
            Update();
            return true;
        }
        else
            return false;
    }
    void writeDateTime()        // function to read date and time from system
    {
        Date = __DATE__;
        Time = __TIME__;
    }
    void readDateTime()         // function to write date and time from system
    {
        cout << "\tAccount Open Date   : " << Date << endl;
        cout << "\tAccount Open Time   : " << Time << endl;
    }
    void New_Pin()              // function to set new pin
    {
        cout << "\tEnter New Pin(4 Digit) : ";
        cin.ignore();
        cin.getline(Pin,5);
        Update();
        cout << "\n\tPin Changed Successfully...\n";
        system("Pause");
    }
    bool found(char Acc_no[],char Pin[])   // function to found account using account number and pin
    {
        bool flag = false;
        ifstream fin("account.dat",ios :: in | ios :: binary);
        if(fin)
        {
            while(fin.read((char*)this,sizeof(*this)))
            {
                if(!strcmp(this->Acc_no,Acc_no) && !strcmp(this->Pin,Pin))
                {
                    flag = true;
                    break;
                }
            }
        }
        fin.close();
        return flag;
    }
    bool found(char Acc_no[])        // function to found account using account number only
    {
        bool flag = false;
        ifstream fin("account.dat",ios :: in | ios :: binary);
        if(fin)
        {
            while(fin.read((char*)this,sizeof(*this)))
            {
                if(!strcmp(this->Acc_no,Acc_no))
                {
                    flag = true;
                    break;
                }
            }
        }
        fin.close();
        return flag;
    }
    void Update()           // function for Update account details into file
    {
        fstream file("account.dat", ios::ate | ios::in | ios::out | ios::binary);
        if (file)
        {
            streampos position = file.tellg();
            file.seekp(position - static_cast<streampos>(sizeof(*this)), ios::beg);
            file.write((char*)this, sizeof(*this));
            file.close();
        }
    }
};
bool RKBANK :: Create()
{
    bool flag = true;
    int temp;
    ofstream fout("account.dat",ios::out|ios::app|ios::binary);
    cout << "\tAccount Number : ";
    cin.ignore();
    cin.getline(Acc_no,15);
    cout << "\tFull Name : ";
    cin.getline(Name,20);
    cout << "\tAccount Type(c for Current Account/s for Saving Account) : ";
    cin >> Type;
    cout << "\tResidental Address : ";
    cin.ignore();
    cin.getline(Address,25);
    if(Type == 'c')
    {
        cout << "\tBusiness : ";
        cin.getline(BusOcc,20);
        CUR :
        cout << "\tDeposite (min amount 5000) : ";
        cin >> Bal;
        if(Bal < 5000)
        {
            system("cls");
            cout << "\tOops! Sorry " << Name << endl;
            cout << "\n\t1. Reset Amount \n";
            cout << "\n\t2. Back \n";
            cin >> temp;
            if(temp == 1)
                goto CUR;
            else
                flag = false;
        }
    }
    else
    {
        cout << "\tOccupation : ";
        cin.getline(BusOcc,20);
        SAV :
        cout << "\tDeposite (min amount 100) : ";
        cin >> Bal;
        if(Bal < 100)
        {
            system("cls");
            cout << "\tOops! Sorry " << Name << endl;
            cout << "\n\t1. Reset Amount \n";
            cout << "\n\t2. Back \n";
            cin >> temp;
            if(temp == 1)
                goto SAV;
            else
                flag = false;
        }
    }
    if(!flag)
    {
        fout.close();
        return flag;
    }
    else
    {
        cout << "\tPin(4 Digit) : ";
        cin.ignore();
        cin.getline(Pin,5);
	    writeDateTime();
        fout.write((char *)this, sizeof(*this));
        fout.close();
        return flag;
    }
}
void RKBANK :: Display()
{
    cout << "\tAccount Number      : " << Acc_no << endl;
    cout << "\tName                : " << Name << endl;
    cout << "\tAccount Type        : ";

    if(Type == 'c')
        cout << "Current\n";
    else
        cout << "Saving\n";

    cout << "\tResidental Address  : " << Address << endl;
    if(Type == 'c')
    	cout << "\tBusiness            : " << BusOcc << endl;
    else
    	cout << "\tOccupation          : " << BusOcc << endl;
    cout << "\tBalance             : " << Bal << endl;
}
void RKBANK :: Modify()
{
    int ch;
    char name[20],address[25],busocc[20];
    do
    {
        cout << "\n\t1. Name\n";
        cout << "\n\t2. Residental Address\n";
        cout << "\n\t3. Business/Occupation\n";
        cout << "\n\t4. Done\n";
        cin >> ch;
        switch(ch)
        {
            case 1:
            cout << "\tFull Name : ";
            cin.ignore();
            cin.getline(name,20);
            strcpy(this->Name,name);
            break;
            case 2:
            cout << "\tResidental Address : ";
            cin.ignore();
            cin.getline(address,25);
            strcpy(this->Address,address);
            break;
            case 3:
            if(Type == 'c')
            {
                cout << "\tBusiness : ";
                cin.ignore();
                cin.getline(busocc,20);
                strcpy(this->BusOcc,busocc);
            }
            else
            {
                cout << "\tOccupation : ";
                cin.ignore();
                cin.getline(BusOcc,20);
                strcpy(this->BusOcc,busocc);
            }
            break;
            case 4:Update();
            return;
            default : cerr << "\tInvalid Choice\n";
        }
    }while(ch>0&&ch<5);
}
void RKBANK :: Delete(char acc_no[])
{
    ifstream fin;
    ofstream fout;

    fin.open("account.dat",ios :: in | ios::binary);
    fout.open("temp.dat",ios :: out | ios::binary);
    fin.read((char*)this,sizeof(*this));
    if(fin)
    {
        while (!fin.eof())
        {
            if (strcmp(this->Acc_no,acc_no))
                fout.write((char *)(this), sizeof(*this));
            fin.read((char*)this,sizeof(*this));
        }
        fin.close();
        fout.close();
        remove("account.dat");
        rename("temp.dat", "account.dat");
        cout << "\n\tAccount Delete Successfully...\n";
    }
    else
    {
        cerr << "\n\tAccount Can't Be Deleted\n";
    }
}
void RKBANK :: Display_All()
{
    ifstream fin("account.dat",ios::in | ios::binary);
    if(fin)
    {
        fin.read((char*)this,sizeof(*this));
        while(!fin.eof())
        {
            Display();
            readDateTime();
            cout <<"\n\t###############################################\n\n";
            fin.read((char*)this,sizeof(*this));
        }
    }
    else
        cerr << "\nCan't Be Displayed\t";
    fin.close();

}


//***************************************************************
//    	function declaration
//****************************************************************

void WriteAccount();	   // function to write record in binary file
void Modify_Details();     //function to modify record of file
void Delete_Details();     //function to delete record of file
void Display_all();   	   // function to display all account details
void Rights();             // function to give rights
void EmployeeMenu();       // function for employee usage
void CustomerMenu();       // function for customer usage

//***************************************************************
//    	THE MAIN FUNCTION OF PROGRAM
//****************************************************************

int main()
{
    int choice;
    do
    {
        system("cls");
        cout << "\t------------------------------\n";
        cout << "\t  WELCOME TO R K PUBLIC BANK \n";
        cout << "\t------------------------------\n";
        cout << "\n\t1. Employee\n";
        cout << "\n\t2. Customer\n";
        cout << "\n\t3. Administrative Rights/ Customer Rights\n";
        cout << "\n\t4. Exit\n";
        cin >> choice;
        switch(choice)
        {
            case 1: system("cls");
            EmployeeMenu();
            break;
            case 2: system("cls");
            CustomerMenu();
            break;
            case 3: system("cls");
            Rights();
            break;
            case 4:
            system("cls");
            cout << "\n\tTHANKS FOR VISITING RK PUBLIC BANK\n";
            cout << "\n\tExiting...\n";
            system("Pause");
            exit(0);
            default : cerr << "\n\tInvalid Choice !\n";
        }
    }while(choice>0 && choice <5);
    return 0;
}

void EmployeeMenu()
{
    int choice;
    string Id,Pswd;
    EMP:
    cout << "\n\tEmployee ID : ";
    cin >> Id;
    cout << "\n\tPassword : ";
    cin >> Pswd;
    if(Id == "RK@123" && Pswd == "RK#123")
    {
        do
        {
            system("cls");
            cout << "\t-------------------------------\n";
            cout << "\t  WELCOME TO EMPLOYEE SECTION \n";
            cout << "\t-------------------------------\n";
            cout << "\n\t1. Create Account\n";
            cout << "\n\t2. Modify Account\n";
            cout << "\n\t3. Delete Account\n";
            cout << "\n\t4. All Account Holders Details\n";
            cout << "\n\t5. Back\n";
            cout << "\n\t6. Exit\n";
            cin >> choice;
            switch(choice)
            {
                case 1: system("cls");
                WriteAccount();
                break;
                case 2: system("cls");
                Modify_Details();
                break;
                case 3: system("cls");
                Delete_Details();
                break;
                case 4: system("cls");
                Display_all();
                break;
                case 5: system("cls");
                return;
                case 6:
                system("cls");
                cout << "\n\tTHANKS FOR VISITING RK PUBLIC BANK\n";
                cout << "\n\tExiting...\n";
                system("Pause");
                exit(0);
                default : cerr << "\n\tInvalid Choice !\n";
            }
        }while(choice>0 && choice <7);
    }
    else
    {
        cout << "\t---------------------------\n";
        cout << "\t  OOPS INCORECT PASSWORD! \n";
        cout << "\t---------------------------\n";
        cout << "\n\t1. Retry\n";
        cout << "\n\t2. Back\n";
        cout << "\n\t3. Exit\n";
        cin >> choice;
        switch(choice)
        {
            case 1:system("cls");
            goto EMP;
            break;
            case 2:system("cls");
            return;
            case 3: system("cls");
            cout << "\n\tTHANKS FOR VISITING RK PUBLIC BANK\n";
            cout << "\n\tExiting...\n";
            system("Pause");
            exit(0);
            default : return;
        }
    }
}
void CustomerMenu()
{
    int choice,temp;
    char Acc_no[15],Pin[5];
    RKBANK user;
    CUS:
    cout << "\n\tAccount Number : ";
    cin.ignore();
    cin.getline(Acc_no,15);
    cout << "\n\tPin : ";
    cin.getline(Pin,5);
    if(user.found(Acc_no,Pin))
    {
        do
        {
            system("cls");
            cout << "\t-------------------------------\n";
            cout << "\t  WELCOME TO CUSTOMER SECTION \n";
            cout << "\t-------------------------------\n";
            cout << "\n\t1. Account Details\n";
            cout << "\n\t2. Withdraw Money\n";
            cout << "\n\t3. Deposite Money\n";
            cout << "\n\t4. Change Pin\n";
            cout << "\n\t5. Back\n";
            cout << "\n\t6. Exit\n";
            cin >> choice;
            switch(choice)
            {
                case 1:system("cls");
                user.Display();
                system("Pause");
                break;
                case 2:system("cls");
                cout << "\tEnter Amount : ";
                cin >> temp;
                if(!user.Draw(temp))
                    cout << "\tInsufficient Balance\n";
                break;
                case 3: system("cls");
                cout << "\tEnter Amount : ";
                cin >> temp;
                user.Dep(temp);
                break;
                case 4: system("cls");
                user.New_Pin();
                break;
                case 5: system("cls");
                return;
                case 6: system("cls");
                cout << "\n\tTHANKS FOR VISITING RK PUBLIC BANK\n";
                cout << "\n\tExiting...\n";
                system("Pause");
                exit(0);
                default : cerr << "\n\tInvalid Choice !\n";
            }
        }while(choice>0 && choice <7);
    }
    else
    {
        cout << "\t------------------------------\n";
        cout << "\t  OOPS INCORECT INFORMATION! \n";
        cout << "\t------------------------------\n";
        cout << "\n\t1. Retry\n";
        cout << "\n\t2. Back\n";
        cout << "\n\t3. Exit\n";
        cin >> choice;
        switch(choice)
        {
            case 1:system("cls");
            goto CUS;
            break;
            case 2:system("cls");
            return;
            case 3: system("cls");
            cout << "\n\tTHANKS FOR VISITING RK PUBLIC BANK\n";
            cout << "\n\tExiting...\n";
            system("Pause");
            exit(0);
            default : return;
        }
    }
}
void WriteAccount()
{
    RKBANK user;
    if(user.Create())
    {
        cout << "\n\tAccount Created Successfully...\n";
        system("Pause");
    }

    else
    {
        cout <<"\n\tAccount Can't Be Created...\n";
        system("Pause");
    }
}
void Modify_Details()
{
    RKBANK user;
    char acc_no[15];
    int choice;
    ACC :
    cout << "\n\tAccount Number : ";
    cin.ignore();
    cin.getline(acc_no,15);
    if(user.found(acc_no))
    {
        user.Display();
        cout << "\n\t################################\n";
        user.Modify();
    }
    else
    {
        cout << "\t---------------------------------\n";
        cout << "\t  OOPS INCORECT ACCOUNT NUMBER! \n";
        cout << "\t---------------------------------\n";
        cout << "\n\t1. Retry\n";
        cout << "\n\t2. Back\n";
        cout << "\n\t3. Exit\n";
        cin >> choice;
        switch(choice)
        {
            case 1:system("cls");
            goto ACC;
            break;
            case 2:system("cls");
            return;
            case 3: system("cls");
            cout << "\n\tTHANKS FOR VISITING RK PUBLIC BANK\n";
            cout << "\n\tExiting...\n";
            system("Pause");
            exit(0);
            default : return;
        }
    }
}
void Delete_Details()
{
    RKBANK user;
    char acc_no[15];
    int choice;
    ACC :
    cout << "\n\tAccount Number : ";
    cin.ignore();
    cin.getline(acc_no,15);
    if(user.found(acc_no))
    {
        user.Display();
        user.Delete(acc_no);
	system("Pause");
    }
    else
    {
        cout << "\t---------------------------------\n";
        cout << "\t  OOPS INCORECT ACCOUNT NUMBER! \n";
        cout << "\t---------------------------------\n";
        cout << "\n\t1. Retry\n";
        cout << "\n\t2. Back\n";
        cout << "\n\t3. Exit\n";
        cin >> choice;
        switch(choice)
        {
            case 1:system("cls");
            goto ACC;
            break;
            case 2:system("cls");
            return;
            case 3: system("cls");
            cout << "\n\tTHANKS FOR VISITING RK PUBLIC BANK\n";
            cout << "\n\tExiting...\n";
            system("Pause");
            exit(0);
            default : return;
        }
    }
}
void Display_all()
{
    RKBANK user;
    user.Display_All();
    system("Pause");
}
void Rights()
{
    cout << "\n\t### Administrative Rights ###\n\n";
    cout << "\n\t1. Regulatory Compliance : Banks must adhere to financial regulations for system stability.\n";
    cout << "\n\t2. Risk Management : Financial institutions manage risks to protect both the bank and customers.\n";
    cout << "\n\t3. Account Management : Banks can open, close, and suspend accounts with set conditions.\n";
    cout << "\n\t4. Security Measures : Banks implement measures to protect data and prevent fraud.\n";
    cout << "\n\t5. Technology Infrastructure : Maintenance and upgrades ensure smooth digital banking operations.\n";
    cout << "\n\n\t### Consumer Rights ###\n\n";
    cout << "\n\t1. Privacy and Confidentiality : Customers have the right to data privacy and confidentiality.\n";
    cout << "\n\t2. Fair and Transparent Practices : Customers deserve clear disclosure of terms, fees, and rates.\n";
    cout << "\n\t3. Access to Information : Customers can access account details, transactions, and fees.\n";
    cout << "\n\t4. Dispute Resolution : Customers can dispute unauthorized transactions and seek resolution.\n";
    cout << "\n\t5. Non-Discrimination : Banks must treat all customers fairly and without bias.\n";
    cout << "\n\t6. Redress Mechanisms : Consumers have the right to seek redress for grievances and disputes.\n";
    system("Pause");
}
