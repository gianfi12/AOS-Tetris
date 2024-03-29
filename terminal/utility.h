#ifndef UTILITY_H
#define UTILITY_H

#include <atomic>

using namespace std;

/* Define here used global variables */
extern atomic<bool> isDone;

/* Key mapping defintion */
#define ARROW_UP 65
#define ARROW_DOWN 66
#define ARROW_LEFT 68
#define ARROW_RIGHT 67
#define NULL_CHAR " "
#define A 97
#define S 115

/* Modify here to change the mapped key */
#define ROTATE_LEFT A
#define ROTATE_RIGHT S
#define MOVE_LEFT ARROW_LEFT
#define MOVE_RIGHT ARROW_RIGHT
#define MOVE_DOWN ARROW_DOWN
#define ESCAPE 113 //press q to exit the game
#define ESC 27
#define CTRLC 3
#define ENTER 13

/* Terminal settings defintion, modify here to change the resolution */
#define COL_TETRIS 65
#define ROW_TETRIS 45

#define BLK "\e[0;30m"
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define YEL "\e[0;33m"
#define BLU "\e[0;34m"
#define MAG "\e[0;35m"
#define CYN "\e[0;36m" 
#define WHT "\e[0;37m"
#define RSTCLR "\e[0;0m"


//Regular bold text
#define BBLK "\e[1;30m"
#define BRED "\e[1;31m"
#define BGRN "\e[1;32m"
#define BYEL "\e[1;33m"
#define BBLU "\e[1;34m"
#define BMAG "\e[1;35m"
#define BCYN "\e[1;36m" 
#define BWHT "\e[1;37m"

//Regular underline text
#define UBLK "\e[4;30m"
#define URED "\e[4;31m"
#define UGRN "\e[4;32m"
#define UYEL "\e[4;33m" 
#define UBLU "\e[4;34m"
#define UMAG "\e[4;35m"
#define UCYN "\e[4;36m" 
#define UWHT "\e[4;37m"

//Regular background
#define BLKB "\e[40m"
#define REDB "\e[41m"
#define GRNB "\e[42m"
#define YELB "\e[43m"
#define BLUB "\e[44m"
#define MAGB "\e[45m"
#define CYNB "\e[46m"
#define WHTB "\e[47m"

//High intensty background
#define BLKHB "\e[0;100m"
#define REDHB "\e[0;101m"
#define GRNHB "\e[0;102m"
#define YELHB "\e[0;103m"
#define BLUHB "\e[0;104m"
#define MAGHB "\e[0;105m"
#define CYNHB "\e[0;106m" 
#define WHTHB "\e[0;107m"

//High intensty text
#define HBLK "\e[0;90m"
#define HRED "\e[0;91m"
#define HGRN "\e[0;92m"
#define HYEL "\e[0;93m"
#define HBLU "\e[0;94m"
#define HMAG "\e[0;95m"
#define HCYN "\e[0;96m" 
#define HWHT "\e[0;97m"

//Bold high intensity text
#define BHBLK "\e[1;90m"
#define BHRED "\e[1;91m"
#define BHGRN "\e[1;92m"
#define BHYEL "\e[1;93m"
#define BHBLU "\e[1;94m"
#define BHMAG "\e[1;95m"
#define BHCYN "\e[1;96m"
#define BHWHT "\e[1;97m"
 
//Reset
#define RESET_CHAR "\e[0m"


//Character
#define BLOCK_MENU "\u2588"
#define BLOCK "\u2598"

#define GRID_OFFSET 5
#define SPAWN_OFFSET 4


#endif 