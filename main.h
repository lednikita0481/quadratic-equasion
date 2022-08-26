enum Working_Mode
{
    /**
     * @brief Neede to choose the working mode of the programm
     * 
     * HANDLE_INPUT    needed to enter coefficients from keyboard
     * UNIT_TEST_INPUT needed to enter coefficients from the massive in the programm
     * FILE_INPUT      needed to enter coefficients from the file
     * NON_INPUT       default value untill user changes it
     */

    HANDLE_INPUT,
    UNIT_TEST_INPUT,
    FILE_INPUT,
    NON_INPUT
};

/**
 * @brief function to get coefficients by manual input
 *
 * Gets three numbers and write them to the parametrs of the equasion
 *
 * @param out_check checks if a user enters 'q' and finish entering after that
 * @param EqParametrs has all parametrs of current equasion
 *
 * @see struct SquareEq
 *
*/


void enter_coefficients_manually(bool * out_check, struct SquareEq * EqParametrs);

/**
 * @brief function to solve quadratic equasion
 *
 * Function calls function of linear equasion solving if a == 0 and solves quadratic equasion
 * if a != 0 with help of discriminant
 *
 * @param EqParametrs has all parametrs of current equasion
 *
 * @see struct SquareEq
 *
*/
void solve_quadratic_equation(struct SquareEq * EqParametrs);

/**
 * @brief function solves linear equasion
 *
 * Is called from solve_quadratic_equasion if a-coeff == 0
 *
 * @param EqParametrs has all parametrs of current equasion
 *
 * @see struct SquareEq
*/
void solve_linear_equation(struct SquareEq * EqParametrs);

/**
 * @brief puts the resulf of solving the quadratic equasion after manual input
 *
 * @param EqParametrs has all parametrs of current equasion
 *
 * @see struct SquareEq
*/
void result_output(struct SquareEq * EqParametrs);

/**
 * @brief function to choose the working mode
 *
 * Takes 1 or 2 in handle input and chooses regime of work
 *
 * @param *working_mode gets the type of work from the user, 1 is manual input, 2 is file input
*/
void work_regime_choice(enum Working_Mode * working_mode);

/**
 * @brief function checks an approximate equality of double numbers
 *
 * @param a is the first number
 * @param b is the second number
 *
*/
bool are_equal(double a, double b);


/**
 * @brief Checks the algoritm of quadratic equasion solving 
 * 
 * Has a massive of massives with 3 coefficients (a, b, c), 
 * expected amount of roots, expected answeres.
 * Calls the function of quadratic equasion solving 
 * and the function of comparison of received answeres and expected ones.
 * 
 * @param EqParametrs has all parametrs of current equasion
 * 
 * @see struct SquareEq
 */
void Unit_Test(struct SquareEq * EqParametrs);


/**
 * @brief Compares received answers with expected
 * 
 * @param i shows number of test
 * @param EqParametrs has all parametrs of current equasion
 * @param Expected_nRoots 
 * @param Expected_x1 
 * @param Expected_x2 
 * 
 * @see struct SquareEq
 */
void Checks_values(int i, struct SquareEq * EqParametrs, int Expected_nRoots, double Expected_x1, double Expected_x2);


void File_Input(struct SquareEq * EqParametrs);

/**
 * @brief Cleans the buffer after enter
 *
 * Function skips symbols untill '\n'
 *
 */
void buffer_cleaning();
