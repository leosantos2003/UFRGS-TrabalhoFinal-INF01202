#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

#define PLAYER_INVINCIBILITY_DURATION 1.5f

typedef struct {
    Vector2 gridPos;
    int orientation;
    int lives;
    int score;
    bool isInvincible;
    float invincibilityTimer;
    bool isDying;
} Player;

// Funções de mecânica e estado
void InitPlayerState(void);
void SetPlayerStartPosition(Vector2 startPos);
void UpdatePlayer(const char (*map)[24]); // O número 24 vem de MAP_COLS em level.h
Player *GetPlayer(void);
void DamagePlayer(Vector2 oldPos);
bool IsPlayerDead(void);

#endif // PLAYER_H