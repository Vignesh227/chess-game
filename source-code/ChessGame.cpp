
/*
                TWO PLAYER CHESS GAME !!

  Created by : VIGNESH PANDIAN T 
  Date : 08-08-2022.

*/

#include<iostream>
#include<cstring> //header to use memset function
#include<iomanip>
#include<string>
#include<windows.h> //header to change text color of the OP text
#include<limits> 
#define N 8
using namespace std;

//function to change the color of the output text
void changeColor(int desiredColor)
{
     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), desiredColor);
}
//class to do chess game operations
class ChessGame
{
    int i, j,k,movecount=1, prev_white_col,prev_black_col;
    int prev_curr_row, prev_curr_col,curr_piece_value,  move_piece_value;

    string curr_piece, move_piece;
    string board[N][N];

    int BW[N][N] , whitepawn_moves[N],blackpawn_moves[N] ;
    int whiterook[N], blackrook[N];
    int current_row, current_col,move_row,move_col, promote_choice;
    bool blackenpassant[N], whiteenpassant[N];

  public:
    ChessGame() //constructor to initialize the board
    {
        changeColor(11);
        cout<<"\n\t\t\t TWO PLAYER CHESS GAME \n";
        changeColor(12);
        cout<<"\n   red -> ";changeColor(7);cout<<" BLACK COINS";
        changeColor(14);
        cout<<"\n   yellow -> ";changeColor(7);cout<<" WHITE COINS";
        changeColor(7);
        cout<<"\n\n   ";
    }
    bool flag=true;
    int move_flag, whiteking=0, blackking=0;

    void declare();
    void display(); //function to display the chess board
    void getmoves(); //function to get input for the moves
    void moves();  //function to do the moves
    void notvalid_display(); //if invalid, then display "invalid"
    void white_move(); //to do a move for white piece
    void black_move(); //to do a move for black piece
    void rookmove(); //function to move a rook
    void knightmove(); //function to move a knight
    void bishopmove(); //function to move a bishop
    void kingmove(); //function to move a king
    void pawn_promotion_choice();//func to get choice for pawnpromotion
    void pawnpromotion(); //function to do pawn promotion
    bool whitecheck();
    bool blackcheck();

    bool check_rookmove(int , int, int);
    bool check_bishopmove(int, int, int);
    bool check_knightmove(int, int, int);
    bool check_kingmove(int, int, int);

    void copy_contents_back();
    void play_again();
};

//Function to create a chess board
void ChessGame::declare()
{
    flag=true;
    move_flag, whiteking=0, blackking=0,movecount=1;

    memset(whitepawn_moves,0,sizeof(whitepawn_moves));
    memset(blackpawn_moves,0,sizeof(blackpawn_moves));
    memset(whiterook,0,sizeof(whiterook));
    memset(blackrook,0,sizeof(blackrook));

    memset(BW,0,sizeof(BW));
    memset(board,'\0',64);

    memset(blackenpassant,false,sizeof(blackrook));
    memset(whiteenpassant,false,sizeof(blackrook));

    //declaring black pawn
    for(i=1,j=0;j<8;j++)
    {
        board[i][j] = "pawn";
        BW[i][j] = 1;     //1 for black
    }

    //declaring white pawn
    for(i=6,j=0;j<8;j++)
    {
        board[i][j] = "pawn";
        BW[i][j] = 2;     //2 for white
    }

    //DECLARING BLACK COINS

    //black rooks
    board[0][0] = "rook";
    BW[0][0] = 1;
    board[0][7] = "rook";
    BW[0][7] = 1;

    //black horses
    board[0][1] = "knight";
    BW[0][1] = 1;
    board[0][6] = "knight";
    BW[0][6] = 1;

    //black bishops
    board[0][2] = "bishop";
    BW[0][2] = 1;
    board[0][5] = "bishop";
    BW[0][5] = 1;

    //black king and queen
    board[0][3] = "queen";
    BW[0][3] = 1;
    board[0][4] = "king";
    BW[0][4] = 1;


    //DECLARING WHITE COINS

    //white rooks
    board[7][0] = "rook";
    BW[7][0] = 2;
    board[7][7] = "rook";
    BW[7][7] = 2;

    //white horses
    board[7][1] = "knight";
    BW[7][1] = 2;
    board[7][6] = "knight";
    BW[7][6] = 2;

    //white bishops
    board[7][2] = "bishop";
    BW[7][2] = 2;
    board[7][5] = "bishop";
    BW[7][5] = 2;

    //white king and queen
    board[7][3] = "queen";
    BW[7][3] = 2;
    board[7][4] = "king";
    BW[7][4] = 2;

}

//Function to display the chess board
void ChessGame::display()
{
    cout<<"\t";
    //to display column numbers above the board
    for(i=0;i<N;i++)
        cout<<i<<"        ";
    cout<<"\n   ";
    for(i=0;i<8;i++)
        cout<<"---------";
    cout<<"-"<<endl;
    for(i=0;i<N;i++)
    {
        cout<<" "<<i; //to display row numbers
        for(j=0;j<N;j++)
        {
            if(BW[i][j]==1)
            {
                changeColor(7); //changes text color to white
                cout<<" |";
                changeColor(12);//changes text color to red
                cout<<setw(7)<<board[i][j];
            }
            else{
                changeColor(7);
                cout<<" |";
                changeColor(14); //changes text color to yellow
                cout<<setw(7)<<board[i][j];
            }
        }
        changeColor(7);
        //to display row numbers on right side of the board
        cout<<" | "<<i<<"\n   ";
        for(k=0;k<8;k++)
            cout<<"---------";
        cout<<"-\n";
    }
    cout<<"\t";
    //to display column numbers below the board
    for(i=0;i<N;i++)
        cout<<i<<"        ";
    cout<<"\n";
}

