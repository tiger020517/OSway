#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "Console.h"

//#define SYNCHRONIZE

#define TRUE 1
#define FALSE 0

#define ESC 27
#define DRAW 1
#define ERASE 0

int home_x = 1, home_y = 1;

typedef struct {
    char warhead;
    float x, y;
    float dx, dy;
    int height;
    int max_x, max_y;
    pthread_t tid;
} Missile;

void* MoveMissile(void *vparam);
int DrawMissile(Missile *m, int erase);

int main() {
    static char key_list[] = "asdfghjkl;\'";
    int no_key = strlen(key_list);

    int screen_width = getWindowWidth();
    int screen_height = getWindowHeight() - 3;

    home_x = 1;
    home_y = screen_height + 1;

    clrscr();
    EnableCursor(FALSE);

    while (TRUE) {
        if (kbhit()) {
            int k = getch();
            if (k == ESC)
                break;

            char *p = strchr(key_list, k);
            if (p) {
                int idx = p - key_list;

                Missile *m = (Missile*)malloc(sizeof(Missile));
                if (m == NULL) {
                    PrintXY(home_x, home_y, "Memory allocation failed!");
                    continue;
                }

                m->warhead = k;
                m->x = screen_width * (idx + 1) / (no_key + 1);
                m->y = screen_height - 2;
                m->dx = 0;
                m->dy = -1;
                m->height = 2;
                m->max_x = screen_width;
                m->max_y = screen_height;
                m->tid = 0;

                pthread_create(&(m->tid), NULL, MoveMissile, (void*)m);

            } else if (k == ' ') {
                for (int i = 0; i < no_key; i++) {
                    Missile *m = (Missile*)malloc(sizeof(Missile));
                    if (m == NULL) {
                        PrintXY(home_x, home_y, "Memory allocation failed!");
                        continue;
                    }

                    m->warhead = '^';
                    m->x = screen_width * (i + 1) / (no_key + 1);
                    m->y = screen_height - 2;
                    m->dx = 0;
                    m->dy = -1;
                    m->height = 2;
                    m->max_x = screen_width;
                    m->max_y = screen_height;
                    m->tid = 0;

                    pthread_create(&(m->tid), NULL, MoveMissile, (void*)m);
                }
            }
        }

#ifdef SYNCHRONIZE
        LockDisplay();
#endif
        gotoxy(home_x, home_y);
        fflush(stdout);
#ifdef SYNCHRONIZE
        UnlockDisplay();
#endif

        MySleep(10);
    }

    gotoxy(1, screen_height);
    printf("Bye!\n");
    fflush(stdout);

    return 0;
}

void* MoveMissile(void *vparam) {
    Missile *m = (Missile *)vparam;

    DrawMissile(m, DRAW);

    while (1) {
        DrawMissile(m, ERASE);

        m->x += m->dx;
        m->y += m->dy;

        if (!DrawMissile(m, DRAW))
            break;

#ifdef SYNCHRONIZE
        LockDisplay();
#endif
        gotoxy(home_x, home_y);
        fflush(stdout);
#ifdef SYNCHRONIZE
        UnlockDisplay();
#endif

        MySleep(50);
    }

    free(m);  // 메모리 해제
    return NULL;
}

int DrawMissile(Missile *m, int flag) {
    if (m->x < 1 || m->x > m->max_x || m->y < 1 || m->y + m->height - 1 > m->max_y)
        return FALSE;

#ifdef SYNCHRONIZE
    LockDisplay();
#endif

    for (int i = 0; i < m->height; i++) {
        gotoxy((int)(m->x + 0.5F), (int)(m->y + i + 0.5F));
        if (flag == DRAW)
            putchar((i == 0) ? m->warhead : '|');
        else
            putchar(' ');
    }

    gotoxy(home_x, home_y);
    fflush(stdout);

#ifdef SYNCHRONIZE
    UnlockDisplay();
#endif

    return TRUE;
}
