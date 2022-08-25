#include <stdio.h>
//#include "TXLib.h"
#include <iso646.h>
#include <math.h>
#include <assert.h>
#include "main.h"

const double eps = 0.00000001;

enum Roots
{
    /**
     * @brief has values that nRoots parametr in SquareEq structure can take
     */
    ZERO_ROOTS,
    ONE_ROOT,
    TWO_ROOTS,
    INF_ROOTS
};

struct SquareEq
{
    /**
     * @brief structure contains all information about square equasion
     */
    Roots nRoots;
    double x1;
    double x2;
    double a;
    double b;
    double c;
};


int main(void)
{
    printf("%d\n", NAN == NAN);
    int working_mode = 3; // 1 - standart input for coeffs, 2 - file input, gets value in work_regime_choice()

    struct SquareEq EqParametrs;

    work_regime_choice(&working_mode);

    if (working_mode == 1) // handle input of coefficients
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

    else // UNIT TEST
    {
        Unit_Test(&EqParametrs);
    }

    return 0;
}

//enum

void work_regime_choice(int * working_mode)
{
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

void enter_coefficients_manually(bool * out_check, struct SquareEq * EqParametrs)
{
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
    assert(EqParametrs != nullptr);

    if (are_equal(EqParametrs->a, 0.0))
    {
        solve_linear_equation(EqParametrs);
        return;
    } //!

    double dicriminant = ((EqParametrs->b)*(EqParametrs->b)) - 4*((EqParametrs->a))*((EqParametrs->c));

    if (dicriminant < 0)
    {
        EqParametrs->nRoots = ZERO_ROOTS;
        EqParametrs->x1 = 0.0;
        EqParametrs->x2 = 0.0;
    }

    if (are_equal(dicriminant, 0.0))
    {
        EqParametrs->x1 = (-(EqParametrs->b))/(2*(EqParametrs->a));
        EqParametrs->x2 = 0.0;
        if (are_equal(EqParametrs->x1, 0.0)) EqParametrs->x1 = 0.0;
        EqParametrs->nRoots = ONE_ROOT;
    }

    if (dicriminant > 0)
    {
        double sqrt_discriminant = sqrt(dicriminant);
        EqParametrs->x1 = ((-(EqParametrs->b)) - sqrt_discriminant)/(2*(EqParametrs->a));
        EqParametrs->x2 = ((-(EqParametrs->b)) + sqrt_discriminant)/(2*(EqParametrs->a));
        EqParametrs->nRoots = TWO_ROOTS;
    }
}


void solve_linear_equation(struct SquareEq * EqParametrs)
{
    assert(EqParametrs != nullptr);

    if (are_equal(EqParametrs->b, 0.0))
    {
        if (are_equal(EqParametrs->c, 0.0))
        {
            EqParametrs->nRoots = INF_ROOTS;
            EqParametrs->x1 = 0.1;
            EqParametrs->x2 = 0.1;
            return;
        }

        EqParametrs->nRoots = ZERO_ROOTS;
        EqParametrs->x1 = 0.0;
        EqParametrs->x2 = 0.0;
        return;
    }

    EqParametrs->x1 = (-(EqParametrs->c))/(EqParametrs->b);
    EqParametrs->x2 = 0.0;
    EqParametrs->nRoots = ONE_ROOT;
}

void result_output(struct SquareEq * EqParametrs)
{
    assert(EqParametrs != nullptr);
    assert(isfinite(EqParametrs->x1) && isfinite(EqParametrs->x2));

    if (are_equal(EqParametrs->x1, 0.0)) EqParametrs->x1 = 0.0;
    if (are_equal(EqParametrs->x2, 0.0)) EqParametrs->x2 = 0.0;

    switch (EqParametrs->nRoots)
    {
    case ZERO_ROOTS:
        printf("the equasion has 0 solutions\n\n>");
        break;
    case ONE_ROOT:
        printf("The equasion has 1 solution. x = %lg\n\n>", EqParametrs->x1);
        break;
    case TWO_ROOTS:
        printf("The equasion has 2 solutions. x1 = %lg, x2 = %lg\n\n>", EqParametrs->x1, EqParametrs->x2);
        break;
    case INF_ROOTS:
        printf("The equasion has an infinity of solutions\n\n>");
        break;
    }
}

bool are_equal(double a, double b)
{
    return (fabs(a - b) <= eps);
}

void Unit_Test(struct SquareEq * EqParametrs)
{
    double Tests[10][6] =
    {
        {2, -7, 3, 2, 0.5, 3},   // a, b, c, Expected_nRoots, Expected_x1, Expected_x2
        {0, 0, 0, 3, 0.1, 0.1},
        {4, -44, 121, 1, 5.5, 0.0},
        {0, 16, 56, 1, -3.5, 0.0},
        {0, 12, 0, 1, 0, 0.0},
        {3, -5, -8, 2, -1, (8.0/3.0)},
        {1, 0, 0, 1, 0, 0.0},
        {1, 0, -81, 2, -9, 9},
        {1, -1, -40200, 2, -200, 201},
        {1, 33, -34, 2, -34, 1}
    };

    for (int i = 0; i < 10; i++)
    {
        EqParametrs->a = Tests[i][0];
        EqParametrs->b = Tests[i][1];
        EqParametrs->c = Tests[i][2];
        solve_quadratic_equation(EqParametrs);
        int Expected_nRoots = Tests[i][3];
        double Expected_x1 = Tests[i][4];
        double Expected_x2 = Tests[i][5];
        Checks_values(i, EqParametrs, Expected_nRoots, Expected_x1, Expected_x2);
    }
}

void Checks_values(int i, struct SquareEq * EqParametrs, int Expected_nRoots, double Expected_x1, double Expected_x2)
{
    if ((EqParametrs->nRoots != Expected_nRoots) || !are_equal(EqParametrs->x1, Expected_x1) || !are_equal(EqParametrs->x2, Expected_x2))
    {
        printf("\nFAILED Test %d. \n"
                "Expected: nRoots = %d, x1 = %10lg, x2 = %10lg\n"
                "Got:      nRoots = %d, x1 = %10lg, x2 = %10lg\n\n", i+1, Expected_nRoots, Expected_x1, Expected_x2,
                EqParametrs->nRoots, EqParametrs->x1, EqParametrs->x2);
        return;
    }
    printf("success Test %d\n", i+1);
}

