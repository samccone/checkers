/*
 *  checkers.cc
 *  checkers
 *
 *  Created by Sam Saccone on 5/7/10.
 *  Copyright 2010 . All rights reserved.
 *
 */
#include "checkers.h"
#include "colors.h"
#include "pieces.h"
#include <stdio.h>
#include <stdlib.h>
namespace main_savitch_14
{
	const int checkers::SIZE;
	
	checkers::checkers() //constructor
	{
		
	}
	
	
	std::string checkers::get_user_move() const //gets a users move
	{
		std::string move;
		std::cout<<"\n\nEnter a move (EX F1E2) \n> ";
		std::getline(std::cin,move);
		return move;
		
	}
	
	void checkers::display_status( ) const //displays the current board  DONE
	{
		system("clear");
		std::cout<<"\n\n";
		char left = 'A';
		std::string color;
		for (int x=0;x<SIZE;x++)
		{
			std::cout<<"                          "; //barbaric approach to center the board
			
			std::cout<<BLUE<<char(left+x)<<" ";
			for (int y=0;y<SIZE;y++)
			{
				if ((y+x)%2) color=B_RED;else color=B_BLACK;
				line(board[x][y],color);
			}
			if (x==7)
			{
				std::cout<<"\n"<<"    ";
				std::cout<<"                          "; //barbaric approach to center the board
				for (int yy=0;yy<SIZE;yy++)
					std::cout<<BLUE<<yy<<"   "; 		
				std::cout<<"\n                                        "; //barbaric approach to center the board
			}
			
			std::cout<<"\n";
		}
		
		std::cout<<WHITE;
		
	}
	
	void checkers::line(pieces piece,std::string color) const //prints one line of the board DONE
	{
		
		for (int ii = 0;ii<4;ii++)
		{
			if (ii==2&&!piece.is_empty()) 
			{
				if (piece.is_king())
				{
					if (piece.is_red())
						std::cout<<MAGENTA<<"K";
					if(piece.is_black())
						std::cout<<WHITE<<"K";
				}
				else
				{
					if (piece.is_red())
						std::cout<<MAGENTA<<"□";
					else if(piece.is_black())
						std::cout<<WHITE<<"□";
				}


			}

			else std::cout<<color<<" ";	

		}
		
		std::cout<<RESET;
		
	}
		
	
	void checkers::restart() //resets the game DONE
	{
		system("clear");
		pieces tmp;
		std::cout<<RESET;
		for (int i =0;i<SIZE;++i)
			for (int j=0;j<SIZE;++j)
			{
				if((i+j)%2&&i<=2)
				{
					tmp.set_red();
				}
				else if((i+j)%2&&i>=5)
				{
					tmp.set_black();
				}
				else 
					tmp.set_empty();
				board[i][j]=tmp;
			}
	}
	
	void checkers::make_move(const std::string& move) //makes the users move
	{
		std::string movez(move);
		std::transform(movez.begin(), movez.end(),movez.begin(), ::toupper); //converts the string to all upper
		bool flag=1;bool was_jump =0;
		while (flag)
		{
			if (isjump(movez)) was_jump=1;
			move_it(movez);
			display_status();
			

			
			flag=can_jump(movez,was_jump);
			if (flag){ 
				std::string move2(get_user_move());
				while(!is_legal(move2)){ std::cout<<"Illegal move.\n";move2 = get_user_move();}
				make_move(move2);		game::make_move(movez);
			}
		}
		game::make_move(movez);

	}
	
	bool checkers::is_legal(const std::string& move)const //checks to see if the users move is legal
	{
		std::string movez = move;
		std::transform(movez.begin(), movez.end(),movez.begin(), ::toupper); //converts the string to all upper
		pieces tmp =board[movez[0]-'A'][movez[1]-48];
		pieces tmp2 =board[movez[2]-'A'][movez[3]-48];
		
		if (movez[3] == '/' || movez[3] == '.'||movez[3] == '8'||movez[3] == ':'||movez[2]=='I'||movez[2]=='@') return 0;
		if (!is_forward(movez) || !check_jumps(movez)||move.size()!=4||tmp.is_empty()||!is_player_piece(tmp)||(!is_diag(movez)&&!isjump(movez))||!tmp2.is_empty())
			return 0;

		
		return 1;
	}
	
