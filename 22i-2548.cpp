#include<iostream>
#include<conio.h>
#include<string.h>
#include<string>
#include<fstream>
#include<unistd.h>
#include<ctime>
#include<stdlib.h>
using namespace std;




tm get_local_time();
bool datecheck(int,int,int,int);
const char l_destination[5][20] = { "LAHORE","ISLAMABAD","KARACHI","PESHAWAR","QUETTA" };   //local Destination
const char i_destination[25][20] = { "LONDON","BERLIN","DUBAI","RIYADH","BEIJING","PARIS","CANBERRA","TOKYO","WASHINGTON","DELHI","NEW_YORK", "ROME", "MADRID", "OTTAWA", "MEXICO", "BRASÍLIA", "BUENOSAIRES","MOSCOW", "CAIRO","ANKARA", "BAGHDAD", "TEHRAN", "JERUSALEM", "HANOI", "PRETORIA" }; //International Destination
int wt; 
int tkt;
int bus, eco;
string st="PM";
bool validCnic(string str){
	int count=0;
	for(int i=0;str[i]!='\0';++i){
		count++;
	}
	if(count==13){
		return true;
	}
	else
	return false;
}
string readPassword() {
    string password = "";
    char ch;
    while ((ch = _getch()) != '\r') {
        if (ch == '\b') {
            if (!password.empty()) {
                password.erase(password.length() - 1);
                cout << "\b \b"; // clear the last character from console
            }
        } else {
            password += ch;
            cout << "*";
        }
    }

    cout << endl;

    return password;
}
class FlightSchedule {
private:
    string des,loc;
    int x;
public:
    void schedule() {
        cout << "Schedule of Departure Airport \n";
        cout << "Departure Airports are : "<<endl;
        for (int i = 0; i < 5; i++)
        {
            cout << l_destination[i] << endl;
        }
        cout<< "Enter your origin(using BLOCK letters): ";
        cin >> des;
        cout << endl << "1. North\n2. South" << endl;
        x = getch();
        if (x == 49) {
            loc = "NORTH";
        }
        else {
            loc = "SOUTH";
        }
        cout << "Do you want to see schedule of \n1. Local \n2. Foreign\n";
        x = getch();
        if (x == 49) {
            LocalSchedule();
        }
        else if(x==50) {
            ForeignSchedule();
        }
    }
    void LocalSchedule() {
        int n = 0;
        int t = wt + 1;
        int tt=t+2;
        int x;
        for (int i = 0; n < 10; i++)
        {
        	x = rand() % 5;
        	//cout<<x<<endl;
            if (des != l_destination[x]) {
                cout << des << " " << loc << "\t\t" << l_destination[x] << "\t\t\t" << t << ":00" << "\t\t\t "<< tt << ":00" << endl;
                t += 2;
                tt += 2;
                if (t >= 24) {
                    t -=24;
                }
                if(tt>=24){
				tt-=24;
			    }
                n++;
            }
        }
    }
    void ForeignSchedule() {
        int t = wt + 3;
        int tt=t+6;
        int n = 0;
        int x;
        for (int i = 0; n<5 ; i++)
        {
        	if(t>=24){
            	t-=24;
			}
			if(tt>=24){
				tt-=24;
			}
            x = rand() % 25;
            //cout<<x<<endl;
            cout << des << " " << loc << "\t\t" << i_destination[x] << "\t\t" << t << ":00" << "\t\t "<< tt << ":00" << endl;
            t += 3;
            tt += 3;
            n++;
        }
    }
};

