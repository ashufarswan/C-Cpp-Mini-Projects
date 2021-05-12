#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<windows.h>
using namespace std;

#define UNASSIGNED 0
#define N 9

/* Searches the matrix to find an entry that is unassigned. */
bool FindUnassignedPosition(int mat[N][N], int &row, int &col)
{
    for(row=0;row<N;row++)
        for(col=0;col<N;col++)
            if(mat[row][col]==UNASSIGNED)
                return true;
    return false;
}

/* Returns whether any assigned entry n the specified row matches the given number. */
bool CheckRow(int mat[N][N], int row, int num)
{
    for(int col = 0;col<N;col++)
        if(mat[row][col]==num)
            return true;
    return false;
}


/* Returns whether any assigned entry in the specified column matches the given number. */
bool CheckCol(int mat[N][N],int col,int num)
{
    for(int row=0;row<N;row++)
        if(mat[row][col]==num)
            return true;
    return false;
}


/* Returns whether any assigned entry within the specified 3x3 box matches  the given number. */
bool CheckBox(int mat[N][N], int boxStartRow, int boxStartCol, int num)
{
    for(int row=0;row<3;row++)
        for(int col=0;col<3;col++)
            if(mat[row+boxStartRow][col+boxStartCol]==num)
                return true;
    return false;
}



/* Returns whether it will be legal to assign num to the given row,col location. */
bool isSafe(int mat[N][N],int row,int col,int num)
{
    return !CheckRow(mat,row,num)&&!CheckCol(mat,col,num)&&!CheckBox(mat,row-row%3,col-col%3,num);
}




/* assign values to all unassigned locations for Sudoku solution   */
bool SolveSudoku(int mat[N][N])
{
    int row,col;
    if(!FindUnassignedPosition(mat,row,col))
       return true;
    for(int num = 1;num<=N;num++)
    {
        if(isSafe(mat,row,col,num))
        {
            mat[row][col]=num;
            if (SolveSudoku(mat))
                return true;
            mat[row][col]=UNASSIGNED;
        }
    }
    return false;
}



/*IF SUDOKU INPUTED IS COMPLETLY FILLED CHECK IT IS RIGHT OR WRONG*/
bool CheckSudoku(int mat[N][N])
{
    for(int i=0;i<N;i++)
    {
        int sum_row=0,sum_column=0;
        for(int j=0;j<N;j++)
        {
            sum_row+=mat[i][j];
            sum_column+=mat[j][i];
        }
        /*CHECK FOR REPEATED ELMENT IN ROW*/
        if(sum_row!=45)
        {
            cout<<" & INCORRECT. ELEMENT REPEATED IN "<<i+1<<" ROW......\n";
            return false;
        }
        /*CHECK FOR REPEATED ELMENT IN COLUMN*/
        if(sum_column!=45)
        {
            cout<<" & INCORRECT. ELEMENT REPEATED IN "<<i+1<<" COLUMN......\n";
            return false;
        }
    }
    for(int i=0;i<N;i+=3)
    {
        for(int j=0;j<N;j+=3)
        {
            int sum_box=0;
            for(int k=0;k<3;k++)
            {
                for(int m=0;m<3;m++)
                    sum_box+=mat[i+k][j+m];
            }
            /*CHECK FOR REPEATED ELMENT IN BOX*/
            if(sum_box!=45)
                {
                    cout<<"& INCORRECT. ELEMENT REPEATED IN BOX ROW ("<<i+1<<","<<i+3<<")";
                    cout<<"COLUMN ("<<j+1<<","<<j+3<<").....\n";
                    return false;
                }
        }
    }
    return true;
}



/* print matrix*/
void print(int mat[N][N])
{
    for(int row=0;row<N;row++)
    {
        for(int col=0;col<N;col++)
            cout<<mat[row][col]<<"  ";
        cout<<endl;
    }
}



/* Main */
int main()
{
    char ch;
    do
    {
        /*MENU*/
        cout<<"---------------------------------------------------------------------\n";
        cout<<"                 WELCOME TO SUDOKU SOLVING PROGRAM                   \n";
        cout<<"---------------------------------------------------------------------\n";
        cout<<"\n\n\n";
        cout<<"NOTE: 1) FILL BLANK SPACE WITH 0.\n";
        cout<<"      2) INPUT ONLY 9 X 9 MATRIX.\n\n\n";


        /*INPUTTING SUDOKU*/
        cout<<"INPUT SUDOKU :\n";
        int mat[N][N],r,c;
        for(int i=0;i<N;i++)
            for(int j=0;j<N;j++)
                cin>>mat[i][j];

        cout<<"\n\n\n";
        if(!FindUnassignedPosition(mat,r,c))
        {
            cout<<"SUDOKU IS COMPLETELY FILLED ";
            if(CheckSudoku(mat))
                cout<<"& CORRECT.....\n";
        }
        else
        {
            if(SolveSudoku(mat)== true)
                    print(mat);
            else
                    cout<<"\n\nNO SOLUTION EXIST.....\n";
        }


        cout<<"\n\n\n";
        cout<<"WANT TO ENTER MORE SUDOKU(Y/N): ";
        cin>>ch;
        cout<<"\n\n\n";
        system("CLS");
    }while(ch=='y'||ch=='Y');
    return 0;
}