	bool checkers::is_forward(std::string move) const
	{
		pieces tmp =board[move[0]-'A'][move[1]-48];
		if (tmp.is_king())
				return 1;
		if (tmp.is_red()&&(move[0] - move[2])==-1)
			return 1;
		if (tmp.is_black()&&(move[0] - move[2])==1)
			return 1;
		return 0;
	}

	
	bool checkers::is_legal2(const std::string& move) const //used for the isjump function so not to cause any infinate loops 	
	{
		
		std::string movez = move;
		std::transform(movez.begin(), movez.end(),movez.begin(), ::toupper); //converts the string to all upper
		pieces tmp =board[movez[0]-'A'][movez[1]-48];
		pieces tmp2 =board[movez[2]-'A'][movez[3]-48];
		
		if (movez[3] == '/' || movez[3] == '.'||movez[3] == '8'||movez[3] == ':'||movez[2]=='I'||movez[2]=='@') return 0;
		if (!is_forward(movez) || move.size()!=4||tmp.is_empty()||!is_player_piece(tmp)||(!is_diag(movez)&&!isjump(movez))||!tmp2.is_empty())
			return 0;
		
		
		return 1;
		
	}

	bool checkers::is_player_piece(pieces piece)const //determines if the piece being moved belongs to the current mover
	{
		if (next_mover() == 2&&piece.is_red()) //RED MOVE
			return 1;
		if (next_mover() == 0&&piece.is_black()) //BLACK MOVE
			return 1;
		
		return 0;
	}
	bool checkers::is_diag(const std::string &move)const //determines if the move is diagonal
	{
		int y,x,y2,x2;
		pieces tmp =board[move[0]-'A'][move[1]-48];
		x2=(int)move[0]-'A';
		y2=(int)move[1]-48;
		x =	(int)move[2]-'A';
		y = (int)move[3]-48;

		if ((y+x)%2)//checks diag
			if (y2-y==-1 || y2-y==1) return 1; 
		return 0;
	}
	
	bool checkers::isjump(const std::string move) const //determines if the move passed is a jump
	{
		pieces tmp,final;
		int y,x,y2,x2,jumpx,jumpy;
		y=(int)move[0]-'A';
		x=(int)move[1]-48;
		y2 = (int)move[2]-'A';
		x2 = (int)move[3]-48;
		final = board[y2][x2];
		
		if ((y-y2==-2||y-y2==2))		
		{
			if (y-y2==-2) //red pieces
				jumpy = y2-1;
			else //black pieces
				jumpy = y2+1;
			if (x2 < x)
				jumpx = x2+1;
			else 
				jumpx = x2-1;
			tmp = board[jumpy][jumpx];
			if ( (tmp.is_red()&&next_mover()==0)||(tmp.is_black()&&next_mover()==2)&&final.is_empty())
				return 1;
			
		}
		return 0;
	}
	void checkers::jump(const std::string move) //jumps a piece
	{
		if (isjump(move))
		{
			int y,x,y2,x2,jumpx,jumpy;
			y=(int)move[0]-'A';
			x=(int)move[1]-48;
			y2 = (int)move[2]-'A';
			x2 = (int)move[3]-48;
			
			if ((y-y2==-2||y-y2==2))		
			{
				if (y-y2==-2) //red pieces
					jumpy = y2-1;
				else //black pieces
					jumpy = y2+1;
				if (x2 < x)
					jumpx = x2+1;
				else 
					jumpx = x2-1;
			}
			
			board[jumpy][jumpx].set_empty();
		}
		
	}
	bool checkers::can_jump(std::string move,bool was_jump)const //sees if a piece can jump after already jumping
	{
		bool flag =0;
		pieces piece = board[move[0]-'A'][move[1]-48];
		std::string topleft,topright,bottomleft,bottomright;
		topleft +=move[2]; topleft +=move[3];
		topright = bottomleft = bottomright = topleft;
		topleft += move[2]-2;topright= topleft;
		topleft += move[3]-2;topright+= move[3]+2;
		bottomleft+= move[2]+2;bottomright = bottomleft;
		bottomleft += move[3]-2;bottomright += move[3]+2;
		if (next_mover() == 0||piece.is_king())
		{
		if (is_legal(topleft)&&was_jump){flag=1;}
		if (is_legal(topright)&&was_jump){flag=1;}
		}
		if (next_mover() == 2||piece.is_king())
		{
			if (is_legal(bottomleft)&&was_jump){flag=1;}
		if (is_legal(bottomright)&&was_jump){flag=1;}
		}
		return flag;
	}

