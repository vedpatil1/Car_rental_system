#include <iostream>
#include <conio.h>
#include <string.h>
#include <windows.h>
#include <fstream>

using namespace std;

struct Car
{
    string company, model, car_number;
    int year, rent;
    string status;
};

int customer_counter = 0;

string customer_login = "";

struct Account
{
    string username;
    string password;
    string city;
    string mail;
    long long int number;
};

Account accounts[100];

//struct Car cardata[50];

int count = 0;
string code = "";
long long int number;

void change_pass();
void add_vehicle();
void login();       //admin login
void activity();
void car_list();
// void car_details(Car car);
void change_details();
void admin_details();
// void logout();

// costumer
void customer_AC();
// void costomer_login();
void createAc();
int loadAccounts();
bool login_customer(string username, string password);
void saveAccounts();
void customer_activity();
void rentVehicle();
void returnVehicle();
void printdata();

fstream file("password.txt", ios::in | ios::out | ios::app);
fstream admin("admin.txt", ios::in | ios::out | ios::app);

int main()
{

    file.close();
    admin.close();
    file.open("password.txt");
    if (!file.is_open())
    {
        cout << "Somthing went wrong..." << endl;
        return 0;
    }
    else
    {
       // string a;
        while (file.good())
            getline(file, code);
        file.close();
    }
    customer_counter = loadAccounts();
    int choice;
    do
    {
        cout << "Enter who are you?\n1.Admin\n2.Customer\n3.Exit:";
        cin >> choice;
        switch (choice)
        {
        case 1:
            login();
            count = 0;
            break;
        case 2:
            customer_AC();
            break;
        case 3:
             choice = 0;
            cout << "Exited";
            break;           
        default:
            printf("\nInvalid option");
        }

    } while (choice != 0);

    return 0;
}

void login()
{
    string pass = "";
    char ch;
    // cout << "Car Rental System Login: "<<endl;
    cout << "*******Login Page***********" << endl;
    cout << "Enter Password: " << endl;
    ch = _getch();
    int limit = 0;
    while ((ch != 13) && (limit != 10))
    {
        pass.push_back(ch);
        cout << '*';
        ch = _getch();
        limit++;
    }
    if (pass == code)
    {
        cout << "\tPassword Matched" << endl;

        cout << "\tLoading...." << endl;
        char loading = 219;
        for (int i = 0; i <= 30; i++)
        {
            cout << loading;
            Sleep(40);
        }
        // system("PAUSE");
        cout << endl;
        cout << "Access Granted!\n***********Welcome to car rental system************" << endl;
        system("PAUSE");
        system("cls");
        activity();
    }
    else
    {
        cout << endl
             << "Wrong password\n";
        count++;
        if (count == 3)
        {
            cout << endl
                 << "Three attempts are done" << endl;
            system("PAUSE");
            system("cls");
            return;
        }
        else
        {
            login();
        }
    }
}

void activity()
{ // admin
    int ch;
    do
    {
        cout << "\nEnter Your choice:\n1.Vehicle list\n2.Add a new vehicle\n3.Change Admin Details\n4.Change Password\n5.customer details\n6.Admin details\n7.Logout\n:";
        cin >> ch;
        switch (ch)
        {
        case 1:
            car_list();
            break;
        case 2:
            add_vehicle();
            break;
        case 3:
            change_details();
            break;
        case 4:
            change_pass();
            break;
        case 5:
            printdata();
            break;
        case 6:
            admin_details();
            break;
        case 7:
            system("cls");
            return;
            break;
        default:
            cout << endl
                 << "Invalid option";
        }
    } while (ch != 0);
}

void change_pass()
{
    cout << "Enter the previous password: " << endl;
    string prev;
    char ch;
    ch = _getch();
    while (ch != 13)
    {
        prev.push_back(ch);
        cout << '*';
        ch = _getch();
    }
    if (prev == code)
    {
        cout << "Password matched successfully..." << endl;
        system("PAUSE");
        cout << "Enter the new password: ";
        ch = _getch();
        code = "";
        while (ch != 13)
        {
            code.push_back(ch);
            cout << '*';
            ch = _getch();
        }
        cout << endl;
        char loading = 219;
        for (int i = 0; i <= 30; i++)
        {
            cout << loading;
            Sleep(10);
        }
        cout << endl
             << "Successfully done..." << endl;
        cout << endl
             << "Enter 1 to show password or 0 to decline: ";
        int choi;
        cin >> choi;
        file.open("password.txt");
        if (!file.is_open())
        {
            cout << "Something went wrong.Password is saved temporarily" << endl;
        }
        else
        {
            // file<<endl;
            file << code;
            file.close();
        }
        if (choi == 1)
        {
            cout << endl
                 << code << endl;
        }
        else
            cout << "Got it..." << endl;

        system("PAUSE");
        system("cls");
    }
    else
    {
        cout << endl
             << "Wrong password\n"
             << endl;
    }
}

