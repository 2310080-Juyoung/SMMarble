#include <time.h>
#include <string.h>
#include "smm_object.h"
#include "smm_database.h"
#include "smm_common.h"

#define MAX_GRADE	9
#define BOARDFILEPATH "marbleBoardConfig.txt"
#define FOODFILEPATH "marbleFoodConfig.txt"
#define FESTFILEPATH "marbleFestivalConfig.txt"



//board configuration parameters
static int board_nr;
static int food_nr;
static int festival_nr;

static int player_nr;
  

typedef struct player {
	int energy;
	int position;
	char name[MAX_CHARNAME];
	int accumCredit;
	int flag_graduate;
} player_t;

static player_t *cur_player;
//static player_t cur_player[MAX_PLAYER];
 
#if 0
static int player_energy[MAX_PLAYER];
static int player_position[MAX_PLAYER];
static char player_name[MAX_PLAYER][MAX_CHARNAME];
#endif

//function prototypes
#if 0
int isGraduated(void); //check if any player is graduated
//print grade history of player
void goForward(int player, int step); //make player go "step" steps on the board (check if player is graduated)
void printPlayerStatus(void); //print all player status at the beginning of each turn
float calcAverageGrade(int player); //calculate average grade of the player
smmGrade_e takeLecture(int player, char *lectureName, int credit); //take the lecture (insert a grade of the player)
void* findGrade(int player, char *lectureName); //find the grade from the player's grade history
void printGrades(int player); //print all the grade history of the player

#endif

// Function to print the opening message
void opening(void){
    printf("\n\n~~+~~+~~+~~+~~+~~+~~+~~+~~+~~+~~+~~+~~+~~+~~+~~+~~+~~+~~+~~+~~+~~+~~+~~+~~+~~+~~+\n");
    printf("             !!Sookmyung Marble!! Let's Graduate (total credit : 30)             \n");
    printf("~~+~~+~~+~~+~~+~~+~~+~~+~~+~~+~~+~~+~~+~~+~~+~~+~~+~~+~~+~~+~~+~~+~~+~~+~~+~~+~~+\n\n\n");
}


// Function to print grades of a player
void printGrades(int player){
    int i;
    void* gradePtr;
    for (i = 0; i < smmdb_len(LISTNO_OFFSET_GRADE + player); i++)
    {
        gradePtr = smmdb_getData(LISTNO_OFFSET_GRADE + player, i);
        printf("%s : %i\n", smmObj_getNodeName(gradePtr), actionNode(gradePtr));
    }
}

// Function to generate new players
void generatePlayers(int n, int initEnergy) {
    int i;
    // n time loop
    for (i = 0; i < n; i++)
    {
        // Input name
        printf("Input player %i's name:", i); // Prompt
        scanf("%s", cur_player[i].name);
        fflush(stdin);
  
        // Set position
        cur_player[i].position = 0;
         
        // Set energy
        cur_player[i].energy = initEnergy;
        cur_player[i].accumCredit = 0;
        cur_player[i].flag_graduate = 0;
    }
}

// Function to print player status
void printPlayerStatus(int player){
    void* currentNode = smmdb_getData(LISTNO_NODE, cur_player[player].position);

    printf("%s at %i. %s, credit %i, energy %i\n", cur_player[player].name, cur_player[player].position, smmObj_getNodeName(currentNode), cur_player[player].accumCredit, cur_player[player].energy);
	
}

// Function to simulate rolling a die
int rolldie(int player) {
    char c;
    int turn=0;
    printf("This is %s's turn ::::Press any key to roll a die (press g to see grade): ",cur_player[turn].name);
    c = getchar();
    fflush(stdin);
    
    // Print grades if 'g' is pressed
    if (c == 'g')
        printGrades(player);
    
    return (rand() % MAX_DIE + 1);
}

//action code when a player stays at a node
void actionNode(int player)
{
	void *boardPtr = smmdb_getData(LISTNO_NODE, cur_player[player].position );

	int type = smmObj_getNodeType( boardPtr );
	const char* name = smmObj_getNodeName(boardPtr);

	switch(type)
	{
    //case lecture:
    case SMMNODE_TYPE_LECTURE:
        
        if(cur_player[player].energy >= smmObj_getNodeEnergy(boardPtr)){
            cur_player[player].accumCredit += smmObj_getNodeCredit(boardPtr);
            cur_player[player].energy -= smmObj_getNodeEnergy(boardPtr);

            // grade generation
            smmObject_t* gradePtr = (smmObject_t*)smmObj_genObject(name, smmObjType_grade, 0, smmObj_getNodeCredit(boardPtr), 0, smmObjGrade_rand());
            smmdb_addTail(LISTNO_OFFSET_GRADE + player, gradePtr);
        }
        break;
    default:
        break;
	}
}		

// Function to make a player go forward
void goForward(int player, int step) {
    void* boardPtr;
    cur_player[player].position += step;
    boardPtr = smmdb_getData(LISTNO_NODE, cur_player[player].position);
    printf("Player %s go to node %i (name:%s)\n", cur_player[player].name, cur_player[player].position, smmObj_getNodeName(boardPtr));
}

