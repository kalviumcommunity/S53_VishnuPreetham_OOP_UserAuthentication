#include <iostream>
#include <fstream>
#include <sstream>
#include <unistd.h>
#include <vector>

using namespace std;

class User
{
private:
    string userName;
    string userId;

public:
    User() : userName(""), userId("") {}

    // Setters
    void setUserName(string userName)
    {
        this->userName = userName;
    }

    void setUserId(string userId)
    {
        this->userId = userId;
    }

    // Getters
    string getUserName() const
    {
        return this->userName;
    }

    string getUserId() const
    {
        return this->userId;
    }
};

class Authenticate
{
private:
    vector<User> userArray; 

    void saveData()
    {
        ofstream outFile("./Data.txt", ios::app);
        if (!outFile)
        {
            cout << "\tError: File can't open!" << endl;
        }
        else
        {
            for (const auto &user : userArray)
            {
                outFile << "UserId: " << user.getUserId() << ", Username: " << user.getUserName() << endl;
            }
            outFile.close();
        }
    }

public:
    void storingData()
    {
        User newUser; 
        string userName, userId;

        cout << "\tEnter UserName: ";
        cin >> userName;
        newUser.setUserName(userName);

    start:
        cout << "\tEnter a UserId (8 characters): ";
        cin >> userId;

        if (userId.length() == 8)
        {
            newUser.setUserId(userId);
        }
        else
        {
            cout << "\tUserId should be 8 characters long." << endl;
            goto start;
        }

  
        userArray.push_back(newUser);

 
        saveData();


        cout << "\tPlease Wait, User Registering";
        for (int i = 0; i < 3; i++)
        {
            cout << ".";
            sleep(1);
        }
        cout << endl;
        cout << "\tUser Registered Successfully!" << endl;
        sleep(1);
    }

    void authenticateUser()
    {
        string userId, userName;
        cout << "\tEnter UserId: ";
        cin >> userId;
        cout << "\tEnter UserName: ";
        cin >> userName;

        bool isAuthenticated = false;
        for (const auto &user : userArray)
        {
            if (user.getUserId() == userId && user.getUserName() == userName)
            {
                isAuthenticated = true;
                break;
            }
        }

        if (isAuthenticated)
        {
            cout << "\tPlease Wait";
            for (int i = 0; i < 3; i++)
            {
                cout << ".";
                sleep(1);
            }
            cout << endl;
            cout << "\tWelcome to the system!" << endl;
        }
        else
        {
            cout << "\tError: Incorrect UserId or UserName!" << endl;
        }
    }
};

int main()
{
    Authenticate AuntenticateUser;
    bool exit = false;
    while (!exit)
    {
        cout << "\n / xxxxxxxxxxxxxxx -:- USER AUTHENTICATION -:- xxxxxxxxxxxxxx / " << endl;
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
            cout << "\tThank you! Please Visit Again." << endl;
        }
    }
    return 0;
}
