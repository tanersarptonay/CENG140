/*
FINDING NEAREST POINT
In this question, you are required to calculate the nearest point 
in a 2 dimensional (2D) space where each point has x and y pair. 
You will prompt the user by asking x and y coordinate of a point P, 
then you will find the index of the nearest point in the stored arrays.  
*/

#include <stdio.h>
#include <math.h>


int main()
{
    int i;
    int xcoors[10], ycoors[10];
    int x, y, p_x, p_y, min_index;
    float dist, min_dist=9999.0;
    
    for (i=0; i<10; i++)
    {
        scanf("%d ", &xcoors[i]);
    }
    
    for (i=0; i<10; i++)
    {
        scanf("%d ", &ycoors[i]);
    }
    
    scanf("%d\n%d", &p_x, &p_y);
     
    for (x=0, y=0 ; x<10 ; ++x, ++y)
    {
        dist = sqrt(pow(xcoors[x]-p_x, 2) + pow(ycoors[y]-p_y, 2));
        if (dist < min_dist)
        {
            min_dist = dist;
            min_index = x;
        }
    }
    
    printf("P = (%d,%d), nearest point index = %d, distance = %.1f", p_x, p_y, min_index, min_dist);

    return 0;
}