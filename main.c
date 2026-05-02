#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK  1024
#define WALL       '#'
#define PATH       '.'
#define START      'S'
#define END        'E'
#define PLAYER     '@'
#define VISITED    '*'


typedef struct {
    int rows, cols;
    char grid[16][16];   
} Level;


typedef struct {
    int r, c;
} Pos;

typedef struct {
    Pos data[MAX_STACK];
    int top;
} Stack;

void stack_init(Stack *s)            { s->top = 0; }
int  stack_empty(Stack *s)           { return s->top == 0; }
void stack_push(Stack *s, Pos p)     { if (s->top < MAX_STACK) s->data[s->top++] = p; }
Pos  stack_pop(Stack *s)             { return s->data[--s->top]; }
Pos  stack_peek(Stack *s)            { return s->data[s->top - 1]; }


void init_level1(Level *L) {
    L->rows = 6; L->cols = 6;
    const char *rows[6] = {
        "S.#...",
        "#..#.#",
        "...#..",
        ".##..#",
        "..#.##",
        "#....E"
    };
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 6; j++)
            L->grid[i][j] = rows[i][j];
}

void init_level2(Level *L) {
    L->rows = 10; L->cols = 10;
    const char *rows[10] = {
        "S.........",
        "#.#.#.##.#",
        "#.....#...",
        "#.#.##.#.#",
        "....#....#",
        ".##.#.##.#",
        "....#.....",
        "#.##.##.#.",
        "#..##...##",
        "##...##..E"
    };
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            L->grid[i][j] = rows[i][j];
}

void init_level3(Level *L) {
    L->rows = 14; L->cols = 14;
    const char *rows[14] = {
        "S....###....##",
        "#.#...........",
        "#.#.##.##..#.#",
        "#...#...##....",
        "...##.###.##..",
        "#..#..#..#.#..",
        "#.#..##.###.#.",
        "..#..##.#..#..",
        "#.#.#..##.#..#",
        "..#.......#...",
        "#.#..##.###.##",
        "....##.#....#.",
        "#.#.###.#.#..#",
        "....#..#.#...E"
    };
    for (int i = 0; i < 14; i++)
        for (int j = 0; j < 14; j++)
            L->grid[i][j] = rows[i][j];
}


void clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void print_border(int cols) {
    printf("+");
    for (int j = 0; j < cols; j++) printf("--");
    printf("+\n");
}

void display(Level *L, int pr, int pc) {
    printf("\n");
    print_border(L->cols);
    for (int i = 0; i < L->rows; i++) {
        printf("|");
        for (int j = 0; j < L->cols; j++) {
            char ch = L->grid[i][j];
            if (i == pr && j == pc)      printf(" @");
            else if (ch == '#')          printf(" #");
            else if (ch == 'S')          printf(" S");
            else if (ch == 'E')          printf(" E");
            else if (ch == '*')          printf(" *");
            else                         printf(" .");
        }
        printf(" |\n");
    }
    print_border(L->cols);
}


int bfs_shortest(Level *L) {
    int dist[16][16];
    memset(dist, -1, sizeof(dist));
    int qr[256], qc[256], head = 0, tail = 0;
    int dr[] = {-1,1,0,0}, dc[] = {0,0,-1,1};

    dist[0][0] = 0;
    qr[tail] = 0; qc[tail++] = 0;

    while (head < tail) {
        int r = qr[head], c = qc[head++];
        if (r == L->rows-1 && c == L->cols-1) return dist[r][c];
        for (int d = 0; d < 4; d++) {
            int nr = r+dr[d], nc = c+dc[d];
            if (nr<0||nr>=L->rows||nc<0||nc>=L->cols) continue;
            if (L->grid[nr][nc]=='#') continue;
            if (dist[nr][nc] != -1) continue;
            dist[nr][nc] = dist[r][c]+1;
            qr[tail] = nr; qc[tail++] = nc;
        }
    }
    return -1; 
}


void show_efficiency(int moves_taken, int shortest) {
    printf("\n╔══════════════════════════════╗\n");
    printf("║      EFFICIENCY REPORT       ║\n");
    printf("╠══════════════════════════════╣\n");
    printf("║  Your moves   : %-4d         ║\n", moves_taken);
    printf("║  Optimal path : %-4d         ║\n", shortest);
    if (shortest > 0) {
        int efficiency = (shortest * 100) / moves_taken;
        printf("║  Efficiency   : %3d%%         ║\n", efficiency);
        if (efficiency == 100)
            printf("║  Rating       : PERFECT!     ║\n");
        else if (efficiency >= 75)
            printf("║  Rating       : Great        ║\n");
        else if (efficiency >= 50)
            printf("║  Rating       : Good         ║\n");
        else
            printf("║  Rating       : Keep practicing!║\n");
    }
    printf("╚══════════════════════════════╝\n");
}