void Registration(){
	string cnic;
	string name;
	cout<<"Enter your full name : ";
	getline(cin,name);
	cout<<"Enter your CNIC No : ";
	getline(cin,cnic);
	while(true){
		if(validCnic(cnic)==1){
			break;
		}
		else{
			cout<<"Re-enter your CNIC No : ";
			getline(cin,cnic);
			}
	}
	ofstream myfile("Register.txt", ios::out | ios::app);
	myfile<<"Name : "<<name<<endl;
	myfile<<"CNIC No : "<<cnic<<endl;
}
class passenger {
private:
    const int bseats;
    const int eseats;
protected:
    string firstname, lastname, phone, mealtype, passport, Address;
    int  datedep, payment;
    char origin[30];
    char destination[30];
public:
    passenger(string f_name, string l_name, string phone_no, string add = "N/A", string pass_no = "N/A", int dd = 000000) : bseats(10), eseats(50)
    {
        datedep = dd;
        firstname = f_name;
        lastname = l_name;
        Address = add;
        phone = phone_no;
        passport = pass_no;
        bus = bseats;
        eco = eseats;
    }

    virtual bool ldest() = 0;
    virtual bool idest(string pass) = 0;
    virtual void seats() = 0;
    virtual void Meals() = 0;
    virtual void Registration() = 0;
    virtual bool display() = 0;
    virtual void drive() = 0;

};

class booking :public passenger
{
protected:
    int i, j, n, m, k, NoOfSeats, choice,xe;
    string loc;
public:

    booking(string f, string l, string num, string add, string pass, int dd) :passenger(f, l, add, num, pass, dd)
    {
        n = 0;
        m = 0;
    }

    bool ldest()
    {
    	payment=12000;
        cout << endl << "These are the local destinations where we are flying: \n";
        for (i = 0; i < 5; i++)
        {
            for (j = 0; j < 20; j++)
            {
                cout << l_destination[i][j];
            }
            cout << "\n";
        }

    again:
        cout << endl << "Enter your origin(using BLOCK letters): ";
        cin >> origin;
        cout<<endl<<"Enter Ariport Direction : \n1. North\n2. South\n";
		xe=getch();
		if(xe==49){
			loc="NORTH_AIRPORT";
		}
		else{
			loc="SOUTH_AIRPORT";
		}
		cout<<loc;
        cout << endl << "Enter your destination(using BLOCK letters): ";
        cin >> destination;
        if (strcmp(origin, destination) == 0)
        {
            cout << "Invalid Origin and Destination Enter again\n";
            goto again;
        }
        else
        {
            for (i = 0; i < 5; i++)
            {
                if (strcmp(l_destination[i], origin) == 0)
                    n++;
            }
            for (j = 0; j < 5; j++)
            {
                if (strcmp(l_destination[j], destination) == 0)
                    m++;
            }
            if (m == 1 && n == 1)
            {

                cout << endl << "Price: " << payment << " Pkr/seat" << endl;
                return true;
            }
            else
                return false;

        }
    }

    bool idest(string pass)
    {
        passport = pass;
        payment=60000;
        cout << endl << "These are the international destinations where we are flying: \n";
        for (i = 0; i < 25; i++)
        {
            for (j = 0; j < 20; j++)
            {
                cout << i_destination[i][j];
            }
            cout << "\n";
        }
    again:
        cout << endl << "Enter your origin(using BLOCK letters): ";
        cin >> origin;
        cout<<endl<<"Enter Ariport Direction : \n1. North\n2. South\n";
		xe=getch();
		if(xe==49){
			loc="NORTH_AIRPORT";
		}
		else{
			loc="SOUTH_AIRPORT";
		}
		cout<<loc;
        cout << endl << "Enter your destination(using BLOCK letters): ";
        cin >> destination;
        if (strcmp(origin, destination) == 0)
        {
            cout << "Invalid Origin and Destination Enter again\n";
            goto again;
        }
        else
        {
            for (i = 0; i < 5; i++)
            {
                if (strcmp(l_destination[i], origin) == 0){
                    n++;
                    break;
                }
            }
            for (j = 0; j < 25; j++)
            {
                if (strcmp(i_destination[j], destination) == 0){
                    m++;
                    break;
                }
            }
            if (m == 1 && n == 1)
            {

                cout << endl << "Price: " << payment << " Pkr/seat" << endl;
                return true;
            }
            else
                return false;
        }
    }


