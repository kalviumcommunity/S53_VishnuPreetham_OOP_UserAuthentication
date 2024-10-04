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

    void setUserName(const string &name)
    {
        userName = name;
    }

    void setUserId(const string &id)
    {
        userId = id;
    }

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

class FileHandler
{
public:
    virtual void saveData(const vector<User> &userArray, int userCount) = 0;
};

class TextFileHandler : public FileHandler
{
public:
    void saveData(const vector<User> &userArray, int userCount) override
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

class Validator
{
public:
    virtual bool validate(const string &input) const = 0;
};

class UserIdValidator : public Validator
{
public:
    bool validate(const string &userId) const override
    {
        return userId.length() >= 8;
    }
};

class Authenticator
{
protected:
    vector<User> userArray;
    static int userCount;

public:
    virtual void registerUser() = 0;
    virtual void authenticateUser() = 0;

    virtual ~Authenticator() {}
};

int Authenticator::userCount = 0;

class BasicAuthenticator : public Authenticator
{
private:
    Validator *validator;
    FileHandler *fileHandler;

public:
    BasicAuthenticator(Validator *v, FileHandler *f) : validator(v), fileHandler(f) {}

    void registerUser() override
    {
        User newUser;
        string userName, userId;

        cout << "\tEnter UserName: ";
        cin >> userName;
        newUser.setUserName(userName);

    start:
        cout << "\tEnter a UserId (8 characters): ";
        cin >> userId;

        if (validator->validate(userId))
        {
            bool userExists = false;
            for (const auto &user : userArray)
            {
                if (user.getUserId() == userId)
                {
                    userExists = true;
                    break;
                }
            }

            if (!userExists)
            {
                newUser.setUserId(userId);
                userArray.push_back(newUser);
                userCount++;
                fileHandler->saveData(userArray, userCount);

                cout << "\tUser Registered Successfully!" << endl;
                cout << "\tUserNo: " << userCount << ", UserId: " << newUser.getUserId() << ", Username: " << newUser.getUserName() << endl;
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

    void authenticateUser() override
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
};


class AdminAuthenticator : public BasicAuthenticator
{
public:
    AdminAuthenticator(Validator *v, FileHandler *f) : BasicAuthenticator(v, f) {}

    void adminOnlyFeature()
    {
        cout << "\tAccessing User Info (Admin Feature)" << endl;
        for (const auto &user : userArray)
        {
            user.displayUserInfo();
        }
    }
};

class UserInterface
{
public:
    static void displayInterface(Authenticator &authenticator)
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
                authenticator.registerUser();
            }
            else if (val == 2)
            {
                authenticator.authenticateUser();
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
    UserInterface::displayInterface(adminAuth);
    adminAuth.adminOnlyFeature();
    return 0;
}
