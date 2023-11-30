

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>
char board[3][3];
const char GIOCATORE = 'X';
const char COMPUTER = 'O';
int difficoltà;
int punteggiogiocatore = 0;
int punteggiocomputer = 0;
int mossecomputer = 0;
void stampavincitore(char vincitore)
{
    if(vincitore == GIOCATORE)
    {
        printf("hai vinto!\n");
        punteggiogiocatore ++;
    }
    else if (vincitore == COMPUTER)
    {
        printf("hai perso!\n");
        punteggiocomputer ++;
    }
    else
    {
        printf("pareggio!\n");

    }
    printf("punteggio: %d-%d\n", punteggiogiocatore, punteggiocomputer);
}


void resettaboard(void)
{
    for(int i = 0; i<3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            board[i][j] = ' ';
        }
    }
}

void stampaboard(void)
{
    printf(" %c | %c | %c ", board[0][0], board[0][1], board[0][2]);
    printf("\n---|---|---\n");
    printf(" %c | %c | %c ", board[1][0], board[1][1], board[1][2]);
    printf("\n---|---|---\n");
    printf(" %c | %c | %c ", board[2][0], board[2][1], board[2][2]);
    printf("\n");

}
int controllaspaziliberi(void)
{
    int spaziliberi = 9;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] != ' ')
            {
                spaziliberi --;
            }
        }
    }
    return  spaziliberi;
}
void mossagiocatore(void)
{
    int x;
    int y;
    do
    {
        printf("inserisci riga (1-3): ");
        scanf("%d", &x);
        x--;
        printf("inserisci colonna (1-3): ");
        scanf("%d", &y);
        y--;

        if (board[x][y] != ' ')
        {
            printf("mossa non valida!\n");
        }
        else
        {
            board[x][y] = GIOCATORE;
            break;
        }
    }while (board[x][y] != ' ');

}
void contamossecomputer(void)
{
    mossecomputer = 0;
}
char controllavincitore(void)
{
    // controllo righe
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][0] == board[i][2])
        {
            return board[i][0];
        }
    }

    // controllo colonne
    for (int i = 0; i < 3; i++)
    {
        if (board[0][i] != ' ' && board[0][i] == board[1][i] && board[0][i] == board[2][i])
        {
            return board[0][i];
        }
    }
    //controllo diagonali
    if (board[0][0] == board[1][1] && board[0][0] == board[2][2])
    {
        return board[0][0];
    }
    if (board[0][2] == board[1][1] && board[0][2] == board[2][0])
    {
        return board[0][2];
    }
    return ' ';
}

int minimax(int depth, bool isMaximizingPlayer)
{
    char result = controllavincitore();
    if (result != ' ')
    {
        if (result == COMPUTER)
        {
            return 10 - depth;
        }
        else
        {
            return depth - 10;
        }
    }

    if (controllaspaziliberi() == 0)
    {
        return 0;
    }

    if (isMaximizingPlayer)
    {
        int bestScore = -1000;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i][j] == ' ')
                {
                    board[i][j] = COMPUTER;
                    int score = minimax(depth+1, false);
                    board[i][j] = ' ';
                    bestScore = (score > bestScore) ? score : bestScore;
                }
            }
        }
        return bestScore;
    }
    else
    {
        int bestScore = 1000;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i][j] == ' ')
                {
                    board[i][j] = GIOCATORE;
                    int score = minimax(depth+1, true);
                    board[i][j] = ' ';
                    bestScore = (score < bestScore) ? score : bestScore;
                }
            }
        }
        return bestScore;
    }
}

void mossacomputer(void)
{
    int bestScore = -1000;
    int bestX = -1;
    int bestY = -1;
    //int y;
    //int x;

    switch(difficoltà)
    {
        case 1:
            srand((unsigned int) time(0));
            int x;
            int y;

            if (controllaspaziliberi() > 0)
            {
                do
                {
                    x = rand() % 3;
                    y = rand() % 3;
                } while (board[x][y] != ' ');

                board[x][y] = COMPUTER;
                mossecomputer ++;
            }
            else
            {
                stampavincitore(' ');
            }
            break;

        case 2:

            srand((unsigned int) time(0));


            if (controllaspaziliberi() > 0)
            {
                // Scelta casuale della mossa nel 25% dei casi
                if (rand() % 2 == 0)
                {
                    do
                    {
                        x = rand() % 3;
                        y = rand() % 3;
                    } while (board[x][y] != ' ');

                    board[x][y] = COMPUTER;
                    mossecomputer ++;
                }
                    // Altrimenti si utilizza il minimax come nella difficoltà impossibile
                else
                {
                    int bestScore = -1000;
                    int bestX = -1;
                    int bestY = -1;

                    for (int i = 0; i < 3; i++)
                    {
                        for (int j = 0; j < 3; j++)
                        {
                            if (board[i][j] == ' ')
                            {
                                board[i][j] = COMPUTER;
                                int score = minimax(0, false);
                                board[i][j] = ' ';
                                if (score > bestScore)
                                {
                                    bestScore = score;
                                    bestX = i;
                                    bestY = j;
                                }
                            }
                        }
                    }

                    board[bestX][bestY] = COMPUTER;
                    mossecomputer ++;
                }
            }
            else
            {
                stampavincitore(' ');
            }


            break;

        case 3:

            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    if (board[i][j] == ' ')
                    {
                        board[i][j] = COMPUTER;
                        mossecomputer++;
                        int score = minimax(0, false);
                        board[i][j] = ' ';
                        if (score > bestScore)
                        {
                            bestScore = score;
                            bestX = i;
                            bestY = j;
                        }
                    }
                }
            }

            board[bestX][bestY] = COMPUTER;
            mossecomputer++;
            break;
    }

}
int main()
{
    char vincitore = ' ';
    char risposta;
    char giocatore = 'X';
    char computer = 'O';
    int mossa_iniziale;  // variabile per determinare chi inizia la partita
    int counter = 0;
    printf("scegli chi inizia la partita, 1 per giocatore, 2 per computer: ");
    scanf("%d", &mossa_iniziale);

    if (mossa_iniziale == 2) {  // se il computer inizia, scambia i simboli
        giocatore = 'O';
        computer = 'X';
    }

    printf("scegli la difficoltà, 1 per facile, 2 per intermedio e 3 per impossibile: ");
    scanf("%d", &difficoltà);

    do
    {
        vincitore = ' ';
        risposta = ' ';
        resettaboard();
        if (mossecomputer != 0 || giocatore == 'X')
        {
            stampaboard();
        }

        while (vincitore == ' ' && controllaspaziliberi() != 0)
        {


            if (giocatore == 'X')
            {
                mossagiocatore();
                vincitore = controllavincitore();
                giocatore = 'O';
                computer = 'X';
            }
            else
            {
                mossacomputer();

                if (controllavincitore()!= COMPUTER && controllaspaziliberi() != 0)

                {
                    stampaboard();
                }

                vincitore = controllavincitore();
                giocatore = 'X';
                computer = 'O';
                counter ++;
            }

            if (vincitore != ' ' || controllaspaziliberi() == 0)
            {
                stampaboard();
                break;
            }
        }

        stampavincitore(vincitore);
        mossecomputer = 0;
        printf("vuoi giocare ancora? (s/n): ");
        scanf(" %c", &risposta);
        risposta = toupper(risposta);
    } while (risposta == 'S');

    printf("grazie per aver giocato!\n");

    return 0;
}

