#include "finite_state_machine.hpp"

#include <iostream>

enum FSM_States : int {
    STATE_0,
    STATE_1,
    STATE_2,
};

static int event = 0xFF;

bool IsEvent_0() {return event == 0;}
bool IsEvent_1() {return event == 1;}
bool IsEvent_2() {return event == 2;}

void Action_0() {std::cout << "Event_0 is received, execute Action_0() and go to STATE_0" << std::endl;}
void Action_1() {std::cout << "Event_1 is received, execute Action_1() and go to STATE_1" << std::endl;}
void Action_2() {std::cout << "Event_2 is received, execute Action_2() and go to STATE_2" << std::endl;}

static constexpr fsm::FSM_TableRow_t kFsmTable[] = {
// | Present state | Event | Action | Next state |
    {FSM_States::STATE_0, IsEvent_1, Action_1, FSM_States::STATE_1},
    {FSM_States::STATE_1, IsEvent_2, Action_2, FSM_States::STATE_2},
    {FSM_States::STATE_2, IsEvent_0, Action_0, FSM_States::STATE_0},
    {FSM_States::STATE_2, IsEvent_1, Action_1, FSM_States::STATE_1},
};

int main()
{
    fsm::FSM fsm(kFsmTable, sizeof(kFsmTable), FSM_States::STATE_0);  // Instantiate and initialize FSM

    while (true) {
        fsm::FSM_ReturnCode_t status_code = fsm.FSM_Kernel();  // FSM kernel task running on background
        
        if (status_code != fsm::FSM_SUCCESS) {
            std::cout << "FSM error status code: " << status_code << std::endl;
            return EXIT_FAILURE;
        }

        std::cout << "\nFSM current state: " << fsm.FSM_GetCurrentState() << std::endl;
        std::cout << "Enter an event [0, 1 or 2]: ";
        std::cin >> event;

        // You can insert some time delay here
    }

    return EXIT_SUCCESS;
}
