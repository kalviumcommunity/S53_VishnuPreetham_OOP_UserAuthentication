#include <iostream>
using namespace std;
class Shape
{
public:
    int area()
    {
        return 0;
    }
};
class Circle : public Shape
{
private:
    float PIE_VALUE = 3.14;

public:
    float area(float radius)
    {
        return PIE_VALUE * radius * radius;
    }
};
int main()
{
    Circle circlex5;
    circlex5.area(5);
    cout<<circlex5.area(5);
    return 0;
}