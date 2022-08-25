#include <stdio.h>
//#include "TXLib.h"
#include <iso646.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>

void enter_coefficients_manually(bool * out_check, double * a, double * b, double * c);
int solve_quadratic_equation(double a, double b, double c, double * x1, double * x2);
int solve_linear_equation(double b, double c, double * x1, double * x2);
int solve_quadratic_equasion_without_b_coeff(double a, double c, double * x1, double * x2);
void result_output(int nRoots, double x1, double x2);
void work_regime_choice(int * working_mode);

int main(void)
{
    int working_mode = 3; // 1 - standart input for coeffs, 2 - file input

    // -INFINITY == no solutions
    //  INFINITY == inf solutions
    double x1 = -INFINITY;
    double x2 = -INFINITY;
    double a = 0.0;
    double b = 0.0;
    double c = 0.0;

    work_regime_choice(&working_mode);

    if (working_mode == 1)
    {
        bool out_check = false; //checks if a user wants to finish and enters 'q'
        printf("\nOk, let's do it! Just enter coefficients through a space, also write down zeros, 3 numbers in common.\n"
            "If you wanna finish, enter just 'q'\n>");

        while(!out_check)
        {
            printf("%d %d %d %d\n>", &out_check == nullptr, &a == nullptr, &b == nullptr, &c == nullptr);
            enter_coefficients_manually(&out_check, &a, &b, &c);
            if (out_check)
            {
                break;
            }
            printf("check result: a = %lg, b = %lg, c = %lg.\n", a, b, c);
            int nRoots = solve_quadratic_equation(a, b, c, &x1, &x2);
            result_output(nRoots, x1, x2);
        }
        printf("It was nice to see you here! Come back!\n");
    }

    else
    {
        // Here should be file_input function call.
    }

    return 0;
}

void work_regime_choice(int * working_mode)
{
    //assert(!working_mode);

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
            while (getchar() != '\n')
            {
                continue;
            }
        }
        printf("Please, enter an integer number, 1 or 2: ");
    }

}

void enter_coefficients_manually(bool * out_check, double * a, double * b, double * c)
{
    assert(out_check == nullptr or a == nullptr or b == nullptr or c == nullptr);
    printf("%d %d %d %d\n>", out_check == nullptr, a == nullptr, b == nullptr, c == nullptr);
    while (scanf("%lg %lg %lg", a, b, c) != 3) //input errors processing
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

int solve_quadratic_equation(double a, double b, double c, double * x1, double * x2)
{
    //assert(!x1 || !x2);

    if (a == 0.0)
    {
        int nRoots = solve_linear_equation(b, c, x1, x2);
        return nRoots;
    }
    else
    {
        if (b == 0.0)
        {
            int nRoots = solve_quadratic_equasion_without_b_coeff(a, c, x1, x2);
            return nRoots;
        }
        else
        {
            if (c == 0)                                                                   //ax^2 + bx = 0
            {
                double sol1 = 0.0;
                double sol2 = (-b)/(a);

                if (sol1 > sol2)
                {
                    *x1 = sol2;
                    *x2 = sol1;
                }
                else
                {
                    *x1 = sol1;
                    *x2 = sol2;
                }
                return 2;
            }

            else                                                                         //ax^2 + bx + c = o
            {
                double dicriminant = (b*b) - 4*(a)*(c);

                if (dicriminant < 0)
                {
                    return 0;
                }

                if (dicriminant == 0.0)
                {
                    *x1 = (-b)/(2*(a));
                    return 1;
                }

                if (dicriminant > 0)
                {
                    *x1 = ((-b) - pow(dicriminant, 0.5))/(2*(a));
                    *x2 = ((-b) + pow(dicriminant, 0.5))/(2*(a));
                    return 2;
                }
            }
        }
    }
}

int solve_linear_equation(double b, double c, double * x1, double * x2)
{
    //assert(!x1 || !x2);

    if (b == 0.0)
    {
        if (c == 0.0)                                                                      //0=0
        {
            return INFINITY;
        }
        else                                                                               //0=c
        {
            return 0;
        }
    }
    else
    {
        if (c == 0)                                                                        //bx = 0
        {
            *x1 = 0.0;
            return 1;
        }
        else                                                                               //bx + c = 0
        {
            *x1 = (-c)/(b);
            return 1;
        }
    }
}

int solve_quadratic_equasion_without_b_coeff(double a, double c, double * x1, double * x2)
{
    //assert(!x1 || !x2);

    if (c == 0.0)                                                                          //ax^2 = 0
    {
        *x1 = 0.0;
        return 1;
    }

    else                                                                                   //ax^2 + c = 0
    {
        double eq = (-c)/(a);
        if (eq > 0)
        {
            *x1 = -pow(eq, 0.5);
            *x2 =  pow(eq, 0.5);
            return 2;
        }
        else
        {
            return 0;
        }
    }
}

void result_output(int nRoots, double x1, double x2)
{
    if (nRoots == INFINITY)
    {
        printf("The equasion has an infinity of solutions");
    }
    if (nRoots == 1)
    {
        printf("The equasion has 1 solution. x = %lf", x1);
    }
    if (nRoots == 2)
    {
        printf("The equasion has 2 solutions. x1 = %lf, x2 = %lf", x1, x2);
    }
    if (nRoots == 0)
    {
        printf("the equasion has 0 solutions");
    }

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