void add_vehicle()
{
    ofstream file("vehicles.txt", ios::app);
    if (!file.is_open())
    {
        cout << "Error: Unable to open file." << endl;
        return;
    }

    Car newVehicle;
    cout << "Enter Company: ";
    cin >> newVehicle.company;
    cout << "Enter model: ";
    cin >> newVehicle.model;
    cout << "Enter car number: ";
    cin >> newVehicle.car_number;
    cout << "Enter manufacturing year: ";
    cin >> newVehicle.year;
    cout << "Enter rent per day: ";
    cin >> newVehicle.rent;
    newVehicle.status = "Available";

    file << newVehicle.company << "\t" << newVehicle.model << "\t" << newVehicle.car_number << "\t" << newVehicle.year << "\t" << newVehicle.rent << "\t" << newVehicle.status << endl;

    file.close();
    char loading = 219;
    for (int i = 0; i <= 30; i++)
    {
        cout << loading;
        Sleep(10);
    }
    cout << "\nVehicle added successfully." << endl;
    system("PAUSE");
    system("cls");
}

void car_list()
{
    ifstream file("vehicles.txt");
    if (!file.is_open())
    {
        cout << "Error: Unable to open file." << endl;
        system("PAUSE");
        return;
    }

    cout << "Note That if rental status is a customer name then it is rented by that customer." << endl;
    Car temp;
    while (file >> temp.company >> temp.model >> temp.car_number >> temp.year >> temp.rent >> temp.status)
    {
        cout << "\nCompany name: " << temp.company << "\n";
        Sleep(400);
        cout << "\nModel Name: " << temp.model << "\n";
        Sleep(400);
        cout << "\nCar number: " << temp.car_number << "\n";
        Sleep(400);
        cout << "\nModel year: " << temp.year << "\n";
        Sleep(400);
        cout << "\nCar rent: " << temp.rent << "\n";
        Sleep(400);
        cout << "\nRental status: " << temp.status << "\n";
        Sleep(400);
        cout << endl
             << endl;
        Sleep(1000);
    }

    file.close();
    system("PAUSE");
}

void change_details()
{
    string first_name, mid_name, last_name;
    cout << "Enter First name: " << endl;
    cin >> first_name;
    cout << "Enter Mid name: " << endl;
    cin >> mid_name;
    cout << "Enter Last name: " << endl;
    cin >> last_name;
    long long int number;
    cout << "Enter contact number: " << endl;
    cin >> number;
    ofstream admin("admin.txt");
    if (!admin.is_open())
    {
        cout << "Admin informaiton file missing..." << endl;
    }
    admin << "**************Car Rental System****************" << endl;
    admin << "Company owner: " << first_name << " " << mid_name << " " << last_name << endl;
    admin << "Contact number: " << number << endl;
    admin.close();
    // system("PAUSE");
    return;
}

void admin_details()
{
    admin.open("admin.txt");
    if (!admin.is_open())
    {
        cout << "Error: Unable to open file." << endl;
    }
    else
    {
        string own;
        while (admin.good())
        {
            getline(admin, own);
            cout << own << endl;
        }
        admin.close();
    }
    system("PAUSE");
}

void customer_AC()
{
    bool loggedIn = false;
    string username, password;
    char ch;
    cout << "1. Create Account\n";
    cout << "2. Login\n";
    cout << "3. Exit\n";
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;

    switch (choice)
    {
    case 1:
        createAc();
        saveAccounts();
        cout << "Enter\n 1 for login\n 0 for exit\n: " << endl;
        int cho;
        cin >> cho;
        if (cho == 1)
        {
            cout << "Please wait..." << endl;
            char loading = 219;
            for (int i = 0; i <= 30; i++)
            {
                cout << loading;
                Sleep(10);
            }
            customer_activity();
        }
        else
        {
            return;
        }
        break;
    case 2:
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        ch = _getch();
        while (ch != 13)
        {
            password.push_back(ch);
            cout << '*';
            ch = _getch();
        }
        loggedIn = login_customer(username, password);
        if (loggedIn)
        {
            customer_login = username;
            cout<<endl<< "Login successful!\n";
            cout << "Please wait..." << endl;
            char loading = 219;
            for (int i = 0; i <= 30; i++)
            {
                cout << loading;
                Sleep(10);
            }
            system("cls");
            customer_activity();
        }
        else
        {
            cout << "Incorrect username or password. Please try again.\n";
        }
        break;
    case 3:
        cout << "Exiting the program...\n";
        return;
    default:
        cout << "Invalid choice. Please try again.\n";
        break;
    }
}

void printdata()
{
    for (int i = 0; i < customer_counter; i++)
    {
        cout << "username: " << accounts[i].username << endl;
        cout << "password: " << accounts[i].password << endl;
        cout << "city: " << accounts[i].city << endl;
        cout << "mail: " << accounts[i].mail << endl;
        cout << "number: " << accounts[i].number << endl;
        cout << "---------------------------------------------" << endl;
        Sleep(1000);
    }
    system("PAUSE");
    system("cls");
}

