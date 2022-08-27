#include <stdio.h>
//#include "TXLib.h"
#include <iso646.h>
#include <math.h>
#include <assert.h>
#include <string.h>
#include "solving.h"
#define FILE_NAME_LEN 40

const double eps = 1e-7;

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
    }

    if (are_equal(dicriminant, 0.0))
    {
        EqParametrs->x1 = (-(EqParametrs->b))/(2*(EqParametrs->a));
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
            return;
        }

        EqParametrs->nRoots = ZERO_ROOTS;
        return;
    }

    EqParametrs->x1 = (-(EqParametrs->c))/(EqParametrs->b);
    EqParametrs->nRoots = ONE_ROOT;
}

enum Working_Mode work_regime_choice(int argc, char *argv[])
{
    switch (argc)
    {
    case 1:
        return HANDLE_INPUT;

    case 2:
        if (!strcmp(argv[1], "--read_file"))
        {
            return FILE_INPUT_READ;
        }
        
        printf("I don't know what the second argument means");
        return NON_INPUT;
    
    case 3:
        if (!strcmp(argv[1], "--read_file"))
        {
            return FILE_INPUT_CMD;
        }

        printf("I don't know what the second argument means");
        return NON_INPUT;
    
    default:
        if (!strcmp(argv[1], "--read_file"))
        {
            return FILE_INPUT_CMD;
        }

        printf("WHATA YOU WANT FROM ME???");
        return NON_INPUT;
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

        buffer_cleaning();

        printf("Enter 3 numbers, like that: \"1 2 3\", or enter 'q' to finish\n>");
    }
}

void manual_result_output(struct SquareEq * EqParametrs)
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

        default:
            printf("OOPs! Something went wrong and nRoots is broken\n");
            break;
    }
}

char * get_file_name()
{
    printf("Please, enter, what file should I find to take tests?\n>");
    char *file_name = new char[FILE_NAME_LEN];

    fgets(file_name, FILE_NAME_LEN, stdin);

    int i = 0;
    while (file_name[i] != '\n') i++;

    file_name[i] = '\0';
    return file_name;
}

void File_Input(struct SquareEq * EqParametrs, char *file_name)
{
    FILE *file;

    if ((file = fopen(file_name, "r")) == NULL)
    {
        printf("OoOps :( Please, create file \"%s\" with tests and try again", file_name);
        return;
    }

    int Expected_nRoots = 0;
    double Expected_x1 = 0.0;
    double Expected_x2 = 0.0;

    int i = 0;

    while ((fscanf(file, "%lg, %lg, %lg, %d, %lg, %lg", &(EqParametrs->a), &(EqParametrs->b), &(EqParametrs->c),
                &Expected_nRoots, &Expected_x1, &Expected_x2)) == 6)
    {
        solve_quadratic_equation(EqParametrs);

        Checks_values(i, EqParametrs, Expected_nRoots, Expected_x1, Expected_x2);

        (*EqParametrs) = {};

        i++;
    }
    
    fclose(file);
}

void Checks_values(int i, struct SquareEq * EqParametrs, int Expected_nRoots, double Expected_x1, double Expected_x2)
{
    if ((EqParametrs->nRoots != Expected_nRoots) || !are_equal(EqParametrs->x1, Expected_x1) ||
                                                    !are_equal(EqParametrs->x2, Expected_x2))
    {
        printf("\nFAILED Test %d. \n"
                "Expected: nRoots = %d, x1 = %10lg, x2 = %10lg\n"
                "Got:      nRoots = %d, x1 = %10lg, x2 = %10lg\n\n", i+1, Expected_nRoots, Expected_x1, Expected_x2,
                EqParametrs->nRoots, EqParametrs->x1, EqParametrs->x2);
        return;
    }

    printf("success Test %2d\n", i+1);
}

bool are_equal(double a, double b)
{
    return (fabs(a - b) <= eps);
}

void buffer_cleaning()
{
    while (getchar() != '\n')
    {
        continue;
    }
}