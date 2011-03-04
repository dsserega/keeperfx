/******************************************************************************/
// Free implementation of Bullfrog's Dungeon Keeper strategy game.
/******************************************************************************/
/** @file map_columns.c
 *     Column and columns array data management functions.
 * @par Purpose:
 *     Functions to support the column data array.
 * @par Comment:
 *     None.
 * @author   Tomasz Lis
 * @date     27 Oct 2009 - 09 Nov 2009
 * @par  Copying and copyrights:
 *     This program is free software; you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation; either version 2 of the License, or
 *     (at your option) any later version.
 */
/******************************************************************************/
#include "map_columns.h"
#include "globals.h"

#include "slab_data.h"
#include "keeperfx.hpp"

#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************************/
/******************************************************************************/
DLLIMPORT void _DK_init_columns(void);
DLLIMPORT long _DK_get_top_cube_at_pos(long mpos);
DLLIMPORT void _DK_clear_columns(void);
DLLIMPORT long _DK_find_column(struct Column *col);
DLLIMPORT long _DK_create_column(struct Column *col);
DLLIMPORT void _DK_init_top_texture_to_cube_table(void);
DLLIMPORT void _DK_init_whole_blocks(void);
/******************************************************************************/
struct Column *get_column(long idx)
{
  if ((idx < 1) || (idx >= COLUMNS_COUNT))
    return &game.columns[0];
  return &game.columns[idx];
}

struct Column *get_column_at(MapSubtlCoord stl_x, MapSubtlCoord stl_y)
{
  struct Map *map;
  map = get_map_block_at(stl_x, stl_y);
  if (map_block_invalid(map))
    return &game.columns[0];
  return &game.columns[map->data & 0x7FF];
}

struct Column *get_map_column(const struct Map *map)
{
  if (map_block_invalid(map))
    return &game.columns[0];
  return &game.columns[map->data & 0x7FF];
}

TbBool column_invalid(const struct Column *col)
{
  if (col == NULL)
    return true;
  if (col == INVALID_COLUMN)
    return true;
  return (col < &game.columns[0]);
}

long get_top_cube_at_pos(long stl_num)
{
  struct Column *col;
  struct Map *map;
  unsigned long top_pos;
  long tcube;
  //return _DK_get_top_cube_at_pos(mpos);
  map = get_map_block_at_pos(stl_num);
  col = get_map_column(map);
  top_pos = (col->bitfileds >> 4) & 0x0F;
  if (top_pos > 0)
    tcube = col->cubes[top_pos-1];
  else
    tcube = game.field_14BB65[col->baseblock];
  return tcube;
}

long get_top_cube_at(MapSubtlCoord stl_x, MapSubtlCoord stl_y)
{
  struct Column *col;
  unsigned long top_pos;
  long tcube;
  col = get_column_at(stl_x, stl_y);
  top_pos = (col->bitfileds >> 4) & 0x0F;
  if (top_pos > 0)
    tcube = col->cubes[top_pos-1];
  else
    tcube = game.field_14BB65[col->baseblock];
  return tcube;
}

void make_solidmask(struct Column *col)
{
  int i;
  col->solidmask = 0;
  for (i=0; i<COLUMN_STACK_HEIGHT; i++)
  {
    if (col->cubes[i] != 0)
      col->solidmask |= (1 << i);
  }
}

unsigned short find_column_height(struct Column *col)
{
  unsigned short h;
  h = 0;
  if (col->solidmask == 0)
    return h;
  while (col->cubes[h] > 0)
  {
    h++;
    if (h >= COLUMN_STACK_HEIGHT)
      return COLUMN_STACK_HEIGHT;
  }
  return h;
}

long get_floor_height_at(struct Coord3d *pos)
{
    const struct Map *mapblk;
    const struct Column *col;
    long i,cubes_height;
    mapblk = get_map_block_at(pos->x.val >> 8, pos->y.val >> 8);
    col = get_map_column(mapblk);
/*    if (column_invalid(col))
        return (1 << 8);*/
    cubes_height = 0;
    i = col->bitfileds;
    if ((i & 0xF0) > 0)
        cubes_height = i >> 4;
    return cubes_height << 8;
}

long find_column(struct Column *col)
{
  return _DK_find_column(col);
}

long create_column(struct Column *col)
{
  return _DK_create_column(col);
}

void clear_columns(void)
{
  //  _DK_clear_columns();
  struct Column *col;
  int i;
  for (i=0; i < COLUMNS_COUNT; i++)
  {
    col = &game.columns[i];
    memset(col, 0, sizeof(struct Column));
    col->baseblock = 1;
    make_solidmask(col);
  }
  game.field_149E6E = -1;
  game.field_149E7C = 24;
  game.field_149E77 = 0;
  for (i=0; i < 18; i++)
  {
    game.field_14A818[i] = 0;
  }
}

void init_columns(void)
{
  _DK_init_columns();
}

void init_whole_blocks(void)
{
  struct Column lcol;
  long i;
  //_DK_init_whole_blocks(); return;
  game.field_149E6E = -1;
  memset(&lcol, 0, sizeof(lcol));
  // Prepare the local column
  lcol.baseblock = 22;
  lcol.cubes[0] = 10;
  lcol.cubes[1] = 1;
  lcol.cubes[2] = 1;
  lcol.cubes[3] = 1;
  lcol.cubes[4] = 141;
  make_solidmask(&lcol);
  // Find it or add to column list
  i = find_column(&lcol);
  if (i == 0)
    i = create_column(&lcol);
  // Update its parameters
  game.columns[i].bitfileds |= 0x01;
  game.field_149E7C = 24;
  game.field_149E77 = i;
}

void init_top_texture_to_cube_table(void)
{
  _DK_init_top_texture_to_cube_table();
}

TbBool cube_is_water(long cube_id)
{
    return (cube_id == 39);
}

TbBool cube_is_lava(long cube_id)
{
    return (cube_id == 40) || (cube_id == 41);
}
/******************************************************************************/
#ifdef __cplusplus
}
#endif
