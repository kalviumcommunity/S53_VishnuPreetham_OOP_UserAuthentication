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
            sleep(1);
        }
        cout << endl;
    }

    void settingUserId()
    {
        cout << "\tSetting UserId";
        for (int i = 0; i < 3; i++)
        {
            cout << ".";
            sleep(1);
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

class Validator
{
public:
    virtual bool validate(const string &input) = 0;
};

class UserIdValidator : public Validator
{
public:
    bool validate(const string &userId) override
    {
        return userId.length() >= 8;
    }
};

class FileHandler
{
public:
    virtual void saveUserData(const vector<User> &userArray, int userCount) = 0;
};

class TextFileHandler : public FileHandler
{
public:
    void saveUserData(const vector<User> &userArray, int userCount) override
    {
        ofstream outFile("./Data.txt", ios::app);
        if (!outFile)
        {
            cout << "\tError: File can't open!" << endl;
        }
        else
        {
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
};




class Authenticator
{
protected:
    vector<User> userArray;
    Validator *idValidator;
    FileHandler *fileHandler;
    static int userCount;

public:
    Authenticator(Validator *validator, FileHandler *fileHandler)
        : idValidator(validator), fileHandler(fileHandler) {}

    virtual void registerUser()
    {
        User newUser;
        string userName, userId;

        cout << "\tEnter UserName: ";
        cin >> userName;
        newUser.setUserName(&userName);

    start:
        cout << "\tEnter a UserId (8 characters): ";
        cin >> userId;

        if (idValidator->validate(userId))
        {
            if (!checkUserExists(userId))
            {
                newUser.setUserId(&userId);
                userArray.push_back(newUser);
                userCount++;
                fileHandler->saveUserData(userArray,userCount);
                cout << "\tUser Registered Successfully!" << endl;
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
    }

    virtual void authenticateUser()
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

    bool checkUserExists(const string &userId)
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

int Authenticator::userCount = 0;

class AdminAuthenticator : public Authenticator
{
public:
    AdminAuthenticator(Validator *validator, FileHandler *fileHandler)
        : Authenticator(validator, fileHandler) {}

    void adminOnlyFeature()
    {
        cout << "\tAdmin Accessing User Info" << endl;
        for (const auto &user : userArray)
        {
            user.displayUserInfo();
        }
    }
};

class UserInterface
{
public:
    static void displayMenu(Authenticator &auth)
    {
        bool exit = false;
        while (!exit)
        {
            cout << "\n / -:- USER AUTHENTICATION MENU -:- / " << endl;
            cout << "\t1. User Register" << endl;
            cout << "\t2. User Login" << endl;
            cout << "\t3. Exit" << endl;
            cout << "\tPlease Select an option: ";
            int val;
            cin >> val;

            if (val == 1)
            {
                auth.registerUser();
            }
            else if (val == 2)
            {
                auth.authenticateUser();
            }
            else if (val == 3)
            {
                exit = true;
                cout << "\tThank you! Please Visit Again." << endl;
            }
        }
    }
};

int main()
{
    UserIdValidator idValidator;
    TextFileHandler textFileHandler;

    AdminAuthenticator adminAuth(&idValidator, &textFileHandler);
    UserInterface::displayMenu(adminAuth);

    adminAuth.adminOnlyFeature();
    return 0;
}