void ChessGame::getmoves()
{
    if(movecount%2 != 0)
    {
        changeColor(14);
        cout<<"\n WHITE'S MOVE \n";
        move_flag=1; //a flag to indicate that this is white's move
        changeColor(7);
    }
    else
    {
        changeColor(12);
        cout<<"\n BLACK'S MOVE \n ";
        move_flag=0; //a flag to indicate that this is black's move
        changeColor(7);
    }

    cout<<"\n Enter the current ROW of the piece which you want to move : ";

    /* getting input through 'cin', and checking if it is not an integer */

    while(!(cin >> current_row))
    {
        /* if the entered value is not an integer,
        then while loop gets executed */

        cin.clear();
        /* cin.clear() clears the error flag on cin,
           so that future I/O operations will work correctly. */

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        /* cin.ignore(numeric_limits<streamsize>::max(), '\n')
           skips to the next newline (to ignore anything else on the same line
           as the non-number so that it does not cause another parse failure) */

        /* streamsize is signed integral which gives the number of i/o character
        transferred (or) size of I/O buffer.

        Here, by using "numeric_limits" template class we wanted to know max limit
         of I/O buffer or character transferred. */

        notvalid_display();
        cout<<"\n Enter the current ROW of the piece which you want to move : ";
    }

    cout<<" Enter the current COL of the piece which you want to move : ";
    while(!(cin >> current_col))  //to get only integer values as input
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        notvalid_display();
        cout<<"\n Enter the current COL of the piece which you want to move : ";
    }

    cout<<" Enter the ROW where you want to move : ";
    while(!(cin >> move_row))  //to get only integer values as input
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        notvalid_display();
        cout<<"\n Enter the ROW where you want to move : ";
    }

    cout<<" Enter the COL where you want to move : ";
    while(!(cin >> move_col))  //to get only integer values as input
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        notvalid_display();
        cout<<"\n Enter the COL where you want to move : ";
    }

    if(current_row<0 || current_row>7 ||current_col<0 ||current_col>7 ||
       move_row<0 ||move_row>7 ||move_col<0||move_col>7)   //Invalid input
    {
        notvalid_display();
    }

    else if(board[current_row][current_col] == "\0") //if choosing a empty location
    {
        notvalid_display();
    }
    else if(current_row == move_row && current_col == move_col) //moving to same location
    {
        notvalid_display();
    }

    else if(move_flag && BW[current_row][current_col]==2)
    {
        int ch;
        //copy the current location's piece name and value
        curr_piece = board[current_row][current_col];
        curr_piece_value = BW[current_row][current_col];

        //copy the current location's piece name and value
        move_piece = board[move_row][move_col];
        move_piece_value = BW[move_row][move_col];

        white_move(); /* WHITE MOVE FUNCTION CALL */

    //if the current white move leads to CHECK for white king, then stop the move
        if(blackcheck() && flag)
        {
            cout<<"\n\t\t  This move will bring your ";changeColor(14);
            cout<<"King ";changeColor(7);
            cout<<"under ";changeColor(11);
            cout<<"CHECKMATE\n";changeColor(7);

            cout<<"\n Do you want to continue?\n 1 -> Yes\n 2 -> No";
            cout<<"\n Enter your choice : ";
            while(!(cin>>ch) || (ch!=1 && ch!=2))
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout<<"\n\t\t\t  Please enter a ";changeColor(11);
                cout<<"valid ";changeColor(7);cout<<"choice !!";
                cout<<"\n\n Enter your choice correctly : ";
            }
            if(ch==1)
            {
                /* In main function the checkmate is displayed,
                   and the game ends */
            }
            else if(ch==2)
            {
                copy_contents_back();
            }
            else
            {
                notvalid_display();
            }
        }
    }

    else if(!move_flag && BW[current_row][current_col]==1)
    {
        int ch;
        //copy the current location's piece name and value
        curr_piece = board[current_row][current_col];
        curr_piece_value = BW[current_row][current_col];

        //copy the current location's piece name and value
        move_piece = board[move_row][move_col];
        move_piece_value = BW[move_row][move_col];

        black_move();  /* BLACK MOVE FUNCTION CALL */

    //if the current black move leads to CHECK for black king, then stop the move
        if(whitecheck() && flag)
        {
            cout<<"\n\t\t  This move will bring your ";changeColor(12);
            cout<<"King ";changeColor(7);
            cout<<"under ";changeColor(11);
            cout<<"CHECKMATE\n";changeColor(7);
            cout<<"\n Do you want to continue?\n 1 -> Yes\n 2 -> No";
            cout<<"\n Enter your choice : ";
            while(!(cin>>ch) || (ch!=1 && ch!=2))
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout<<"\n\t\t\t  Please enter a ";changeColor(11);
                cout<<"valid ";changeColor(7);cout<<"choice !!";
                cout<<"\n\n Enter your choice correctly : ";
            }
            if(ch==1)
            {
                /* In main function the checkmate is displayed,
                   and the game ends */
            }
            else if(ch ==2)
            {
                copy_contents_back();
            }
            else
            {
                notvalid_display();
            }
        }
    }
    else
        notvalid_display();
}

//function to reverse back a current move
void ChessGame::copy_contents_back()
{
    changeColor(11);
    cout<<"\n\t\t   Move cancelled successfully !!\n";
    changeColor(7);

    flag=false; //set flag as false
    movecount--;

    //copying back the moving location's piece contents
    board[move_row][move_col]=move_piece;
    BW[move_row][move_col]=move_piece_value;

    //copying back the current location's piece contents
    board[current_row][current_col]=curr_piece;
    BW[current_row][current_col]=curr_piece_value;
}

