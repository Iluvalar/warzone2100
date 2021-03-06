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
 *  Definitions for the base object type.
 */

#ifndef __INCLUDED_BASEDEF_H__
#define __INCLUDED_BASEDEF_H__

#include "lib/framework/vector.h"
#include "displaydef.h"
#include "statsdef.h"

//the died flag for a droid is set to this when it gets added to the non-current list
#define NOT_CURRENT_LIST 1

typedef enum _object_type
{
	OBJ_DROID,      ///< Droids
	OBJ_STRUCTURE,  ///< All Buildings
	OBJ_FEATURE,    ///< Things like roads, trees, bridges, fires
	OBJ_PROJECTILE, ///< Comes out of guns, stupid :-)
	OBJ_TARGET,     ///< for the camera tracking
	OBJ_NUM_TYPES,  ///< number of object types - MUST BE LAST
} OBJECT_TYPE;

typedef struct _tilePos
{
	UBYTE x, y;
} TILEPOS;

/*
 Coordinate system used for objects in Warzone 2100:
  x - "right"
  y - "forward"
  z - "up"

  For explanation of yaw/pitch/roll look for "flight dynamics" in your encyclopedia.
*/

#define BASE_ELEMENTS1(pointerType) \
	OBJECT_TYPE     type;                           /**< The type of object */ \
	UDWORD          id;                             /**< ID number of the object */ \
	Vector3uw       pos;                            /**< Position of the object */ \
	float           direction;                      /**< Object's yaw +ve rotation around up-axis */ \
	SWORD           pitch;                          /**< Object's pitch +ve rotation around right-axis (nose up/down) */ \
	SWORD           roll                            /**< Object's roll +ve rotation around forward-axis (left wing up/down) */

#define BASE_ELEMENTS2(pointerType) \
	SCREEN_DISP_DATA    sDisplay;                   /**< screen coordinate details */ \
	UBYTE               player;                     /**< Which player the object belongs to */ \
	UBYTE               group;                      /**< Which group selection is the droid currently in? */ \
	UBYTE               selected;                   /**< Whether the object is selected (might want this elsewhere) */ \
	UBYTE               cluster;                    /**< Which cluster the object is a member of */ \
	UBYTE               visible[MAX_PLAYERS];       /**< Whether object is visible to specific player */ \
	UDWORD              died;                       /**< When an object was destroyed, if 0 still alive */ \
	UDWORD              lastEmission;               /**< When did it last puff out smoke? */ \
	UDWORD              lastHitWeapon;		/**< The weapon that last hit it */ \
	UDWORD              timeLastHit;		/**< The time the structure was last attacked */ \
	UDWORD              body;			/**< Hit points with lame name */ \
	BOOL                inFire;                     /**< true if the object is in a fire */ \
	UDWORD              burnStart;                  /**< When the object entered the fire */ \
	UDWORD              burnDamage;                 /**< How much damage has been done since the object entered the fire */ \
	SDWORD              sensorPower;		/**< Active sensor power */ \
	SDWORD              sensorRange;		/**< Range of sensor */ \
	SDWORD              ECMMod;			/**< Ability to conceal oneself from sensors */ \
	UWORD               numWatchedTiles;		/**< Number of watched tiles, zero for features */ \
	TILEPOS             *watchedTiles;		/**< Variable size array of watched tiles, NULL for features */ \
	UDWORD              armour[NUM_HIT_SIDES][WC_NUM_WEAPON_CLASSES]

#define NEXTOBJ(pointerType) \
	pointerType     *psNext;			/**< Pointer to the next object in the object list */ \
	pointerType     *psNextFunc			/**< Pointer to the next object in the function list */

#define SIMPLE_ELEMENTS(pointerType) \
	BASE_ELEMENTS1(pointerType); \
	NEXTOBJ(pointerType)

#define BASE_ELEMENTS(pointerType) \
	SIMPLE_ELEMENTS(pointerType); \
	BASE_ELEMENTS2(pointerType)

typedef struct BASE_OBJECT
{
	BASE_ELEMENTS( struct BASE_OBJECT );
} WZ_DECL_MAY_ALIAS BASE_OBJECT;

typedef struct SIMPLE_OBJECT
{
	SIMPLE_ELEMENTS( struct SIMPLE_OBJECT );
} SIMPLE_OBJECT;

static inline bool isDead(const BASE_OBJECT* psObj)
{
	// See objmem.c for comments on the NOT_CURRENT_LIST hack
	return (psObj->died > NOT_CURRENT_LIST);
}

static inline int objPosDiffSq(Vector3uw pos1, Vector3uw pos2)
{
	const int xdiff = pos1.x - pos2.x;
	const int ydiff = pos1.y - pos2.y;
	return (xdiff * xdiff + ydiff * ydiff);
}

// Must be #included __AFTER__ the definition of BASE_OBJECT
#include "baseobject.h"

#endif // __INCLUDED_BASEDEF_H__
