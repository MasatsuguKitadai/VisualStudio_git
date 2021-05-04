/******************************************************************************
PROGRAM NAME : airfoil_fixed.c
AUTHER : Masatsugu Kitadai
DATE : 18/4/2021
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <math.h>
#define num 10000

double coordinate[num][3];
char airfoil_name[1000];
char buf[128];
char read_file[1000];
char output_file[1000];

FILE* read;
FILE* output;

/*********************************   MAIN   *********************************/
int main()
{
    int i, chord;
    double x, z;

    i = 0;

    // �ǂݍ��ރt�@�C�����w�肷��

    printf("�t�@�C�����F");
    scanf("%s", airfoil_name);

    // ���������w�肷��

    printf("������(mm)�F");
    scanf("%d", &chord);

    // ���́E�o�̓t�@�C�����̎w��

    sprintf(read_file, "original//%s.dat", airfoil_name);
    sprintf(output_file, "result//%s_fixed_%d.csv", airfoil_name, chord);

    // �ǂݍ��ރt�@�C�����J��

    read = fopen(read_file, "r");
    if (read == NULL)
    {
        printf("I can't open the file\n");
        exit(0);
    }

    // �ŏ���1�s��ǂݔ�΂�

    fgets(buf, sizeof(buf), read);

    // �Ō�̍s�ȊO��ǂݍ��݁C�z��Ɋi�[����

    while (fscanf(read, "%lf %lf", &x, &z) != EOF)
    {
        i = i + 1;
        coordinate[i][1] = x;
        coordinate[i][2] = 0;
        coordinate[i][3] = z;
    }

    // EOF�Ŕ��ʂł��Ȃ��Ō�̍s��ǂݍ���

    fscanf(read, "%lf %lf", &x, &z);
    i = i + 1;
    coordinate[i][1] = x;
    coordinate[i][2] = 0;
    coordinate[i][3] = z;

    fclose(read);

    // �z��̑傫��������

    int data_long;
    data_long = i;

    // �w�肳�ꂽ�������ɏC������

    for (i = 1; i < data_long; i++)
    {
        coordinate[i][1] = chord * coordinate[i][1];
        coordinate[i][2] = chord * coordinate[i][2];
        coordinate[i][3] = -1.0 * chord * coordinate[i][3];
    }

    // �������ރt�@�C�����J��

    output = fopen(output_file, "w");

    // printf("\n�yResult�z-------------------------------------------------\n\n");

    fprintf(output,"x,y,z\n");

    for (i = 1; i < data_long; i++)
    {
        // printf("%d\t%lf\t%lf\t%lf\n", i, coordinate[i][1], coordinate[i][2], coordinate[i][3]);
        fprintf(output, "%lf,%lf,%lf\n", coordinate[i][1], coordinate[i][2], coordinate[i][3]);
    }
    // printf("\n-----------------------------------------------------------\n\n");

    fclose(output);

    return (0);
}