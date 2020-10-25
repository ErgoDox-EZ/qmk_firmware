#ifndef SNAKE_H_INCLUDED
#define SNAKE_H_INCLUDED

#include "ssd1306.h"
#include "timer.h"
#include "stdlib.h"

#define SNAKE_BOARD_HEIGHT MatrixRows
#define SNAKE_BOARD_WIDTH  MatrixCols

enum direction {
    NONE,
    UP,
    DOWN,
    LEFT,
    RIGHT
};

typedef struct
{
    uint8_t x;
    uint8_t y;
} vec2_t;

typedef struct snake_node_
{
    vec2_t pos;
    struct snake_node_ * next;
} SnakeNode;


// typedef struct
// {
//     int dir;
//     SnakePart head;
// } SnakeHead;

uint16_t snake_key;
bool snake_new_key;
// bool snake_key_pressed;
uint16_t last_time;

SnakeNode * snake_head;
vec2_t * snake_food;

int snake_score;
// int high_score[5];

enum direction currentDirection; // in global space

bool snake_first_time;
void snake_init(void);

void snake_clear(void);
void snake_pop_back(void);
void snake_push_front(vec2_t pos);
int snake_update(void);
int snake_frame(struct CharacterMatrix *matrix);
void snake_set_direction(uint16_t keycode);
vec2_t snake_move(void);

bool snake_in_collision(vec2_t next_head);

bool snake_found_food(void);
void snake_place_food(void);

uint16_t snake_timer_period;

// vec2_t get_direction_vec(enum direction);

#endif
