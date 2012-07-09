/******************************************************************************/
// Free implementation of Bullfrog's Dungeon Keeper strategy game.
/******************************************************************************/
/** @file creature_battle.h
 *     Header file for creature_battle.c.
 * @par Purpose:
 *     Creature battle structure and utility functions.
 * @par Comment:
 *     Just a header file - #defines, typedefs, function prototypes etc.
 * @author   KeeperFX Team
 * @date     23 Jul 2011 - 05 Sep 2011
 * @par  Copying and copyrights:
 *     This program is free software; you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation; either version 2 of the License, or
 *     (at your option) any later version.
 */
/******************************************************************************/
#ifndef DK_CRTRBATTLE_H
#define DK_CRTRBATTLE_H

#include "bflib_basics.h"
#include "globals.h"

#ifdef __cplusplus
extern "C" {
#endif

/** Max amount of battles supported on any map. */
#define BATTLES_COUNT       48
/******************************************************************************/
#pragma pack(1)

struct Thing;

struct CreatureBattle { // sizeof = 17
  unsigned long fighters_num;
  unsigned char field_4[9];
  unsigned short first_creatr;
  unsigned short last_creatr;
};

#pragma pack()
/******************************************************************************/
#define INVALID_CRTR_BATTLE (&game.battles[0])

struct CreatureBattle *creature_battle_get(long battle_idx);
struct CreatureBattle *creature_battle_get_from_thing(const struct Thing *thing);
TbBool creature_battle_invalid(const struct CreatureBattle *battle);

void setup_combat_flee_position(struct Thing *thing);
void set_creature_in_combat(struct Thing *fighter, struct Thing *enemy, long possible_combat);
long get_combat_state_for_combat(struct Thing *fighter, struct Thing *enemy, long possible_combat);

/******************************************************************************/
#ifdef __cplusplus
}
#endif
#endif