    void seats()
    {
    bus_eco:
        if (bus > 0 && eco > 0)
        {
            cout << endl << "1.Business Class\n2.Economy Class\n";
            k = getch();
            switch (k)
            {
            case 49:
            {
                cout << endl << "Business Class";
                cout << endl << "Enter the number of seats: ";
                cin >> NoOfSeats;
                payment = (payment * NoOfSeats) + 5000;
                if (NoOfSeats <= bus)
                {
                    cout << endl << "Seats are available.\n\n";
                    bus = bus - NoOfSeats;
                }
                else
                {
                    cout << endl << "Seats are not available.\n\n";
                    cout << "we have only " << bus << " seats available.\n" << endl;
                    cout << "Do you wish to book remaining seats\nPress 1 for YES\nPress 2 for NO\n";
                    k = getch();
                    if (k == 49)
                    {
                        NoOfSeats = bus;
                        payment = (payment * NoOfSeats) + (NoOfSeats*5000);
                        cout << "Seats are booked\n\n";
                        bus = 0;
                    }
                    else
                    {
                        cout << endl << "See you again.\n";
                        exit(0);
                    }
                }
                break;
            }

            case 50:
            {
                cout << endl << "Economy Class";
                cout << endl << "Enter the number of seats: ";
                cin >> NoOfSeats;
                payment = (payment * NoOfSeats);
                if (NoOfSeats <= eco)
                {
                    cout << endl << "Seats are available.\n\n";
                    eco = eco - NoOfSeats;
                }
                else
                {
                    cout << endl << "Seats are not available.\n\n";
                    cout << "we have only " << eco << " seats available.\n" << endl;
                    cout << "Do you wish to book remaining seats\nPress 1 for YES\nPress 2 for NO\n";
                    k = getch();
                    if (k == 49)
                    {
                        NoOfSeats = eco;
                        payment = (payment * NoOfSeats);
                        cout << endl << "Seats are booked\n\n";
                        eco = 0;
                    }
                    else
                    {
                        cout << endl << "See you again.\n";
                        exit(0);
                    }
                }
                break;
            }

            default:
            {
                cout << "Error!\n";
                goto bus_eco;
            }
            }
        }
        else
        {
            cout << endl << "Sorry no seats available\nHave a nice day!";
            exit(0);
        }
    }


    void Meals()
    {
    meal:
        int n;
        cout << endl << "Available meal types:\n1.Vegetarian\n2.Non-Vegetarian\n";
        n = getch();
        if (n == 49)
            mealtype = "Vegetarian";
        else if (n == 50)
            mealtype = "Non Vegetarian";
        else
        {
            cout << "ERROR!!!" << endl;
            goto meal;
        }
    }

    void Registration()
    {
        srand(time(NULL));
        tkt = rand() % 1000;
        if (k == 49)
        {
            ofstream outfile;
            outfile.open("flight.txt",ios::app);
            outfile << "|TICKET INFORMATION:" << endl << endl
                << "Name: " << firstname << " " << lastname << endl
                << "Phone: " << Address << endl
                << "Address: " << phone << endl
                << "Passport Number: " << passport << endl
                << "Origin: " << origin
                << endl << "Destination: " << destination
                << endl << "Food: " << mealtype
                << endl << "Number of Seats: " << NoOfSeats
                << endl << "Class: Business"
                << endl << "Date of departure: " << datedep
                << endl << "Time: "<<wt<<":00 "<<st
                << endl << "Ticket: HF" << tkt
                << endl << "Bill(in pakistani rupees): " << payment << "/-" << endl;
            outfile.close();
            wt+=2;
            if(wt>12){
            	wt-=12;
            	st="AM";
			}
        }
        else if (k == 50)
        {
            ofstream outfile;
            outfile.open("flight.txt",ios::app);
            outfile << "|TICKET INFORMATION:" << endl << endl
                << "Name: " << firstname << " " << lastname << endl
                << "Phone: " << Address << endl
                << "Address: " << phone << endl
                << "Passport Number: " << passport << endl
                << "Origin: " << origin
                << endl << "Destination: " << destination
                << endl << "Food: " << mealtype
                << endl << "Number of Seats: " << NoOfSeats
                << endl << "Class: Economy"
                << endl << "Date of departure: " << datedep
                << endl << "Time: "<<wt<<":00 "<<st
                << endl << "Ticket: HF" << tkt
                << endl << "Bill(in pakistani rupees): " << payment << "/-" << endl;
            outfile.close();
            wt+=2;
            if(wt>12){
            	wt-=12;
            	st="AM";
			}
        }
        
    }

