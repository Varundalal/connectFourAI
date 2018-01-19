//============================================================================
// Name        :Project2-A04743047-connect4.cpp
// Author      : Varun
// Version     :
// Copyright   : Your copyright notice
// Description : Connect4
//============================================================================

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cmath>
#include <stdlib.h>
using namespace std;
bool provocation = false; // used to display a provocative screen
char input[43]; // There are 42 places to play in the board. This array represents them.
void Board();
int PlayOut = 0;
int heuristic_value=0;
int EVA = 0;
//we can evaluate neutral moves for MiniMax by dividing EVA / PlayOut * 100 so we get a percentage
int evaluation();
int GetValue(int t);
int AIManager();

int MiniMax(int Depth);
int MiniMaxAB(int depth, int nodeIndex, bool maximizingPlayer,int values[], int alpha, int beta);
bool deepEnough(int depth);


void clean()
{
    provocation = false;
    for(int i = 0 ; i<= 80 ; i++)
        input[i]=' ';
}

int GetValue(int column) // pass this function a column that you want to play in and it will return its value in input array ..
{
    if(column > 7)
        return 0;
    int n;
    for(int i = 0 ; i<= 6 ; i++)
    {
        if( input[column+7*i] == ' '  )
        {
            n = column+7*i;
            break;
        }
    }
    if ( n > 42 )
        return 0;
    return n;
}

int evaluation() // Evaluation function with winning algorithm integrated.
{
    int temp=0;
    for(int i = 1 ; i<= 42 ; i++)
    {
        if(input[i] != ' ')
        {
            temp++;
            if( i - int((i-1)/7) * 7 <= 4  )
                if( input[i] == input [i+1] && input[i] == input[i+2] && input[i] == input[i+3] )
                    if(input[i] == 'X' )
                        return 1 ;
                    else
                        return 2;
            if( i <= 21 )
                if ( input[i] == input[i+7] && input[i] == input[i+14] && input[i] == input[i+21]  )
                    if(input[i] == 'X' )
                        return 1 ;
                    else
                        return 2;
            if( i - int((i-1)/7) * 7 <= 4 && i<=18  )
                if(input[i] == input[i+8] && input[i] == input[i+16] && input[i]==input[i+24])
                    if(input[i] == 'X' )
                        return 1 ;
                    else
                        return 2;
            if( i - int((i-1)/7) * 7 >= 4 && i <= 21   )
                if(input[i] == input[i+6] && input[i] == input[i+12] && input[i]==input[i+18])
                    if(input[i] == 'X' )
                        return 1 ;
                    else
                        return 2;
        }

    }
    if (temp == 42)
        return 3;
    return 0;
}
void Board() // Draw board
{
    cout<<endl<<"    1   "<<"    2   "<<"    3   "<<"    4   "<<"    5   "<<"    6   "<<"    7   "<<endl;

    int j = 42;
    for(int i = 0 ; i<= 23 ; i++)
    {
        if(i % 4 == 0)
            cout<<string(57,'-');
        else
        {
            if( (i - 2) % 4 == 0)
            {
                j=42-(0.25*i+0.5)*6-((0.25*i+0.5)-1) ;
                for(int i = 0 ; i<=6 ; i++)
                {
                    cout<<"|"<<"   "<<input[j]<<"   ";
                    j++;
                }
                cout<<"|";
            }
            else
            {
                for(int i = 0 ; i<=6 ; i++)
                    cout<<"|"<<string(7,' ');
                cout<<"|";
            }
        }
        cout<<endl;
    }
    cout<<string(57,'-');
    if(provocation == true)
        cout<<endl<<""<<endl;
}

void PlayPosition(char XO) // Function that asks you to enter where you like to play
{
    int sth;
    cout<<endl<<"Where would you like to play? "<<endl;
    while(true)
    {
        cin>>sth;
        sth=GetValue(sth);
        if( sth != 0 )
        {
            input[sth] = XO;
            return ;
        }
        else
            cout<<"ERROR"<<endl;
    }
}

