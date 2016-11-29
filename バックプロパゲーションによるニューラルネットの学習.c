//
//  main.c
//  バックプロパゲーションによるニューラルネットの学習
//
//  Created by TakanoriHasebe on 2016/09/14.
//  Copyright © 2016年 TakanoriHasebe. All rights reserved.
//

/* ヘッダファイルのインクルード */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* 記号定数の定義 */
#define INPUTNO 3 /* 入力層のセル数 */
#define HIDDENNO 20 /* 中間層のセル数 */
#define ALPHA 10 /* 学習係数 */
#define SEED 65535 /* 乱数のシード */
#define MAXINPUTNO 100 /* 学習データの最大個数 */
#define BIGNUM 100 /* 誤差の初期値 */
#define LIMIT 0.001 /* 誤差の上限値 */

/* 関数のプロトタイプ宣言 */
double f(double u); /* 伝達関数（シグモイド関数） */
void initwh(double wh[HIDDENNO][INPUTNO + 1]); /* 中間層の重みの初期化 */
void initwo(double wo[HIDDENNO + 1]); /* 出力層の重みの初期化 */
double drnd(void); /* 乱数の生成 */
void print(double wh[HIDDENNO][INPUTNO + 1], double wo[HIDDENNO + 1]); /* 結果の出力 */
double forward(double wh[HIDDENNO][INPUTNO + 1], double wo[HIDDENNO + 1], double hi[], double e[INPUTNO + 1]); /* 順方向の計算 */
void olearn(double wo[HIDDENNO + 1], double hi[], double e[INPUTNO + 1], double o); /* 出力層の重みの調整 */
int getdata(double e[][INPUTNO + 1]); /* 学習データの読み込み */
void hlearn(double wh[HIDDENNO][INPUTNO + 1], double wo[HIDDENNO + 1], double hi[], double e[INPUTNO + 1], double o); /* 中間層の重みの調整 */

/* main関数 */
int main(void)
{
    double wh[HIDDENNO][INPUTNO + 1]; /* 中間層の重み（閾値で+1） */
    double wo[HIDDENNO + 1]; /* 出力層の重み（閾値で+1） */
    double e[MAXINPUTNO][INPUTNO + 1]; /* 学習データセット */
    double hi[HIDDENNO + 1]; /* 中間層の出力 */
    double o; /* 出力 */
    double err = BIGNUM; /* 誤差の評価 */
    int i, j; /* 繰り返しの評価 */
    int n_of_e = 8; /* 学習データの個数 */
    int count = 0; /* 繰り返し回数のカウンタ */
    FILE *fp; /* ファイルの読み込み */
    
    /* 乱数の初期化 */
    srand(SEED);
    
    /* 重みの初期化 */
    initwh(wh); /* 中間層の重みの初期化 */
    initwo(wo); /* 出力層の重みの初期化 */
    print(wh, wo); /* 重みの結果の出力 */
    
    /*学習データの読み込み*/
    fp=fopen("majority.txt","r");
    
    if (fp == NULL){
        printf("ファイルを開けませんでした。\n");
    }else{
        printf("ファイルを開きました。\n");
    }
    
    for (i = 0; i < 8; i++){
        for (j = 0; j < 4; j++){
            fscanf(fp, "%lf", &(e[i][j]));
        }
    }
    /* 学習データの読み込み完了 */
    
    /* 学習 */
    while (err > LIMIT){
        err = 0.0;
        for (j = 0; j < n_of_e; ++j){
            /* 順方向の計算 */
            o = forward(wh, wo, hi, e[j]);
            /* 出力層の重みの調整 */
            olearn(wo, hi, e[j], o);
            /* 中間層の重みの調整 */
            hlearn(wh, wo, hi, e[j], o);
            /* 誤差の積算 */
            err += ((o - e[j][INPUTNO]) * (o - e[j][INPUTNO])) * 1/2;
        }
        ++count;
        /* 誤差の出力 */
        fprintf(stderr, "%d\t%lf\n", count, err);
    }/* 学習終了 */
    
    /* 結合荷重の出力 */
    print(wh, wo);
    
    /* 学習データに対する出力 */
    for (i = 0; i < n_of_e; i++){
        printf("%d ", i);
        for (j = 0; j < INPUTNO + 1; ++j){
            printf("%lf ", e[i][j]);
        }
        o = forward(wh, wo, hi, e[i]); /* ここでは重みが変わっている */
        printf("%lf\n", o);
    }
    
    return 0;
}