    bool display()
    {
        bool ans;
        system("cls");
        string temp;
        ifstream infile;
        infile.open("flight.txt");
        while (!infile.eof())
        {
            getline(infile, temp);
            cout << temp << endl;
        }
        ans = confirm();
        return ans;
    }

    bool confirm()
    {
        char ch;
    confirm:
        cout << endl << endl << "Do you wish to confirm your ticket?(y/n): ";
        ch = getch();
        if (ch == 'Y' || ch == 'y')
        {
            cout << endl << endl << "|STATUS CONFIRMED";
            ofstream outfile;
            outfile.open("flight.txt", ios::app);
            outfile << endl << "|STATUS CONFIRMED";
            outfile.close();
            return true;
        }
        else if (ch == 'N' || ch == 'n')
        {
            ofstream outfile;
            outfile.open("flight.txt", ios::app);
            outfile << endl << "|BOOKING CANCELLED";
            cout << endl << endl << "|BOOKING CANCELLED"
                << endl << "Going back to main page";
            sleep(3);
            outfile.close();
            return false;
        }
        else
        {
            cout << endl << "ERROR!!!";
            goto confirm;
        }
    }

    inline void drive()
    {
        string pick;
        cout << endl << "Please enter your pickup point: ";
        cin.ignore();
        getline(cin, pick);
        cout << endl << endl << "Pickup Location: " << pick;
        cout << endl << "Drop Off: " << origin << " Airport"
            << endl << "Fare: 300/-";
        cout << endl << endl << "You will be contacted by our driver shortly\nHave a nice day!";
        fstream ofile;
        ofile.open("flight.txt", ios::app);
        ofile << endl << endl << "Pick'n Drop: YES" << endl << endl
            << "Pickup Location: " << pick
            << endl << "Drop Off: " << origin << " Airport"
            << endl << "Fare: 300/-";
        ofile.close();
    }
};

class Manage
{
private:
    string temp, y, c2;
    int option;
public:
    int change()
    {
        int i = 0;

        ifstream file("flight.txt");
        if (file.is_open())
        {
            cout << endl << "Enter your Ticket Number or Press 0 to exit\nTicket Number: ";
            cin >> temp;
            if (temp == "0")
                return 1;
            string v("Ticket: " + temp);

            while (!file.eof())
            {
                getline(file, y);
                if (y == v)
                {
                    file.seekg(0, ios::beg);
                    while (!file.eof())
                    {
                        getline(file, temp);
                        cout << temp << endl;
                    }
                    cout << endl << endl << "1.Change date\n2.Cancel the flight\n3.Go Back\n";
                    option = getch();
                    switch (option)
                    {
                    case 49:
                    {
                        file.seekg(0, ios::beg);
                        ofstream ofile("temp.txt");
                        cout << endl << "Enter the new date of departure(DDMMYYYY): ";
                        cin >> c2;
                        string c1("Date of departure: " + c2);
                        while (!file.eof())
                        {
                            getline(file, y);
                            if (i == 11)
                            {
                                i++;
                                ofile << c1 << endl;
                            }
                            else
                            {
                                i++;
                                ofile << y << endl;
                            }
                        }
                        file.close();
                        ofile.close();
                        ofstream outfile;
                        outfile.open("flight.txt");
                        ifstream readfile("temp.txt");
                        while (!readfile.eof())
                        {
                            getline(readfile, y);
                            outfile << y << endl;
                        }
                        outfile.close();
                        readfile.close();
                        remove("temp.txt");
                        cout << endl << "Date Changed!";
                        return 1;
                        break;
                    }

                    case 50:
                    {
                        file.close();
                        ofstream ofli;
                        ofli.open("flight.txt", ios::trunc);
                        ofli.close();
                        remove("flight.txt");
                        system("cls");
                        cout << endl << "Booking cancelled!\n\n";
                        return 1;
                        break;
                    }
                    case 51:
                        system("cls");
                        return 1;
                    }
                }
            }
        }
        else if (!file.is_open())
        {
            cout << endl << endl << "unable to find any record" << endl;
            cout << endl << "going back to main page\n\n";
            file.close();
            return 1;
        }
    }
};

