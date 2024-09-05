#include <iostream>
#include <fstream>
#include <sstream>
#include <unistd.h>
#include <map>

using namespace std;

class User {
private:
    string userName;
    string userId;

public:
    User() : userName(""), userId("") {}

    // Setters
    void setUserName(string userName) {
        this->userName = userName;
    }

    void setUserId(string userId) {
        this->userId = userId;
    }

    // Getters
    string getUserName() {
        return this->userName;
    }

    string getUserId() {
        return this->userId;
    }
};

class Authenticate : public User {
private:
    map<string, string> userMap;

    void loadData() {
        ifstream infile("./Data.txt");
        if (!infile) {
            cout << "\tError: File can't open!" << endl;
        } else {
            string line;
            while (getline(infile, line)) {
                stringstream ss(line);
                string userId, userName;
                ss >> userId >> userName;
                userMap[userId] = userName;
            }
            infile.close();
        }
    }

    void saveData() {
        ofstream outFile("./Data.txt");
        if (!outFile) {
            cout << "\tError: File can't open!" << endl;
        } else {
            for (const auto& pair : userMap) {
                outFile << pair.first << " " << pair.second << endl;
            }
            outFile.close();
        }
    }

public:
    void storingData() {
        loadData();

        string userName, userId;
        cout << "\tEnter UserName: ";
        cin >> userName;
        setUserName(userName);

    start:
        cout << "\tEnter a UserId: ";
        cin >> userId;

        if (userId.length() == 8) {
            setUserId(userId);
        } else {
            cout << "\tThere should be 8 characters" << endl;
            goto start;
        }

        userMap[userId] = userName;
        saveData();

        cout << "\tPlease Wait, User Registering";
        for (int i = 0; i < 3; i++) {
            cout << ".";
            sleep(2);
        }
        cout << endl;
        cout << "\tUser Registered Successfully" << endl;
        sleep(3);
    }

    void authenticateUser() {
        loadData();

        string userId, userName;
        cout << "\tEnter UserId: ";
        cin >> userId;
        cout << "\tEnter UserName: ";
        cin >> userName;

        if (userMap.find(userId) != userMap.end() && userMap[userId] == userName) {
            cout << "\tPlease Wait";
            for (int i = 0; i < 3; i++) {
                cout << ".";
                sleep(4);
            }
            cout << endl;
            cout << "\tWelcome to this page" << endl;
        } else {
            cout << "\tError: Incorrect Login ID or Password!" << endl;
            cout << "\tSelect Option to ReLogin" << endl;
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
