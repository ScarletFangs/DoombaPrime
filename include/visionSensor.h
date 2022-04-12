/*vex-vision-config:begin*/
#include "vex.h"
vex::vision::signature BLUE_GOAL = vex::vision::signature (1, -3241, -2077, -2659, 8969, 12483, 10726, 3, 0);
vex::vision::signature RED_GOAL = vex::vision::signature (2, 6945, 9731, 8338, -999, -523, -760, 2, 0);
vex::vision::signature DONUT = vex::vision::signature (3, 941, 1879, 1410, 5113, 7005, 6060, 3, 0);
vex::vision::signature YELLOW_GOAL = vex::vision::signature (4, 3069, 3485, 3277, -3203, -2919, -3061, 8.5, 0);
vex::vision::signature SIG_5 = vex::vision::signature (5, 0, 0, 0, 0, 0, 0, 3, 0);
vex::vision::signature SIG_6 = vex::vision::signature (6, 0, 0, 0, 0, 0, 0, 3, 0);
vex::vision::signature SIG_7 = vex::vision::signature (7, 0, 0, 0, 0, 0, 0, 3, 0);
vex::vision Vision1 = vex::vision (vex::PORT14, 50, BLUE_GOAL, RED_GOAL, DONUT, YELLOW_GOAL, SIG_5, SIG_6, SIG_7);
/*vex-vision-config:end*/