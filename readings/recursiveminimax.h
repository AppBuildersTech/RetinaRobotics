int GameControl::Evaluate(ChessBoard _B)
{

    int material=0,bonus=0,mobility=0;
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
        {

            if(_B.Board[i][j]!=EMPTY)
            {
                if(_B.Board[i][j]->pieceColor==WHITE){
                    material+=-_B.Board[i][j]->Weight;
                    bonus+=-_B.Board[i][j]->bonusPosition[i][j];
                    mobility+=-_B.Board[i][j]->getPossibleMovesList(i,j,B).size();
                }
                else {
                    material+=_B.Board[i][j]->Weight;
                    bonus+=_B.Board[i][j]->bonusPosition[i][j];             
                mobility+=_B.Board[i][j]->getPossibleMovesList(i,j,B).size();
                }
            }
        }
        return material+bonus/10+mobility/20;
}


pair<pair<int,int>,pair<int,int>> GameControl::minimax( int depth , ChessBoard _B )
{
    short int i,j;

    int bestValue = -INFINITY;

    pair<pair<int,int>,pair<int,int>> bestMove;

    vector< pair<int,int> > ::iterator it;

    vector< pair<int,int> > Z;

    for( i = 0; i < 8; i++ )

        for( j = 0; j < 8; j++ )
        {
            if(_B.Board[i][j]!=EMPTY && _B.Board[i][j]->pieceColor==BLACK )
            {
                Z=_B.Board[i][j]->getPossibleMovesList(i,j,_B);
                for(it=Z.begin();it!=Z.end();it++)
                {
                    pair<int,int> temp;
                    temp.first=i,temp.second=j;
                    ChessPieces* DestinationPiece;
                    DestinationPiece=_B.Board[(*it).first][(*it).second];
                    //Moving
                    _B.Board[(*it).first][(*it).second]=_B.Board[i][j];
                    _B.Board[i][j]=EMPTY;
                    //
                    int value = minSearch( depth-1 , _B );
                    if( value > bestValue )
                    {
                        bestValue = value;
                        bestMove.first.first = i;
                        bestMove.first.second = j;
                        bestMove.second.first = (*it).first;
                        bestMove.second.second = (*it).second;

                    }
                    //Undo Move
                    _B.Board[i][j]=_B.Board[((*it).first)][(*it).second];
                    _B.Board[(*it).first][(*it).second]=DestinationPiece;
                }

            }
        }

        return bestMove;
}


int GameControl::minSearch( int depth , ChessBoard _B )
{

    short int i;
    short int j;
    if(depth==0)
        return Evaluate(_B);

    int bestValue = INFINITY;
    for( i = 0; i < 8; i++ )
        for( j = 0; j < 8; j++ )
        {
            vector< pair<int,int> > ::iterator it;
            vector< pair<int,int> > Z;
            if(_B.Board[i][j]!=EMPTY && _B.Board[i][j]->pieceColor==WHITE  && !_B.Board[i][j]->V.empty())
            {

                Z=_B.Board[i][j]->getPossibleMovesList(i,j,_B);
                for(it=Z.begin();it!=Z.end();it++)
                {

                    pair<int,int> temp;
                    temp.first=i;
                    temp.second=j;
                    ChessPieces* DestinationPiece;
                    DestinationPiece=_B.Board[(*it).first][(*it).second];
                    // Moving
                    _B.Board[(*it).first][(*it).second]=_B.Board[i][j];
                    _B.Board[i][j]=EMPTY;
                    //
                    int value = maxSearch( depth-1 , _B );
                    if( value < bestValue )
                        bestValue = value;  
                    //Undo Move
                    _B.Board[i][j]=_B.Board[(*it).first][(*it).second];     
                    _B.Board[(*it).first][(*it).second]=DestinationPiece;
                    //
                }

            }
        }
        return bestValue;
}


int GameControl::maxSearch( int depth , ChessBoard _B )
{


    short int i;
    short int j;
    if(depth==0)
        return Evaluate(_B);
    vector< pair<int,int> > ::iterator it;
    vector< pair<int,int> > Z;
    int bestValue = -INFINITY;
    for( i = 0; i < 8; i++ )
        for( j = 0; j < 8; j++ )
        {

            if(_B.Board[i][j]!=EMPTY && _B.Board[i][j]->pieceColor==BLACK )
            {
                Z=_B.Board[i][j]->getPossibleMovesList(i,j,_B);
                for(it=Z.begin();it!=Z.end();it++)
                {
                    pair<int,int> temp;

                    temp.first=i,temp.second=j;
                    ChessPieces* DestinationPiece;
                    DestinationPiece=_B.Board[(*it).first][(*it).second];
                    //Moving
                    _B.Board[(*it).first][(*it).second]=_B.Board[i][j];
                    _B.Board[i][j]=EMPTY;
                    //
                    int value = minSearch( depth-1 , _B );
                    if( value > bestValue )     
                        bestValue = value;

                    //Undo Move
                    _B.Board[i][j]=_B.Board[((*it).first)][(*it).second];   
                    _B.Board[(*it).first][(*it).second]=DestinationPiece;
                }

            }
        }
        return bestValue;
}