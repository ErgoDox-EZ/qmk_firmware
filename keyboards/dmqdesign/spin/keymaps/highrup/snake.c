#include "snake.h"

void snake_init(void)
{
    timer_init();
    last_time = timer_read();
    snake_timer_period = 500;

    snake_head = (SnakeNode*)malloc(sizeof(SnakeNode));
    snake_food = (vec2_t*)malloc(sizeof(vec2_t));
    // Initialize the snake head and one body part
    // The snake is essentially a linked list
    snake_head->pos.x = SNAKE_BOARD_WIDTH/2 - 1;
    snake_head->pos.y = SNAKE_BOARD_HEIGHT/2 - 1;
    // snake_head->pos.x = 3;
    // snake_head->pos.y = 1;
    snake_head->next = NULL;

    vec2_t tmp;

    tmp.x = MatrixCols/2;
    tmp.y = MatrixRows/2 - 1;
    snake_push_front(tmp);

    // tmp.x = MatrixCols/2 + 1;
    // tmp.y = MatrixRows/2 - 1;
    // snake_push_front(tmp);

    currentDirection = RIGHT;

    // Spawn food
    // snake_food->x = 2;
    // snake_food->y = 1;

    // snake_food->x = rand() % SNAKE_BOARD_WIDTH;
    // snake_food->y = rand() % SNAKE_BOARD_HEIGHT;
    snake_place_food();

    return;
}

void snake_place_food(void)
{
    snake_food->x = -1;
    snake_food->y = -1;

    while (snake_in_collision(*snake_food))
    {
        snake_food->x = rand() % SNAKE_BOARD_WIDTH;
        snake_food->y = rand() % SNAKE_BOARD_HEIGHT;
    }
}

void snake_clear(void)
{
    while (snake_head->next != NULL)
    {
        snake_pop_back();
    }
}

void snake_pop_back(void)
{
    SnakeNode * tmp = snake_head;
    SnakeNode * secondToLast = snake_head;

    while (tmp->next != NULL)
    {
        secondToLast = tmp;
        tmp = tmp->next;
    }

    secondToLast->next = NULL;
    free(tmp);
}

void snake_push_front(vec2_t pos)
{
    SnakeNode * newHead = (SnakeNode*)malloc(sizeof(SnakeNode));
    newHead->next = snake_head;
    newHead->pos.x = pos.x;
    newHead->pos.y = pos.y;
    snake_head = newHead;
}

void snake_set_direction(uint16_t keycode)
{
    // The keycode is a local direction and can be either left or right relative to the direction,
    // the snake is already moving.

    switch (currentDirection)
    {
    case UP:
        if (snake_key == KC_LEFT)
        {
            currentDirection = LEFT;
        }
        else if (snake_key == KC_RIGHT)
        {
            currentDirection = RIGHT;
        }
        break;

    case DOWN:
        if (snake_key == KC_LEFT)
        {
            currentDirection = RIGHT;
        }
        else if (snake_key == KC_RIGHT)
        {
            currentDirection = LEFT;
        }
        break;

    case LEFT:
        if (snake_key == KC_LEFT)
        {
            currentDirection = DOWN;
        }
        else if (snake_key == KC_RIGHT)
        {
            currentDirection = UP;
        }
        break;

    case RIGHT:
        if (snake_key == KC_LEFT)
        {
            currentDirection = UP;
        }
        else if (snake_key == KC_RIGHT)
        {
            currentDirection = DOWN;
        }
        break;

    default:
        break;
    }
}

vec2_t snake_move(void)
{ // Moves the snake one step in the currentDirection
    vec2_t move;

    switch (currentDirection)
    {
    case UP:
        move.x = snake_head->pos.x;
        move.y = snake_head->pos.y - 1;
        break;

    case RIGHT:
        move.x = snake_head->pos.x + 1;
        move.y = snake_head->pos.y;
        break;

    case DOWN:
        move.x = snake_head->pos.x;
        move.y = snake_head->pos.y + 1;
        break;

    case LEFT:
        move.x = snake_head->pos.x - 1;
        move.y = snake_head->pos.y;
        break;

    default:
        move.x = 0;
        move.y = 0;
        break;
    }

    return move;
}

bool snake_found_food(void)
{
    if (snake_food != NULL)
    {
        return (snake_head->pos.x == snake_food->x) && (snake_head->pos.y == snake_food->y);
    }
    else
    {
        return false;
    }
}

