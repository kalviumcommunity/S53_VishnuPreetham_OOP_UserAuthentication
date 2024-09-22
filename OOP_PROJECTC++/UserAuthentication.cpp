#include <iostream>
#include <fstream>
#include <sstream>
#include <unistd.h>
#include <vector>

using namespace std;


class UserBase
{
public:
    virtual void displayUserInfo() const = 0; 
};

class User : public UserBase  
{
protected:
    string userName;
    string userId;

    void settingUserTheme()
    {
        cout << "\tSetting User";
        for (int i = 0; i < 3; i++)
        {
            cout << ".";
            sleep(2);
        }
        cout << endl;
    }

    void settingUserId()
    {
        cout << "\tSetting UserId";
        for (int i = 0; i < 3; i++)
        {
            cout << ".";
            sleep(2);
        }
        cout << endl;
    }

public:
    User() : userName(""), userId("") {}

    // Setters
    void setUserName(string *userName)
    {
        settingUserTheme();
        this->userName = *userName;
    }

    void setUserId(string *userId)
    {
        settingUserId();
        this->userId = *userId;
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


    void displayUserInfo() const override
    {
        cout << "UserId: " << userId << ", Username: " << userName << endl;
    }
};

class Authenticate : public User
{
protected:
    vector<User> userArray;
    static int userCount;

    static bool isUserId(string &userId)
    {
        return userId.length() >= 8;
    }

    static bool checkUserExists(string &userId, vector<User> &userArray)
    {
        cout << "\tChecking Whether User Exists";
        for (int i = 0; i < 3; i++)
        {
            cout << ".";
            sleep(1);
        }
        cout << endl;
        for (const auto &user : userArray)
        {
            if (user.getUserId() == userId)
            {
                return true;
            }
        }
        return false;
    }

    void saveData()
    {
        ofstream outFile("./Data.txt", ios::app);
        if (!outFile)
        {
            cout << "\tError: File can't open!" << endl;
        }
        else
        {
            userCount++;
            cout << "\tSaving Data";
            for (int i = 0; i < 3; i++)
            {
                cout << ".";
                sleep(1);
            }
            cout << endl;
            for (const auto &user : userArray)
            {
                outFile << "UserNo: " << userCount << " UserId: " << user.getUserId() << ", Username: " << user.getUserName() << endl;
            }
            outFile.close();
        }
    }

public:
    Authenticate()
    {
        cout << "\tI am a constructor" << endl;
    }

    void storingData()
    {
        User newUser;
        string *userName = new string;
        string *userId = new string;

        cout << "\tEnter UserName: ";
        cin >> *userName;
        newUser.setUserName(userName);

    start:
        cout << "\tEnter a UserId (8 characters): ";
        cin >> *userId;

        if (Authenticate::isUserId(*userId))
        {
            if (!Authenticate::checkUserExists(*userId, userArray))
            {
                newUser.setUserId(userId);
                userArray.push_back(newUser);
                saveData();
            }
            else
            {
                cout << "\tError: UserId already exists!" << endl;
                goto start;
            }
        }
        else
        {
            cout << "\tUserId should be 8 characters long." << endl;
            goto start;
        }

        delete userName;
        delete userId;
        userName = nullptr;
        userId = nullptr;

        cout << "\tPlease Wait, User Registering";
        for (int i = 0; i < 3; i++)
        {
            cout << ".";
            sleep(1);
        }
        cout << endl;
        cout << "\tUser Registered Successfully!" << endl;
        cout << "\tUserNo: " << userCount << ", UserId: " << newUser.getUserId() << ", Username: " << newUser.getUserName() << endl;

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

    static void userInterface(Authenticate AuntenticateUser)
    {
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
    }

    ~Authenticate()
    {
        cout << "\tDestructor called." << endl;
    }
};

class AdminAuthenticate : public Authenticate
{
public:
    void adminOnlyFeature()
    {
        cout << "\tAccessing User Info (Admin Feature)" << endl;
        for (const auto &user : userArray)
        {
            user.displayUserInfo(); 
        }
    }
};

int Authenticate::userCount = 0;

int main()
{
    AdminAuthenticate admin;
    admin.userInterface(admin);
    admin.adminOnlyFeature();
    return 0;
}