//Function to do White's move
void ChessGame::white_move()
{
    //WHITE PAWN

    if(board[current_row][current_col] == "pawn" &&
        BW[current_row][current_col] == 2)
    {
        if(move_row >= current_row)
        {
            notvalid_display();
        }
        //checking if the moving location is not having a white piece
        else if(BW[move_row][move_col] !=2)
        {
            if(current_row == 6)
            {
                blackenpassant[prev_black_col]=false;
                if(whitepawn_moves[current_col]==0) //if first move of a pawn
                {
                    //a pawn can move 1 or 2 steps forward in first move
                    if((current_row - move_row ==1 || current_row - move_row==2)&&
                       current_col == move_col && BW[move_row][move_col]!=1 &&
                        BW[current_row-1][current_col]==0)
                    {
                        if(current_row-move_row==2) //to make whiteenpasant true
                        {
                            prev_white_col=current_col;
                            whiteenpassant[current_col]=true;
                        }
                        whitepawn_moves[current_col]++;
                        moves();
                    }
                    else if((current_row == move_row+1)&& current_col != move_col &&
                        (abs(move_col - current_col)<2) && BW[move_row][move_col]==1)
                                //if a pawn can capture a piece at first move
                    {
                        whitepawn_moves[current_col]++;
                        moves();
                    }
                    else
                    {
                        notvalid_display();
                    }

                }
                //moves forward one step after its first step
                else if(current_row - move_row == 1 && current_col == move_col &&
                         BW[move_row][move_col]!=1)
                {
                    moves();
                }
                //pawn capturing a piece after its first step
                else if(current_row - move_row == 1 && current_col!=move_col &&
                    ((abs(move_col - current_col)<2) && BW[move_row][move_col]==1))
                {
                    moves();
                }
            }
            //Pawn promotion condition for white pawn
            else if(current_row==1 && current_row - move_row == 1 &&
                    current_col == move_col && BW[move_row][move_col]!=1)
            {
                blackenpassant[prev_black_col]=false;
                changeColor(14);

                pawn_promotion_choice();  //getting input for promotion choice

                moves();        //do the move first

                changeColor(14);
                cout<<"\n\t\t White player ";changeColor(7);
                cout<<"has promoted ";changeColor(14);
                cout<<"Pawn ";changeColor(7);cout<<"to ";
                changeColor(14);

                pawnpromotion(); //do pawn promotion
            }
            else
            {

                //moves forward one step after its first step
                if(current_row - move_row == 1 && current_col == move_col
                   && BW[move_row][move_col]!=1)
                {
                    blackenpassant[prev_black_col]=false;
                    moves();
                }

                //En passant condition
                else if(current_row - move_row == 1 && current_col!=move_col &&
                     (abs(move_col - current_col)<2) &&
                    ((board[current_row][current_col+1]=="pawn" && BW[current_row][current_col+1]==1)||
                     (board[current_row][current_col-1]=="pawn"&& BW[current_row][current_col-1]==1))&&
                        blackpawn_moves[move_col]==1 &&blackenpassant[prev_black_col])
                {
                    bool enpassant_move=true;//to indicate if enpasant has happened or not

                    //right side black pawn condtion
                    if(board[current_row][current_col+1]=="pawn" && BW[current_row][current_col+1]==1 &&
                       current_row==move_row+1 && current_col==move_col-1)
                    {
                        board[current_row][current_col+1]="\0";
                        BW[current_row][current_col+1]=0;
                        moves();
                    }

                    //left side black pawn condition
                    else if(board[current_row][current_col-1]=="pawn"&& BW[current_row][current_col-1]==1 &&
                       current_row==move_row+1 && current_col==move_col+1)
                    {
                        board[current_row][current_col-1]="\0";
                        BW[current_row][current_col-1]=0;
                        moves();
                    }
                    else
                    {
                        enpassant_move=false;
                        notvalid_display();
                    }
                    if(enpassant_move) //if en passant has happened
                    {
                        changeColor(14);
                        cout<<"\t\t White pawn ";changeColor(7);
                        cout<<"has captured ";changeColor(12);
                        cout<<"Black pawn";changeColor(7);
                        cout<<" by ";changeColor(11);cout<<"En Passant\n\n";
                        changeColor(7);
                    }
                }

                //pawn capturing a piece after its first step
                else if(current_row - move_row == 1 && current_col!=move_col &&
                        ((abs(move_col - current_col)<2) && BW[move_row][move_col]==1))
                {
                    blackenpassant[prev_black_col]=false;
                    moves();

                    //if moving to last row, then pawn promotion is possible
                    if(current_row==1)
                    {

                        changeColor(14);

                        pawn_promotion_choice();

                        changeColor(14);
                        cout<<"\n\t\t White player ";changeColor(7);
                        cout<<"has promoted ";changeColor(14);
                        cout<<"Pawn ";changeColor(7);cout<<"to ";
                        changeColor(14);
                        pawnpromotion();
                        cout<<"\n";
                    }
                }
                else
                {
                    notvalid_display();
                }
            }
        }
        else
        {
            notvalid_display();
        }
    }

    //WHITE ROOK

    else if(board[current_row][current_col]=="rook" && BW[current_row][current_col]==2)
    {
        //if (current row and move row) or (current col and move col) are same, then
        if((current_row == move_row || current_col == move_col)&&
           BW[move_row][move_col]!=2) //moving location must not have a white piece
        {
            blackenpassant[prev_black_col]=false;
            whiterook[current_col]++;
            rookmove();
        }
        else
        {
            notvalid_display();
        }
    }

    //WHITE KNIGHT

    else if(board[current_row][current_col]=="knight" && BW[current_row][current_col]==2)
    {
         if(current_row!= move_row && current_col!=move_col &&
            BW[move_row][move_col]!=2)
         {
             blackenpassant[prev_black_col]=false;
             knightmove();
         }
         else
         {
             notvalid_display();
         }
    }

    //WHITE BISHOP

    else if(board[current_row][current_col]=="bishop" && BW[current_row][current_col]==2)
    {
        if(current_row!= move_row && current_col!=move_col &&
            BW[move_row][move_col]!=2)
         {
             blackenpassant[prev_black_col]=false;
             bishopmove();
         }
         else
         {
             notvalid_display();
         }
    }

    //WHITE KING

    else if(board[current_row][current_col]=="king" && BW[current_row][current_col]==2)
    {
        //kingside castling
        if(BW[7][5]==0 && BW[7][6]==0 &&current_row==7 &&current_col==4 &&
           move_row==7 && move_col==6 && whiteking==0 &&
            whiterook[7]==0 &&board[7][7]=="rook")
        {
            blackenpassant[prev_black_col]=false;

            whiteking++;
            whiterook[7]++;

            board[7][6]="king";
            BW[7][6]=2;
            board[7][4]="\0";
            BW[7][4]=0;

            board[7][5]="rook";
            BW[7][5]=2;
            board[7][7]="\0";
            BW[7][7]=0;

            changeColor(14);
            cout<<"\n\t\t  White player ";changeColor(7);
            cout<<"has performed ";changeColor(14);
            cout<<"Kingside castling\n\n";
            changeColor(7);

            movecount++;       //increment the total number of moves
            flag=true;         //a move has happened successfully
        }
        //Queen side castling
        else if(BW[7][3]==0 && BW[7][2]==0 &&BW[7][1]==0 &&current_row==7 &&
           current_col==4 && move_row==7 && move_col==2 && whiteking==0 &&
            whiterook[0]==0 &&board[7][0]=="rook")
        {
            blackenpassant[prev_black_col]=false;

            whiteking++;
            whiterook[0]++;

            board[7][2]="king";
            BW[7][2]=2;
            board[7][4]="\0";
            BW[7][4]=0;

            board[7][3]="rook";
            BW[7][3]=2;
            board[7][0]="\0";
            BW[7][0]=0;

            changeColor(14);
            cout<<"\n\t\t  White player ";changeColor(7);
            cout<<"has performed ";changeColor(14);
            cout<<"Queenside castling\n\n";
            changeColor(7);

            movecount++;       //increment the total number of moves
            flag=true;         //a move has happened successfully
        }
        else if(BW[move_row][move_col]!=2)
        {
            blackenpassant[prev_black_col]=false;
            kingmove();
        }
        else
        {
            notvalid_display();
        }
    }

    //WHITE QUEEN

    else if(board[current_row][current_col]=="queen" && BW[current_row][current_col]==2)
    {
        //if (current row and move row) or (current col and move col) are same, then
        if((current_row == move_row || current_col == move_col)&&
           BW[move_row][move_col]!=2) //moving location must not have a white piece
        {
            blackenpassant[prev_black_col]=false;
            //if queen's move location is similar to rook's move,then
            //do rook move for queen
            rookmove();
        }
        else if(current_row!= move_row && current_col!=move_col &&
            BW[move_row][move_col]!=2)
        {
            blackenpassant[prev_black_col]=false;
            //if queen's move location is similar to bishop's move,then
            //do bishop move for queen
            bishopmove();
        }
        else
        {
            notvalid_display();
        }
    }
}

