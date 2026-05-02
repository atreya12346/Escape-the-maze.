              Escape The Maze 

Escape The Maze is a console-based maze navigation game developed in **C language** using **Data Structures and Algorithms** concepts such as **Stack** and **Breadth-First Search (BFS)**.

The player starts at **S (Start)** and must reach **E (Exit)** while avoiding walls (`#`). The system evaluates performance by comparing player moves with the optimal path length computed using BFS.

----------------------------------------------------------------------------------------

                  Project Objectives

- Implement stack-based undo functionality
- Apply BFS algorithm for shortest path detection
- Demonstrate 2D array manipulation
- Design an interactive terminal-based UI
- Analyze player efficiency using algorithmic comparison

----------------------------------------------------------------------------------------

 Data Structures & Algorithms Used

### Stack
Used to store movement history and enable **Undo** operation.

### Breadth-First Search (BFS)
Used to calculate the **shortest possible path** from start to exit.

### 2D Arrays
Used for representing maze layouts.

-----------------------------------------------------------

 Game Features

 Multiple difficulty levels  
 Interactive keyboard controls  
 Undo move functionality  
 Efficiency score calculation  
 Shortest path comparison  
 Console-based visual maze display  

--------------------------------------------------------

                  Controls

| Key | Action |
|-----|--------|
| W | Move Up |
| A | Move Left |
| S | Move Down |
| D | Move Right |
| U | Undo last move |
| Q | Quit game |

--------------------------------------------------

                Difficulty Levels

| Level | Grid Size | Difficulty |
|------|-----------|-----------|
| Level 1 | 6 × 6 | Easy |
| Level 2 | 10 × 10 | Medium |
| Level 3 | 14 × 14 | Hard |

---------------------------------------------------------

                Efficiency Calculation

After completing a level:

Efficiency = (Shortest Path / Moves Taken) × 100

Performance Rating:

| Efficiency | Rating |
|-----------|--------|
| 100% | PERFECT |
| 75% – 99% | GREAT |
| 50% – 74% | GOOD |
| Below 50% | NEEDS IMPROVEMENT |

--------------------------------------------------------
