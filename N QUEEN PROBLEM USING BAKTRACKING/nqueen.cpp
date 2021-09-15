#include<iostream>
using namespace std;

bool checkcol(int **a,int n,int col){
    for(int row=0;row<n;row++){
        if(a[row][col]==1)
            return true;
    }
    return false;
}

bool checkdig(int **a,int n,int row,int col){
    int r = row-1,c = col+1;
    while(r>=0&&c<n){
        if(a[r][c]==1)
            return true;
        r--;
        c++;
    }
    r=row-1;
    c=col-1;
    while(r>=0&&c>=0){
        if(a[r][c]==1)
            return true;
        r--;
        c--;
    }
    return false;
}

bool issafe(int **a,int n,int row,int col){
    return !checkcol(a,n,col)&&!checkdig(a,n,row,col);
}


bool placequeen(int **a,int n,int row){
    if(row>=n)
        return true;
    int col=0;
    while(col<n){
        if(issafe(a,n,row,col)){
            a[row][col]=1;
            if(placequeen(a,n,row+1))
                return true;
            a[row][col]=0;
        }
        col++;
    }
    return false;
}



void print(int **a,int n){
    for(int row=0;row<n;row++){
        for(int col=0;col<n;col++)
            cout<<a[row][col]<<"  ";
        cout<<endl;
    }
}


int main(){

    int n;
    cin>>n;
    int** a = new int*[n];
    for(int i=0; i<n; i++)
        a[i] = new int[n];

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++)
            a[i][j]=0;
    }


    if(placequeen(a,n,0))
        print(a,n);
    else
        cout<<"NOT POSSIBLE\n";
    return 0;
}
