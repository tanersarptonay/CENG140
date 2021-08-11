#include <stdio.h>
#include <math.h>

/* 
    Helper functions use the arrays, knots and currents.
    So to not to give the arrays as arguments each time,
    they are declared as global variables
*/
double knots[101], currents[101];
int n;

double coefficient(int i)
{
    /* Uses recursion to determine the coefficient */
    double add; 
    if (i == 0) return 0.0;
    else
    {
        add = 2*(currents[i]-currents[i-1])/(knots[i]-knots[i-1]);
        return (-coefficient(i-1) + add);
    }
}

double current(double x)
{
    /*  
        Calculates the current at specific x coordinate value 
        according to non-uniform quadratic spline interpolation
    */
    int i;
    double s;
    for (i=0 ; i<=n-1 ; ++i)
    {
        if (knots[i] == x) return currents[i];
        else if (knots[i] < x && x < knots[i+1])
        {
            s = currents[i] + coefficient(i)*(x-knots[i]) + ((coefficient(i+1)-coefficient(i))/(2*(knots[i+1]-knots[i]))) * pow(x-knots[i],2) ;
            return s;
        }
        else continue;
    }
    return 0.0;
}


int main()
{
    double delta_t;
    double velocity;
    double end;
    double velocity_x, velocity_y;
    double x=0.0, time=0.0;
    int i;

    scanf("%lf %lf", &delta_t, &velocity);
    scanf("%d", &n);
    for (i=0 ; i<=n ; ++i)
    {
        /* Takes inputs and appends them to arrays */
        scanf("%lf %lf", &knots[i], &currents[i]);
    }
    end = knots[n];

    while (x < end)
    {
        /* Moves the boat untill it reaches to the other side of the river */
        velocity_y = -current(x);
        velocity_x = sqrt(pow(velocity, 2) - pow(velocity_y, 2));
        x += velocity_x * delta_t;
        time += delta_t;        
    }

    printf("%f\n", time);

    return 0;
}
