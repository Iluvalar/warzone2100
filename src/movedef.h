/*
	This file is part of Warzone 2100.
	Copyright (C) 1999-2004  Eidos Interactive
	Copyright (C) 2005-2011  Warzone 2100 Project

	Warzone 2100 is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.

	Warzone 2100 is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with Warzone 2100; if not, write to the Free Software
	Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
*/
/** \file
 *  Definitions for movement tracking.
 */

#ifndef __INCLUDED_MOVEDEF_H__
#define __INCLUDED_MOVEDEF_H__

//Watermelon:num of VTOL weapons should be same as DROID_MAXWEAPS
#define VTOL_MAXWEAPS		3

typedef struct _move_control
{
	UBYTE	Status;						// Inactive, Navigating or moving point to point status
	UBYTE	Position;	   				// Position in asPath
	UBYTE	numPoints;					// number of points in asPath
	Vector2i *asPath;					// Pointer to list of block X,Y map coordinates.
	SDWORD	DestinationX, DestinationY;			// World coordinates of movement destination
	SDWORD	srcX,srcY,targetX,targetY;

	/* Stuff for John's movement update */
	float	fx,fy;						// droid location as a fract
	float	speed;						// Speed of motion
	SWORD	boundX,boundY;				// Vector for the end of path boundary

	float	moveDir;						// direction of motion (not the direction the droid is facing)
	SWORD	bumpDir;					// direction at last bump
	UDWORD	bumpTime;					// time of first bump with something
	UWORD	lastBump;					// time of last bump with a droid - relative to bumpTime
	UWORD	pauseTime;					// when MOVEPAUSE started - relative to bumpTime
	UWORD	bumpX,bumpY;				// position of last bump

	UDWORD	shuffleStart;				// when a shuffle started

	struct _formation	*psFormation;			// formation the droid is currently a member of

	/* vtol movement - GJ */
	SWORD	iVertSpeed;

	// iAttackRuns tracks the amount of ammunition a VTOL has remaining for each weapon
	UDWORD	iAttackRuns[VTOL_MAXWEAPS];

	// added for vtol movement
	float	fz;
} MOVE_CONTROL;

#endif // __INCLUDED_MOVEDEF_H__
