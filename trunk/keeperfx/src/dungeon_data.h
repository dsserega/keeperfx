/******************************************************************************/
// Free implementation of Bullfrog's Dungeon Keeper strategy game.
/******************************************************************************/
/** @file dungeon_data.h
 *     Header file for dungeon_data.c.
 * @par Purpose:
 *     Dungeon data structures definitions.
 * @par Comment:
 *     Just a header file - #defines, typedefs, function prototypes etc.
 * @author   Tomasz Lis
 * @date     10 Nov 2009 - 20 Jan 2010
 * @par  Copying and copyrights:
 *     This program is free software; you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation; either version 2 of the License, or
 *     (at your option) any later version.
 */
/******************************************************************************/
#ifndef DK_DNGN_DATA_H
#define DK_DNGN_DATA_H

#include "bflib_basics.h"
#include "globals.h"
#include "engine_camera.h"
#include "thing_creature.h"
#include "thing_doors.h"
#include "room_data.h"
#include "player_data.h"
#include "map_events.h"
#include "tasks_list.h"

#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************************/
#define DUNGEONS_COUNT          5
#define IMP_TASK_MAX_COUNT     64
#define TRAP_TYPES_COUNT        7
#define DUNGEON_RESEARCH_COUNT 34
#define MAX_THINGS_IN_HAND      8
#define KEEPER_SPELLS_COUNT    20
#define TURN_TIMERS_COUNT       8
#define SCRIPT_FLAGS_COUNT      8
#define MAX_SOE_RADIUS         13
#define CREATURE_GUI_JOBS_COUNT 3

#define INVALID_DUNGEON (&bad_dungeon)

enum DungeonCreatureTendencies {
    CrTend_None       = 0,
    CrTend_Imprison   = 1,
    CrTend_Flee       = 2,
};

enum DungeonResearchCategory {
    RsCat_None        = 0,
    RsCat_Power       = 1,
    RsCat_Room        = 2,
    RsCat_Creature    = 3,
};

#pragma pack(1)

struct DiggerStack { // sizeof = 4
      unsigned short field_0;
      unsigned short task_id;
};

struct LevelStats { // sizeof = 392
  unsigned long things_researched;
  unsigned long field_4;
  unsigned long field_8;
  unsigned long field_C;
  unsigned long field_10;
  unsigned long field_14;
  unsigned long field_18;
  unsigned long field_1C;
  unsigned long field_20;
  unsigned long field_24;
  unsigned long field_28;
  unsigned long field_2C;
  unsigned long field_30;
  unsigned long field_34;
  unsigned long field_38;
  unsigned long field_3C;
  unsigned long field_40;
  unsigned long field_44;
  unsigned long field_48;
  unsigned long field_4C;
  unsigned long field_50;
  unsigned long field_54;
  unsigned long field_58;
  unsigned long field_5C;
  unsigned long field_60;
  unsigned long field_64;
  unsigned long field_68;
  unsigned long field_6C;
  unsigned long field_70;
  unsigned long field_74;
  unsigned long field_78;
  unsigned long field_7C;
  unsigned long field_80;
  unsigned long field_84;
  unsigned long field_88;
  unsigned long gold_mined;
  unsigned long field_90;
  unsigned long manufactured_doors;
  unsigned long manufactured_traps;
  unsigned long manufactured_items;
  unsigned long start_time;
  unsigned long end_time;
  unsigned long creatures_trained;
  unsigned long creatures_tortured;
  unsigned long creatures_sacrificed;
  unsigned long creatures_converted;
  unsigned long creatures_summoned;
  unsigned long num_slaps;
  unsigned long num_caveins;
  unsigned long bridges_built;
  unsigned long rock_dug_out;
  unsigned long salary_cost;
  unsigned long flies_killed_by_spiders;
  unsigned long territory_destroyed;
  unsigned long territory_lost;
  unsigned long rooms_constructed;
  unsigned long traps_used;
  unsigned long traps_armed;
  unsigned long doors_used;
  unsigned long keepers_destroyed;
  unsigned long area_claimed;
  unsigned long backs_stabbed;
  unsigned long chickens_hatched;
  unsigned long chickens_eaten;
  unsigned long chickens_wasted;
  unsigned long promises_broken;
  unsigned long ghosts_raised;
  unsigned long skeletons_raised;
  unsigned long friendly_kills;
  unsigned long lies_told;
  unsigned long creatures_annoyed;
  unsigned long graveyard_bodys;
  unsigned long vamps_created;
  unsigned long num_creatures;
  unsigned long imps_deployed;
  unsigned long battles_won;
  unsigned long battles_lost;
  unsigned long money;
  unsigned long dngn_breached_count;
  unsigned long doors_destroyed;
  unsigned long rooms_destroyed;
  unsigned long dungeon_area;
  unsigned long ideas_researched;
  unsigned long creatures_scavenged;
  unsigned long creatures_from_sacrifice;
  unsigned long spells_stolen;
  unsigned long gold_pots_stolen;
  unsigned long average_room_efficiency;
  unsigned long player_rating;
  unsigned long player_style;
  unsigned long doors_unused;
  unsigned long traps_unused;
  unsigned long num_rooms;
  unsigned long gameplay_time;
  unsigned long num_entrances;
  unsigned long hopes_dashed;
  unsigned long allow_save_score;
  unsigned long player_score;
};

