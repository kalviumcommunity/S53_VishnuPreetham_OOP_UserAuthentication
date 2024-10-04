#include <iostream>
#include <fstream>
#include <vector>
#include <unistd.h>

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

public:
    User() : userName(""), userId("") {}

    // Setters
    void setUserName(const string &name)
    {
        userName = name;
    }

    void setUserId(const string &id)
    {
        userId = id;
    }

    // Getters
    string getUserName() const
    {
        return userName;
    }

    string getUserId() const
    {
        return userId;
    }

    void displayUserInfo() const override
    {
        cout << "UserId: " << userId << ", Username: " << userName << endl;
    }
};

class SaveData{
public:
    static void saveData(const vector<User> &userArray, int userCount)
    {
        ofstream outFile("./Data.txt", ios::app);
        if (!outFile)
        {
            cout << "\tError: File can't open!" << endl;
            return;
        }

        for (const auto &user : userArray)
        {
            outFile << "UserNo: " << userCount << " UserId: " << user.getUserId() << ", Username: " << user.getUserName() << endl;
        }
        outFile.close();
        cout << "\tData saved successfully." << endl;
    }
};

class UserValidator{
public:
    static bool isUserId(const string &userId)
    {
        return userId.length() >= 8;
    }

    static bool checkUserExists(const string &userId, const vector<User> &userArray)
    {
        for (const auto &user : userArray)
        {
            if (user.getUserId() == userId)
            {
                return true;
            }
        }
        return false;
    }
};

class Authenticate : public User
{
protected:
    vector<User> userArray;
    static int userCount;

public:
    Authenticate() {}

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

        if (UserValidator::isUserId(userId))
        {
            if (!UserValidator::checkUserExists(userId, userArray))
            {
                newUser.setUserId(userId);
                userArray.push_back(newUser);
                userCount++;
                SaveData::saveData(userArray, userCount);

                cout << "\tUser Registered Successfully!" << endl;
                cout << "\tUserNo: " << userCount << ", UserId: " << newUser.getUserId() << ", Username: " << newUser.getUserName() << endl;
            }
            else
            {
                cout << "\t UserId already exists!" << endl;
                goto start;
            }
        }
        else
        {
            cout << "\tUserId should be 8 characters long." << endl;
            goto start;
        }
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
            cout << "\tWelcome to the system!" << endl;
        }
        else
        {
            cout << "\tError: Incorrect UserId or UserName!" << endl;
        }
    }

    static void userInterface(Authenticate &authenticateUser)
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
                authenticateUser.storingData();
            }
            else if (val == 2)
            {
                authenticateUser.authenticateUser();
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