void ChessGame::black_move()
{
    //BLACK PAWN
    if(board[current_row][current_col] == "pawn" && BW[current_row][current_col]==1)
    {
        if(move_row <= current_row)
        {
            notvalid_display();
        }
        //checking if the moving location is not having a black piece
        else if(BW[move_row][move_col] !=1)
        {
            if(current_row==1)
            {
                whiteenpassant[prev_white_col]=false;
                if(blackpawn_moves[current_col]==0)
                {
                    //a pawn can move 1 or 2 steps forward in first move
                     if((move_row - current_row ==1 || move_row - current_row==2 )&&
                           current_col == move_col && BW[move_row][move_col]!=2 &&
                           BW[current_row+1][current_col]==0)
                        {
                            if(move_row-current_row==2)
                            {
                                prev_black_col=current_col;
                                blackenpassant[current_col]=true;
                            }
                            blackpawn_moves[current_col]++;
                            moves();
                        }
                        else if((move_row == current_row+1) && current_col != move_col &&
                                (abs(move_col - current_col)<2) && BW[move_row][move_col] == 2)
                                    //if a pawn can capture a piece at first move
                        {
                            blackpawn_moves[current_col]++;
                            moves();
                        }
                        else
                        {
                            notvalid_display();
                        }
                }
            }
            //Pawn promotion condition for black pawn
            else if(current_row==6 && move_row - current_row == 1 &&
                    current_col == move_col && BW[move_row][move_col]!=2)
            {
                whiteenpassant[prev_white_col]=false;
                changeColor(12);

                pawn_promotion_choice(); //get input for promotion choice

                moves();        //do the move first

                changeColor(12);
                cout<<"\n\t\t Black player ";changeColor(7);
                cout<<"has promoted ";changeColor(12);
                cout<<"Pawn ";changeColor(7);cout<<"to ";
                changeColor(12);

                pawnpromotion(); //do pawn promotion
            }
            else
            {
                //moves forward one step after its first step
                if(move_row - current_row == 1 && current_col == move_col && BW[move_row][move_col]!=2)
                {
                    whiteenpassant[prev_white_col]=false;
                    moves();
                }

                //En passant condition
                else if(move_row - current_row == 1 && current_col!=move_col &&
                     (abs(move_col - current_col)<2) &&
                    ((board[current_row][current_col+1]=="pawn" && BW[current_row][current_col+1]==2)||
                     (board[current_row][current_col-1]=="pawn"&& BW[current_row][current_col-1]==2))&&
                        whitepawn_moves[move_col]==1 &&whiteenpassant[prev_white_col])
                {
                    bool enpassant_move=true; //to indicate if en passant has happened or not

                    //right side white pawn condition
                    if(board[current_row][current_col+1]=="pawn" && BW[current_row][current_col+1]==2 &&
                           current_row==move_row-1 && current_col==move_col-1)
                    {
                        board[current_row][current_col+1]="\0";
                        BW[current_row][current_col+1]=0;
                        moves();
                    }

                    //left side white pawn condition
                    else if(board[current_row][current_col-1]=="pawn"&& BW[current_row][current_col-1]==2 &&
                           current_row==move_row-1 && current_col==move_col+1)
                    {
                        board[current_row][current_col-1]="\0";
                        BW[current_row][current_col-1]=0;
                        moves();
                    }
                    else
                    {
                        enpassant_move=false;
                        notvalid_display();
                    }
                    if(enpassant_move)
                    {
                        changeColor(12);
                        cout<<"\t\t Black pawn ";changeColor(7);
                        cout<<"has captured ";changeColor(14);
                        cout<<"White pawn";changeColor(7);
                        cout<<" by ";changeColor(11);cout<<"En Passant\n\n";
                        changeColor(7);
                    }
                }

                //pawn capturing a piece after its first step
                else if(move_row - current_row == 1 && current_col!=move_col &&
                        ((abs(move_col - current_col)<2) && BW[move_row][move_col]==2))
                {
                    whiteenpassant[prev_white_col]=0;
                    moves();

                    //if moving to last row, then pawn promotion is possible
                    if(current_row==6)
                    {

                        changeColor(12);

                        pawn_promotion_choice();

                        changeColor(12);
                        cout<<"\n\t\t Black player ";changeColor(7);
                        cout<<"has promoted ";changeColor(12);
                        cout<<"Pawn ";changeColor(7);cout<<"to ";
                        changeColor(12);

                        pawnpromotion();
                        cout<<"\n";
                    }
                }
                else
                {
                    notvalid_display();
                }
            }
        }
        else
        {
            notvalid_display();
        }
    }

    //BLACK ROOK

    else if(board[current_row][current_col]=="rook" && BW[current_row][current_col]==1)
    {
        //if (current row and move row) or (current col and move col) are same, then
        if((current_row == move_row || current_col == move_col)&&
           BW[move_row][move_col]!=1) //moving location must not have a black piece
        {
            whiteenpassant[prev_white_col]=false;
            blackrook[current_col]++;
            rookmove();
        }
        else
        {
            notvalid_display();
        }
    }

    //BLACK KNIGHT

    else if(board[current_row][current_col]=="knight" && BW[current_row][current_col]==1)
    {
         if(current_row!= move_row && current_col!=move_col &&
            BW[move_row][move_col]!=1)
         {
             whiteenpassant[prev_white_col]=false;
             knightmove();
         }
         else
         {
             notvalid_display();
         }
    }

    //BLACK BISHOP

    else if(board[current_row][current_col]=="bishop" && BW[current_row][current_col]==1)
    {
        if(current_row!= move_row && current_col!=move_col &&
            BW[move_row][move_col]!=1)
         {
             whiteenpassant[prev_white_col]=false;
             bishopmove();
         }
         else
         {
             notvalid_display();
         }
    }

    //BLACK KING

    else if(board[current_row][current_col]=="king" && BW[current_row][current_col]==1)
    {
        //kingside castling
        if(BW[0][5]==0 && BW[0][6]==0 &&current_row==0 &&current_col==4 &&
           move_row==0 && move_col==6 && blackking==0 &&
            blackrook[7]==0 &&board[0][7]=="rook")
        {
            whiteenpassant[prev_white_col]=false;

            blackking++;
            blackrook[7]++;

            board[0][6]="king";
            BW[0][6]=1;
            board[0][4]="\0";
            BW[0][4]=0;

            board[0][5]="rook";
            BW[0][5]=1;
            board[0][7]="\0";
            BW[0][7]=0;

            changeColor(12);
            cout<<"\n\t\t  Black player ";changeColor(7);
            cout<<"has performed ";changeColor(12);
            cout<<"Kingside castling\n\n";
            changeColor(7);

            movecount++; //increment the total number of moves
            flag=true;   //a move has happened successfully
        }
        //Queen side castling
        else if(BW[0][3]==0 && BW[0][2]==0 &&BW[0][1]==0 &&current_row==0 &&
           current_col==4 && move_row==0 && move_col==2 && blackking==0 &&
            blackrook[0]==0 &&board[0][0]=="rook")
        {
            whiteenpassant[prev_white_col]=false;

            blackking++;
            blackrook[0]++;

            board[0][2]="king";
            BW[0][2]=1;
            board[0][4]="\0";
            BW[0][4]=0;

            board[0][3]="rook";
            BW[0][3]=1;
            board[0][0]="\0";
            BW[0][0]=0;

            changeColor(12);
            cout<<"\n\t\t  Black player ";changeColor(7);
            cout<<"has performed ";changeColor(12);
            cout<<"Queenside castling\n\n";
            changeColor(7);

            movecount++;       //increment the total number of moves
            flag=true;         //a move has happened successfully
        }

        else if(BW[move_row][move_col]!=1)
        {
            whiteenpassant[prev_white_col]=false;

            kingmove();
        }
        else
        {
            notvalid_display();
        }
    }

    //BLACK QUEEN
    else if(board[current_row][current_col]=="queen" && BW[current_row][current_col]==1)
    {
        //if (current row and move row) or (current col and move col) are same, then
        //queen is going to have same move as rook, then call rookmove function
        if((current_row == move_row || current_col == move_col)&&
           BW[move_row][move_col]!=1)
        {
            whiteenpassant[prev_white_col]=false;
            rookmove();
        }
        //if (current row and move row) or (current col and move col) are not same,then
        //queen is going to have same move as bishop, then call bishopmove function
        else if(current_row!= move_row && current_col!=move_col &&
            BW[move_row][move_col]!=1)
        {
            whiteenpassant[prev_white_col]=false;
            bishopmove();
        }
        else
        {
            notvalid_display();
        }
    }

}
void ChessGame::rookmove() //function to move a rook
{
    int k;
    bool rookflag=true; //to indicate if rook can move or not
    if(current_row == move_row)
    {
        if(current_col<move_col)
        {
            //traversing to check if there are any obstacles
            //(white or black pieces) in moving path
            for(k=current_col+1;k<move_col && rookflag;k++)
            {
                //if there are pieces, then set rookflag to false
                if(BW[current_row][k]==2 || BW[current_row][k]==1)
                {
                    rookflag=false;
                }
            }
            //else, move the rook
            if(rookflag)
            {
                moves();
            }
        }
        else //current column is greater than move column
        {
            rookflag=true;
            for(k=current_col-1;k>move_col && rookflag;k--)
            {
                if(BW[current_row][k]==2 || BW[current_row][k]==1)
                {
                    rookflag=false;
                }
            }
            if(rookflag)
            {
                moves();
            }
        }
    }
    else if(current_col == move_col)
    {
        if(current_row<move_row)
        {
            for(k=current_row+1;k<move_row && rookflag;k++)
            {
                if(BW[k][current_col]==2 || BW[k][current_col]==1)
                {
                    rookflag=false;
                }
            }
            if(rookflag)
            {
                moves();
            }
        }
        else //current row is greater than move row
        {
            rookflag=true;
            for(k=current_row-1;k>move_row && rookflag;k--)
            {
                if(BW[k][current_col]==2 || BW[k][current_col]==1)
                {
                    rookflag=false;
                }
            }
            if(rookflag)
            {
                moves();
            }
        }
    }
    if(!rookflag)
    {
        notvalid_display();
    }
}

