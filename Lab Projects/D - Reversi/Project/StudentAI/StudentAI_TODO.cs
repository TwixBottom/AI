using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.IO.Pipes;
using FullSailAFI.GamePlaying.CoreAI;

namespace FullSailAFI.GamePlaying
{
    public class StudentAI : Behavior
    {
        TreeVisLib treeVisLib;  // lib functions to communicate with TreeVisualization
        bool visualizationFlag = false;  // turn this on to use tree visualization (which you will have to implement via the TreeVisLib API)
                                         // WARNING: Will hang program if the TreeVisualization project is not loaded!

        public StudentAI()
        {
            if (visualizationFlag == true)
            {
                if (treeVisLib == null)  // should always be null, but just in case
                    treeVisLib = TreeVisLib.getTreeVisLib();  // WARNING: Creation of this object will hang if the TreeVisualization project is not loaded!
            }
        }

        //
        // This function starts the look ahead process to find the best move
        // for this player color.
        //
        public ComputerMove Run(int _nextColor, Board _board, int _lookAheadDepth)
        {
            ComputerMove nextMove = GetBestMove(_nextColor, _board, _lookAheadDepth);

            return nextMove;
        }

        //
        // This function uses look ahead to evaluate all valid moves for a
        // given player color and returns the best move it can find. This
        // method will only be called if there is at least one valid move
        // for the player of the designated color.
        //
        int GetNextPlayer(int player, Board gameState)
        {
            if (gameState.HasAnyValidMove(-player))
            {
                return -player;
            }
            else
            {
                return player;
            }
        }

        private ComputerMove GetBestMove(int color, Board board, int depth)
        {
            //TODO: the lab

            ComputerMove bestMove = null;
            Board newState = new Board();

            List<ComputerMove> moves = new List<ComputerMove>();

            for (int y = 0; y < 8; y++)
            {
                for (int x = 0; x < 8; x++)
                {
                    if (board.IsValidMove(color, x, y))
                    {
                        moves.Add(new ComputerMove(x, y));
                    }
                }
            }  

            foreach (ComputerMove item in moves)
            {
                newState.Copy(board);
                newState.MakeMove(color, item.row, item.col);

                if (newState.IsTerminalState() || depth == 0)
                {
                    item.rank = Evaluate(newState);
                }
                else
                {
                    item.rank = GetBestMove(GetNextPlayer(color, newState), newState, depth - 1).rank;
                }

                if (color == -1) // black
                {
                    if (bestMove == null || item.rank < bestMove.rank)
                    {
                        bestMove = item;
                    }
                }

                if (color == 1) // white
                {
                    if (bestMove == null || item.rank > bestMove.rank)
                    {
                        bestMove = item;
                    }
                }

            }

            return bestMove;

            // throw new NotImplementedException();
        }

        #region Recommended Helper Functions

        private int Evaluate(Board _board)
        {

            int score = 0;

            for (int y = 0; y < 8; y++)
            {
                for (int x = 0; x < 8; x++)
                {
                    int move = _board.GetSquareContents(x, y);

                    if (move == 0)
                    {
                        continue;
                    }

                    // corners
                    if (x == 0 && y == 0 || x == 7 && y == 0 || x == 0 && y == 7 || x == 7 && y == 7)
                    {
                        score += move * 100;
                    }
                    // sides
                    else if (x == 0 || x == 7 || y == 0 || y == 7)
                    {
                        score += move * 10;
                    }
                    else
                    {
                        score += move;
                    }
                }
            }

            return score;
            
            //TODO: determine score based on position of pieces
            //return ExampleAI.MinimaxAFI.EvaluateTest(_board); // TEST WITH THIS FIRST, THEN IMPLEMENT YOUR OWN EVALUATE
        }

        #endregion

    }
}