	bool checkers::check_jumps(std::string move) const //checks the passed move against all possible jumps if any returns true if is a valid move (meaning if there was a jump it was taken)
	{
		std::queue<std::string> moves;
		
		for (int i =0; i< SIZE;++i)
			for (int j=0;j<SIZE;++j)
			{
				if (is_player_piece(board[i][j]))
				{
					std::string tmp_move1,tmp_move2,tmp_move3,tmp_move4;
					char y,x,y2,x2,x3,y3;
					y = i + 'A';
					x = j+48;
					y2 = y-2; //down 2
					x2 = x+2; // right 2
					x3 = x-2; // left 2
					y3 = y+2; // up 2
					
					tmp_move1 += y;tmp_move1 += x;
					tmp_move2 = tmp_move3 = tmp_move4 = tmp_move1; 
					tmp_move1 += y2;
					tmp_move2 = tmp_move1; // black move and king move
					tmp_move1 += x2; tmp_move2 += x3; 
					tmp_move3 += y3; tmp_move4 += y3; // red move and king move
					tmp_move3 += x2; tmp_move4 += x3;
					if (isjump(tmp_move1)&&is_legal2(tmp_move1)&&(board[i][j].is_black() || board[i][j].is_king()))
						moves.push(tmp_move1);
					if (isjump(tmp_move2)&&is_legal2(tmp_move2)&&(board[i][j].is_black() || board[i][j].is_king()))
						moves.push(tmp_move2);
					if (isjump(tmp_move3)&&is_legal2(tmp_move3)&&(board[i][j].is_red() || board[i][j].is_king()))
						moves.push(tmp_move3);
					if (isjump(tmp_move4)&&is_legal2(tmp_move4)&&(board[i][j].is_red() || board[i][j].is_king()))
						moves.push(tmp_move4);
					
				}
				
			}
		
		if (moves.empty())		return 1;
		while (!moves.empty())
		{
			if (move==moves.front()) return 1;
			moves.pop();
		}
		return 0;
		
	}
		
