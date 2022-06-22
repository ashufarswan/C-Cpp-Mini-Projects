import random

def printgrid(grid):
    for i in range(1,10,3):
        print(' ' + grid[i] + ' | ' + grid[i+1] + ' | ' + grid[i+2])
        print('---|---|---')
    print('\n\n')


def isSpaceFree(grid, move):           #check if the position is empty or filled
    return grid[move] == ' '

    
def PlayerMove(grid):
    move = -1
    while move not in range(1,10) or not isSpaceFree(grid,move):
        print('What is your next move? (1-9)')
        move = int(input());
    return move    


def isgridfull(board):
    for i in range(1, 10):
        if isSpaceFree(board, i):
            return False
    return True       

def iswinner(g, l):
    return ((g[1] == l and g[2] == l and g[3] == l) or # first row
            (g[4] == l and g[5] == l and g[6] == l) or # second row
            (g[7] == l and g[8] == l and g[9] == l) or # third row
            (g[1] == l and g[4] == l and g[7] == l) or # first column
            (g[2] == l and g[5] == l and g[8] == l) or # second column
            (g[3] == l and g[6] == l and g[9] == l) or # dthird column
            (g[1] == l and g[5] == l and g[9] == l) or # primary diagonal
            (g[3] == l and g[5] == l and g[7] == l)) # secondary diagonal


def copygrid(grid):
    copy = []
    for i in grid:
        copy.append(i)
    return copy



def chooseRandom(grid, List):                  # Returns a valid move from the passed list on the passed board.
     possibleMoves = []
     for i in List:
         if isSpaceFree(grid, i):
             possibleMoves.append(i)

     if len(possibleMoves) != 0:
         return random.choice(possibleMoves)
     else:
         return None

def computermove(grid,computerletter,playerletter):
    # First, check if we can win in the next move
     for i in range(1, 10):
         copy = copygrid(grid)
         if isSpaceFree(copy, i):
             copy[i] =  computerletter
             if iswinner(copy, computerletter):
                 return i

     # Check if the player could win on their next move, and block them.
     for i in range(1, 10):
         copy = copygrid(grid)
         if isSpaceFree(copy, i):
             copy[i] = playerletter
             if iswinner(copy, playerletter):
                 return i
             
     # Try to take one of the corners, if they are free.
     move = chooseRandom(grid, [1, 3, 7, 9])
     if move != None:
         return move

     # Try to take the center, if it is free.
     if isSpaceFree(grid, 5):
         return 5
     # Move on one of the sides.
     return chooseRandom(grid, [2, 4, 6, 8])



if __name__== '__main__':    
    grid = [' ']*10
    playerletter = ' '
    computerletter = ' '
    turn = ' '

    print('welcome to tic tac toe')
    while True:
        print('Input your letter(x/o): ')
        playerletter = input()
        if playerletter == 'x':
            computerletter = 'o'
        else:
            computerletter = 'x'
        print('Do you want to play first(y/n):')
        ch = input()
        if(ch=='y'):
            turn = 'p'    #player
        else:
            turn = 'c'    #computer
        while True:
            if turn == 'p':
                printgrid(grid)
                move = PlayerMove(grid)
                grid[move] = playerletter
                if iswinner(grid,playerletter):
                    printgrid(grid)
                    print('you won the game')
                    break
                else:
                    if isgridfull(grid):
                        printgrid(grid)
                        print('tie')
                        break
                        
                    else:
                        turn = 'c'
            else:
                move = computermove(grid,computerletter,playerletter)
                grid[move] = computerletter
                if iswinner(grid,computerletter):
                    printgrid(grid)
                    print('Computer won !!! You lose. ')
                    break
                else:
                    if isgridfull(grid):
                        printgrid(grid)    
                        print('Tie....')
                        break
                        
                    else:
                        turn = 'p'
        print('want to play again(y/n):')
        ch = input()
        if ch == 'y':
            continue
        else:
            break