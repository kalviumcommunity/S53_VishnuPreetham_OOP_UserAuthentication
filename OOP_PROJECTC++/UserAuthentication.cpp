#include <iostream>
#include <bits/stdc++.h>
#include <unistd.h>
#include <cstdlib>
#include <sstream>

using namespace std;
class User
{
private:
    string userName;
    string userId;

public:
    User() : userName(""), userId("") {}

    //   Seter's

    // This below function is to set the user name to the user name variable .
    // This uses this constructor to set the value .

    void setUserName(string userName)
    {
        this->userName = userName;
    }

    // This below function is to set the user id to the user id variable .
    // This uses this constructor to set the value .

    void setUserId(string userId)
    {
        this->userId = userId;
    }

    //   Geter's

    // This below function is to get the user name variable .
    // This uses this constructor to get the value .

    string getUserName()
    {
        return this->userName;
    }

    // This below function is to get the user id variable .
    // This uses this constructor to get the value .

    string getUserId()
    {
        return this->userId;
    }
};
class Authenticate : public User
{
public:
    void storingData()
    {
        string userName, userId;
        cout << "\tEnter UserName : ";
        cin >> userName;
        setUserName(userName);

    start:
        cout << "\tEnter a UserId: ";
        cin >> userId;

        if (userId.length() == 8)
        {
            setUserId(userId);
        }
        else
        {
            cout << "\tThere should be 8 Charaters" << endl;
            goto start;
        }
        // ofstream is used to write the data
        ofstream outLine("./Data.txt", ios::app);
        if (!outLine)
        {
            cout << "\tError: File Can't open!" << endl;
        }
        else
        {
            outLine << "\t" << getUserName() << " : " << getUserId() << endl
                    << endl;
            cout << "\tPlease Wait User Registering";
            for (int i = 0; i < 3; i++)
            {
                cout << ".";
                sleep(2);
            }
            cout << endl;
            cout << "\tUser Registered Successfully" << endl;
        }
        outLine.close();
        sleep(3);
    }
    void authenticateUser()
    {
        sleep(4);
        string userID, userNAme;
        cout << "\t Enter User Name : ";
        cin >> userID;
        cout << "\t Enter UserId: ";
        cin >> userNAme;
        ifstream infile("./Data.txt");
        if (!infile)
        {
            cout << "\tError File cannot open: " << endl;
        }
        else
        {
            string line;
            bool found = false;
            while (getline(infile, line))
            {
                stringstream ss;
                ss << line;
                string userId, userName;
                char delimiter;
                ss >> userId >> delimiter >> userName;
                if (userID == userId && userNAme == userName)
                {
                    found = true;
                    cout << "\tPlease Wait";
                    for (int i = 0; i < 3; i++)
                    {
                        cout << ".";
                        sleep(4);
                    }
                    cout << endl;
                    cout << "\tWelcome to this page" << endl;
                }
            }
            if (!found)
            {
                cout << "\tError: Incorrect Login ID or Password!" << endl;
                cout << "\tSelect Option to ReLogin" << endl;
            }
        }
    }
};
int main()
{
    Authenticate AuntenticateUser;
    bool exit = false;
    while (!exit)
    {
        cout << " / xxxxxxxxxxxxxxx -:- USER AUTHENTICATION -:- xxxxxxxxxxxxxx / " << endl;
        cout << "\t1. User Register " << endl;
        cout << "\t2. User Login" << endl;
        cout << "\t3. Exit" << endl;
        cout << "\tPlease Select the option to Proceed: ";
        int val;
        cin >> val;
        if (val == 1)
        {
            AuntenticateUser.storingData();
        }
        else if (val == 2)
        {
            AuntenticateUser.authenticateUser();
        }
        else if (val == 3)
        {
            exit = true;
            cout << "\tPlease Visit Again";
        }
    }
    return 0;
}