struct ResearchVal { // sizeof = 6
  unsigned char rtyp;
  unsigned char rkind;
  long req_amount;
};

struct TurnTimer { // sizeof = 5
  unsigned long count;
  unsigned char state;
};

#define SIZEOF_Dungeon 0x1508
struct Dungeon {
    unsigned short dnheart_idx;
    struct Coord3d mappos;
    unsigned char creature_tendencies;
    unsigned char field_9;
    unsigned char computer_enabled;
    unsigned short room_kind[ROOM_TYPES_COUNT];
    short creatr_list_start;
    short digger_list_start;
    short field_31;
    short things_in_hand[MAX_THINGS_IN_HAND];
    short field_43;
    int field_45;
    int field_49;
    int field_4D;
    short field_51;
    short field_53;
    int field_55;
    int field_59;
    int field_5D;
    short field_61;
    unsigned char field_63;
    short field_64[480];
    unsigned short job_breeds_count[CREATURE_TYPES_COUNT][3];
    unsigned short field_4E4[CREATURE_TYPES_COUNT][3];
    short field_5A4[15];
    unsigned char room_slabs_count[ROOM_TYPES_COUNT+1];
    int field_5D4;
    short keeper_sight_thing_idx;
    unsigned char field_5DA;
    unsigned char sight_casted_stl_x;
    unsigned char sight_casted_stl_y;
    unsigned char soe_explored_flags[2*MAX_SOE_RADIUS][2*MAX_SOE_RADIUS];
    unsigned char field_881;
    unsigned char field_882;
    unsigned char field_883;
    int field_884;
    int field_888;
    int field_88C[10];
    unsigned char creatures_praying[CREATURE_TYPES_COUNT];
    unsigned char chickens_sacrificed;
    unsigned char field_8D5;
    unsigned char creature_sacrifice[CREATURE_TYPES_COUNT];
    unsigned char creature_sacrifice_exp[CREATURE_TYPES_COUNT];
    unsigned char field_916[2];
    unsigned char num_active_diggers;
    unsigned char num_active_creatrs;
    unsigned char owned_creatures_of_model[32];
    unsigned char buildable_rooms_count;
    unsigned short total_doors;
    unsigned short total_area;
    unsigned short total_creatures_left;
    int field_941;
    int doors_destroyed;
    short field_949;
    short field_94B[32];
    short creatures_scavenged;
    short creatures_summoned;
    short field_98F[96];
    int creature_max_level[CREATURE_TYPES_COUNT];
    unsigned short creatures_annoyed;
    unsigned short battles_lost;
    unsigned short battles_won;
    unsigned short rooms_destroyed;
    unsigned short spells_stolen;
    unsigned short times_broken_into;
    unsigned short gold_pots_stolen;
    int last_entrance_generation_gameturn;
    int turns_between_entrance_generation;
    int field_AE5;
    int field_AE9[3];
    short field_AF5;
    short field_AF7;
    int total_money_owned;
    int offmap_money_owned;
    short hates_player[DUNGEONS_COUNT];
    struct MapTask task_list[MAPTASKS_COUNT];
    int field_E8F;
    int field_E93[3];
    unsigned char owner;
    int camera_deviate_quake;
    int camera_deviate_jump;
    long score;
    struct ResearchVal research[DUNGEON_RESEARCH_COUNT];
    int field_F78;
    unsigned char research_num;
unsigned char field_F7D;
    unsigned char room_buildable[ROOM_TYPES_COUNT];
    unsigned char room_resrchable[ROOM_TYPES_COUNT];
    unsigned char creature_enabled[CREATURE_TYPES_COUNT]; // 'Enabled' creature can come from portal
    unsigned char creature_allowed[CREATURE_TYPES_COUNT]; // 'Allowed' creature is conditionally enabled
    unsigned char magic_level[KEEPER_SPELLS_COUNT];
    unsigned char magic_resrchable[KEEPER_SPELLS_COUNT];
    /** Amount of traps of every kind for which we can place blueprints. */
    unsigned char trap_amount[TRAP_TYPES_COUNT];
    /** Stored information if we can manufacture traps of specific kind. */
    unsigned char trap_buildable[TRAP_TYPES_COUNT];
    /** Stored information if we can place blueprints of traps of specific kind. */
    unsigned char trap_placeable[TRAP_TYPES_COUNT];
    unsigned char door_amount[DOOR_TYPES_COUNT]; // Amount of doors the player can place
    unsigned char door_buildable[DOOR_TYPES_COUNT]; // Door can be build in workshop
    unsigned char door_placeable[DOOR_TYPES_COUNT]; // Door is enabled in GUI panel
    struct TurnTimer turn_timers[TURN_TIMERS_COUNT];
    unsigned char script_flags[SCRIPT_FLAGS_COUNT];
    long max_creatures_attracted;
    unsigned char field_1060[5];
    struct Coord3d pos_1065;
    struct DiggerStack imp_stack[IMP_TASK_MAX_COUNT];
    unsigned long digger_stack_update_turn;
    unsigned long digger_stack_length;
    unsigned char visible_event_idx;
    unsigned char field_1174;
    unsigned char field_1175;
    unsigned char field_1176;
    short zoom_annoyed_creature_idx;
    long total_experience_creatures_gained;
    long total_research_points;
long field_1181;
    long manufacture_progress;
    unsigned char manufacture_class;
    unsigned char manufacture_kind;
long field_118B;
long manufacture_level;
long field_1193;
    struct LevelStats lvstats;
    struct CreatureStorage dead_creatures[DEAD_CREATURES_MAX_COUNT];
    long dead_creatures_count;
    long dead_creature_idx;
    unsigned char field_13A7[EVENT_BUTTONS_COUNT+1];
    long field_13B4[EVENT_KIND_COUNT]; // warning: missing 4 bytes!
unsigned short tortured_creatures[32];
unsigned char bodies_rotten_for_vampire;
unsigned char field_1461[36];
    long field_1485;
unsigned char field_1489[32];
unsigned long fights_num;
unsigned char research_override; // could be easily changed into flags..
int field_14AE;
unsigned char field_14B2[2];
int field_14B4;
int field_14B8;
unsigned char field_14BC[6];
    /** Index of last creature picked up of given model. */
    unsigned short selected_creatures_of_model[CREATURE_TYPES_COUNT];
    /** Index of last creature picked up of given GUI Job. */
    unsigned short selected_creatures_of_gui_job[CREATURE_GUI_JOBS_COUNT];
    };

