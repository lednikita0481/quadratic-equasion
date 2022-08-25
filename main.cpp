#include <stdio.h>
//#include "TXLib.h"
#include <iso646.h>
#include <math.h>
#include <assert.h>

void enter_coefficients_manually(bool * out_check, struct SquareEq * EqParametrs);
void solve_quadratic_equation(struct SquareEq * EqParametrs);
void solve_linear_equation(struct SquareEq * EqParametrs);
void solve_quadratic_equasion_without_b_coeff(struct SquareEq * EqParametrs);
void result_output(struct SquareEq * EqParametrs);
void work_regime_choice(int * working_mode);
bool are_equal(double a, double b);


struct SquareEq
{
    /**
     * @brief structure contains all information about square equasion
     * 
     * @param nRoots contains information about number of roots of equasion
     * @param x1     contains information about the first root of equasion
     * @param x2     contains information about the first root of equasion
     * @param a      contains information about the a-coefficient of equasion
     * @param b      contains information about the a-coefficient of equasion
     * @param c      contains information about the c-coefficient of equasion
     * 
     */
    int nRoots;
    double x1;
    double x2;
    double a;
    double b;
    double c;
};


int main(void)
{
    /**
     * @brief starts the program
     * 
     * Links to choice of working mode, entering coefficients, solving the equasion and output
     * 
     * @param working_mode takes information about regime of work
     * @param out_check helps to stop the programm if users enters 'q' in manual input
     * 
     * @see struct SquareEq
     * @see work_regime_choice()
     * @see enter_coefficients_manually()
     * @see solve_quadratic_equation()
     * @see result_output()
     */
    int working_mode = 3; // 1 - standart input for coeffs, 2 - file input

    struct SquareEq EqParametrs =
    {
        .nRoots = 0,
        .x1 = 0.0,
        .x2 = 0.0,
        .a = 0.0,
        .b = 0.0,
        .c = 0.0,
    };

    work_regime_choice(&working_mode);

    if (working_mode == 1)
    {
        bool out_check = false; //checks if a user wants to finish and enters 'q'
        printf("\nOk, let's do it! Just enter coefficients through a space, also write down zeros, 3 numbers in common.\n"
            "If you wanna finish, enter just 'q'\n>");

        while(!out_check)
        {
            enter_coefficients_manually(&out_check, &EqParametrs);
            if (out_check)
            {
                break;
            }
            printf("check result: a = %lg, b = %lg, c = %lg.\n", EqParametrs.a, EqParametrs.b, EqParametrs.c);
            solve_quadratic_equation(&EqParametrs);
            result_output(&EqParametrs);
        }
        printf("It was nice to see you here! Come back!\n");
    }

    else
    {
        // Here should be file_input function call.
    }

    return 0;
}

//enum

void work_regime_choice(int * working_mode)
{
    /**
     * @brief function to choose the working mode
     * 
     * Takes 1 or 2 in handle input and chooses regime of work
     * 
     * @param *working_mode gets the type of work from the user, 1 is manual input, 2 is file input
     * @param status is a helping var to check the unsuccessfull input
     * 
     * @see main()
     * 
     */
    assert(working_mode != nullptr);

    int status = 0; //varieble shows the result of scanf, 1 == success
    printf("Hello, stranger! Do you wanna solve a quadratic "
           "equation?\nNevertheless, Poltorashka said we gonna do it.\n\n"
           "So, I wanna you to enter three coefficients: a, b and c respectively\n"
           "Or you can choose an input from the file (in developing)\n\n"
           "Enter 1, if you wanna enter coefficients by yourself\n"
           "or 2, if you wanna chose the input from the file: ");

    while ((status = scanf("%d", working_mode)) != 1 or (*working_mode < 1 or *working_mode > 2)) //Entering the working mode with errors processing
    {
        if (status != 1)
        {
            while (getchar() != '\n') //buffer cleaning
            {
                continue;
            }
        }
        printf("Please, enter an integer number, 1 or 2: ");
    }

}
//doxygen
void enter_coefficients_manually(bool * out_check, struct SquareEq * EqParametrs)
{
    /**
     * @brief function to get coefficients by manual input
     * 
     * Gets three numbers and write them to the parametrs of the equasion
     * 
     * @param out_check checks if a user enters 'q' and finish entering after that
     * @param EqParametrs has all parametrs of current equasion
     * 
     * @see main()
     * @see struct SquareEq
     * 
     */
    assert(EqParametrs != nullptr);

    while (scanf("%lg %lg %lg", &(EqParametrs->a), &(EqParametrs->b), &(EqParametrs->c)) != 3) //input errors processing
    {
        if (getchar() == 'q') // user wants to finish the programm
        {
            *out_check = true;
            break;
        }

        while (getchar() != '\n') //buffer cleaning
        {
            continue;
        }
        printf("Enter 3 numbers, like that: \"1 2 3\", or enter 'q' to finish\n>");
    }
}

