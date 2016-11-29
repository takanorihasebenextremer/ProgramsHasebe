//
//  main.c
//  複数のニューロンが結合したもの（学習機能はない）
//  伝達関数としてステップ関数を用いている。
//
//  Created by TakanoriHasebe on 2016/09/13.
//  Copyright © 2016年 TakanoriHasebe. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

/* 配列を表示する関数 */
void printArray(double e[], int n)
{
    
    int i;
    
    for (i = 0; i < n; i++){
        printf("%lf ", e[i]);
    }
    printf("\n");
    
}

/* 初期の重み, 閾値をセットする関数（中間層） */
void initwm(double wm[][3])
{
    
    wm[0][0] = -2.0;
    wm[0][1] = 3.0;
    wm[0][2] = -1.0; /* 閾値 */
    wm[1][0] = -2.0;
    wm[1][1] = 1.0;
    wm[1][2] = 0.5; /* 閾値 */
    
}

/* 初期の重み, 閾値をセットする関数（出力層） */
void initwf(double wf[])
{
    
    wf[0] = -60.0;
    wf[1] = 94.0;
    wf[2] = -1.0; /* 閾値 */
    
}

/* 伝達関数（ステップ関数） */
double transfer(double u)
{
    if (u > 0.0) return 1.0;
    else return 0.0;
}

/* 中間層, 出力層における計算（各変数の初期化をCではしっかりすること）*/
double forward(double wm[2][3], double e[2], double wf[3]) /* 中間層の重みと閾値, 入力データ, 出力層の重みと閾値*/
{
    int i, j; /* for文の制御 */
    double um[2] = {}; /* ステップ関数に入力する値(中間層用) */
    double zm[2] = {}; /* 出力層に入力する値 */
    double u = 0.0; /* 出力層の出力 */
    
    /* 中間層における重みの計算 */
    for (i = 0; i < 2; i++){
        for (j = 0; j < 2; j++){
            //printf("%lf ", e[j]);
            um[i] += wm[i][j] * e[j];
        }
        //putchar('\n');
    }
    /* 中間層における重み計算から閾値を引いている */
    for (i = 0; i < 2; i++){
        //printf("%lf ", wm[i][2]);
        um[i] -= wm[i][2];
    }
    //putchar('\n');
    
    /* 出力層に入力する値の計算 */
    for (i = 0; i < 2; i++){
        zm[i] = transfer(um[i]);
    }
    
    //printf("zm[0] = %lf, zm[1] = %lf ", zm[0], zm[1]);
    
    /* 出力層における重みと閾値の計算 */
    for (i = 0; i < 3; i++){
        u += wf[i] * zm[i];
        if (i == 2) u -= wf[2];
    }
    
    return transfer(u);
}

int main(void)
{
    FILE *fp; /* ファイルのデータを読み込む時に必要 */
    int i, j; /* 繰り返し文の制御 */
    double e[4][2]; /* 入力されたデータ */
    //double um[2]; /* 中間層の出力値（２セット） */
    double o; /* 出力値 */
    double wm[2][3]; /* 中間層の重み */
    double wf[3]; /* 出力層の重み */
    clock_t start, end;
    
    /* 重みのセット */
    initwm(wm);
    initwf(wf);
    
    /* データの入力 */
    fp = fopen("data24.txt", "r");
    if (fp == NULL)
        
        printf("ファイルが見つかりません。\n");
    else
        
        //printf("ファイルが見つかりました。\n");
    for (i = 0; i < 4; i++){
        for ( j = 0; j < 2; j++){
            fscanf(fp, "%lf", &(e[i][j]));
        }
    }
    /* データの入力の終了 */
    
    start = clock();
    /* 出力手順 */
    for (i = 0; i < 4; i++){
        printf("入力値 ");
        for (j = 0; j < 2; j++){
            printf("%lf ", e[i][j]);
        }
        o = forward(wm, e[i], wf);
        printf("出力値 %lf", o);
        putchar('\n');
    }
    end = clock();
    printf( "処理時間:%d[ms]\n", end - start );
    
    return 0;
}
