#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Aug 23 17:38:58 2016

@author: takanori.hasebe
"""

"""
配列の指定した部分から
指定した品詞を抜き出してくる
"""

import MeCab

words = [["1", "自撮り棒"],["2", "カメラ"], ["3", "マインド"], ["4", "いいですね"]]

tagger = MeCab.Tagger("-Ochasen")

result = tagger.parse("いいですね")

print(result)

print(result.split("\t"))

#print(len(words))

temp = list()

for i in range(0, len(words)):
    
    if "名詞" in tagger.parse(words[i][1]):
        
        temp.append(words[i])
        
print(temp)