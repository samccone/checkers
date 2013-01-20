/*
 *  checkers.h
 *  checkers
 *
 *  Created by Sam Saccone on 5/7/10.
 *  Copyright 2010. All rights reserved.
 *
 */
#include "game.h"
#include <iostream>
#include "pieces.h"
namespace main_savitch_14
{
	class checkers : public game
	{
	public:
		checkers();
		static const int SIZE = 8;
	protected:
		void parse_move(std::string move) const;
		void line(pieces piece,std::string color) const;
		bool is_diag(const std::string &move) const;
		void move_it(const std::string &move);
		bool check_king(std::string move,pieces tmp) const;
		void jump(const std::string move);
		bool is_player_piece(pieces piece)const;
		bool isjump(const std::string move) const;
		bool check_jumps(std::string move) const;
		bool is_legal2(const std::string& move) const;
		bool can_jump(std::string move,bool was_jump)const;
		bool is_forward(std::string move) const; 
		void input();
		
		virtual std::string get_user_move( ) const;
		virtual game* clone( ) const;
        // Compute all the moves that the next player can make:
		virtual void compute_moves(std::queue<std::string>& moves) const;
		// Display the status of the current game:
		virtual void display_status( ) const;
		// Evaluate the current board position.
		// NOTE: Positive values are good for the computer.
		virtual int evaluate( ) const;
		// Return true if the current game is finished:
		virtual bool is_game_over( ) const;
		// Return true if the given move is legal for the next player:
		virtual bool is_legal(const std::string& move) const;
		// Have the next player make a specified move:
		virtual void make_move(const std::string& move);
		// Restart the game from the beginning:
		virtual void restart( );	
	private:
		pieces board[SIZE][SIZE];


	};
}