//function to move a knight
void ChessGame::knightmove()
{
    // 7'o clock location from knight
     if(current_row==move_row-2 && current_col==move_col+1)
     {
         moves();
     }
     // 8'o clock location from knight
     else if(current_row==move_row-1 && current_col==move_col+2)
     {
         moves();
     }
     // 10'o clock location from knight
     else if(current_row==move_row+1 && current_col==move_col+2)
     {
         moves();
     }
     // 11'o clock location from knight
     else if(current_row==move_row+2 && current_col==move_col+1)
     {
         moves();
     }
     // 1'o clock location from knight
     else if(current_row==move_row+2 && current_col==move_col-1)
     {
         moves();
     }
     // 2'o clock location from knight
     else if(current_row==move_row+1 && current_col==move_col-2)
     {
         moves();
     }
     //4'o clock location from knight
     else if(current_row==move_row-1 && current_col==move_col-2)
     {
         moves();
     }
     //5'o clock locatoin from knight
     else if(current_row==move_row-2 && current_col==move_col-1)
     {
         moves();
     }
     else
     {
         notvalid_display();
     }
}

//function to move a bishop
void ChessGame::bishopmove()
{
     int p=current_row, q=current_col;
     bool bishopflag=false, obstacleflag=false;

     //left top move condition for bishop
     if(current_row>move_row && current_col>move_col)
     {
         //traverse to left top from the current bishop location
         for(p=p-1,q=q-1;p>=0 && q>=0 && !bishopflag &&!obstacleflag;p--,q--)
         {
             //while traversing, if the location to be moved is found, then
             //set bishopflag to true
             if(p==move_row && q==move_col)
             {
                 bishopflag=true;
             }

             //while traversing, if there are any obstacles(pieces) found,
             //then set obstacleflag to true
             else if(BW[p][q]==1 || BW[p][q]==2)
             {
                 obstacleflag=true;
             }
         }
         //if location is found AND there are no obstacles,
         //then move the bishop
         if(bishopflag && !obstacleflag)
         {
             moves();
         }
         else
         {
             notvalid_display();
         }
     }

     //right top move condition for bishop
     if(current_row>move_row && current_col<move_col)
     {
         //traverse to right top from the current bishop location
         for(p=p-1,q=q+1;p>=0 && q<=7 && !bishopflag &&!obstacleflag;p--,q++)
         {
             if(p==move_row && q==move_col)
             {
                 bishopflag=true;
             }
             else if(BW[p][q]==1 || BW[p][q]==2)
             {
                 obstacleflag=true;
             }
         }
         if(bishopflag && !obstacleflag)
         {
             moves();
         }
         else
         {
             notvalid_display();
         }
     }

     //right bottom move condition for bishop
     if(current_row<move_row && current_col<move_col)
     {
         //traverse to right bottom from the current bishop location
         for(p=p+1,q=q+1;p<=7 && q<=7 && !bishopflag &&!obstacleflag;p++,q++)
         {
             if(p==move_row && q==move_col)
             {
                 bishopflag=true;
             }
             else if(BW[p][q]==1 || BW[p][q]==2)
             {
                 obstacleflag=true;
             }
         }
         if(bishopflag && !obstacleflag)
         {
             moves();
         }
         else
         {
             notvalid_display();
         }
     }

     //left bottom move condition for bishop
     if(current_row<move_row && current_col>move_col)
     {
         //traverse to left bottom from the current bishop location
         for(p=p+1,q=q-1;p<=7 && q>=0 && !bishopflag &&!obstacleflag;p++,q--)
         {
             if(p==move_row && q==move_col)
             {
                 bishopflag=true;
             }
             else if(BW[p][q]==1 || BW[p][q]==2)
             {
                 obstacleflag=true;
             }
         }
         if(bishopflag && !obstacleflag)
         {
             moves();
         }
         else
         {
             notvalid_display();
         }
     }

}

