#include <locale.h>
#include <stdio.h>
#include <math.h>

// Âàðèàíò 7

void main() {

    setlocale(LC_ALL, "RUS");
    
    double x, y, z, gamma;

    printf("Ââåäèòå x\n");
    scanf("%lf", &x);
    printf("Ââåäèòå y\n");
    scanf("%lf", &y);
    printf("Ââåäèòå z\n");
    scanf("%lf", &z);

    gamma=5*atan(x)-0.25*acos(x)*((x+3*fabs(x-y)+pow(x, 2))/(fabs(x-y)*z+pow(x, 2)));

    printf("Ðåçóëüòàò = %lf", gamma);

}
