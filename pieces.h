/*
 *  pieces.h
 *  checkers
 *
 *  Created by Sam Saccone on 5/12/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef _PIECES_
#define _PIECES_
class pieces
{
	public:
	pieces(bool color=0,bool emptyy=1)
	{
		empty = 1;
		red = black = king = 0;
		if (!emptyy)
			if (color)
				red=1;
			else if (!color)
				black=1;
		else 
			empty=1;
	};
	
	//accessor functions
	bool is_king()  const {return king;};
	bool is_empty() const {return empty;};
	bool is_black() const {return black;};
	bool is_red()   const {return	red;};
	
	//mutator functions
	void set_red()        {red =1;black=0;empty=0;};
	void set_black()      {black =1;red=0;empty=0;};
	void set_king()		  {king =1;};
	void set_empty()		 {empty=1;red=0;black=0;};
	
	private:
	bool red;
	bool black;
	bool king;
	bool empty;
	
};
#endif