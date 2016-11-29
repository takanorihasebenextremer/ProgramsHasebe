#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Aug 22 10:22:57 2016

@author: takanori.hasebe
"""

import MeCab
import nltk
mecab = MeCab.Tagger("")


s = "今日は雨ですね"
s1 = "今日は雨"

p = mecab.parseToNode(s1)
print(p)

def get_tokens(text):

  node = mecab.parseToNode(text)

  words = []

  while node:

    if (node.surface is not None) and node.surface != "":

      words.append(node.surface)

    node = node.next

  return words

print(get_tokens(s))
print(get_tokens(s1))

print(nltk.jaccard_distance(set(get_tokens(s)), set(get_tokens(s1))))