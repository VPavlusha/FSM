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

#include "finite_state_machine.h"

#include <stddef.h>

FSM_ReturnCode_t FSM_Kernel(FSM_t *const fsm)
{      
    if (fsm == NULL) {
        return FSM_ARGUMENT_NOT_VALID;
    }

    for (size_t row = 0; row < fsm->fsm_table_size / sizeof(FSM_TableRow_t); ++row) {
        if (fsm->fsm_table[row].present_state == fsm->current_state) {
            if (fsm->fsm_table[row].event != NULL) {
                if (fsm->fsm_table[row].event()) {
                    if (fsm->fsm_table[row].action != NULL) {
                        fsm->fsm_table[row].action();
                    }
                    fsm->current_state = fsm->fsm_table[row].next_state;
                    break;
                }
            } else {
                return FSM_ARGUMENT_NOT_VALID;
            }
        }
    }
    return FSM_SUCCESS;
}
