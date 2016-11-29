#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Aug 16 11:48:20 2016

@author: takanori.hasebe
"""

"""""""""""""""""""""""""""""""""""""""""""""
アソシアトロンは
視覚系のモデルではなく、脳の内部のモデルである

このプログラムでは常緑樹, 落葉樹かを判断するものである。
以下のプログラムでは特徴を４つ与えている。
"""""""""""""""""""""""""""""""""""""""""""""

import numpy as np
import seaborn as sns
from matplotlib import pyplot as plt
import random as rd
import math
import associatronfunction as af

"""""""""""""""""""""""""""""""""""""""""""""
"""
#*****このプログラムは間違っている*****
"""
"""
#A（常緑樹）
"""
x_1 = np.array([1, 1, 1, 1]).reshape(1, 4)
x_2 = np.array([1, 1, 1, 0]).reshape(1, 4)
x_3 = np.array([1, 1, 0, 1]).reshape(1, 4)
x_4 = np.array([0, 1, 1, 0]).reshape(1, 4)
x_5 = np.array([0, 0, 1, 1]).reshape(1, 4)

x_A = np.vstack((x_1, x_2, x_3, x_4, x_5))

"""
#B(落葉樹)
"""
x_6 = np.array([1, 0, 0, 0]).reshape(1, 4)
x_7 = np.array([0, 1, 0, 0]).reshape(1, 4)
x_8 = np.array([0, 0, 1, 0]).reshape(1, 4)
x_9 = np.array([1, 0, 0, 1]).reshape(1, 4)
x_10 = np.array([0, 0, 0, 0]).reshape(1, 4)

x_B = np.vstack((x_6, x_7, x_8, x_9, x_10))

M = np.matmul(x_1.T, x_1) + np.matmul(x_2.T, x_2) + np.matmul(x_3.T, x_3) +\
    np.matmul(x_4.T, x_4) + np.matmul(x_5.T, x_5) + np.matmul(x_6.T, x_6) +\
    np.matmul(x_7.T, x_7) + np.matmul(x_8.T, x_8) + np.matmul(x_9.T, x_9) +\
    np.matmul(x_10.T, x_10)

print(M)

x = np.array([0, 0, 0, 1]).reshape(1, 4)

recall = af.r＿Phi(np.matmul(x, af.m_Phi(M)))

print(recall)

for i in range(0, len(x_A)):
    
    if np.corrcoef(recall, x_A[i].reshape(1, 4))[0][1] > 0.5 or \
       np.array_equal(recall, x_A[i].reshape(1, 4)):
        
        print("常緑樹")
    
    if np.corrcoef(recall, x_B[i].reshape(1, 4))[0][1] > 0.5 or \
        np.array_equal(recall, x_B[i].reshape(1, 4)):
        
        print("落葉樹")
"""""""""""""""""""""""""""""""""""""""""""""
"""
"""
"""
#append
"""
"""
#常緑樹に属するもの
x1 = np.vstack((arr1, arr1, arr1, arr1))
x2 = np.vstack((arr1, arr1, arr1, arr0))
x3 = np.vstack((arr1, arr1, arr0, arr1))
x4 = np.vstack((arr0, arr1, arr1, arr0))
x5 = np.vstack((arr0, arr0, arr1, arr1))
"""

"""
#落葉樹に属するもの
x6 = np.vstack((arr1, arr0, arr0, arr0))
x7 = np.vstack((arr0, arr1, arr0, arr0))
x8 = np.vstack((arr0, arr0, arr1, arr0))
x9 = np.vstack((arr1, arr0, arr0, arr1))
x10 = np.vstack((arr0, arr0, arr0, arr0))
"""

"""
arr0は0を表し
arr1は1を表す

Aは常緑樹クラス
Bは落葉樹クラス

vstackじゃなくてappendを使ってみる
"""

#直交ベクトルを受けとっている
zero_one = af.orthogonal(8)
clustering = af.orthogonal(8)

arr0 = zero_one[0].reshape(1, 16)
arr1 = zero_one[1].reshape(1, 16)

A = clustering[0].reshape(1, 16)
B = clustering[1].reshape(1, 16)

#arr0 = arr0.reshape(1, 16)
#arr1 = arr1.reshape(1, 16)
print(arr0)
print(arr1)
#print(np.matmul(arr0, arr1.T))
#print(np.corrcoef(arr0, arr1)[0][1])
#print(len(A[0]))
#print(B)
#print(np.corrcoef(A, B)[0][1])


#常緑樹に属するもの(Class A)
x1 = np.concatenate((arr1, arr1, arr1, arr1, A), axis = 1)
x2 = np.concatenate((arr1, arr1, arr1, arr0, A), axis = 1)
x3 = np.concatenate((arr1, arr1, arr0, arr1, A), axis = 1)
x4 = np.concatenate((arr0, arr1, arr1, arr0, A), axis = 1)
x5 = np.concatenate((arr0, arr0, arr1, arr1, A), axis = 1)

#落葉樹に属するもの(Class B)
x6 = np.concatenate((arr1, arr0, arr0, arr0, B), axis = 1)
x7 = np.concatenate((arr0, arr1, arr0, arr0, B), axis = 1)
x8 = np.concatenate((arr0, arr0, arr1, arr0, B), axis = 1)
x9 = np.concatenate((arr1, arr0, arr0, arr1, B), axis = 1)
x10 = np.concatenate((arr0, arr0, arr0, arr0, B), axis = 1)


#print(x1)
#print(len(x1[0]))
#print(len(x1))
#print(len(np.matmul(x1.T, x1)))
#print(np.matmul(x1.T, x1))


M = np.matmul(x1.T, x1) + np.matmul(x2.T, x2) + np.matmul(x3.T, x3) + \
    np.matmul(x4.T, x4) + np.matmul(x5.T, x5) + np.matmul(x6.T, x6) + \
    np.matmul(x7.T, x7) + np.matmul(x8.T, x8) + np.matmul(x9.T, x9) + \
    np.matmul(x10.T, x10)
    
#af.matrix_V(M)

#print(len(arr0))

#入力されるもの
y = np.concatenate((arr1, arr0, arr1, arr0,\
                    np.zeros(16, dtype=int).reshape(1, 16)), axis = 1)

#print(y)

#temp = np.matmul(y, af.m_Phi(M))

#print(temp)

#print(af.m_Phi(temp))

recall = af.r＿Phi(np.matmul(y, M))

#print(recall)
#print(recall.reshape(5, 16)[4].reshape(1, 16))
#print(B)

if (np.corrcoef(recall.reshape(5, 16)[4].reshape(1, 16), A)[0][1] and \
   np.corrcoef(recall.reshape(5, 16)[4].reshape(1, 16), B)[0][1]) > 0.8:#?

    print("Class A and Class B")    
    print("判断できません")   
   
elif np.corrcoef(recall.reshape(5, 16)[4].reshape(1, 16), A)[0][1] > 0.7:
    
    print("Class A")
    print("この樹は常緑樹です。")
    
elif np.corrcoef(recall.reshape(5, 16)[4].reshape(1, 16), B)[0][1] > 0.7:
    
    print("Class B")
    print("この樹は落葉樹です。")
   
else:
    
    print("not Class A and Class B")
    print("判断できません")
