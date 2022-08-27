#include <stdio.h>
//#include "TXLib.h"
#include <iso646.h>
#include <math.h>
#include <assert.h>
#include <string.h>
#include "solving.h"
#define FILE_NAME_LEN 40


//./a.exe --run_tests filename.txt
//./a.exe --run_tests 
//./a.exe

int main(int argc, char *argv[])
{
    Working_Mode working_mode = work_regime_choice(argc, argv);
    //!switch-case on function res

    switch (working_mode)
    {
    case HANDLE_INPUT:
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
        }
        break;

    case FILE_INPUT_READ:
        {
            char *file_name = get_file_name();
            struct SquareEq EqParametrs = {};
            File_Input(&EqParametrs, file_name);
            break;
        }

    case FILE_INPUT_CMD:
        {
            char *file_name = argv[2];
            
            if (argc > 3)
            {
                for (int i = 3; i < argc; i++)
                {
                    strncat(file_name, " ", FILE_NAME_LEN);
                    strncat(file_name, argv[i], FILE_NAME_LEN);
                }
            }

            struct SquareEq EqParametrs = {};
            File_Input(&EqParametrs, file_name);
            break;
        }
   
    default:
        break;
    }


    return 0;
}




