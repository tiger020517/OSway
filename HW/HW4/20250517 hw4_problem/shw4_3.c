#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "Console.h"

//#define SYNCHRONIZE

#define ESC 27
#define DRAW 1
#define ERASE 0

typedef struct {
    int x, y;
    int dx, dy;
    int max_x, max_y;
} Fighter;

typedef struct {
    float x, y;
    float dx, dy;
    int height;
    int max_x, max_y;
    pthread_t tid;
} Missile;

Fighter fighter;

void DrawFighter(int flag);
void* MoveMissile(void* param);
int DrawMissile(Missile* m, int flag);

int main() {
    int w = getWindowWidth();
    int h = getWindowHeight() - 3;

    clrscr();
    EnableCursor(0);

    fighter.x = w / 2;
    fighter.y = h;
    fighter.dx = 0;
    fighter.dy = 0;
    fighter.max_x = w;
    fighter.max_y = h;

    while (1) {
        if (kbhit()) {
            int ch = getch();
            if (ch == ESC) break;

            // 방향 제어
            if (ch == 'j') { fighter.dx = -1; fighter.dy = 0; }
            else if (ch == 'l') { fighter.dx = 1; fighter.dy = 0; }
            else if (ch == 'i') { fighter.dx = 0; fighter.dy = -1; }
            else if (ch == 'k') { fighter.dx = 0; fighter.dy = 1; }
            else if (ch == ' ') {
                // 미사일 생성
                Missile* m = (Missile*)malloc(sizeof(Missile));
                if (!m) continue;
                m->x = fighter.x;
                m->y = fighter.y - 1;
                m->dx = 0;
                m->dy = -1;
                m->height = 2;
                m->max_x = fighter.max_x;
                m->max_y = fighter.max_y;
                pthread_create(&(m->tid), NULL, MoveMissile, (void*)m);
            } else {
                fighter.dx = 0;
                fighter.dy = 0;
            }
        }

        // 전투기 이동
        DrawFighter(ERASE);
        fighter.x += fighter.dx;
        fighter.y += fighter.dy;

        // 화면 경계 체크
        if (fighter.x < 2) fighter.x = 2;
        if (fighter.x > fighter.max_x - 1) fighter.x = fighter.max_x - 1;
        if (fighter.y < 1) fighter.y = 1;
        if (fighter.y > fighter.max_y) fighter.y = fighter.max_y;

        DrawFighter(DRAW);

        MySleep(50);
    }

    gotoxy(1, fighter.max_y);
    printf("Bye!\n");
    fflush(stdout);
    return 0;
}

void DrawFighter(int flag) {
#ifdef SYNCHRONIZE
    LockDisplay();
#endif
    gotoxy(fighter.x - 1, fighter.y);
    if (flag == DRAW) printf("<^>");
    else printf("   ");
    fflush(stdout);
#ifdef SYNCHRONIZE
    UnlockDisplay();
#endif
}

void* MoveMissile(void* param) {
    Missile* m = (Missile*)param;
    DrawMissile(m, DRAW);

    while (1) {
        DrawMissile(m, ERASE);
        m->x += m->dx;
        m->y += m->dy;

        if (!DrawMissile(m, DRAW)) break;

#ifdef SYNCHRONIZE
        LockDisplay();
#endif
        gotoxy(1, m->max_y + 2);
        fflush(stdout);
#ifdef SYNCHRONIZE
        UnlockDisplay();
#endif
        MySleep(50);
    }

    free(m);
    return NULL;
}

int DrawMissile(Missile* m, int flag) {
    if (m->x < 1 || m->x > m->max_x || m->y < 1 || m->y + m->height - 1 > m->max_y)
        return 0;

#ifdef SYNCHRONIZE
    LockDisplay();
#endif
    for (int i = 0; i < m->height; i++) {
        gotoxy((int)(m->x + 0.5F), (int)(m->y + i + 0.5F));
        if (flag == DRAW)
            putchar((i == 0) ? '^' : '|');
        else
            putchar(' ');
    }
    fflush(stdout);
#ifdef SYNCHRONIZE
    UnlockDisplay();
#endif
    return 1;
}
