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
   // デザイン
    printf("\n===========================================================\n\n");
    printf("\n                     Airfoil Adjuster                      \n\n");
    printf("\n===========================================================\n\n");

    int i, chord;
    double x, y;

    i = 0;

    // 読み込むファイルを指定する
    printf("ファイル名を入力してください（拡張子「.txt」は除く）\n\n");
    printf("FILE_NAME：");
    scanf("%s", airfoil_name);

    // 入力・出力ファイル名の指定

    sprintf(read_file, "original//%s.txt", airfoil_name);

    // 読み込むファイルを開く

    read = fopen(read_file, "r");
    if (read == NULL)
    {
        printf("\nファイルが開けません\n");
        printf("最初からやり直してください\n\n");
        printf("何か文字を入力してEnterを押すとプログラムが終了します\n");
        scanf("%s", space);
        exit(0);
    }

    // 最初の1行を読み飛ばす

    fgets(buf, sizeof(buf), read);

    // 最後の行以外を読み込み，配列に格納する

    while (fscanf(read, "%lf %lf", &x, &y) != EOF)
    {
        i = i + 1;
        coordinate[i][1] = x;
        coordinate[i][2] = 0;
        coordinate[i][3] = y;
    }

    // EOFで判別できない最後の行を読み込む

    fscanf(read, "%lf %lf", &x, &y);
    i = i + 1;
    coordinate[i][1] = x;
    coordinate[i][2] = 0;
    coordinate[i][3] = y;

    fclose(read);

    // 配列の大きさを決定

    int data_long;
    data_long = i;

    // 翼弦長を指定する
    printf("\n任意の翼弦長(mm)を入力してください\n\n");
    printf("CHORD：");
    scanf("%d", &chord);

    // z座標の上下を反転させる

    for (i = 0; i < data_long; i++)
    {
        coordinate[i][3] = (-1.0) * coordinate[i][3];
    }

    // 指定された翼弦長に修正する

    for (i = 1; i < data_long; i++)
    {
        coordinate[i][1] = chord * coordinate[i][1];
        coordinate[i][3] = chord * coordinate[i][3];
    }

    // 保存するディレクトリを作成

    sprintf(folder_name, "result//%s_%d", airfoil_name, chord);

   if (_mkdir(folder_name) == 0)
   {
       printf("\n「%s」が作成されました\n", folder_name);
   }
   else 
   {
       printf("\n「%s」はすでに作成されています\n", folder_name);
   }

    // 書き込むファイルの名前を指定する

    sprintf(output_file_csv, "result//%s_%d//coordinate.csv", airfoil_name, chord);
// sprintf(output_file_xlsx, "result//%s_%d//coordinate.xlsx", airfoil_name, chord);
    sprintf(output_file_txt, "result//%s_%d//coordinate.txt", airfoil_name, chord);
    sprintf(output_file_asc, "result//%s_%d//coordinate.asc", airfoil_name, chord);

    // それぞれのファイルに書き込む

    //csv ファイル

    output = fopen(output_file_csv, "w");

    for (i = 1; i < data_long; i++)
    {
        fprintf(output, "X,%lf,Y,%lf,Z,%lf\n", coordinate[i][1], coordinate[i][2], coordinate[i][3]);
    }

    fclose(output);

    //xlsx ファイル
/*
    output = fopen(output_file_xlsx, "w");

    for (i = 1; i < data_long; i++)
    {
        fprintf(output, "X,%lf,Y,%lf,Z,%lf\n", coordinate[i][1], coordinate[i][2], coordinate[i][3]);
    }

    fclose(output);
 */

    //txt ファイル

    output = fopen(output_file_txt, "w");

    for (i = 1; i < data_long; i++)
    {
        fprintf(output, "X\t%lf\tY\t%lf\tZ\t%lf\n", coordinate[i][1], coordinate[i][2], coordinate[i][3]);
    }

    fclose(output);

    //asc ファイル

    output = fopen(output_file_asc, "w");

    for (i = 1; i < data_long; i++)
    {
        fprintf(output, "X\t%lf\tY\t%lf\tZ\t%lf\n", coordinate[i][1], coordinate[i][2], coordinate[i][3]);
    }

    fclose(output);

    // アプリケーションに出力

    printf("\n【Result】-------------------------------------------------\n\n");

    printf("\t【 x 】\t\t【 y 】\t\t【 z 】\n");

    for (i = 1; i < data_long; i++)
    {
        printf("%d\t%lf\t%lf\t%lf\n", i, coordinate[i][1], coordinate[i][2], coordinate[i][3]);
    }

    printf("\n-----------------------------------------------------------\n\n");

    printf("何か文字を入力してEnterを押すとプログラムが終了します\n");
    scanf("%s", space);

    return (0);
}