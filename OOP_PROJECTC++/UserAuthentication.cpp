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
    }

    // This below function is to set the user id to the user id variable .
    // This uses this constructor to set the value .

    void setUserId(string userId)
    {
    }

    //   Geter's

    // This below function is to get the user name variable .
    // This uses this constructor to get the value .

    string getUserName()
    {
    }

    // This below function is to get the user id variable .
    // This uses this constructor to get the value .

    string getUserId()
    {
    }
};
class Authenticate : public User
{
public:
    void storingData()
    {
    }
    void authenticateUser()
    {
    }
};
int main()
{
    Authenticate AuntenticateUser;
    return 0;
}
