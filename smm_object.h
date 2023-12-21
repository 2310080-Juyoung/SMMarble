#ifndef smm_object_h
#define smm_object_h

#define SMMNODE_TYPE_LECTURE            0
#define SMMNODE_TYPE_RESTAURANT         1
#define SMMNODE_TYPE_LABORATORY         2
#define SMMNODE_TYPE_HOME               3
#define SMMNODE_TYPE_GOTOLAB            4
#define SMMNODE_TYPE_FOODCHANCE         5
#define SMMNODE_TYPE_FESTIVAL           6
#define SMMNODE_TYPE_EXPERIMENT			7

#define MAX_CHARNAME                200
#define SMMNODE_TYPE_MAX                8
typedef enum smmObjGrade {
    smmObjGrade_Ap,
    smmObjGrade_A0,
    smmObjGrade_Am,
    smmObjGrade_Bp,
    smmObjGrade_B0,
    smmObjGrade_Bm,
    smmObjGrade_Cp,
    smmObjGrade_C0,
    smmObjGrade_Cm
} smmObjGrade_e;

typedef enum smmObjType {
    smmObjType_board = 0,
    smmObjType_card,
    smmObjType_grade
} smmObjType_e;

typedef struct smmGrade {
    smmObjGrade_e grade;
} smmGrade_t;

double getNumericValue(smmObjGrade_e grade);
    // 정확한 부동소수점 값을 반환
  //  return (double)grade;
//}

//1. 구조체 형식 정의
typedef struct smmObject {
       char name[MAX_CHARNAME];
       smmObjType_e objType; 
       int type;
       int credit;
       int energy;
       smmObjGrade_e grade;
       int charge;
} smmObject_t;


//object generation
//smmObj_genObject(const char* name, smmObjType_e objType, int type, int credit, int energy, smmObjGrade_e grade);
//member retrieving

//char* smmObj_getNodeName(int node_nr);
//char* smmObj_getNodeName(const void* obj);

//int smmObj_getNodeType(int node_nr);
//int smmObj_getNodeCredit(int node_nr);
//int smmObj_getNodeEnergy(int node_nr);

//element to string
//char* smmObj_getTypeName(int type);

#endif /* smm_object_h */
