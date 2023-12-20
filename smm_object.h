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

typedef enum smmObjType {
    smmObjType_board = 0,
    smmObjType_card,
    smmObjType_grade
} smmObjType_e;


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

//double getNumericValue(smmObjGrade_e grade) {
    // ��Ȯ�� �ε��Ҽ��� ���� ��ȯ
  //  return (double)grade;
//}

//1. ����ü ���� ����
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
