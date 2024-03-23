# -*- coding: utf-8 -*-

MAX_OF_CHARS = 256

def badCharHeuristic(string, size): 
	''' 
	生成坏字符规则, 记录每个字符出现的索引位置，没有出现的设置为 -1
	'''
	badChar = [-1] * MAX_OF_CHARS 

	for i in range(size): 
		badChar[ ord(string[i]) ] = i

	return badChar

def search(string, pattern): 
	''' 
	只使用坏字符规则的Boyer Moore字符串匹配算法
	'''
	m = len(pattern) 
	n = len(string) 

	badChars = badCharHeuristic(pattern, m) 

	# s is shift of the pattern with respect to text 
	s = 0
    
txt = "ABAAABCD"
pat = "ABC"
search(txt, pat) 