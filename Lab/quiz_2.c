#include <stdio.h>

int limits, x, y;
char direction;

int main() {
    scanf("%c %d %d %d", &direction, &x, &y, &limits);
    
    limits -= 1;
    
    if ((direction == 'N') && (y > 0)) {
        printf("%d %d\n",x, --y);
    }
    
    else if ((direction == 'S') && (y < limits)) {
        printf("%d %d\n", x, ++y);
    }
    else if ((direction == 'W') && (x > 0)) {
        printf("%d %d\n", --x, y);
    }
    else if ((direction == 'E') && (x < limits)) {
        printf("%d %d\n", ++x, y);
    }
    else {
        printf("%d %d\n", x, y);
    }

    return 0;
}