#include "smm_common.h"
#include "smm_object.h"
#include <string.h>


#define MAX_NODETYPE    7
#define MAX_NODE        100
// Array to store names corresponding to node types
static char smmNodeName[SMMNODE_TYPE_MAX][MAX_CHARNAME] = {
       "LECTURE",
       "RESTAURANT",
       "LABORATORY",
       "HOME",
       "GOTOLAB",
       "FOODCHANCE",
       "FESTIVAL"
};


// Function to get the name of a node type
char* smmObj_getTypeName(int type)
{
    return (char*)smmNodeName[type];
}

//2. 구조체 배열 변수 정의 
//static smmObject_t smm_node[MAX_NODE];
//static int smmObj_noNode = 0;

//3. 관련 함수 변경 
//object generation
smmObject_t* smmObj_genObject(const char* name, smmObjType_e objType, int type, int credit, int energy, int charge, smmObjGrade_e grade)
{    
    smmObject_t* ptr;

    ptr = (smmObject_t*)malloc(sizeof(smmObject_t));

    if (ptr != NULL) {
    	 // Copy name, ensuring null-termination
        strncpy(ptr->name, name, MAX_CHARNAME - 1);
        ptr->name[MAX_CHARNAME - 1] = '\0'; // 문자열 종료를 보장
        ptr->objType = objType;
        ptr->type = type;
        ptr->credit = credit;
        ptr->energy = energy;
        ptr->charge = charge;
        ptr->grade = grade;
    }

    return ptr;
}

//3. 관련 함수 변경 
// Function to get the name of a node from an object
const char* smmObj_getNodeName(const void* obj)
{
    const smmObject_t* ptr = (const smmObject_t*)obj;
    return ptr->name;
}

// Function to generate a random grade
smmObjGrade_e smmObjGrade_rand() {
    // Randomly select a value from smmObjGrade_e
    int randomValue = rand() % (smmObjGrade_Cm + 1);  // Generate a random value from 0 to Cm

    // Convert the integer value to smmObjGrade_e and return
    return (smmObjGrade_e)randomValue;
}

//3. 관련 함수 변경 

// Function to get the type of a node from an object
// nodePtr: smmObject_t 구조체를 가리키는 포인터 
int smmObj_getNodeType(const smmObject_t* nodePtr)
{
    return nodePtr->type;
}


// Function to get the credit value of a node from an object
// nodePtr: smmObject_t 구조체를 가리키는 포인터
int smmObj_getNodeCredit(const smmObject_t* nodePtr)
{
    return nodePtr->credit;
}

// Function to get the energy value of a node from an object
// nodePtr: smmObject_t 구조체를 가리키는 포인터  
int smmObj_getNodeEnergy(const smmObject_t* nodePtr)
{
    return nodePtr->energy;
}

// Function to get the charge value of a node from an object
// nodePtr: smmObject_t 구조체를 가리키는 포인터  
int smmObj_getNodeCharge(const smmObject_t* nodePtr)
{
    return nodePtr->charge;
}
