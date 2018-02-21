#include <iostream>

using namespace std;


class Coordinate
{
  public:
    Coordinate(); //blank constructor
    Coordinate(int a, int b); //overload constructor
    ~Coordinate(); //deconstructor

    int getX();
    int getY();
    void setX(int a);
    void setY(int b);

  private:
    int x;
    int y;
}
