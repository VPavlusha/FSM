/*
 * MIT License
 * 
 * Copyright (c) 2022 Volodymyr Pavlusha
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef FINITE_STATE_MACHINE_H_
#define FINITE_STATE_MACHINE_H_

/**
 * \file finite_state_machine.h
 * \brief Finite State Machine (FSM) API.
 */

#include <stdbool.h>
#include <stddef.h>

typedef bool (*FSM_Event_t)(void);
typedef void (*FSM_Action_t)(void);

/**
 * \brief FSM return codes.
 */
typedef enum {
    FSM_SUCCESS            =  0,  ///< Success Code.
    FSM_ARGUMENT_NOT_VALID = -1,  ///< One of the API function arguments is not valid.
} FSM_ReturnCode_t;

/**
 * \brief FSM states type.
 */
typedef int FSM_State_t;

/**
 * \brief FSM transition table row.
 */
typedef struct {
    const FSM_State_t present_state;  ///< Transition present state.
    const FSM_Event_t event;          ///< Event that will trigger this transition.
    const FSM_Action_t action;        ///< Function to be performed during the transition. May be NULL.
    const FSM_State_t next_state;     ///< Transition next state.
} FSM_TableRow_t;

/**
 * \brief FSM instance type.
 */
typedef struct {
    const FSM_TableRow_t *const fsm_table;  ///< Pointer to the FSM transition table.
    const size_t fsm_table_size;            ///< FSM transition table size in bytes.
    FSM_State_t current_state;              ///< FSM current state. Set default state on initialization.
} FSM_t;

/**
 * \brief FSM kernel task running on background.
 *
 * \param[in]  fsm  Pointer to the FSM.
 *
 * \return  FSM_SUCCESS             On success.
 * \return  FSM_ARGUMENT_NOT_VALID  If an argument is a NULL pointer.
 */
FSM_ReturnCode_t FSM_Kernel(FSM_t *const fsm);

#endif  // FINITE_STATE_MACHINE_H_
