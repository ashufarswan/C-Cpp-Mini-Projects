#include<stdio.h>
#include<string.h>
#include<windows.h>
#include<stdlib.h>
#define size 3

//FOR SETTING POSITION OF CURSOR AT OUTPUT WINDOW

void gotoxy(short x,short y)
{
    COORD pos={x,y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}


//FUNCTION FOR FILLING MATRIX WITH .

void  fillmatrix(char arr[][size])
{
    for(int i=0;i<size;i++)
    {
        for(int j=0;j<size ;j++)
            arr[i][j]='.';
    }
}

//FUNCTION FOR PRINTING GRID

void print(char arr[][size])
{
    for(int i=0;i<size;i++)
    {
        printf(" %c | %c | %c",arr[i][0],arr[i][1],arr[i][2]);
        if(i!=2)
            printf("\n---|---|---\n");
    }
    printf("\n\n");
}

//FUNCTION FOR CHECKING ROW,COLUMN,DIAGONAL

int check(char arr[][size],int x,int y,char ch)
{
    int flag=0;
    for(int i=0;i<size;i++)
    {
        if(arr[x][i]!=ch)                                                 //checking row
            {
                flag=1;
                break;
            }
    }
    if(flag==0)
        return 1;
    else
    {
        flag=0;
        for(int i=0;i<size;i++)
        {
            if(arr[i][y]!=ch)                                             //checking column
                {
                    flag=1;
                    break;
                }
        }
        if(flag==0)
            return 1;
        else if(x==y || x+y==2)                                            //checking diagonal
        {
            flag=0;
            if(x==y)
            {
                for(int i=0;i<size;i++)
                    {
                        if(arr[i][i]!=ch)                                   //primary diagonal
                        {
                            flag=1;
                            break;
                        }
                     }
            if(flag==0)
                return 1;
            }
            else
            {
                for(int i=0;i<size;i++)
                {
                    if(arr[i][2]!=ch || arr[i][i]!=ch || arr[0][i])          //secondary diagonal
                    {
                        flag=1;
                        break;
                    }
                    if(flag==0)
                        return 1;
                }
            }
        }
        else
            return 0;
    }
}


int main()
{
    char player[2][20],temp[20];
    char mat[size][size];                                                //INITIAL GRID IS BLANK
    int c=0,turn,x,y;
    char ch='y',sign;
    gotoxy(65,0);
    printf("--------------------------------------------------\n");
    gotoxy(65,1);
    printf("         WELCOME TO TIC TAC TOE GAME              \n");
    gotoxy(65,2);
    printf("--------------------------------------------------\n");
    do
    {
        fillmatrix(mat);
        printf("\nENTER THE NAME OF X PLAYER: ");
        scanf("%s",player[0]);
        printf("\nENTER THE NAME OF O PLAYER: ");
        scanf("%s",player[1]);

        do
        {
            if(c!=0)
            {
                printf("%s is not registered player.\n",temp);
            }
            printf("\nWHO PLAY FIRST: %s or  %s? ",player[0],player[1]);
            scanf("%s",temp);
            c++;
        }while(strcmpi(temp,player[0])!=0&&strcmpi(temp,player[1])!=0);     //CONDITION IF INPUTTED NAME FOR PLAYER IS NOT MATCHED FROM PREVIOUS NAME
        turn=strcmpi(temp,player[0])==0?0:1;                                //0 FOR X PLAYER AND ! FOR O PLAYER
        c=0;
        printf("\n\n---------------INSTRUCTION-----------------\n");
        printf("VALUES OF POSTION MUST BE BETWEEN 1 AND 3\n");
        printf("-----------------------------------------\n");

        print(mat);                                                         //PRINTING INTIAL BLANK GRID
        //GAME LOOP START
        do
        {
            c++;
            printf("\nPLAYER OF CURRENT TURN: %s\n", player[turn]);
            label1:
            printf("\nINPUT POSITION (x y): ");
            scanf("%d%d",&x,&y);
            if(x-1<0 || x-1>2)
            {
                printf("\n%d is not valid row.\n",x);
                goto label1;
            }
            if(y-1<0 || y-1>2)
            {
                printf("\n%d is not valid column\n.",y);
                goto label1;
            }
            sign=turn==0?'X':'O';
            if(mat[x-1][y-1]=='O'||mat[x-1][y-1]=='X')                                 //IF POSITION INPUTTED IS FILLED
            {
                printf("\nPLACE IS FILLED.\n");
                goto label1;
            }
            mat[x-1][y-1]=sign;
            turn=turn==0?1:0;
            system("CLS");
            print(mat);
            if(c==9)                                                                    //CONDITION FOR TIE
                break;
        }while(check(mat,x-1,y-1,sign)!=1 );

        //ENDING OF A GAME LOOP

        printf("\nGAME IS OVER\n");
        if(c==9)
        {
            printf("It's a tie!\n");
        }
        if(turn==0)
        {
            printf("%s Wins !\n",player[1]);
        }
        else
        {
            printf("%s Wins !\n",player[0]);
        }
        printf("WANT TO PLAY MORE(y/n): ");
        fflush(stdin);
        scanf("%c",&ch);
        system("CLS");
    }while(ch=='y'||ch=='Y');

    gotoxy(65,0);
    printf("BYE!");
    return 0;
}