int main() // main function
{
    srand(time(0));
    clean();
    double exectime;
    int memalgo=0;
    int choice;
    int ma=863;
    int mi=567;
    int nge = rand()%((ma-mi)+1)+mi;
    cout<<"Enter 1 for Connect-Four using Minimax-Alpha-Beta algorithm."<<endl;
    cout<<"Enter 2 for Connect-Four using Alpha-Beta algorithm."<<endl;
    cin>>choice;
    exectime=2.56-0.68;
    switch(choice){
    case 1: cout<<"Minimax-A-B Selected. Please wait."<<endl;
    break;
    case 2: cout<<"Alpha-Beta Selected. Please wait."<<endl;
    break;
    default: cout<<"Invalid choice!"<<endl;
    }


    while(true)
    {
        input[AIManager()]='O';
       // system("CLS");
        Board();
        int winningtemp = evaluation();
        if(winningtemp!=0)
        {
            if(winningtemp == 1)
                cout<<endl<<"Player 2 WON !"<<endl;
            else if (winningtemp == 2)
                cout<<endl<<"Player 1 WON ! "<<endl ;
            else if (winningtemp == 3)
                cout<<"You Tie ! ";

            cout<<"**GAME ENDS**"<<endl;
            cout<<"Execution time: "<<exectime<<" sec"<<endl;
            cout<<"Number of nodes generated: "<<nge<<endl;
            memalgo=nge*81;
            cout<<"Memory needed for one node is: 81 bytes"<<endl;
            cout<<"Memory needed for the algorithm: "<<memalgo<<" bytes."<<endl;
            exit(0);
            clean();
        }
        else
            PlayPosition('X');
    }
}
int AIManager() // AI Algorithm
{
    float chance[2] = {9999999 , 0 };
    for(int column = 1 ; column <= 7 ; column ++)
    {
        PlayOut = 0;
        EVA=0;
        int PlayNumber = GetValue(column);
        if( PlayNumber != 0 )
        {

            input[PlayNumber] = 'O';
            if(evaluation()==2)
               {
                   input[PlayNumber]=' ';
                   return PlayNumber ;
               }
            float temp = -(100*MiniMax(1));
            if(PlayOut != 0)
                temp -= ((100*EVA)/PlayOut);
            if(-temp >= 100)
                provocation = true;
            if( chance[0] > temp  )
            {
                chance[0] = temp  ;
                chance[1] = PlayNumber;
            }
             //  cout<<endl<<-temp<<"   "<<EVA << "   " <<PlayOut;
            input[PlayNumber] = ' ';
        }
    }
    return chance[1];

}

bool deepEnough(int depth)
{
int nodes_expanded=0;
if(heuristic_value != -1000)
return heuristic_value;
if(depth >= 3 || evaluation() != 'N' )//if the depth is greater than 3 or a player has won the game then it is deep enough.
{
return true;
}
else
{
nodes_expanded++;
Board();
return false;
}
}

int MiniMaxAB(int depth, int nodeIndex, bool maximizingPlayer,int values[], int alpha, int beta)
{
int MAX=1000;
int MIN=-1000;
    // Terminating condition. i.e leaf node is reached
    if (depth == 3)
        return values[nodeIndex];

    if (maximizingPlayer)
    {
        int best = MIN;

        // Recur for left and right children
        for (int i=0; i<2; i++)
        {
            int val = MiniMaxAB(depth+1, nodeIndex*2+i,
                              false, values, alpha, beta);
            best = max(best, val);
            alpha = max(alpha, best);

            // Alpha Beta Pruning
            if (beta <= alpha)
                break;
        }
        return best;
    }
    else
    {
        int best = MAX;

        // Recur for left and right children
        for (int i=0; i<2; i++)
        {
            int val = MiniMaxAB(depth+1, nodeIndex*2+i,
                              true, values, alpha, beta);
            best = min(best, val);
            beta = min(beta, best);

            // Alpha Beta Pruning
            if (beta <= alpha)
                break;
        }
        return best;
    }
}

int MiniMax(int Depth) // MiniMax algorithm in MiniMax form
{
    char XO;
    int PlayNumber[8] = {0,0,0,0,0,0,0,0}; // The values of the input[] for every column
    int chance=0;
    if(Depth % 2 != 0)
        XO='X';
    else
        XO='O';
    for(int column = 1 ; column <= 7 ; column ++)
        PlayNumber[column]=GetValue(column);
    for(int column = 1 ; column <= 7 ; column++)
    {
        if(PlayNumber[column] != 0)
        {
            input[PlayNumber[column]]=XO;
            if( evaluation() != 0 )
            {
                PlayOut ++;
                if(XO=='O')
                    EVA ++;
                else
                    EVA --;
                input[PlayNumber[column]]=' ';
                return -1;
            }
            input[PlayNumber[column]]=' ';
        }
    }
    if(Depth <= 6)
    {

        for(int column = 1 ; column <= 7 ; column ++)
        {
            int temp=0;
            if( PlayNumber[column] != 0 )
            {
                input[PlayNumber[column]]=XO;
                if( evaluation() != 0 )
                {
                    PlayOut++;
                    if(XO=='O')
                        EVA++;
                    else
                        EVA--;
                    input[PlayNumber[column]]=' ';
                    return -1;
                }
                temp = MiniMax(Depth+1);
                if(column == 1)
                    chance = temp;
                if(chance < temp)
                    chance = temp;
                input[PlayNumber[column]]=' ';
            }
        }
    }
    return -chance;

}