//function to move a king
void ChessGame::kingmove()
{
    bool moved=true; //to indicate if king has moved or not
    //moving left or right one step
    if(current_row==move_row &&
       (current_col==move_col+1 || current_col==move_col-1))
    {
        moves();
    }
    //moving up or down one step
    else if(current_col==move_col &&
            (current_row==move_row+1 || current_row==move_row-1))
    {
        moves();
    }
    //moving left top one step
    else if(current_row==move_row+1 && current_col==move_col+1)
    {
        moves();
    }
    //moving right top one step
    else if(current_row==move_row+1 && current_col==move_col-1)
    {
        moves();
    }
    //moving right bottom one step
    else if(current_row==move_row-1 && current_col==move_col-1)
    {
        moves();
    }
    //moving left bottom one step
    else if(current_row==move_row-1 && current_col==move_col+1)
    {
        moves();
    }
    else
    {
        moved=false; //if king has not moved
        notvalid_display();
    }
    if(moved)
    {
    //Increment the value for the moved king. Since by calling
    //moves() function above,the movecount value increases
    //by 1,hence change the below if condition
        if(move_flag==1)
            whiteking++;
        else
            blackking++;
    }
}

//Function to get choice for pawn promotion
void ChessGame::pawn_promotion_choice()
{
    cout<<"\n Pawn ";changeColor(7);
    cout<<"promotion\n\n Promote pawn to ?\n 1-> Queen\n 2-> Rook";
    cout<<"\n 3-> Bishop\n 4-> Knight";
    cout<<"\n Enter your choice : ";

    //to get integer input for the promotion choice
    while(!(cin>>promote_choice) || (promote_choice!=1 &&
        promote_choice!=2 && promote_choice!=3 && promote_choice!=4))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout<<"\n\t\t\t  Please enter a ";changeColor(11);
        cout<<"valid ";changeColor(7);cout<<"choice !!";
        cout<<"\n\n Enter your choice correctly : ";
    }
}

//Function to do pawn promotion
void ChessGame::pawnpromotion()
{
    switch(promote_choice)
    {
        //pawn to queen
        case 1:
            board[move_row][move_col] = "queen";
            cout<<"queen\n";
            break;
        //pawn to rook
        case 2:
            board[move_row][move_col] = "rook";
            cout<<"rook\n";
            break;
        //pawn to bishop
        case 3:
            board[move_row][move_col] = "bishop";
            cout<<"bishop\n";
            break;
        //pawn to knight
        case 4:
            board[move_row][move_col] = "knight";
            cout<<"knight\n";
            break;
    }
    changeColor(7);
}

//function to display that the input is invalid !
void ChessGame::notvalid_display()
{
    changeColor(11);
    cout<<"\n\t\t PLEASE ENTER A VALID MOVE !! \n\n";
    changeColor(7);
    flag=false;
}

//function to move a piece from current to desired location
void ChessGame::moves()
{
    //if a piece captures other piece
    if(BW[current_row][current_col] + BW[move_row][move_col] == 3)
    {
        //if black captures white
        if(BW[current_row][current_col]==1)
        {
            changeColor(12);
            cout<<"\n\t\t\t Black "<<board[current_row][current_col];changeColor(7);
            cout<<" captured ";changeColor(14);
            cout<<"White "<<board[move_row][move_col];
            changeColor(7);
        }
        else //if white captures black
        {
            changeColor(14);
            cout<<"\n\t\t\t White "<<board[current_row][current_col];changeColor(7);
            cout<<" captured ";changeColor(12);
            cout<<"Black "<<board[move_row][move_col];
            changeColor(7);
        }
        cout<<endl;
    }
    cout<<"\n ";
    board[move_row][move_col] = board[current_row][current_col];

    if(BW[current_row][current_col] == 2) //if current piece is white
        BW[move_row][move_col] = 2;
    else                                  //if current piece is black
        BW[move_row][move_col] = 1;

    board[current_row][current_col] = '\0';
    BW[current_row][current_col] = 0;   //setting the current location to zero
    movecount++;       //increment the total number of moves
    flag=true;         //a move has happened successfully
}