/* hlearn関数 */
/* 中間層の重み学習 */
/* 中間層の重み, 出力層の重み, 中間層の出力, 入力データ, 出力 */
void hlearn(double wh[HIDDENNO][INPUTNO + 1], double wo[HIDDENNO + 1], double hi[], double e[INPUTNO + 1], double o)
{
    int i, j; /* 繰り返しの制御 */
    double dj; /* 中間層の重み計算に利用 */
    
    for (j = 0; j < HIDDENNO; ++j){ /* 中間層の各セルjを対象 */
        dj = hi[j] * (1 - hi[j]) * wo[j] * (e[INPUTNO] - o) * o * (1 - o); /* まずはj番目の誤差について計算 */
        for (i = 0; i < INPUTNO; ++i){ /* i番目の重みを処理 */
            wh[j][i] += ALPHA * e[i] * dj;
        }
        wh[j][i] += ALPHA * (-1.0) * dj; /* 閾値の学習 */
    }
    
}


/* olearn関数 */
/* 出力層の重み学習 */
/* 出力層の重み, 中間層の出力, 入力データ, 出力 */
void olearn(double wo[HIDDENNO + 1], double hi[], double e[INPUTNO + 1], double o)
{
    int i; /*　繰り返しの制御 */
    double d; /* 重み計算に利用 */
    
         /* 教師データ */
    d = (e[INPUTNO] - o) * o * (1 - o); /* 誤差の計算（微分したものをかけている）*/
    
    for (i = 0; i < HIDDENNO; ++i){
        wo[i] += ALPHA * hi[i] * d; /* 中間層の出力と出力層の重みにより, 出力層の重みが変更される */
    }
    
    wo[i] += ALPHA * (-1.0) * d; /* 閾値の計算 */
}

/* forward関数 */
/* 順方向の計算 */
/* 中間層の重み, 出力層の重み, 中間層の出力, 入力データ */
double forward(double wh[HIDDENNO][INPUTNO + 1], double wo[HIDDENNO + 1], double hi[], double e[INPUTNO + 1])
{
    int i, j; /* 繰り返しの制御 */
    double u; /* 重みつき和の計算 */
    double o; /* 出力の計算 */
    
    /* hiの計算 */
    for (i = 0; i < HIDDENNO; ++i){
        u = 0; /* 重みつき和を求める */
        for (j = 0; j < INPUTNO; ++j){
            u += e[j] * wh[i][j];
        }
        u -= wh[i][j]; /* 閾値の処理 */
        hi[i] = f(u); /* 中間層の出力がでた*/
    }
    o = 0;
    for (i = 0; i < HIDDENNO; ++i){
        o += hi[i] * wo[i]; /* 出力層の出力がでた */
    }
    o -= wo[i]; /* 閾値の処理 */
    
    return f(o);
}

/* print()関数 */
/* 結果の出力 */
void print(double wh[HIDDENNO][INPUTNO + 1], double wo[HIDDENNO + 1])
{
    int i, j; /* 繰り返しの制御 */
    
    for (i = 0; i < HIDDENNO; ++i){
        for (j = 0; j < INPUTNO; ++j){
            printf("%lf ", wh[i][j]);
        }
    }
    printf("\n");
    for (i = 0; i < HIDDENNO + 1; ++i){
        printf("%lf ", wo[i]);
    }
    printf("\n");
}

/* initwh関数 */
/* 中間層の重みの初期化 */
void initwh(double wh[HIDDENNO][INPUTNO + 1])
{
    int i, j; /* 繰り返しの制御 */
    
    /* 乱数による重みの決定 */
    for (i = 0; i < HIDDENNO; ++i){
        for (j = 0; j < INPUTNO + 1; ++j){
            wh[i][j] = drnd();
        }
    }
}

/* initwo関数 */
/* 出力層の重みの初期化 */
void initwo(double wo[HIDDENNO + 1])
{
    int i; /* 繰り返しの制御 */
    
    /* 乱数による重みの決定 */
    for (i = 0; i < HIDDENNO + 1; ++i){
        wo[i] = drnd();
    }
}

/* drnd関数 */
/* 乱数の生成 */
double drnd(void)
{
    double rndno; /* 生成した乱数 */
    
    while((rndno = (double)rand() / RAND_MAX) == 1.0);
    rndno = rndno * 2 - 1; /* -1から1の間の乱数を生成 */
    return rndno;
}

/* f関数 */
/* 伝達関数 */
/* （シグモイド関数） */
double f(double u)
{
    return 1.0 / (1.0 + exp(-u));
}










