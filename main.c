#include    <stdio.h>
#include    <stdlib.h>
#include    <time.h>

/*
** clear the buffer to avoid scanf problems
*/
void    clear_buffer(void)
{
        int c;
        while((c=getchar()) != EOF && c != '\n');
}

/*
** Say to the player that the number he chose is bigger or smaller (or same) as the "nombre mystere"
** Also check if the choice is in the good interval
*/
void    verif_choice(signed short p_number_tested, signed short p_number, signed short p_max_value)
{
        if (p_number_tested >= 1 && p_number_tested <= p_max_value)
        {
            if (p_number_tested > p_number)
                printf("Le nombre choisi est trop GRAND !\n");

            else if (p_number_tested < p_number)
                printf("le nombre choisi est trop PETIT !\n");
         
            else 
                printf("Et c'est le GG!\n");
        }
        else 
            printf("ATTENTION ! Entrez un nombre compris entre 1 et %hd !\n", p_max_value);
}

/*
** Generate a random integer between 1 and p_max_value
*/
int     gen_number(signed short p_max_value)
{
        return (rand() % (p_max_value)) + 1;
}

/*
** check if the level chose by the player is 1, 2 or 3 and nothing else
*/
short   verif_level(int p_ret_scanf, signed short p_level)
{
        clear_buffer();
        if(p_ret_scanf == 1)
        {
            switch (p_level)
            {
                case 1: 
                case 2: 
                case 3: 
                    return (1);
                break;
                default:
                    return (0);
            }
        }
        else
            return(0);
}

/*
** Just printf the main menu
*/
void    show_menu(void)
{
        printf("\nBienvenue dans le jeu du PLUS OU MOINS !\n");
        printf("========================================\n");
        printf("Entrez le niveau de difficulte desire:\n");
        printf("-------------------------------------\n");
        printf("1 - Nombre mystere compris entre 1 et 100\n");
        printf("2 - Nombre mystere compris entre 1 et 1000\n");
        printf("3 - Nombre mystere compris entre 1 et 10000!!!\n");
        printf("C'est a vous: ");
}

/*
** Just printf the beginning of the game width the level and the interval
*/
void    show_msg_go(signed short p_level)
{

        printf("\n===========================\n");
        printf("SUPER ! Allez c'est parti !\n");
        printf("===========================\n");
        switch(p_level)
        {
            case 1:
                printf("Niveau 1: Facile          !\n");
                printf("===========================\n");
                printf("Intervalle  [1;100]       !\n");
            break;

            case 2:
                printf("Niveau 2: Moyen           !\n");
                printf("===========================\n");
                printf("Intervalle  [1;1000]      !\n");
            break;

            case 3:
                printf("Niveau 3: HardCore        !\n");
                printf("===========================\n");
                printf("Intervalle  [1;10000]     !\n");
            break;

            default:
                printf("Error, probleme dans la fonction show_msg_error\n");
        }
        printf("===========================\n\n");
}

/*
** Select the level by the user
*/
signed short    select_level(void)
{
                signed short result_scanf_level;
                signed short level;

                do
                {
                    show_menu();
                    result_scanf_level = scanf("%hd", &level);

                } while (verif_level(result_scanf_level, level) != 1);

                return level;
}

/*
** return the max value of the "Nombre Mystere" knowing the level
*/
signed short    select_max_value(signed short p_level)
{
    switch(p_level)
    {
        case 1:
            return (100);
        break;
        case 2:
            return (1000);
        break;
        case 3:
            return (10000);
        break;
        default:
            return (0);
    }
}

/*
** Do a complete game from generating the mystery number and ask until the player find it
*/
void    game(void)
{
        signed short    number;
        signed short    number_tested;
        signed int      count;
        char            *plural;
        signed short    max_value;
        signed short    level;

        plural = "s";
        count = 0;
        level = select_level();
        max_value = select_max_value(level);
        number = gen_number(max_value);

        show_msg_go(level);
        while (number_tested != number)
        {
            count++;
            printf("Entrez un nombre: ");
            scanf("%hd", &number_tested);
            getchar();
            verif_choice(number_tested, number, max_value);
        }

        if (count == 1)
            plural = "";

        printf("Bravo vous avez trouve !\nLe nombre mystere etait %d !\nVous avez trouve en %d essai%s !\n", number, count, plural);
        printf("Veuillez appuyer sur [ENTREE] pour nous communiquer votre satisfaction !");
}

/*
** Ask to the player if he wants a new game, and return the answer
*/
short   ask_continue()
{
        char            c_continue;
        signed short    bool_loop;

        do
        {
            clear_buffer();
            printf("\n");
            printf("Yeah ! Voulez-vous refaire une partie ? (O/N): ");
            bool_loop = scanf("%c", &c_continue);
        }
        while ((bool_loop != 1) || (c_continue != 'O' && c_continue != 'N'));

        if(c_continue == 'O')
            return (1);

        else
            return (0);
}

/*
** Main..   
*/
int     main(void)
{
        signed short    continue_bool;

        srand(time(NULL));
        continue_bool = 1;
        while(continue_bool == 1)
        {
            game();
            continue_bool = ask_continue();
        }

        printf("\n========================================================\n");
        printf("Au revoir ! On s'est bien marres ! A Tot-Bien j'espere !");
        printf("\n========================================================\n\n");
        return (0);
}           
