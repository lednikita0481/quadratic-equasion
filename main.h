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
void work_regime_choice(int * working_mode);

/**
 * @brief function checks an approximate equality of double numbers
 * 
 * @param a is the first number
 * @param b is the second number
 * 
*/
bool are_equal(double a, double b);