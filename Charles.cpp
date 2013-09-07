#include "Robot.h"
/*
	Karel is a framework for manipulating with Karel the robot.
	Karel is a subclass of ROBOT from the library Robot.
	Last Modified:	September 16 2006, by Pieter Koopman, RU Nijmegen
	With some additions: September 12 2007, by Ger Paulussen & Peter Achten
	More additions: August 21 2013, by Peter Achten
*/


// =========================================================================

// Here are the examples that have been explained during the lecture
void take_3_steps ()
{
    step () ;
    step () ;
    step () ;
}

void swap_ball ()
{
    if (on_ball ())
        get_ball () ;
    else
	    put_ball () ;
    step () ;
}

// put_a_ball_somewhere adds a single ball to Charles' world on a random location
void put_a_ball_somewhere ()
{
    int lane   = 1 + rand () % (WereldHoogte  - 2) ;
    int street = 1 + rand () % (WereldBreedte - 2) ;
    create_ball (street, lane) ;
}

// make_church creates a Church-like shape of walls
void make_church ()
{
    place_rectangle (10,10,20,8) ;
    place_rectangle (10,18, 4,4) ;
    place_walls (12,22,4,false) ;
    place_walls (11,25,2,true) ;
}

// turn_north makes Charles look north
void turn_north ()
{
    while (!north())
        turn_left();
}

void turn_around ()
{
    turn_left() ;
    turn_left() ;
}
// walk_to_wall makes Charles walk ahead and stop immediately before the wall
void walk_to_wall ()
{
    while (!in_front_of_wall())
        step () ;
}

// go_to_north_west_corner makes Charles move to north-west corner and look to the east
// it is assumed that that there are only the exterior walls
void go_to_north_west_corner ()
{
    turn_north() ;
    walk_to_wall() ;
    turn_left() ;
    walk_to_wall() ;
    turn_around() ;
}

// sweep_lane makes Charles walk ahead until it is on top of a ball or immediately before a wall
void sweep_lane ()
{
    while (!in_front_of_wall())
    {
        step();
        if (on_ball())
        {
            get_ball();
        }

    }
}

// Charles has to walk back to his position of departure (lane 15, street 1)
void go_back_to_point_of_departure ()
{
	turn_north();   //Richting het Noorden draaien.
	walk_to_wall(); //Loop naar de bovenste muur.
	turn_left();    //Draai naar links.
    walk_to_wall(); //Loop naar de linker muur.
    turn_left();    //Draai naar links.
    steps(13);      //Charles bevindt zich in laan 2. Hij moet naar laan 15. Hij moet nu 13 lanen langsgaan (dus 13 stappen zetten).
    turn_left();    //Draai naar links om in de startrichting te komen.
}

// go_down_east_if_not_on_ball moves Charles one lane to the south if he is not on a ball.
// it is assumed that Charles is facing east and is not on the southernmost lane
void go_down_east_if_not_on_ball ()
{
    if (!on_ball())
    {
        turn_right() ;
        step() ;
        if (on_ball())
        {
            get_ball();
        }
        turn_right() ;
    }
}

// go_down_west_if_not_on_ball moves Charles one lane to the south if he is not on a ball.
// it is assumed that Charles is facing west and is not on the southernmost lane
void go_down_west_if_not_on_ball ()
{
    if (!on_ball())
    {
        turn_left () ;
        if (!in_front_of_wall())
        {
            step () ;
            if (on_ball)
            {
                get_ball;
            }
            turn_left () ;
        }
    }
}

// sweep_lanes makes Charles move to the east and find the ball, followed by
// going on lane south and moving to the west to find the ball.
// Assumptions: Charles is standing at the north-west corner and is looking east, there are only the exterior walls, and a ball is present.
// Result:      Charles is standing on the ball
void sweep_lanes ()
{
    while (!on_ball() && !in_front_of_wall())
    {
        sweep_lane () ;
        go_down_east_if_not_on_ball () ;
        sweep_lane () ;
        go_down_west_if_not_on_ball () ;
    }
}

// This example has been discussed during the lecture
// The effect of this function is that Charles will search for a ball in its universe.
// Assumptions: Charles is standing on its base position, there are only the exterior walls, and a ball is present.
// Result:      Charles is standing on the ball.
void find_ball ()
{
    go_to_north_west_corner() ;
    sweep_lanes() ;
}

// here starts the part with code to be completed by the students

// Name / student number / study student 1 :
// Name / student number / study student 2 :



void back_to_departure ()
{
    int lanes   = 1 + rand () % ((WereldHoogte - 3)/2) ;
    int streets = 1 + rand () % (WereldBreedte - 2) ;
    bool up = static_cast<bool>(rand () % 2);

    reset () ;
    steps (streets) ;
    if (up)
        turn_right () ;
    else
        turn_left () ;
    steps (lanes) ;
    go_back_to_point_of_departure() ;
}

void clean_balls  ()                        //Functie om Charles ballen op te laten ruimen.
{
    while(on_ball() && !in_front_of_wall()) //Kijkt of Charles op een bal staat en of hij niet voor een muur staat. Beide condities moeten gelden.
        {
            get_ball();                     //Charles pakt een bal op
            step();                         //Charles zet een stap
        }
}

void clean_string_with_balls ()
{
    make_string_with_balls ();      //Er wordt een string van ballen gemaakt.
    turn_right();                   //Draai naar rechts.
        while(in_front_of_wall())   //Kijkt of Charles voor een muur staat.
            {
                turn_left();        //Draai naar links.
                clean_balls();
            }

}
// give one or more comment lines about what will happen in this function
void clean_chaos_with_balls ()
{
	make_chaos_with_balls () ;
    go_to_north_west_corner ();
    sweep_lanes();
    turn_around();
    steps(13);
    turn_right();
}

// give one or more comment lines about what will happen in this function
void rondje_om_de_kerk ()
{
    make_church () ;
    // give your own code completion
}

// Charles searches for the ball and remains there
void start ()
{
	put_a_ball_somewhere () ;
	find_ball () ;
}

// end of part with code to be completed by students
// =========================================================================


void quick  () { rest(    1); };
void normal () { rest(dInit); };
void slow   () { rest(  250); };
void very_slow  () { rest( 1000); };

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
    Menu charles_menu ((char*)"Charles") ;
    charles_menu.add ((char*)"Clean", reset)
                .add ((char*)"Stop",  stop) ;

	Menu l1_menu ((char*)"Examples Lecture 1");
	l1_menu.add ((char*)"Steps",take_3_steps)
	       .add ((char*)"Swap ball",swap_ball)
	       .add ((char*)"Find ball",start);

	Menu a1_menu ((char*)"Assignment 1");
	a1_menu.add ((char*)"ing back to point of departure..", back_to_departure )
		   .add ((char*)"Balls: a string..", clean_string_with_balls )
		   .add ((char*)"Balls: chaos..", clean_chaos_with_balls )
		   .add ((char*)"Bonus: rondje om de kerk...", rondje_om_de_kerk );

	Menu sn_menu ((char*)"Velocity");
	sn_menu.add ((char*)"Quick", quick)
		   .add ((char*)"Normal",normal)
		   .add ((char*)"Slow",slow)
		   .add ((char*)"Very slow",very_slow);

	try
	{
		karelsWereld().Run (charles_menu,WINARGS(hInstance, hPrevInstance, szCmdLine, iCmdShow));
	}
	catch (IllegaleActie dezeIllegaleActie )
	{
		dezeIllegaleActie.report ();
	}
	catch (...)
	{
		makeAlert ("Something went terrible wrong!");
	}

	return 0;
}
