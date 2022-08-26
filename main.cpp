#include <stdio.h>
//#include "TXLib.h"
#include <iso646.h>
#include <math.h>
#include <assert.h>
#include "solving.h"


int main(void)
{
    Working_Mode working_mode = NON_INPUT;

    work_regime_choice(&working_mode);

    if (working_mode ==  HANDLE_INPUT)
    {
        bool out_check = false; //checks if a user wants to finish and enters 'q'
        printf("\nOk, let's do it! Just enter coefficients through a space, also write down zeros, 3 numbers in common.\n"
            "If you wanna finish, enter just 'q'\n>");

        while(!out_check)
        {
            struct SquareEq EqParametrs = {};

            enter_coefficients_manually(&out_check, &EqParametrs);

            if (out_check)
            {
                break;
            }

            printf("check result: a = %lg, b = %lg, c = %lg.\n", EqParametrs.a, EqParametrs.b, EqParametrs.c);

            solve_quadratic_equation(&EqParametrs);

            manual_result_output(&EqParametrs);
        }

        printf("It was nice to see you here! Come back!\n");
    }

    else if (working_mode == UNIT_TEST_INPUT)
    {
        struct SquareEq EqParametrs = {};

        Unit_Test(&EqParametrs);
    }


    else if (working_mode == FILE_INPUT)
    {
        struct SquareEq EqParametrs = {};

        File_Input(&EqParametrs);
    }


    return 0;
}