int loadAccounts()
{
    ifstream inFile("accounts.txt");
    int customer_counter = 0;
    if (!inFile.is_open())
    {
        cout << "Warning: Unable to open file for reading. No existing accounts found.\n";
        return customer_counter;
    }
    while (inFile >> accounts[customer_counter].username >> accounts[customer_counter].password >> accounts[customer_counter].city >> accounts[customer_counter].mail >> accounts[customer_counter].number)
    {
        customer_counter++;
    }
    inFile.close();
    return customer_counter;
}

void saveAccounts()
{
    ofstream outFile("accounts.txt");
    if (!outFile.is_open())
    {
        cout << "Error: Unable to open file for writing.\n";
        return;
    }
    for (int i = 0; i < customer_counter; ++i)
    {
        outFile << accounts[i].username << " " << accounts[i].password << " " << accounts[i].city << " " << accounts[i].mail << " " << accounts[i].number << endl;
    }
    outFile.close();
}

bool login_customer(string username, string password)
{
    for (int i = 0; i < customer_counter; ++i)
    {
        if (accounts[i].username == username && accounts[i].password == password)
        {
            return true;
        }
    }
    return false;
}

void createAc()
{
    cout << "Enter username: ";
    cin >> accounts[customer_counter].username;
    cout << "Enter password: ";
    string prev;
    char ch;
    ch = _getch();
    while (ch != 13)
    {
        prev.push_back(ch);
        cout << '*';
        ch = _getch();
    }
    accounts[customer_counter].password = prev;
    cout << "Enter City: ";
    cin >> accounts[customer_counter].city;
    cout << "Enter e-mail id: ";
    cin >> accounts[customer_counter].mail;
    cout << "Enter contact number: ";
    cin >> accounts[customer_counter].number;
    cout << "Account created successfully!\n";
    customer_counter++;
}

void customer_activity()
{
    int choice;
    do
    {
        cout << "\nenter your choice\n1.check vehicles \n2.rent vehicles\n3.return vehicle \n4.contact information\n5.Exit" << endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
            car_list();
            break;
        case 2:
            rentVehicle();
            break;
        case 3:
            returnVehicle();
            break;
        case 4:
            admin_details();
            break;
        case 5:
            return;
        default:
            cout << "Invalid option." << endl;
            break;
        }
    } while (choice != 0);
}

void rentVehicle()
{
    string company, model;
    cout << "Enter company of vehicle to rent: ";
    cin >> company;
    cout << "Enter model of vehicle to rent: ";
    cin >> model;

    ifstream file("vehicles.txt");
    if (!file)
    {
        cout << "Error: Unable to open file." << endl;
        return;
    }

    ofstream tempFile("temp.txt");
    Car temp;
    bool found = false;
    while (file >> temp.company >> temp.model >> temp.car_number >> temp.year >> temp.rent >> temp.status)
    {
        if (temp.company == company && temp.model == model && temp.status == "Available")
        {
            temp.status = customer_login;
            cout << "\nCompany name: " << temp.company << "\n";
            Sleep(400);
            cout << "\nModel Name: " << temp.model << "\n";
            Sleep(400);
            cout << "\nCar number: " << temp.car_number << "\n";
            Sleep(400);
            cout << "\nModel year: " << temp.year << "\n";
            Sleep(400);
            cout << "\nCar rent: " << temp.rent << "\n";
            Sleep(400);
            cout << "\nRental status: " << temp.status << "\n";
            Sleep(400);
            cout << "Pickup and Drop up location: At shop, TKIET, warananagar, kolhapur" << endl;
            found = true;
        }
        tempFile << temp.company << " " << temp.model << " " << temp.car_number << " " << temp.year << " " << temp.rent << " " << temp.status << endl;
    }

    file.close();
    tempFile.close();

    remove("vehicles.txt");
    rename("temp.txt", "vehicles.txt");

    if (found)
        cout << "Vehicle rented successfully." << endl;
    else
        cout << "Vehicle not found or already rented." << endl;
}

void returnVehicle()
{
    string make, model;
    cout << "Enter company of vehicle to return: ";
    cin >> make;
    cout << "Enter model of vehicle to return: ";
    cin >> model;

    ifstream file("vehicles.txt");
    if (!file)
    {
        cout << "Error: Unable to open file." << endl;
        return;
    }

    ofstream tempFile("temp.txt");
    Car temp;
    bool found = false;
    while (file >> temp.company >> temp.model >> temp.car_number >> temp.year >> temp.rent >> temp.status)
    {
        if (temp.company == make && temp.model == model && temp.status == customer_login)
        {
            temp.status = "Available";
            found = true;
        }
        tempFile << temp.company << " " << temp.model << " " << temp.car_number << " " << temp.year << " " << temp.rent << " " << temp.status << endl;
    }

    file.close();
    tempFile.close();

    remove("vehicles.txt");
    rename("temp.txt", "vehicles.txt");

    if (found)
        cout << "Vehicle returned successfully." << endl;
    else
        cout << "Vehicle not found or already available." << endl;
}
