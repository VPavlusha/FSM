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

#include <finite_state_machine.hpp>

#include <cstddef>

namespace fsm {

FSM_State_t FSM::FSM_GetCurrentState() const noexcept
{
    return current_state_;
}

FSM_ReturnCode_t FSM::FSM_Kernel() noexcept
{
    for (size_t row = 0; row < fsm_table_size_ / sizeof(FSM_TableRow_t); ++row) {
        if (fsm_table_[row].present_state == current_state_) {
            if (fsm_table_[row].event != nullptr) {
                if (fsm_table_[row].event()) {
                    if (fsm_table_[row].action != nullptr) {
                        fsm_table_[row].action();
                    }
                    current_state_ = fsm_table_[row].next_state;
                    break;
                }
            } else {
                return FSM_ReturnCode_t::FSM_ARGUMENT_NOT_VALID;
            }
        }
    }
    return FSM_ReturnCode_t::FSM_SUCCESS;
}

}  // namespace fsm