//A function to check if there are any check for Black king
bool ChessGame::whitecheck()
{
    int row, col,check_flag=1;
    for(i=0;i<N;i++)
    {
        for(j=0;j<N;j++)
        {
            if(BW[i][j]==2)
            {
            //check if there are possibilities for check to black king by white pawn
                if(board[i][j]=="pawn")
                {
                    if(j==7 && i!=0)
                    {
                        if(board[i-1][j-1]=="king" && BW[i-1][j-1]==1)
                           return true;
                    }
                    else if(j==0 && i!=0)
                    {
                        if(board[i-1][j+1]=="king" && BW[i-1][j+1]==1)
                           return true;
                    }
                    else if((board[i-1][j-1]=="king" && BW[i-1][j-1]==1)||
                   (board[i-1][j+1]=="king" && BW[i-1][j+1]==1))
                    {
                        return true;
                    }
                }
            //check if there are possibilities for check to black king by white rook
                else if(board[i][j]=="rook")
                {
                    if(check_rookmove(i, j,check_flag))
                        return true;
                }
            //check if there are possibilities for check to black king by white bishop
                else if(board[i][j]=="bishop")
                {
                    if(check_bishopmove(i, j,check_flag))
                        return true;
                }
            //check if there are possibilities for check to black king by white knight
                else if(board[i][j]=="knight")
                {
                    if(check_knightmove(i, j, check_flag))
                        return true;
                }
            //check if there are possibilities for check to black king by white queen
                else if(board[i][j]=="queen")
                {
                    if(check_rookmove(i, j,check_flag) ||
                       check_bishopmove(i, j,check_flag))
                        return true;
                }
                else if(board[i][j]=="king")
                {
                    if(check_kingmove(i,j, check_flag))
                        return true;
                }
            }
        }
    }
    return false;
}

//A function to check if there are any check for White King
bool ChessGame::blackcheck()
{
    int row, col,check_flag=2;
    for(i=0;i<N;i++)
    {
        for(j=0;j<N;j++)
        {
            if(BW[i][j]==1)
            {
            //check if there are possibilities for CHECK to white king by black pawn
                if(board[i][j]=="pawn")
                {
                    if(j==7 && i!=7)
                    {
                        if(board[i+1][j-1]=="king" && BW[i+1][j-1]==2)
                           return true;
                    }
                    else if(j==0 && i!=7)
                    {
                        if(board[i+1][j+1]=="king" && BW[i+1][j+1]==2)
                           return true;
                    }
                    else if((board[i+1][j-1]=="king" && BW[i+1][j-1]==2)||
                            (board[i+1][j+1]=="king" && BW[i+1][j+1]==2))
                    {
                        return true;
                    }
                }
            //check if there are possibilities for check to black king by white rook
                else if(board[i][j]=="rook")
                {
                    if(check_rookmove(i, j, check_flag))
                        return true;
                }
            //check if there are possibilities for check to black king by white bishop
                else if(board[i][j]=="bishop")
                {
                    if(check_bishopmove(i, j, check_flag))
                        return true;
                }
            //check if there are possibilities for check to black king by white knight
                else if(board[i][j]=="knight")
                {
                    if(check_knightmove(i, j, check_flag))
                        return true;
                }
            //check if there are possibilities for check to black king by white queen
                else if(board[i][j]=="queen")
                {
                    if(check_rookmove(i, j,check_flag) ||
                       check_bishopmove(i, j,check_flag))
                        return true;
                }
                else if(board[i][j]=="king")
                {
                    if(check_kingmove(i,j, check_flag))
                        return true;
                }
            }
        }
    }
    return false;
}

//function to check if a rook can defeat opponent king or not(CHECK condition)
bool ChessGame::check_rookmove(int i, int j,int flag)
{
    int row,col;

    //traversing up and checking
    if(i !=0)
    {
        for(row=i-1,col=j;row>=0;row--)
        {
            if(board[row][col]=="king" && BW[row][col]==flag)
            {
                return true;
            }
            else if(BW[row][col]==1 || BW[row][col]==2)
            {
                break;
            }
        }
    }

    //traversing down and checking
    if(i !=7)
    {
        for(row=i+1,col=j;row<=7;row++)
        {
            if(board[row][col]=="king" && BW[row][col]==flag)
            {
                return true;
            }
            else if(BW[row][col]==1 || BW[row][col]==2)
            {
                break;
            }
        }
    }

    //traversing right and checking
    if(j!=7)
    {
        for(row=i,col=j+1;col<=7;col++)
        {
            if(board[row][col]=="king" && BW[row][col]==flag)
            {
                return true;
            }
            else if(BW[row][col]==1 || BW[row][col]==2)
            {
                break;
            }
        }
    }

    //traversing left and checking
    if(j !=0)
    {
        for(row=i,col=j-1;col>=0;col--)
        {
            if(board[row][col]=="king" && BW[row][col]==flag)
            {
                return true;
            }
            else if(BW[row][col]==1 || BW[row][col]==2)
            {
                return false;
                break;
            }
        }
    }

    return false;
}

//function to check if a bishop can defeat opponent king or not(CHECK condition)
bool ChessGame::check_bishopmove(int i, int j,int flag)
{
    int row, col;
    //traverse to left top from the current bishop location
    if(i !=0 && j !=0)
    {
         for(row=i-1,col=j-1;row>=0 && col>=0;row--,col--)
         {
             //while traversing, if black king is found, then return true
             if(board[row][col]=="king"&&BW[row][col]==flag)
             {
                 return true;
             }
             //while traversing, if there are any obstacles(pieces) found,
             //then break the loop
             else if(BW[row][col]==1 || BW[row][col]==2)
             {
                 break;
             }
         }
    }

     //traverse to right top from the current bishop location
     if(i!=0 && j!=7)
     {
         for(row=i-1,col=j+1;row>=0 && col<=7 ;row--,col++)
         {
             if(board[row][col]=="king"&&BW[row][col]==flag)
             {
                 return true;
             }
             else if(BW[row][col]==1 || BW[row][col]==2)
             {
                 break;
             }
         }
     }

     //traverse to right bottom from the current bishop location
     if(i!=7 && j!= 7)
     {
         for(row=i+1,col=j+1;row<=7 && col<=7;row++,col++)
         {
             if(board[row][col]=="king"&&BW[row][col]==flag)
             {
                 return true;
             }
             else if(BW[row][col]==1 || BW[row][col]==2)
             {
                 break;
             }
         }
     }

     //traverse to left bottom from the current bishop location
     if(i!=7 && j!=0)
     {
         for(row=i+1,col=j-1;row<=7 && col>=0;row++,col--)
         {
             if(board[row][col]=="king"&&BW[row][col]==flag)
             {
                 return true;
             }
             else if(BW[row][col]==1 || BW[row][col]==2)
             {
                 break;
             }
         }
     }

     return false;
}

