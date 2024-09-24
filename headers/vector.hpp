#ifndef DRAW_VECTOR_FUNCTIONS
#define DRAW_VECTOR_FUNCTIONS

struct VectorCoordinates
{
    double x;
    double y;
    double z;
    double x_0;
    double y_0;
    double z_0;
};

class Vector
{
    double x;
    double y;
    double x_0;
    double y_0;
    double z_0;
    double z;

    double length;
    bool is_length_real;

public:
    Vector( double init_x, double init_y, double init_x_0, double init_y_0, double init_z = 0, double init_z_0 = 0);
    ~Vector() {};

    VectorCoordinates getCoordinates() const;
    double getLength();
    void setLength( double new_length);

    Vector &move( double new_x_0, double new_y_0, double new_z_0 = 0);
    void createEnding( VectorCoordinates *end_1, VectorCoordinates *end_2) const;

    Vector &operator/= ( double cf);
    Vector &operator!= ( Vector &vec);
    Vector operator= ( const Vector &vec) const;

    Vector reflectNormal( Vector &normal);
};

Vector operator+ ( const Vector &vec_1, const Vector &vec_2);
Vector operator- ( const Vector &vec_1, const Vector &vec_2);
double operator* ( const Vector &vec_1, const Vector &vec_2);
Vector operator* ( const Vector &vec, double cf);
Vector operator/ ( const Vector &vec, double cf);
Vector operator! ( const Vector &vec);
Vector operator~ ( const Vector &vec);

double getAngle( Vector &vec_1, Vector &vec_2);
double cosOfDifference( double cos_x, double cos_y);
Vector normalize( Vector &vec);

#endif // DRAW_VECTOR_FUNCTIONS
