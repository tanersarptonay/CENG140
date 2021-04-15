#include <stdio.h> 

int main() {
    float mon, tue, wed, thu, fri;
    float avr;
    
    scanf("%f %f %f %f %f", &mon, &tue, &wed, &thu, &fri);
    
    mon = (mon-32)/1.8;
    tue = (tue-32)/1.8;
    wed = (wed-32)/1.8;
    thu = (thu-32)/1.8;
    fri = (fri-32)/1.8;
    avr = (mon+tue+wed+thu+fri)/5;
    
    printf("Celsius on Mon: %.2f\n", mon);
    printf("Celsius on Tue: %.2f\n", tue);
    printf("Celsius on Wed: %.2f\n", wed);
    printf("Celsius on Thu: %.2f\n", thu);
    printf("Celsius on Fri: %.2f\n", fri);
    printf("Average: %.2f\n", avr);
    
    return 0;
}