#pragma pack()
/******************************************************************************/
extern struct Dungeon bad_dungeon;
/******************************************************************************/
struct Dungeon *get_players_num_dungeon_ptr(long plyr_idx,const char *func_name);
struct Dungeon *get_players_dungeon_ptr(struct PlayerInfo *player,const char *func_name);
struct Dungeon *get_dungeon_ptr(PlayerNumber plyr_num,const char *func_name);
#define get_players_num_dungeon(plyr_idx) get_players_num_dungeon_ptr(plyr_idx,__func__)
#define get_players_dungeon(player) get_players_dungeon_ptr(player,__func__)
#define get_dungeon(plyr_idx) get_dungeon_ptr(plyr_idx,__func__)
#define get_my_dungeon() get_players_num_dungeon_ptr(my_player_number,__func__)

TbBool dungeon_invalid(struct Dungeon *dungeon);

void clear_dungeons(void);
void decrease_dungeon_area(unsigned char plyr_idx, long value);
void increase_room_area(unsigned char plyr_idx, long value);
void decrease_room_area(unsigned char plyr_idx, long value);
void increase_dungeon_area(unsigned char plyr_idx, long value);
void player_add_offmap_gold(long plyr_idx, long value);
TbBool player_has_room(long plyr_idx, RoomKind rkind);
TbBool dungeon_has_room(struct Dungeon *dungeon, RoomKind rkind);
TbBool set_creature_tendencies(struct PlayerInfo *player, unsigned short tend_type, TbBool val);
TbBool toggle_creature_tendencies(struct PlayerInfo *player, unsigned short tend_type);
TbBool player_creature_tends_to(long plyr_idx, unsigned short tend_type);
TbBool set_trap_buildable_and_add_to_amount(long plyr_idx, long trap_kind, long buildable, long amount);
TbBool set_door_buildable_and_add_to_amount(long plyr_idx, long door_kind, long buildable, long amount);

TbBool restart_script_timer(long plyr_idx, long timer_id);
TbBool set_script_flag(long plyr_idx, long flag_id, long value);

/******************************************************************************/
#ifdef __cplusplus
}
#endif
#endif