void solve_quadratic_equation(struct SquareEq * EqParametrs)
{
    /**
     * @brief function to solve quadratic equasion
     * 
     * Function calls function of linear equasion solving if a == 0 and solves quadratic equasion
     * if a != 0 with help of discriminant
     * 
     * @param EqParametrs has all parametrs of current equasion
     * @param dicriminant has a value of discriminant of quadratic equasion
     * @param sqrt_discriminant has a value of sqrt of discriminant of quadratic equasion
     * 
     * @see main()
     * @see solve_linear_equation()
     * @see struct SquareEq
     * 
     */
    assert(EqParametrs != nullptr);

    if (are_equal(EqParametrs->a, 0.0))
    {
        solve_linear_equation(EqParametrs);
        return;
    } //!

    double dicriminant = ((EqParametrs->b)*(EqParametrs->b)) - 4*((EqParametrs->a))*((EqParametrs->c));

    if (dicriminant < 0)
    {
        EqParametrs->nRoots = 0;
    }

    if (are_equal(dicriminant, 0.0))
    {
        EqParametrs->x1 = (-(EqParametrs->b))/(2*(EqParametrs->a));
        if (are_equal(EqParametrs->x1, 0.0)) EqParametrs->x1 = 0.0;
        EqParametrs->nRoots = 1;
    }

    if (dicriminant > 0)
    {
        double sqrt_discriminant = sqrt(dicriminant);
        EqParametrs->x1 = ((-(EqParametrs->b)) - sqrt_discriminant)/(2*(EqParametrs->a));
        EqParametrs->x2 = ((-(EqParametrs->b)) + sqrt_discriminant)/(2*(EqParametrs->a));
        EqParametrs->nRoots = 2;
    }
}


void solve_linear_equation(struct SquareEq * EqParametrs)
{
    /**
     * @brief function solves linear equasion
     * 
     * Is called from solve_quadratic_equasion if a-coeff == 0
     * 
     * @param EqParametrs has all parametrs of current equasion
     * 
     * @see solve_quadratic_equation()
     * @see struct SquareEq
     * 
     */
    assert(EqParametrs != nullptr);

    if (are_equal(EqParametrs->b, 0.0))
    {
        if (are_equal(EqParametrs->c, 0.0))                                                                      
        {
            EqParametrs->nRoots = -1;
            return;
        }
                                                                              
        EqParametrs->nRoots = 0;
        return;
    }

    EqParametrs->x1 = (-(EqParametrs->c))/(EqParametrs->b);
    EqParametrs->nRoots = 1;
}

void result_output(struct SquareEq * EqParametrs)
{
    /**
     * @brief puts the resulf of solving the quadratic equasion after manual input
     * 
     * @param EqParametrs has all parametrs of current equasion
     * 
     * @see main()
     * 
     * @see struct SquareEq
     */
    assert(EqParametrs != nullptr);
    assert(isfinite(EqParametrs->x1) or isfinite(EqParametrs->x2));

    if (are_equal(EqParametrs->x1, 0.0)) EqParametrs->x1 = 0.0;
    if (are_equal(EqParametrs->x2, 0.0)) EqParametrs->x2 = 0.0;

    if (EqParametrs->nRoots == -1)
    {
        printf("The equasion has an infinity of solutions\n\n>");
    }
    if (EqParametrs->nRoots == 1)
    {
        printf("The equasion has 1 solution. x = %lg\n\n>", EqParametrs->x1);
    }
    if (EqParametrs->nRoots == 2)
    {
        printf("The equasion has 2 solutions. x1 = %lg, x2 = %lg\n\n>", EqParametrs->x1, EqParametrs->x2);
    }
    if (EqParametrs->nRoots == 0)
    {
        printf("the equasion has 0 solutions\n\n>");
    }

}

bool are_equal(double a, double b)
{
    /**
     * @brief function checks an approximate equality of double numbers
     * 
     * @param a is the first number
     * @param b is the second number
     * 
     */
    return (fabs(a - b) <= 0.000000000000001);
}

//k&r codestyle


/*
early return pattern.
  f():
    if
    if
    if

    ....
*/