bool snake_in_collision(vec2_t next_head)
{
    bool col = (next_head.x < 0) | (next_head.x > SNAKE_BOARD_WIDTH - 1) |
               (next_head.y < 0) | (next_head.y > SNAKE_BOARD_HEIGHT - 1);

    // Check for collision with self
    SnakeNode * tmp = snake_head;

    while (tmp->next != NULL)
    {
        if ((next_head.x == tmp->next->pos.x) && (next_head.y == tmp->next->pos.y))
        {
            col = true;
            break;
        }
        tmp = tmp->next;
    }

    return col;
}

int snake_update(void)
{
    if (timer_elapsed(last_time) < snake_timer_period) // if time elapsed is larger than 500 ms, then do something
    {
        return 0;
    }

    // if (snake_key_pressed)
    if (snake_new_key)
    {
        snake_new_key = false;
        snake_set_direction(snake_key);
    }

    vec2_t move = snake_move();

    // Check if new head is outside border of game or it hit itself.
    if (snake_in_collision(move))
    {
        snake_clear();
        snake_first_time = true; // restart the game
        return 0;
    }

    // Add a new head.
    snake_push_front(move);

    if (snake_found_food())
    // if((snake_head->pos.x == 2) & (snake_head->pos.y == 2))
    {
        snake_score++;

        snake_place_food();

        if (snake_timer_period > 100)
        {
            snake_timer_period -= 20;
        }
    }
    else
    {
        // Delete the tail
        snake_pop_back();
    }

    last_time = timer_read();

    return 1;
}

int snake_frame(struct CharacterMatrix *matrix)
{
    if (snake_first_time)
    {
        snake_init();
        snake_first_time = false;
        snake_score = 0;

        // snake_food->x = rand() % SNAKE_BOARD_WIDTH;
        // snake_food->y = rand() % SNAKE_BOARD_HEIGHT;
        // snake_food->x = 4;
        // snake_food->y = 2;
    }

    snake_update();

    // matrix_clear(matrix);
    // // Test output
    // snprintf(snake_string, sizeof(snake_string), "x: %d", head.pos.x);
    // matrix_write_ln(matrix, snake_string);

    // snprintf(snake_string, sizeof(snake_string), "y: %d", head.pos.y);
    // matrix_write_ln(matrix, snake_string);

    // matrix_write_char(matrix, 0xFF);

    // Draw the head
    // matrix->display[i][0] = 0x07;

    matrix_clear(matrix);

    // char snake_string[24];

    // snprintf(snake_string, sizeof(snake_string), "x: %d, y: %d", snake_head->pos.x, snake_head->pos.y);
    // matrix_write_ln(matrix, snake_string);

    // Updates the snake positions
    SnakeNode * tmp = snake_head;
    while (tmp != NULL)
    {
        matrix->display[tmp->pos.y][tmp->pos.x] = 0x2A;
        // snprintf(snake_string, sizeof(snake_string), "x: %d, y: %d", tmp->pos.x, tmp->pos.y);
        // matrix_write_ln(matrix, snake_string);
        tmp = tmp->next;
    }

    // Draw score
    char str[3];
    sprintf(str, "%d", snake_score);
    matrix_write(matrix, str);

    // draw food
    if (snake_food != NULL)
    {
        matrix->display[snake_food->y][snake_food->x] = 0x03;
    }

    // matrix->display[0][0] = 0x02;
    // matrix->display[1][1] = 0x02;
    // matrix->display[2][2] = 0x02;
    // matrix->display[2][3] = 0x02;

    // snake_food->x = 4;
    // snake_food->y = 2;

    // matrix->display[food->y][food->x] = 0x03;

    // snprintf(snake_string, sizeof(snake_string), "x%d y%d", snake_food->x, snake_food->y);
    // snprintf(snake_string, sizeof(snake_string), "x%d y%d, x%d y%d", snake_head->pos.x, snake_head->pos.y, food->x, food->y);
    // snprintf(snake_string, sizeof(snake_string), "x%d y%d, x%d y%d", snake_head->pos.x, snake_head->pos.y, rand() % SNAKE_BOARD_HEIGHT, rand() % SNAKE_BOARD_WIDTH);
    // snprintf(snake_string, sizeof(snake_string), "x%d y%d", rand() % SNAKE_BOARD_WIDTH, rand() % SNAKE_BOARD_HEIGHT);
    // matrix_write_ln(matrix, snake_string);

    return 1;
}
