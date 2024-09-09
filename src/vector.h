#ifndef DRAW_VECTOR_FUNCTIONS
#define DRAW_VECTOR_FUNCTIONS

struct Coordinates
{
    int x;
    int y;
    int x_0;
    int y_0;
};

class Vector
{
    int x;
    int y;
    int x_0;
    int y_0;

    double length;
    bool is_length_real;

public:
    Vector( int x, int y, int x_0, int y_0);
    ~Vector() {};

    Coordinates getCoordinates();
    Vector addVector( Vector vec);
    Vector divide( double cf);
    double getLength();
    Vector move( int new_x_0, int new_y_0);
    void setLength( double new_length);
    Vector getPerpendicular();
    Vector operator ~();
    void createEnding( Coordinates *end_1, Coordinates *end_2);
};

#endif // DRAW_VECTOR_FUNCTIONS
