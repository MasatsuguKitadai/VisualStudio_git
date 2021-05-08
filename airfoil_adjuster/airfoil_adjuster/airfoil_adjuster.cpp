/******************************************************************************
PROGRAM NAME : airfoil_adjuster.c
AUTHER : Masatsugu Kitadai
DATE : 18/4/2021
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <math.h>
#include <direct.h>
#define num 1000

double coordinate[num][3];
char airfoil_name[100];
char buf[128];
char read_file[100];
char output_file_csv[100];
char output_file_xlsx[100];
char output_file_txt[100];
char output_file_asc[100];
char folder_name[100];
char space[1000];

FILE* read;
FILE* output;
/*********************************   MAIN   *********************************/
int main()
{
   // �f�U�C��
    printf("\n===========================================================\n\n");
    printf("\n                     Airfoil Adjuster                      \n\n");
    printf("\n===========================================================\n\n");

    int i, chord;
    double x, y;

    i = 0;

    // �ǂݍ��ރt�@�C�����w�肷��
    printf("�t�@�C��������͂��Ă��������i�g���q�u.txt�v�͏����j\n\n");
    printf("FILE_NAME�F");
    scanf("%s", airfoil_name);

    // ���́E�o�̓t�@�C�����̎w��

    sprintf(read_file, "original//%s.txt", airfoil_name);

    // �ǂݍ��ރt�@�C�����J��

    read = fopen(read_file, "r");
    if (read == NULL)
    {
        printf("\n�t�@�C�����J���܂���\n");
        printf("�ŏ������蒼���Ă�������\n\n");
        printf("������������͂���Enter�������ƃv���O�������I�����܂�\n");
        scanf("%s", space);
        exit(0);
    }

    // �ŏ���1�s��ǂݔ�΂�

    fgets(buf, sizeof(buf), read);

    // �Ō�̍s�ȊO��ǂݍ��݁C�z��Ɋi�[����

    while (fscanf(read, "%lf %lf", &x, &y) != EOF)
    {
        i = i + 1;
        coordinate[i][1] = x;
        coordinate[i][2] = 0;
        coordinate[i][3] = y;
    }

    // EOF�Ŕ��ʂł��Ȃ��Ō�̍s��ǂݍ���

    fscanf(read, "%lf %lf", &x, &y);
    i = i + 1;
    coordinate[i][1] = x;
    coordinate[i][2] = 0;
    coordinate[i][3] = y;

    fclose(read);

    // �z��̑傫��������

    int data_long;
    data_long = i;

    // ���������w�肷��
    printf("\n�C�ӂ̗�����(mm)����͂��Ă�������\n\n");
    printf("CHORD�F");
    scanf("%d", &chord);

    // z���W�̏㉺�𔽓]������

    for (i = 0; i < data_long; i++)
    {
        coordinate[i][3] = (-1.0) * coordinate[i][3];
    }

    // �w�肳�ꂽ�������ɏC������

    for (i = 1; i < data_long; i++)
    {
        coordinate[i][1] = chord * coordinate[i][1];
        coordinate[i][3] = chord * coordinate[i][3];
    }

    // �ۑ�����f�B���N�g�����쐬

    sprintf(folder_name, "result//%s_%d", airfoil_name, chord);

   if (_mkdir(folder_name) == 0)
   {
       printf("\n�u%s�v���쐬����܂���\n", folder_name);
   }
   else 
   {
       printf("\n�u%s�v�͂��łɍ쐬����Ă��܂�\n", folder_name);
   }

    // �������ރt�@�C���̖��O���w�肷��

    sprintf(output_file_csv, "result//%s_%d//coordinate.csv", airfoil_name, chord);
// sprintf(output_file_xlsx, "result//%s_%d//coordinate.xlsx", airfoil_name, chord);
    sprintf(output_file_txt, "result//%s_%d//coordinate.txt", airfoil_name, chord);
    sprintf(output_file_asc, "result//%s_%d//coordinate.asc", airfoil_name, chord);

    // ���ꂼ��̃t�@�C���ɏ�������

    //csv �t�@�C��

    output = fopen(output_file_csv, "w");

    for (i = 1; i < data_long; i++)
    {
        fprintf(output, "X,%lf,Y,%lf,Z,%lf\n", coordinate[i][1], coordinate[i][2], coordinate[i][3]);
    }

    fclose(output);

    //xlsx �t�@�C��
/*
    output = fopen(output_file_xlsx, "w");

    for (i = 1; i < data_long; i++)
    {
        fprintf(output, "X,%lf,Y,%lf,Z,%lf\n", coordinate[i][1], coordinate[i][2], coordinate[i][3]);
    }

    fclose(output);
 */

    //txt �t�@�C��

    output = fopen(output_file_txt, "w");

    for (i = 1; i < data_long; i++)
    {
        fprintf(output, "X\t%lf\tY\t%lf\tZ\t%lf\n", coordinate[i][1], coordinate[i][2], coordinate[i][3]);
    }

    fclose(output);

    //asc �t�@�C��

    output = fopen(output_file_asc, "w");

    for (i = 1; i < data_long; i++)
    {
        fprintf(output, "X\t%lf\tY\t%lf\tZ\t%lf\n", coordinate[i][1], coordinate[i][2], coordinate[i][3]);
    }

    fclose(output);

    // �A�v���P�[�V�����ɏo��

    printf("\n�yResult�z-------------------------------------------------\n\n");

    printf("\t�y x �z\t\t�y y �z\t\t�y z �z\n");

    for (i = 1; i < data_long; i++)
    {
        printf("%d\t%lf\t%lf\t%lf\n", i, coordinate[i][1], coordinate[i][2], coordinate[i][3]);
    }

    printf("\n-----------------------------------------------------------\n\n");

    printf("������������͂���Enter�������ƃv���O�������I�����܂�\n");
    scanf("%s", space);

    return (0);
}