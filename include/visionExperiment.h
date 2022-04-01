/*vex-vision-config:begin*/
#include "vex.h"
vex::vision::signature BLUE_GOAL = vex::vision::signature (1, -2521, -1837, -2180, 6521, 9309, 7916, 3, 0);
vex::vision::signature YELLOW_GOAL = vex::vision::signature (2, 1011, 1605, 1308, -3015, -2371, -2693, 3.7, 0);
vex::vision::signature RED_GOAL = vex::vision::signature (3, 6355, 7225, 6790, 209, 479, 344, 8.7, 0);
vex::vision::signature SIG_4 = vex::vision::signature (4, 0, 0, 0, 0, 0, 0, 2.5, 0);
vex::vision::signature SIG_5 = vex::vision::signature (5, 0, 0, 0, 0, 0, 0, 2.5, 0);
vex::vision::signature SIG_6 = vex::vision::signature (6, 0, 0, 0, 0, 0, 0, 2.5, 0);
vex::vision::signature SIG_7 = vex::vision::signature (7, 0, 0, 0, 0, 0, 0, 2.5, 0);
vex::vision Vision1 = vex::vision (vex::PORT19, 50, BLUE_GOAL, YELLOW_GOAL, RED_GOAL, SIG_4, SIG_5, SIG_6, SIG_7);
/*vex-vision-config:end*/