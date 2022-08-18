[![GitHub](https://img.shields.io/github/license/VPavlusha/FSM?color=blue&label=License&logo=github)](LICENSE)
![GitHub Workflow Status](https://img.shields.io/github/workflow/status/VPavlusha/FSM/CMake?label=CMake&logo=Github)
![GitHub Workflow Status](https://img.shields.io/github/workflow/status/VPavlusha/FSM/cpp-linter?label=cpp-linter&logo=Github)
---

# FSM - Finite State Machine
A static (no dynamic allocations) C/C++ Finite State Machine (FSM) header-only library.<br />
Based on original design published at: <a href="https://github.com/AstarLight/FSM-framework"><strong>FSM-framework</strong></a>.

#### Table of Contents  
&emsp;[1. Features](#1-features)  
&emsp;[2. State Transition Table](#2-state-transition-table)  
&emsp;[3. Basic Usage in C](#3-basic-usage-in-c)  
&emsp;[4. Basic Usage in C++](#4-basic-usage-in-c)  
&emsp;[5. Examples](#5-examples)  
&emsp;[6. Installation](#6-installation)  
&emsp;[7. Requirement](#7-requirement)  
&emsp;[8. Build Procedure](#8-build-procedure)  
&emsp;[9. License](#9-license)  

## 1. Features
  - **Permissive** MIT License.
  - **C and C++ languages** – state machine is written both in C and C++ languages.
  - **Compact** – consumes a minimum amount of resources.
  - **Header-only library** – no special installation steps are needed.
  - **Fully static** – no dynamic memory allocations.
  - **Objects** – support multiple FSM instantiations of a single state machine type.
  - **Transition table** – transition table precisely controls state transition behavior.
  - **Event** – every event is a separate function.
  - **State action** – every state action is a separate function.
  - **Error checking** – runtime checks catch mistakes early.

## 2. State Transition Table

<img src="./doc/img/fsm_diagram.svg" alt="Finite State Machine" width="550"/>

The state diagram shown in the figure can be described via a state transition table. This table has four columns and as many rows as needed. Each row describes a transition from the **Present State** to the **Next State**. The transition is triggered by the **Event** (a combination of one or more event flags). The **Action** describes all the actions associated with the transition.
| Present State | Event | Action | Next State |
|:-------------:|:-----:|:------:|:----------:|
| STATE_0 | IsEvent_1 | Action_1 | STATE_1 |
| STATE_1 | IsEvent_2 | Action_2 | STATE_2 |
| STATE_2 | IsEvent_0 | Action_0 | STATE_0 |
| STATE_2 | IsEvent_1 | Action_1 | STATE_1 |

## 3. Basic Usage in C
```C
// 1. Include FSM header:
#include "finite_state_machine.h"

// 2. Create enumeration for FSM states:
enum FSM_States {
    STATE_0,
    STATE_1,
    STATE_2,
};

// 3. Create Event functions:
bool IsEvent_0(void) {...}
bool IsEvent_1(void) {...}
bool IsEvent_2(void) {...}

// 3. Create Action functions:
void Action_0(void) {...}
void Action_1(void) {...}
void Action_2(void) {...}

// 4. Create FSM Transition table:
static const FSM_TableRow_t kFsmTable[] = {
// | Present state | Event | Action | Next state |
    {STATE_0, IsEvent_1, Action_1, STATE_1},
    {STATE_1, IsEvent_2, Action_2, STATE_2},
    {STATE_2, IsEvent_0, Action_0, STATE_0},
    {STATE_2, IsEvent_1, Action_1, STATE_1},
};

int main()
{
    // 5. Instantiate and initialize FSM:
    FSM_t fsm = {kFsmTable, sizeof(kFsmTable), STATE_0};

    while (true) {
        // 6. Handle FSM instance:
        FSM_ReturnCode_t status_code = FSM_Kernel(&fsm);  // FSM kernel task running on background
        
        if (status_code != FSM_SUCCESS) {
            return EXIT_FAILURE;
        }

        // You can insert some time delay here
    }

    return EXIT_SUCCESS;
}
```

## 4. Basic Usage in C++
```C
// 1. Include FSM header:
#include "finite_state_machine.hpp"

// 2. Create enumeration for FSM states:
enum FSM_States : int {
    STATE_0,
    STATE_1,
    STATE_2,
};

// 3. Create Event functions:
bool IsEvent_0(void) {...}
bool IsEvent_1(void) {...}
bool IsEvent_2(void) {...}

// 3. Create Action functions:
void Action_0(void) {...}
void Action_1(void) {...}
void Action_2(void) {...}

// 4. Create FSM Transition table:
static constexpr fsm::FSM_TableRow_t kFsmTable[] = {
// | Present state | Event | Action | Next state |
    {FSM_States::STATE_0, IsEvent_1, Action_1, FSM_States::STATE_1},
    {FSM_States::STATE_1, IsEvent_2, Action_2, FSM_States::STATE_2},
    {FSM_States::STATE_2, IsEvent_0, Action_0, FSM_States::STATE_0},
    {FSM_States::STATE_2, IsEvent_1, Action_1, FSM_States::STATE_1},
};

int main()
{
    // 5. Instantiate and initialize FSM:
    fsm::FSM fsm(kFsmTable, sizeof(kFsmTable), FSM_States::STATE_0);

    while (true) {
        // 6. Handle FSM instance:
        fsm::FSM_ReturnCode_t status_code = fsm.FSM_Kernel();  // FSM kernel task running on background
        
        if (status_code != fsm::FSM_SUCCESS) {
            return EXIT_FAILURE;
        }

        // You can insert some time delay here
    }

    return EXIT_SUCCESS;
}
```

## 5. Examples
Do not hesitate to read, run and explore the [`examples`](https://github.com/VPavlusha/FSM/tree/main/examples) directory which should be really useful if you want to understand quickly the FSM API.

## 6. Installation
FSM is a header-only library, no special installation steps are needed. Just point your compiler to the [`include`](https://github.com/VPavlusha/FSM2/tree/main/include) directory.

## 7. Requirement
For the build process :
  - cmake
  - make
  - gcc

For the documentation generation :
  - doxygen

## 8. Build Procedure
```
git clone https://github.com/VPavlusha/FSM.git
cd fsm
mkdir build && cd build
cmake .. -G "Unix Makefiles" && make
```

## 9. License
FSM is [Open Source] software. It may be used for any purpose,
including commercial purposes, at absolutely no cost. It is
distributed under the terms of the [MIT license].

  [Open Source]: http://www.opensource.org/docs/definition.html
  [MIT license]: http://www.opensource.org/licenses/mit-license.html
