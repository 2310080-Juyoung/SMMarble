#include "smm_common.h"
#include "smm_object.h"
#include "smm_database.h"

#include <string.h>


#define MAX_NODETYPE    8
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
const char* getGradeString(smmObjGrade_e grade) {
    switch (grade) {
        case smmObjGrade_Ap:
            return "A+";
        case smmObjGrade_A0:
            return "A0";
        case smmObjGrade_Am:
            return "A-";
        case smmObjGrade_Bp:
            return "B+";
        case smmObjGrade_B0:
            return "B0";
        case smmObjGrade_Bm:
            return "B-";
        case smmObjGrade_Cp:
            return "C+";
        case smmObjGrade_C0:
            return "C0";
        case smmObjGrade_Cm:
            return "C-";
        default:
            return "Unknown Grade";
    }
}

double getNumericValue(smmObjGrade_e grade) {
    switch (grade) {
        case smmObjGrade_Ap:
            return 4.30;
        case smmObjGrade_A0:
            return 4.00;
        case smmObjGrade_Am:
            return 3.70;
        case smmObjGrade_Bp:
            return 3.40;
        case smmObjGrade_B0:
            return 3.10;
        case smmObjGrade_Bm:
            return 2.80;
        case smmObjGrade_Cp:
            return 2.50;
        case smmObjGrade_C0:
            return 2.20;
        case smmObjGrade_Cm:
            return 1.70;
    }
}
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

int smmObj_getGrade(void* obj) {
    smmGrade_t* gradeObj = (smmGrade_t*)obj;
    return gradeObj->grade;
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
