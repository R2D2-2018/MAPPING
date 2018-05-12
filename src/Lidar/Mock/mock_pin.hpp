/**
 * @file
 * @brief     Mock pin class
 * @author    Bendeguz Toth
 * @license   See LICENSE
 */

#ifndef MOCK_PIN_HPP
#define MOCK_PIN_HPP

#include "../../wrap-hwlib.hpp"
#include <array>

namespace Mapping
{
    class MockPin : public hwlib::target::pin_in
    {
    private:
        int counter;
        ///< This array contains the bits that the function
        /// get() wll return in order.It is not possible to 
        /// pass a bool array longer than 64 to the constructor,
        /// that is why it had to be hardcoded here.
        static std::array<bool, 72> answers;
    public:
        MockPin();

        /**
         * @brief This function returns a bit.
         * 
         * This function returns a bit that is at index 
         * [number of calls this function ha been called 
         * previously] of answers.
         * 
         * @return A bit.
         */
        bool get(hwlib::buffering buf = hwlib::buffering::unbuffered ) override;
    };
}

#endif //MOCK_PIN_HPP