class Admin{
    string username, password;
    string user1, pass1;
    string cnic;
	string name;
public:
    void Registration1() {
	cout<<"Enter your full name : ";
	getline(cin,name);
	cout<<"Enter your CNIC No : ";
	getline(cin,cnic);
	while(true){
		if(validCnic(cnic)==1){
			break;
		}
		else{
			cout<<"Re-enter your CNIC No : ";
			getline(cin,cnic);
			}
	}
        cout << "Entre your username: ";
        cin >> username;
        cout << "Register your password: ";
        password=readPassword();
        while (true) {
            if (password.size() < 8) {
                cout << "Password must contain 8 letters ";
                cout << "Re-Enter your Password : ";
                cin >> password;
            }
            else {
                break;
            }
        }
        ofstream myfile("AdminRegistration.txt", ios::out | ios::app);
        myfile << "Username is : " << username << endl << "Password is : " << password << endl << endl << endl;
        myfile.close();
    }
    void login() {
        cout << "------------------------------------" << endl;
        cout << "Accout created, now you may log in." << endl;
        cout << "------------------------------------" << endl;
        cout << "Enter Your username :";
        cin >> user1;
        cout << "Enter registered Password :";
        pass1=readPassword();
        cout << "------------------------------------" << endl;

        if (user1 == username)
        {
            if (pass1 == password)
            {

                cout << "##########PROCEED##########" << endl;
                getch();
                system("cls");
                 }
            else
            {
                cout << "##########INVALID USER NAME OR PASSWORD##########" << endl;

            }
        }
        else {
            cout << "##########INVALID USER NAME OR PASSWORD##########" << endl;
        }

    }
    void setEseats(int n){
    	eco=n;
	}
	void setBseats(int n){
    	bus=n;
	}
};
class about
{
public:
    void Aboutus()
    {
        cout << "NAFS is functional in five major cities of Pakistan. These cities are Islamabad, Lahore,\n"
        <<"Quetta, Peshawar, and Karachi. Each city has two airports located at the North and South. NAFS\n"
        <<"team wants to have a flight reservation system. NAFS has 10 airplanes in each city whereas a\n"
        <<"maximum of 5 can land at a time in an airport. NAFS has established a network of flights in 25\n"
        <<"countries around the globe. Due to COVID situation some countries have travel bans. NAFS\n"
        <<"greatly value its passengers and abide by the international travelling laws. 50,000 passengers use\n"
        <<"NAFS annually. Ten Local flights and Five International flights take off from each airport daily\n"
        <<"depending on their schedule. Each plane of NAFS has a seating capacity of 50 passengers in\n"
        <<"economy class and 10 in business class. The days passengers are seated with a gap of one seat\n"
        <<"during the COVID days." << endl << endl;
        cout << "Press any key to continue...";
    }

};

class complain
{
private:
    string f_name, l_name, p_num;
    int choice;
    string sentence;
    string types;
    char ch;
public:
    complain(string f, string l, string num)
    {
        f_name = f;
        l_name = l;
        p_num = num;
    }

