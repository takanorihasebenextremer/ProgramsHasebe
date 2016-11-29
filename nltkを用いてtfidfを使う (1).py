#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Aug 30 11:40:32 2016

@author: takanori.hasebe
"""

"""
このプログラムは
nltkを用いてtfidfを使う
"""

import nltk
import numpy as np

"""
リストを指定した数（n）で分割する
"""
def split_list (list,n):
    list_size = len(list)
    a = list_size // n
    b = list_size % n
    return [list[i*a + (i if i < b else b):(i+1)*a + (i+1 if i < b else b)] for i in range(n)]

#a = [1, 2, 3, 4]

#print(split_list(a, 2))

docs = [
    ['明日','の','天気','は','晴れ'],
    ['今日','の','天気','は','曇'],
    ['昨日','の','天気','は','晴れ']]
    
collection = nltk.TextCollection(docs)
uniqTerms = list(set(collection))    
uniqTerms_tfidf = list()
uniqTerms_tfidf_sum = np.array([])
index = list()

#ここでdocsは文章である。
for doc in docs:
    #print("====================")
    #print("doc"+str(doc))
    for term in uniqTerms:
        #print("%s : %f" % (term, collection.tf_idf(term, doc)))
        uniqTerms_tfidf.append(collection.tf_idf(term, doc))
    #print("====================")

#print(uniqTerms_tfidf)    


uniqTerms_tfidf_split = split_list(uniqTerms_tfidf, len(docs))

#print(np.array(uniqTerms_tfidf_split))

arr_tfidf_sum = np.zeros(8)

#print(arr)

for i in range(0, len(uniqTerms_tfidf_split)):
    
    arr_tfidf_sum += uniqTerms_tfidf_split[i]

#print(arr_tfidf_sum)

arr_tfidf_sum_list = list(arr_tfidf_sum)

"""
リストの中から
最大のもののindexをとってくる
"""
index = [i for i, x in enumerate(arr_tfidf_sum_list) if x == max(arr_tfidf_sum_list)]

print(index)

for i in index:
    
    print(uniqTerms[i])