//function to check if a knight can defeat opponent king or not(CHECK condition)
bool ChessGame::check_knightmove(int i, int j,int flag)
{
    int row=i,col=j;
    //10'o clock condition
    if(row>=1 && col >=2)
    {
        if(board[row-1][col-2]=="king"&& BW[row-1][col-2]==flag)
        {
           return true;
        }
    }

    //11'o clock condition
    if(row >=2 && col >=1)
    {
        if(board[row-2][col-1]=="king"&& BW[row-2][col-1]==flag)
        {
           return true;
        }
    }

    //1'o clock condition
    if(row >=2 && col <=6)
    {
        if(board[row-2][col+1]=="king"&& BW[row-2][col+1]==flag)
        {
           return true;
        }
    }

    //2'o clock condition
    if(row>=1 && col <=5)
    {
        if(board[row-1][col+2]=="king"&& BW[row-1][col+2]==flag)
        {
           return true;
        }
    }

    //4'o clock condition
    if(row<=6 && col <=5)
    {
        if(board[row+1][col+2]=="king"&& BW[row+1][col+2]==flag)
        {
           return true;
        }
    }

    //5'o clock condition
    if(row<=5 && col<=6)
    {
        if(board[row+2][col+1]=="king"&& BW[row+2][col+1]==flag)
        {
           return true;
        }
    }

    //7'o clock condition
    if(row<=5 && col>=1)
    {
        if(board[row+2][col-1]=="king"&& BW[row+2][col-1]==flag)
        {
           return true;
        }
    }

    //8'o clock condition
    if(row<=6 && col >=2)
    {
        if(board[row+1][col-2]=="king"&& BW[row+1][col-2]==flag)
        {
           return true;
        }
    }
}

//function to check if a king can defeat opponent king or not(CHECK condition)
bool ChessGame::check_kingmove(int i, int j, int flag)
{
    int row=i, col=j;
    //top left move condition
    if(row!=0 && col!=0)
    {
        if(board[row-1][col-1]=="king"&&BW[row-1][col-1]==flag)
            return true;
    }
    //top move condition
    if(row!=0)
    {
        if(board[row-1][col]=="king"&&BW[row-1][col]==flag)
            return true;
    }
    //top right move condition
    if(row!=0 && j!=7)
    {
        if(board[row-1][col+1]=="king"&&BW[row-1][col+1]==flag)
            return true;
    }
    //right move condition
    if(col!=7)
    {
        if(board[row][col+1]=="king"&& BW[row][col+1]==flag)
            return true;
    }
    //bottom right move condition
    if(row!=7 && col!=7)
    {
        if(board[row+1][col+1]=="king" && BW[row+1][col+1]==flag)
            return true;
    }
    //bottom move condition
    if(row!=7)
    {
        if(board[row+1][col]=="king" && BW[row+1][col]==flag)
            return true;
    }
    //bottom left move condition
    if(row!=7 && col!=0)
    {
        if(board[row+1][col-1]=="king"&&BW[row+1][col-1]==flag)
            return true;
    }
    //left move condition
    if(col!=0)
    {
        if(board[row][col-1]=="king" && BW[row][col-1]==flag)
            return true;
    }
    return false;
}

//function to ask the user if they want to play again?
void ChessGame::play_again()
{
    int play_choice;
    cout<<"\n Do you want to play another game?";
    cout<<"\n 1 -> Yes\n 2 -> No";
    cout<<"\n Enter your choice : ";
    while(!(cin>>play_choice) || (play_choice!=1 && play_choice!=2))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout<<"\n\t\t\t  Please enter a ";changeColor(11);
        cout<<"valid ";changeColor(7);cout<<"choice !!";
        cout<<"\n\n Enter your choice correctly : ";
    }
    if(play_choice==1)
    {
        //separator line
        cout<<endl;
        for(int i=0;i<14;i++)
            cout<<"--------";
        cout<<endl;

        changeColor(11);
        cout<<"\n\n\t\t\t\t NEW GAME \n\n";
        changeColor(7);

        //call the declare function to newly declare the board
        declare();
        for(i=2;i<6;i++)
        {
            for(j=0;j<N;j++)
            {
                board[i][j]="\0";
                BW[i][j]=0;
            }
        }
        display(); //display the newly declared board
    }
    else
    {
        cout<<"\n\n\t\t\t   THANKS FOR ";changeColor(10);
        cout<<"PLAYING CHESS !!\n\n";changeColor(7);
        //separator line
        cout<<endl;
        for(int i=0;i<14;i++)
            cout<<"--------";
        cout<<endl;
        exit(0); //exits the program
    }
}
int main()
{
    ChessGame obj; //creating an object for the class ChessGame
    obj.declare();
    obj.display(); //display the initial board;

    while(true)
    {
        //displaying the separator(border) for differentiating each move
        cout<<endl;
        for(int i=0;i<14;i++)
            cout<<"--------";
        cout<<endl;

        obj.getmoves(); //getting input for the move and performing it

        //if a move has happened, then display the board
        if(obj.flag)
        {
            obj.display();
            if(obj.move_flag)
            {
                //checking CHECKMATE condition for white king
                if(obj.blackcheck())
                {
                    changeColor(11);
                    cout<<"\n\n\t\t\t     CHECKMATE";changeColor(7);
                    cout<<" for ";changeColor(14);
                    cout<<"White King";
                    changeColor(7);

                    changeColor(12);
                    cout<<"\n\n\t\t\t Black player";changeColor(7);
                    cout<<" has ";changeColor(11);
                    cout<<"WON the game";
                    changeColor(7);cout<<" !!\n\n";

                    //function to ask user if they want to play again
                    obj.play_again();

                }
                //'CHECK' condition for black king
                if(obj.whitecheck())
                {
                    changeColor(11);
                    cout<<"\n\t\t\t    Check ";changeColor(7);
                    cout<<"for ";changeColor(12);
                    cout<<"Black King";
                    changeColor(7);cout<<" !!\n";
                }
            }
            else
            {
                //checking CHECKMATE condition for black king
                if(obj.whitecheck())
                {
                    changeColor(11);
                    cout<<"\n\n\t\t\t     CHECKMATE";changeColor(7);
                    cout<<" for ";changeColor(12);
                    cout<<"Black King";
                    changeColor(7);

                    changeColor(14);
                    cout<<"\n\n\t\t\t White player";changeColor(7);
                    cout<<" has ";changeColor(11);
                    cout<<"WON the game";
                    changeColor(7);cout<<" !!\n\n";

                    obj.play_again();
                }
                //'CHECK' condition for white king
                else if(obj.blackcheck())
                {
                    changeColor(11);
                    cout<<"\n\t\t\t    Check ";changeColor(7);
                    cout<<"for ";changeColor(14);
                    cout<<"White King";
                    changeColor(7);cout<<" !!\n";
                }
            }
        }
    }
    return 0;
}