    void type()
    {
    back:
        cout << endl << endl << "Enter the type of complain you want to register:\n1.Airport Handling\n2.Baggage Delivery\n3.Booking and ticketing\n4.Other\n";
        choice = getch();
        cin.ignore();
        cout << "Enter your complain:\n";
        if (choice == 49)
        {
            cout << "Airport Handling: ";
            types = "Aiprort Handling: ";
        }
        else if (choice == 50)
        {
            cout << "Baggage Delivery: ";
            types = "Baggage Delivery: ";
        }
        else if (choice == 51)
        {
            cout << "Booking and Ticketing: ";
            types = "Booking and Ticketing: ";
        }
        else if (choice == 52)
        {
            cout << "Other: ";
            types = "Other: ";
        }
        getline(cin, sentence);
        cout << endl << "Do you want to edit your complain(y/n): ";
        ch = getch();
        if (ch == 'Y' || ch == 'y')
            goto back;
        else
        {
            cout << endl << "Complain noted!\n";
            ofstream outfile;
            outfile.open("complain.txt");
            outfile << "Name: " << f_name << " " << l_name << endl
                << "Phone: " << p_num << endl
                << "Complain:\n" << types << sentence;
            outfile.close();
            sleep(3);
        }
    }
};

class routes {
public:
    bool print()
    {
        int i, j;
        char ch;
        cout << "\n\n\n\n\tFollowing are the international flights available" << endl;
        for (i = 0; i < 11; i++)
        {
            cout << endl;
            for (j = 0; j < 11; j++)
            {
                if (i == j)
                {
                    continue;
                }
                else
                {
                    cout << "Flight from " << i_destination[i] << " to " << i_destination[j] << endl;
                }

            }
        }
        cout << "\n\n\n\n\tFollowing are the local flights available" << endl;
        for (i = 0; i < 5; i++)
        {
            cout << endl;
            for (j = 0; j < 5; j++)
            {
                if (i == j)
                {
                    continue;
                }
                else
                {
                    cout << "Flight from " << l_destination[i] << " to " << l_destination[j] << endl;
                }
            }
        }
        cout << endl << "Do you want to book a flight(y/n) ";
        ch = getch();
        if (ch == 'Y' || ch == 'y')
        {
            cout << endl << endl;
            return true;
        }
        else
            return false;
    }

};


