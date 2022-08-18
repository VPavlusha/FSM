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

#ifndef FINITE_STATE_MACHINE_HPP_
#define FINITE_STATE_MACHINE_HPP_

/**
 * \file finite_state_machine.hpp
 * \brief Finite State Machine (FSM) API.
 */

#include <cstddef>

namespace fsm {

using FSM_Event_t = bool(*)(void);
using FSM_Action_t = void(*)(void);

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
    const FSM_Event_t event;          ///< The event that will trigger this transition.
    const FSM_Action_t action;        ///< The function to be performed during the transition. May be nullptr.
    const FSM_State_t next_state;     ///< Transition next state.
} FSM_TableRow_t;

/**
 * \brief The FSM class does the actual work of finite state machine.
 */
class FSM {
  public:
    /**
     * \brief FSM class initialization.
     *
     * \param[in]  fsm_table       The pointer to the FSM transition table.
     * \param[in]  fsm_table_size  The FSM transition table size in bytes.
     * \param[in]  default_state   The initial default FSM state.
     */
    FSM(const FSM_TableRow_t *const fsm_table, const size_t fsm_table_size, const FSM_State_t default_state) noexcept
        : fsm_table_(fsm_table), fsm_table_size_(fsm_table_size), current_state_(default_state) {}

    FSM(const FSM &) = delete;
    FSM &operator=(const FSM &) = delete;
    FSM(FSM &&) = delete;
    FSM &operator=(FSM &&) = delete;
    ~FSM() = default;

    FSM_State_t FSM_GetCurrentState() const noexcept;
    FSM_ReturnCode_t FSM_Kernel() noexcept;

  private:
    const FSM_TableRow_t *const fsm_table_;
    const size_t fsm_table_size_;
    FSM_State_t current_state_;
};

/**
 * \brief Get FSM current state.
 *
 * \return  FSM_State_t  The FSM current state.
 */
FSM_State_t FSM::FSM_GetCurrentState() const noexcept
{
    return current_state_;
}

/**
 * \brief FSM kernel task running on background.
 *
 * \return  FSM_SUCCESS             On success.
 * \return  FSM_ARGUMENT_NOT_VALID  If an argument is a nullptr pointer.
 */
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

#endif  // FINITE_STATE_MACHINE_HPP_