	void checkers::compute_moves(std::queue<std::string>& moves) const
	{
		for (int i =0; i< SIZE;++i)
			for (int j=0;j<SIZE;++j)
			{
				if (is_player_piece(board[i][j]))
				{
					std::string tmp_move1,tmp_move2,tmp_move3,tmp_move4,tmp_move5,tmp_move6,tmp_move7,tmp_move8;
					char y,x,y2,x2,x3,y3,y4,y5,x4,x5;
					y = i + 'A';
					x = j+48;
					y2 = y-2; //down 2
					y3 = y+2; // up 2
					y4 = y+1; // up 1
					y5 = y-1; // down 1

					x2 = x+2; // right 2
					x3 = x-2; // left 2
					x4 = x+1; // right 1
					x5 = x-1; // left 1
					
					tmp_move1 += y;tmp_move1 += x;
					tmp_move5 = tmp_move6 = tmp_move7 = tmp_move8 = tmp_move2 = tmp_move3 = tmp_move4 = tmp_move1; 
					tmp_move1 += y2;
					tmp_move2 = tmp_move1; // black jump move and king jump move
					tmp_move1 += x2; tmp_move2 += x3; 
					tmp_move3 += y3; tmp_move4 += y3; // red jump move and king jump move
					tmp_move3 += x2; tmp_move4 += x3;
					tmp_move5 += y4; tmp_move6 = tmp_move5; //red move
					tmp_move5 += x4; tmp_move6 += x5;
					tmp_move7 += y5; tmp_move8 = tmp_move7; //black move
					tmp_move7 += x4; tmp_move8 += x5;
					if (isjump(tmp_move1)&&is_legal2(tmp_move1)&&(board[i][j].is_black() || board[i][j].is_king()))
						moves.push(tmp_move1);
					if (isjump(tmp_move2)&&is_legal2(tmp_move2)&&(board[i][j].is_black() || board[i][j].is_king()))
						moves.push(tmp_move2);
					if (isjump(tmp_move3)&&is_legal2(tmp_move3)&&(board[i][j].is_red() || board[i][j].is_king()))
						moves.push(tmp_move3);
					if (isjump(tmp_move4)&&is_legal2(tmp_move4)&&(board[i][j].is_red() || board[i][j].is_king()))
						moves.push(tmp_move4);
					if (is_legal(tmp_move5)&&(board[i][j].is_red() || board[i][j].is_king()))
						moves.push(tmp_move5);
					if (is_legal(tmp_move6)&&(board[i][j].is_red() || board[i][j].is_king()))
						moves.push(tmp_move6);
					if (is_legal(tmp_move7)&&(board[i][j].is_black() || board[i][j].is_king()))
						moves.push(tmp_move7);
					if (is_legal(tmp_move8)&&(board[i][j].is_black() || board[i][j].is_king()))
						moves.push(tmp_move8);

					
					
				}
				
			}
		
	}
	
	bool checkers::check_king(std::string move,pieces piece) const //determines if a piece if in its respecive back row and can be made into a king
	{	int tmp = (int)(move[2]-'A');
		if (tmp==0&&piece.is_black())return 1;
		if (tmp==7&&piece.is_red()) return 1;		
		return 0;
	}
	
	void checkers::move_it(const std::string &move) //actually moves the piece and takes care of figuring out if a piece need to become a king
	{
		std::string movez = move;
		std::transform(movez.begin(), movez.end(),movez.begin(), ::toupper); //converts the string to all upper
		pieces tmp = board[movez[0]-'A'][movez[1]-48];
		jump(movez);
		if (check_king(movez,tmp)) tmp.set_king();
		board[movez[0]-'A'][movez[1]-48].set_empty();
		board[movez[2]-'A'][movez[3]-48] = tmp;
		
	}
	
	bool checkers::is_game_over( ) const //determines if a game is over, returns true if it is
	{
		bool red_piece =0;
		bool black_piece =0;
		for (int i =0;i<SIZE;i++)
			for (int j=0;j<SIZE;j++)
			{
				if (board[i][j].is_red()) red_piece = 1;
				if (board[i][j].is_black()) black_piece = 1;
			}
		if (red_piece== 0 || black_piece == 0) return 1;
		return 0;
	}
	
	game* checkers::clone( ) const
	{
		return new checkers(*this);
	}
	
	int checkers::evaluate( ) const
	{
		int point_value = 0;
		for (int i =0; i< SIZE;++i)
			for (int j=0;j<SIZE;++j)
			{
				if (is_player_piece(board[i][j]))
				{
					if (board[i][j].is_king())
						point_value+=2;
					else 
						point_value+=1;
				}
				if (!is_player_piece(board[i][j])&&!(board[i][j].is_empty()))
				{
					if (board[i][j].is_king())
						point_value-=2;
					else 
						point_value-=1;
				}
			 
				
			}

		return point_value;
	}

	
	
}