int main()
{
	string f_name, l_name, add, pass_no, phone_no;
    int choice, datedep, date, month, year;
    bool ans;
    bool admin=0;
    char ch;
    bool x=0;
    int re;
    tm local_time=get_local_time();
    date = local_time.tm_mday;
    month = local_time.tm_mon + 1;
    year = local_time.tm_year + 1900;
    wt=local_time.tm_hour;
    FlightSchedule sch;
    Admin ad;
    system("cls");
    cout << " \n\t\t\t\t\t\tCOMPUTER PROGRAMMING PROJECT\n\t\t\t\t\t##########$$AIR PORT MANAGEMENT SYSTEM$$##########";
    cout << "\nPress Enter to continue: ";
    getch();
    system("cls");
//    cout<<date<<endl;
//    cout<<month<<endl;
//    cout<<year<<endl;

back2:
	
	cout << endl << "\n\n\n\t\t\t\t\t    $$$$WELLCOME TO NUCES AIRLINE SYSTEM$$$$" << endl;
    cout<< endl << "Press 0 for Register" 
	    << endl << "Press 1 for Booking"
        << endl << "Press 2 for Routes"
        << endl << "Press 3 for Complaint"
        << endl << "Press 4 for About"
        << endl << "Press 5 for Manage"
        << endl << "Press 6 for Schedule"
        << endl << "Press Esc For Terminating the code\n"; 
    choice = getch();
    system("cls");
    switch (choice)
    {
    case 49:
    {
    	if(x==1){
    my:
        cout << "@@@@@@@@@@BOOKING@@@@@@@@@@\n";
        passenger* ptr;
        cout << "Enter Your First Name: ";
        cin >> f_name;
        cin.ignore();
        cout << "Enter Your Last Name: ";
        getline(cin, l_name);
        cout << "Enter Your Address(Using Commas only): ";
        getline(cin, add);
        cout << "Enter Your Phone Num(Without -): ";
        cin >> phone_no;
    date:
        cout << "Enter date of departure(DDMMYYYY): ";
        cin >> datedep;

                       ans = datecheck(datedep,date,month,year);
                       if(ans==false)
                       {
                           cout<<"WRONG DATE"<<endl<<endl;
                           goto date;
                       }
        booking obj1(f_name, l_name, phone_no, add, pass_no, datedep);
        ptr = &obj1;
    back:
        cout << endl << "1.Local Destination\n2.International Destination\n3.Back\n4.Exit\n";
        choice = getch();

        if (choice == 49)
        {

            if (ptr->ldest() == false)
            {
                cout << endl << "We donot fly to this place\nPlease Choose again\n";
                goto back;
            }
            else
            {
                cout << endl << "Yes we do fly\n";
                ptr->seats();
                ptr->Meals();
                ptr->Registration();
                system("cls");
                ans = ptr->display();
                if (ans == false)
                {
                    system("cls");
                    goto back2;
                }
                else if (ans == true)
                {
                    cout << endl << "Thanks for Flying With Us" << endl << endl
                        << "Would you like to avail our Pick'n Drop facility?(y/n)";
                    ch = getch();
                    if (ch == 'y' || ch == 'Y')
                        ptr->drive();
                    else if (ch == 'n' || ch == 'N')
                    {
                        ofstream ofile;
                        ofile.open("flight.txt", ios::app);
                        ofile << endl << endl << "Pick'n Drop: NO";
                        ofile.close();
                    }
                    getch();
                    system("cls");
                    goto back2;
                }
            }
        }
        else if (choice == 50)
        {
            cout << endl << "Enter Your Passport Num(Without \"-\"): ";
            cin >> pass_no;
            ans = ptr->idest(pass_no);
            if (ans == false)
            {
                cout << endl << "We donot fly to this place\n";
                goto back;
            }
            else
            {
                cout << endl << "Yes we do fly\n";
                ptr->seats();
                ptr->Meals();
                ptr->Registration();
                system("cls");
                ans = ptr->display();
                if (ans == false)
                {
                    system("cls");
                    goto back2;
                }
                else if (ans == true)
                {
                    cout << endl << "Thanks for Flying With Us" << endl << endl
                        << "Would you like to avail our Pick'n Drop facility?(y/n)";
                    ch = getch();
                    if (ch == 'y' || ch == 'Y')
                        ptr->drive();
                    else if (ch == 'n' || ch == 'N')
                    {
                        ofstream ofile;
                        ofile.open("flight.txt", ios::app);
                        ofile << endl << endl << "Pick'n Drop: NO";
                        ofile.close();
                    }
                    getch();
                    system("cls");
                    goto back2;
                }
            }
        }
        else if (choice == 51)
        {
            system("cls");
            goto back2;
        }
        else
            exit(0);
        break;
    }
    else{
    	cout<<"First you need to login "<<endl;
    	getch();
    	system("cls");
    	goto back2;
	}
}

    case 50:   //choice = 2
    {
        cout << ">>>>>>>>>>ROUTES<<<<<<<<<<<\n";
        routes obj;
        ans = obj.print();
        if (ans == true)
            goto my;
        else if (ans == false)
        {
            cout << endl;
            system("cls");
            goto back2;
        }
        break;
    }

    case 51:   //choice = 3
    {
        cout << ">>>>>>>>>>COMPLAINT<<<<<<<<<<<\n";
        cout << "Enter Your First Name: ";
        cin >> f_name;
        cin.ignore();
        cout << "Enter Your Last Name: ";
        getline(cin, l_name);
        cout << "Enter Your Phone Num(Without -): ";
        cin >> phone_no;
        complain obj(f_name, l_name, phone_no);
        obj.type();
        system("cls");
        goto back2;
        break;
    }

    case 52:   //choice = 4
    {
        cout << "\t\t>>>>>>>>>>ABOUT US<<<<<<<<<<<\n";
        about obj;
        obj.Aboutus();
        getch();
        system("cls");
        goto back2;
        break;
    }
    case 53:  //choice = 5
    {
        cout << ">>>>>>>>>>MANAGE<<<<<<<<<<<\n";
        if(admin==1){
        Manage pass;
    chnge:
    	cout<<"1. Change Business and Economy Seats\n2. Change Booking Detail" << endl;
    	choice = getch();
		if(choice==49){
			cout<<"1. Business class\n2. Economy class\n";
			choice=getch();
			if(choice==49){
				cout<<"Enter the number of seats : ";
				cin>>re;
				ad.setBseats(re);
			}
			else{
				cout<<"Enter the number of seats : ";
				cin>>re;
				ad.setEseats(re);				
			}
    	    sleep(2);
            system("cls");
            goto back2;			
		}
		else{ 
        choice = pass.change();
        if (choice == 1)
        {
            sleep(2);
            system("cls");
            goto back2;
        }
        else
        {
            cout << "No record found\n";
            goto chnge;
        }

        break;
    }
}
    else{
    	cout<<"First you need to login as a admin "<<endl;
    	    sleep(2);
            system("cls");
            goto back2;
	}
    }
    case 54:
        sch.schedule();
        getch();
        system("cls");
        goto back2;
        break;
    case 48:   //choice = 0
    {

    menustart:
        string pass;
        string user;
        string ppass;
        string uuser;
        char arr[100];

        cout << "---------------------------" << endl;
        cout << "|AIRPORT MANAGEMENT SYSTEM|" << endl;
        cout << "---------------------------" << endl;
        cout << "---------------------------" << endl;

        cout << " # new user detected # " << endl;
        cout << "---------------------------" << endl;
        cout << "Create an account to proceed." << endl;
        cout << "---------------------------" << endl;




        cout << "**Press any key to proceed**" << endl;
        cout << "**Press any key to proceed**" << endl<<endl;
        cout << "1. Register as Admin\n2. Register as Passenger"<<endl<<endl;
        choice = getch();
        x = 1;
        if (choice == 49) {
        	admin=1;
            ad.Registration1();
            ad.login();
            goto back2;
        }
        //	cin>>arr;
        //cin.getline(arr, 100);
        else{
        Registration();
        cout << "Entre your username: ";
        cin >> user;
        cout << "Register your password: ";
        pass=readPassword();
        while(true){
        if(pass.size()<8){
        	cout<<"Password must contain 8 letters ";
        	cout<<"Re-Enter your Password : ";
        	pass=readPassword();
		}
		else{
			break;
		}
	}
        cout << "------------------------------------" << endl;
        cout << "Accout created, now you may log in." << endl;
        cout << "------------------------------------" << endl;



        ofstream myfile("Register.txt", ios::out | ios::app);

        myfile << arr;
        myfile<<"Username is : "<<user<<endl<<"Password is : "<<pass<<endl<<endl<<endl;
        myfile.close();



        //	cout<<" reading...."<<endl;
        ifstream obj("Register.txt", ios::in);
        obj.get(arr, 100);
        // cout<<arr;
        cout << "Enter Your username :";
        cin >> uuser;
        cout << "Enter registered Password :";
        ppass=readPassword();
        cout << "------------------------------------" << endl;

        if (uuser == user)
        {
            if (ppass == pass)
            {

                cout << "##########PROCEED##########" << endl;
                getch();
                goto back2;

            }
            else
            {
                cout << "##########INVALID USER NAME OR PASSWORD##########" << endl;

            }
        }
        else{
        	cout<<"##########INVALID USER NAME OR PASSWORD##########" << endl;
		}
	}

    }
    return 0;
    }
}
tm get_local_time()
{
    time_t now = time(NULL);
    tm local_time = *localtime(&now);
    return local_time;
}

    bool datecheck(int dd, int d, int m, int y){
    	if((dd%10000)==y){
    		dd=dd/10000;
    		if(dd%100>=m&&dd%100<13){
    			dd=dd/100;
    			if(dd>=d&&dd<32){
    				return true;
				}
				else 
				return false;
			}
				else 
				return false;			
		}
				else 
				return false;
			}
