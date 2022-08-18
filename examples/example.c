#include "finite_state_machine.h"

#include <stdio.h>
#include <stdlib.h>

enum FSM_States {
    STATE_0,
    STATE_1,
    STATE_2,
};

static int event = 0xFF;

bool IsEvent_0(void) {return event == 0;}
bool IsEvent_1(void) {return event == 1;}
bool IsEvent_2(void) {return event == 2;}

void Action_0(void) {printf("Event_0 is received, execute Action_0() and go to STATE_0\n");}
void Action_1(void) {printf("Event_1 is received, execute Action_1() and go to STATE_1\n");}
void Action_2(void) {printf("Event_2 is received, execute Action_2() and go to STATE_2\n");}

static const FSM_TableRow_t kFsmTable[] = {
// | Present state | Event | Action | Next state |
    {STATE_0, IsEvent_1, Action_1, STATE_1},
    {STATE_1, IsEvent_2, Action_2, STATE_2},
    {STATE_2, IsEvent_0, Action_0, STATE_0},
    {STATE_2, IsEvent_1, Action_1, STATE_1},
};

int main()
{
    FSM_t fsm = {kFsmTable, sizeof(kFsmTable), STATE_0};  // Instantiate and initialize FSM

    while (true) {
        FSM_ReturnCode_t status_code = FSM_Kernel(&fsm);  // FSM kernel task running on background
        
        if (status_code != FSM_SUCCESS) {
            printf("FSM error status code: %d\n", status_code);
            return EXIT_FAILURE;
        }

        printf("FSM current state: %d\n", fsm.current_state);
        printf("\nEnter an event [0, 1 or 2]: ");
        if (!scanf("%d", &event)) {
            printf("Failed to read integer.\n");
        }

        // You can insert some time delay here
    }

    return EXIT_SUCCESS;
}
