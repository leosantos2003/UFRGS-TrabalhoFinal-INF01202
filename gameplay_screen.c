#include "gameplay_screen.h"
#include "level.h"
#include "player.h"
#include "monster.h"
#include "combat.h"
#include "ui.h"
#include "renderer.h" // Novo include
#include "stdio.h"
#include "raylib.h"

int RunGameplayScreen(int level)
{
    char fileName[20];
    sprintf(fileName, "nivel%d.txt", level); // Mudar para arquivo de testes aqui
    LoadLevel(fileName); 
    
    Player *player = GetPlayer();
    Monster *monsters = GetMonsters();
    
    while (!WindowShouldClose())
    {
        // --- ATUALIZAÇÃO ---
        Vector2 oldPlayerPos = player->gridPos;
        UpdatePlayer(GetMap());
        UpdateMonsters(GetMap(), level);
        ProcessPlayerAttack(player, monsters, level);
        ProcessCollisions(player, monsters, oldPlayerPos);
        
        // --- VERIFICAÇÃO DE ESTADO ---
        //if (IsPlayerDead()) { return 0; }
        //if (!AreAnyMonstersLeft()) { return 1; }

        // --- VERIFICAÇÃO DE ESTADO ---
        if (IsPlayerDead() || !AreAnyMonstersLeft()) {
             return player->score; // Retorna a pontuação final em ambos os casos (vitória ou derrota)
        }

        // --- DESENHO ---
        BeginDrawing();
            ClearBackground(BLACK);
            
            // Chama o renderer para desenhar tudo
            DrawGameLevel();
            DrawGameMonsters(monsters);
            DrawGamePlayer(player);
            
            int attackOrientation, attackRange;
            if (IsPlayerAttacking(&attackOrientation, &attackRange))
            {
                DrawGameAttack(player, attackOrientation, attackRange);
            }
            
            DrawGameplayUI(player, level);
            
        EndDrawing();
    }
    
    return -1;
}