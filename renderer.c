#include "renderer.h"
#include "level.h" // Precisa das constantes do mapa (TILE_SIZE, etc)
#include "raylib.h"

// Estrutura para guardar todas as texturas do jogo
static struct {
    Texture2D link_front, link_back, link_left, link_right;
    Texture2D enemy_front, enemy_back, enemy_left, enemy_right;
    Texture2D ground, obstacle;
    Texture2D attack_up, attack_down, attack_left, attack_right;
} gameTextures;

void InitRenderer(void)
{
    // Carrega TUDO que é visual aqui
    gameTextures.link_front = LoadTexture("resources/Link_front.png");
    gameTextures.link_back = LoadTexture("resources/Link_back.png");
    gameTextures.link_left = LoadTexture("resources/Link_left.png");
    gameTextures.link_right = LoadTexture("resources/Link_right.png");
    
    gameTextures.enemy_front = LoadTexture("resources/Enemy_front.png");
    gameTextures.enemy_back = LoadTexture("resources/Enemy_back.png");
    gameTextures.enemy_left = LoadTexture("resources/Enemy_left.png");
    gameTextures.enemy_right = LoadTexture("resources/Enemy_right.png");
    
    gameTextures.ground = LoadTexture("resources/Ground.png");
    gameTextures.obstacle = LoadTexture("resources/Obstacle.png");
    
    gameTextures.attack_up = LoadTexture("resources/Attack_up.png");
    gameTextures.attack_down = LoadTexture("resources/Attack_down.png");
    gameTextures.attack_left = LoadTexture("resources/Attack_left.png");
    gameTextures.attack_right = LoadTexture("resources/Attack_right.png");
}

void UnloadRenderer(void)
{
    // Descarrega TUDO
    UnloadTexture(gameTextures.link_front);
    UnloadTexture(gameTextures.link_back);
    // ... descarregar todas as outras texturas ...
}

void DrawGameLevel(void)
{
    const char (*map)[MAP_COLS] = GetMap();
    for (int r = 0; r < MAP_ROWS; r++)
    {
        for (int c = 0; c < MAP_COLS; c++)
        {
            Vector2 tilePos = { (float)c * TILE_SIZE, (float)r * TILE_SIZE + 60 };
            Texture2D texture = (map[r][c] == 'P') ? gameTextures.obstacle : gameTextures.ground;
            DrawTextureV(texture, tilePos, WHITE);
        }
    }
}

void DrawGamePlayer(const Player *player)
{
    Texture2D playerTex;
    if(player->orientation == 0) playerTex = gameTextures.link_front;
    else if(player->orientation == 1) playerTex = gameTextures.link_back;
    else if(player->orientation == 2) playerTex = gameTextures.link_left;
    else playerTex = gameTextures.link_right;

    Vector2 playerPixelPos = { player->gridPos.x * TILE_SIZE, player->gridPos.y * TILE_SIZE + 60 };

    if (player->isInvincible)
    {
        if ((int)(player->invincibilityTimer * 10) % 2 != 0)
        {
            DrawTextureV(playerTex, playerPixelPos, WHITE);
        }
    }
    else
    {
        DrawTextureV(playerTex, playerPixelPos, WHITE);
    }
}

void DrawGameMonsters(const Monster monsters[])
{
    for (int i = 0; i < MAX_MONSTERS; i++)
    {
        if (monsters[i].active)
        {
            Texture2D monsterTex;
            if(monsters[i].orientation == 0) monsterTex = gameTextures.enemy_front;
            else if(monsters[i].orientation == 1) monsterTex = gameTextures.enemy_back;
            else if(monsters[i].orientation == 2) monsterTex = gameTextures.enemy_left;
            else monsterTex = gameTextures.enemy_right;
            
            Color tint = monsters[i].isDying ? RED : WHITE;
            DrawTextureV(monsterTex, (Vector2){ monsters[i].gridPos.x * TILE_SIZE, monsters[i].gridPos.y * TILE_SIZE + 60 }, tint);
        }
    }
}

void DrawGameAttack(const Player *player, int orientation, int range)
{
    Texture2D swordTex;
    if(orientation == 0) swordTex = gameTextures.attack_down;
    else if(orientation == 1) swordTex = gameTextures.attack_up;
    else if(orientation == 2) swordTex = gameTextures.attack_left;
    else swordTex = gameTextures.attack_right;

    for (int step = 1; step <= range; step++)
    {
        Vector2 swordPos = player->gridPos;
        if(orientation == 0) swordPos.y += step;
        else if(orientation == 1) swordPos.y -= step;
        else if(orientation == 2) swordPos.x -= step;
        else if(orientation == 3) swordPos.x += step;

        DrawTextureV(swordTex, (Vector2){swordPos.x * TILE_SIZE, swordPos.y * TILE_SIZE + 60}, WHITE);
    }
}