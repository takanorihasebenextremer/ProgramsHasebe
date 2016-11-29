//
//  main.c
//  単純な階層型ニューラルネットの計算
//  １出力のネットワークを計算します。
//  出力する前に複数のニューロンが関与している。
//
//  Created by TakanoriHasebe on 2016/09/13.
//  Copyright © 2016年 TakanoriHasebe. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* 記号定数の定義 */
#define INPUTNO 2 /* 入力層のセル数 */
#define HIDDENNO 2 /* 中間層のセル数 */
#define MAXINPUTNO 100 /* データの最大個数 */

/* 関数のプロトタイプの宣言 */
double f(double u); /* 伝達関数 */
void initwh(double wh[HIDDENNO + 1][INPUTNO + 1]); /* 中間層の重みの初期化 */
void initwo(double wo[HIDDENNO + 1]); /* 出力層の重みの初期化 */
double forward(double wh[HIDDENNO][INPUTNO + 1], double wo[HIDDENNO + 1],double hi[] ,double e[INPUTNO]); /* 順方向の計算 */

/* main関数 */
int main(void)
{
    double wh[HIDDENNO][INPUTNO + 1]; /* 中間層の重み */
    double wo[HIDDENNO + 1]; /* 出力層の重み */
    double e[MAXINPUTNO][INPUTNO]; /* データセット */
    double hi[HIDDENNO + 1]; /* 中間層の出力 */
    double o; /* 出力 */
    int i, j; /* 繰り返しの制御 */
    int n_of_e = 4; /* データの個数 */
    FILE *fp; /* ファイルからの読み込み */
    
    
    /* 重みの初期化 */
    initwh(wh);
    initwo(wo);
    
    /* 入力データの読み込み */
    fp=fopen("data24.txt","r");
    
    if (fp == NULL){
        printf("ファイルがありません。\n");
        return -1;
    }else{
        printf("ファイルが存在します。\n");
    }
    
    for (i = 0; i < 4; i++){
        for (j = 0; j < 2; j++){
            fscanf(fp, "%lf", &(e[i][j]));
        }
    }
    
    /* 計算の本体 */
    for ( i = 0; i < n_of_e; i++){
        printf("%d ", i);
        for ( j = 0; j < INPUTNO; ++j){
            printf("%1f ", e[i][j]);
        }
        o = forward(wh, wo, hi, e[i]);
        printf("%1f\n", o);
    }
    
    return 0;
}

/* forward関数 */
double forward(double wh[HIDDENNO][INPUTNO + 1], double wo[HIDDENNO + 1], double hi[], double e[INPUTNO])
{
    int i, j; /* 繰り返しの制御 */
    double u; /* 重みつきの和 */
    double o; /* 出力の計算 */
    
    /* hiの計算 */
    for(i = 0; i < HIDDENNO; ++i){
        u = 0; /* 重みつき和を求める */
        for (j = 0; j < INPUTNO; ++j){
            u += e[j] * wh[i][j];
        }
        //printf("{ i = %d, j = %d } ", i, j); /* 閾値を表している */
        //printf("u1 = %lf ", u);
        u -= wh[i][j]; /* 閾値の処理 */
        //printf("u2 = %lf ", u);
        hi[i] = f(u);
    }
    o = 0;
    for (i = 0; i < HIDDENNO; ++i){
        o += hi[i] * wo[i];
    }
    //printf("{ i = %d, j = %d } ", i, j);
    o -= wo[i];
    
    return f(o);
}

/* initwh()関数 */
/* 中間層の重みの初期化 */
void initwh(double wh[HIDDENNO][INPUTNO + 1])
{
    
    /* 荷重を定数として与える */
    wh[0][0] = -2;
    wh[0][1] = 3;
    wh[0][2] = -1; /* 閾値 */
    wh[1][0] = -2;
    wh[1][1] = 1;
    wh[1][2] = 0.5; /* 閾値 */
    
}

/* initwo()関数 */
/* 出力層の重みの初期化 */
void initwo(double wo[HIDDENNO + 1])
{
    
    /* 荷重を定数として与える */
    wo[0] = -60;
    wo[1] = 94;
    wo[2] = -1; /* 閾値 */
    
}

/* f()関数 */
/* 伝達関数 */
double f(double u)
{
    /* ステップ関数の計算 */
    if (u >= 0) return 1.0;
    else return 0.0;
    
    /* シグモイド関数の計算 */
    //return 1.0 / (1.0 + exp(-u));
}
















