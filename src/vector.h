#ifndef DRAW_VECTOR_FUNCTIONS
#define DRAW_VECTOR_FUNCTIONS

struct VectorCoordinates
{
    int x;
    int y;
    int z;
    int x_0;
    int y_0;
    int z_0;
};

class Vector
{
    int x;
    int y;
    int x_0;
    int y_0;
    int z_0;
    int z;

    double length;
    bool is_length_real;

public:
    Vector( int init_x, int init_y, int init_x_0, int init_y_0, int init_z = 0, int init_z_0 = 0);
    ~Vector() {};

    VectorCoordinates getCoordinates() const;
    double getLength();
    void setLength( double new_length);

    Vector &move( int new_x_0, int new_y_0, int new_z_0 = 0);
    void createEnding( VectorCoordinates *end_1, VectorCoordinates *end_2) const;

    Vector &operator/ ( double cf);
    Vector &operator! ();
    Vector &operator~ ();
    Vector operator= ( const Vector &vec) const;
};

Vector operator+ ( const Vector &vec_1, const Vector &vec_2);
Vector operator- ( const Vector &vec_1, const Vector &vec_2);
double operator* ( const Vector &vec_1, const Vector &vec_2);

double getAngle( Vector &vec_1, Vector &vec_2);

#endif // DRAW_VECTOR_FUNCTIONS
