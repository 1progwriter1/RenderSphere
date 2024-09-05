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

    public:
        Vector( int x, int y, int x_0, int y_0);
        Coordinates getCoordinates();
        friend Vector addVectors( Vector vec1, Vector vec2);
};

void initClock();
void destroyClock();
void updateClock();

#endif // DRAW_VECTOR_FUNCTIONS