int main(int argc, const char * argv[]) {
    
    FILE* fp;
    char name[MAX_CHARNAME];
    int type;
    int credit;
    int energy;
    int charge;
    int i;
    int initEnergy=18;
    int turn=0;

    board_nr = 0;
    food_nr = 0;
    festival_nr = 0;
    
    srand(time(NULL));
    
    //1. import parameters ---------------------------------------------------------------------------------
    //1-1. boardConfig 
    if ((fp = fopen(BOARDFILEPATH,"r")) == NULL)
    {
        printf("[ERROR] failed to open %s. This file should be in the same directory of SMMarble.exe.\n", BOARDFILEPATH);
        getchar();
        return -1;
    }
    
    printf("Reading board component......\n");
    while ( fscanf(fp, "%s %i %i %i", name, &type, &credit, &energy) == 4 ) //read a node parameter set
    {
        //store the parameter set
        
        // Generate a board object and store the parameter set in the linked list
		smmObject_t* boardObj = smmObj_genObject(name, smmObjType_board, type, credit, energy, 0);
        smmdb_addTail(LISTNO_NODE, boardObj);
        
        // If the node type is SMMNODE_TYPE_HOME, store the initial energy value
        if (type == SMMNODE_TYPE_HOME)
           initEnergy = energy;
        board_nr++;
    }
    fclose(fp);
    
	// Display information about each board node
    for (i = 0;i<board_nr;i++)
    {
        void* boardObj = smmdb_getData(LISTNO_NODE, i);

        printf("node %i : %s, %i(%s), credit %i, energy %i\n", i, smmObj_getNodeName(boardObj), smmObj_getNodeType(boardObj), smmObj_getTypeName(smmObj_getNodeType(boardObj)), smmObj_getNodeCredit(boardObj), smmObj_getNodeEnergy(boardObj));
    }
    printf("Total number of board nodes : %i\n", board_nr);
    //printf("(%s)", smmObj_getTypeName(SMMNODE_TYPE_LECTURE));
	
    //2. food card config 
    if ((fp = fopen(FOODFILEPATH,"r")) == NULL)
    {
        printf("[ERROR] failed to open %s. This file should be in the same directory of SMMarble.exe.\n", FOODFILEPATH);
        return -1;
    } 
    
    printf("\n\nReading food card component......\n");
    while (fscanf(fp, "%s %i ", name, &charge) == 2 ) //read a food parameter set
    {
        //store the parameter set
        
         // Generate a food card object and store the parameter set in the linked list
        smmObject_t* boardObj = smmObj_genObject(name, 0, 0, 0, 0, charge, 0);
        smmdb_addTail(LISTNO_FOODCARD, boardObj);
        food_nr++;
    }
    fclose(fp);
    
    // Display information about each food card
    for (i = 0;i<food_nr;i++)
    {
        void* boardObj = smmdb_getData(LISTNO_FOODCARD, i);

        printf("%i. %s, charge: %i\n", i, smmObj_getNodeName(boardObj), smmObj_getNodeCharge(boardObj));
    }
    printf("Total number of food cards : %i\n", food_nr);
    
    
    //3. festival card config 
    if ((fp = fopen(FESTFILEPATH,"r")) == NULL)
    {
        printf("[ERROR] failed to open %s. This file should be in the same directory of SMMarble.exe.\n", FESTFILEPATH);
        return -1;
    }
    
    printf("\n\nReading festival card component......\n");
    while (fscanf(fp, "%s", name) == 1 ) //read a festival card string
    {
        //store the parameter set

		// Generate a festival card object and store the parameter set in the linked list        
		smmObject_t* boardObj = smmObj_genObject(name, 0);
        smmdb_addTail(LISTNO_FESTCARD, boardObj);
        
        festival_nr++;
    }
    fclose(fp);
	
	// Display information about each festival card
    for (i = 0;i<festival_nr;i++)
    {
        void* boardObj = smmdb_getData(LISTNO_FESTCARD, i);

        printf("%i. %s\n", i, smmObj_getNodeName(boardObj));
    }
    printf("Total number of festival cards : %i\n", festival_nr);

	//0.opening
    opening();
    
    //1-2 grade
	smmObjGrade_rand();
	
    //2. Player configuration ---------------------------------------------------------------------------------
    
    do
    {
        //input player number to player_nr
        printf("Input player no. (1 ~ 10):");
        scanf("%d", &player_nr);
        fflush(stdin);
    }
    while (player_nr < 0 || player_nr >  MAX_PLAYER);
	
	cur_player = (player_t*)malloc(player_nr*sizeof(player_t));
    generatePlayers(player_nr, initEnergy);


    //3. SM Marble game starts ---------------------------------------------------------------------------------
    while (1) //is anybody graduated?
    {
        int die_result;
        
        
        //4-1. initial printing
        printf("\n========================== PLAYER STATUS ==========================\n");
        for (i = 0; i < player_nr; i++)
    		printPlayerStatus(i);
    	printf("========================== PLAYER STATUS ==========================\n\n");
        
        //4-2. die rolling (if not in experiment) 
		die_result=rolldie(turn);       
        
        //4-3. go forward
        goForward(turn,die_result);
        
		//4-4. take action at the destination node of the board
        actionNode(turn);
        
        //4-5. next turn
        turn=(turn+1)%player_nr;
    }

	free(cur_player);
    return 0;
}