int play_level(Level *L, int level_num) {
    int pr = 0, pc = 0;   
    Stack history;
    stack_init(&history);
    stack_push(&history, (Pos){0,0});

    int moves = 0;
    int shortest = bfs_shortest(L);

    
    if (L->grid[0][0] == 'S') L->grid[0][0] = '.';

    while (1) {
        clear_screen();
        printf("╔══════════════════════════════════════╗\n");
        printf("║          ESCAPE THE MAZE             ║\n");
        printf("╠══════════════════════════════════════╣\n");
        printf("║  Level %d  │  Moves: %-4d             ║\n", level_num, moves);
        printf("║  Controls: W A S D │ U=Undo │ Q=Quit ║\n");
        printf("║  Legend:  @ You  # Wall  * Visited   ║\n");
        printf("║           S Start  E Exit            ║\n");
        printf("╚══════════════════════════════════════╝\n");

        display(L, pr, pc);

        
        if (pr == L->rows-1 && pc == L->cols-1) {
            printf("\n🎉  CONGRATULATIONS! You escaped the maze!\n");
            show_efficiency(moves, shortest);
            printf("\nPress ENTER to continue...");
            while (getchar() != '\n');
            return 1;
        }

        printf("\nMove (W/A/S/D), U=Undo, Q=Quit: ");
        char input[8];
        if (!fgets(input, sizeof(input), stdin)) continue;
        char cmd = input[0];

        if (cmd == 'q' || cmd == 'Q') return 0;

        if (cmd == 'u' || cmd == 'U') {
            if (stack_empty(&history) || history.top == 1) {
                printf("  Nothing to undo!\n");
                printf("  Press ENTER..."); while(getchar()!='\n');
                continue;
            }
            
            stack_pop(&history);
            Pos prev = stack_peek(&history);
            
            if (L->grid[pr][pc] != 'E') L->grid[pr][pc] = '*'; 
            pr = prev.r; pc = prev.c;
            moves++;  
            continue;
        }

        int nr = pr, nc = pc;
        if      (cmd=='w'||cmd=='W') nr--;
        else if (cmd=='s'||cmd=='S') nr++;
        else if (cmd=='a'||cmd=='A') nc--;
        else if (cmd=='d'||cmd=='D') nc++;
        else { printf("  Invalid key!\n"); printf("  Press ENTER..."); while(getchar()!='\n'); continue; }

        
        if (nr < 0 || nr >= L->rows || nc < 0 || nc >= L->cols) {
            printf("  Can't move there — out of bounds!\n");
            printf("  Press ENTER..."); while(getchar()!='\n'); continue;
        }

        if (L->grid[nr][nc] == '#') {
            printf("  Blocked by a wall!\n");
            printf("  Press ENTER..."); while(getchar()!='\n'); continue;
        }


        if (pr != 0 || pc != 0) L->grid[pr][pc] = '*';

        pr = nr; pc = nc;
        stack_push(&history, (Pos){pr,pc});
        moves++;
    }
}


int main() {
    while (1) {
        clear_screen();
        printf("\n");
        printf("  ╔══════════════════════════════════╗\n");
        printf("  ║         ESCAPE  THE  MAZE        ║\n");
        printf("  ╠══════════════════════════════════╣\n");
        printf("  ║  1. Level 1 — Easy   (6×6)       ║\n");
        printf("  ║  2. Level 2 — Medium (10×10)     ║\n");
        printf("  ║  3. Level 3 — Hard   (14×14)     ║\n");
        printf("  ║  4. Exit                         ║\n");
        printf("  ╚══════════════════════════════════╝\n");
        printf("\n  Choose an option: ");

        char input[8];
        if (!fgets(input, sizeof(input), stdin)) continue;
        int choice = input[0] - '0';

        if (choice == 4) {
            printf("\n  Thanks for playing! Goodbye \n\n");
            break;
        }
        if (choice < 1 || choice > 3) {
            printf("  Invalid choice!\n");
            continue;
        }

        Level L;
        if      (choice == 1) init_level1(&L);
        else if (choice == 2) init_level2(&L);
        else                  init_level3(&L);

        play_level(&L, choice);
    }
    return 0;
}

