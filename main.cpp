#include <stdio.h>
//#include "TXLib.h"
#include <iso646.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>

void enter_coefficients_manually(bool * out_check, struct SquareEq * EqParametrs);
void solve_quadratic_equation(struct SquareEq * EqParametrs);
void solve_linear_equation(struct SquareEq * EqParametrs);
void solve_quadratic_equasion_without_b_coeff(struct SquareEq * EqParametrs);
void result_output(struct SquareEq * EqParametrs);
void work_regime_choice(int * working_mode);
int checking_equality_of_doubles(double a, double b);


struct SquareEq
{
    int nRoots;
    double x1;
    double x2;
    double a;
    double b;
    double c;
};


int main(void)
{
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
            //printf("%d %d %d %d\n>", &out_check == nullptr, &a == nullptr, &b == nullptr, &c == nullptr);
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

void enter_coefficients_manually(bool * out_check, struct SquareEq * EqParametrs)
{
    //assert(out_check == nullptr or a == nullptr or b == nullptr or c == nullptr);
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
    //assert(!x1 || !x2);

    if (checking_equality_of_doubles(EqParametrs->a, 0.0))
    {
        solve_linear_equation(EqParametrs);
    }
    else
    //
    //github test
    {
        if (checking_equality_of_doubles(EqParametrs->b, 0.0))
        {
            solve_quadratic_equasion_without_b_coeff(EqParametrs);
        }
        else
        {
            if (checking_equality_of_doubles(EqParametrs->c, 0.0))                                                                   //ax^2 + bx = 0
            {
                double sol1 = 0.0;
                double sol2 = (-(EqParametrs->b))/((EqParametrs->a));

                if (sol1 > sol2)
                {
                    EqParametrs->x1 = sol2;
                    EqParametrs->x2 = sol1;
                }
                else
                {
                    EqParametrs->x1 = sol1;
                    EqParametrs->x2 = sol2;
                }
                EqParametrs->nRoots = 2;
            }

            else                                                                         //ax^2 + bx + c = o
            {
                double dicriminant = ((EqParametrs->b)*(EqParametrs->b)) - 4*((EqParametrs->a))*((EqParametrs->c));

                if (dicriminant < 0)
                {
                    EqParametrs->nRoots = 0;
                }

                if (checking_equality_of_doubles(dicriminant, 0.0))
                {
                    EqParametrs->x1 = (-(EqParametrs->b))/(2*(EqParametrs->a));
                    EqParametrs->nRoots = 1;
                }

                if (dicriminant > 0)
                {
                    EqParametrs->x1 = ((-(EqParametrs->b)) - pow(dicriminant, 0.5))/(2*(EqParametrs->a));
                    EqParametrs->x2 = ((-(EqParametrs->b)) + pow(dicriminant, 0.5))/(2*(EqParametrs->a));
                    EqParametrs->nRoots = 2;
                }
            }
        }
    }
}

void solve_linear_equation(struct SquareEq * EqParametrs)
{
    //assert(!x1 || !x2);

    if (checking_equality_of_doubles(EqParametrs->b, 0.0))
    {
        if (checking_equality_of_doubles(EqParametrs->c, 0.0))                                                                      //0=0
        {
            EqParametrs->nRoots = -1;
        }
        else                                                                               //0=c
        {
            EqParametrs->nRoots = 0;
        }
    }
    else
    {
        if (checking_equality_of_doubles(EqParametrs->c, 0.0))                                                                        //bx = 0
        {
            EqParametrs->x1 = 0.0;
            EqParametrs->nRoots = 1;
        }
        else                                                                               //bx + c = 0
        {
            EqParametrs->x1 = (-(EqParametrs->c))/(EqParametrs->b);
            EqParametrs->nRoots = 1;
        }
    }
}

void solve_quadratic_equasion_without_b_coeff(struct SquareEq * EqParametrs)
{
    //assert(!x1 || !x2);

    if (checking_equality_of_doubles(EqParametrs->c, 0.0))                                                                          //ax^2 = 0
    {
        EqParametrs->x1 = 0.0;
        EqParametrs->nRoots = 1;
    }

    else                                                                                   //ax^2 + c = 0
    {
        double eq = (-(EqParametrs->c))/(EqParametrs->a);
        if (eq > 0)
        {
            EqParametrs->x1 = -pow(eq, 0.5);
            EqParametrs->x2 =  pow(eq, 0.5);
            EqParametrs->nRoots = 2;
        }
        else
        {
            EqParametrs->nRoots = 0;
        }
    }
}

void result_output(struct SquareEq * EqParametrs)
{
    if (EqParametrs->nRoots == -1)
    {
        printf("The equasion has an infinity of solutions\n\n>");
    }
    if (EqParametrs->nRoots == 1)
    {
        printf("The equasion has 1 solution. x = %lf\n\n>", EqParametrs->x1);
    }
    if (EqParametrs->nRoots == 2)
    {
        printf("The equasion has 2 solutions. x1 = %lf, x2 = %lf\n\n>", EqParametrs->x1, EqParametrs->x2);
    }
    if (EqParametrs->nRoots == 0)
    {
        printf("the equasion has 0 solutions\n\n>");
    }

}

int checking_equality_of_doubles(double a, double b)
{
    if (fabs(a - b) <= 0.0000001) return 1;
    return 0;
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
