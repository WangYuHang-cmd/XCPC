# -*- coding: utf-8 -*-
"""
Created on Sun Oct 31 22:12:01 2021

@author: Henry
"""


N = 100010
INF = 0x3f3f3f3f
# init n表示点数，m表示边数,S起点，T终点，idx内存分配器
n = 0; m = 0; S = 0; T = 0; idx = 0;
e = [ 0 for _ in range(2*N) ]; ne = [ 0 for _ in range(2*N) ]; h = [ -1 for _ in range(N) ]; f = [0 for _ in range(N)] # graph
q = [0 for _ in range(N)]; d = [0 for _ in range(N)]; pre = [0 for _ in range(N)]  # bfs用队列 增广路上残留容量 前驱结点
st = [False for _ in range(N)] # 状态

def add(a, b, c):
    e[idx] = b; f[idx] = c; ne[idx] = h[a] ; h[a] = idx ; idx += 1;
    e[idx] = a; f[idx] = c; ne[idx] = h[a] ; h[a] = idx; idx += 1;

def bfs():
    hh = 0 ; tt = 0
    for i in range(len(st)): # 初始化遍历数组
        st[i] = 0
    q[0] = S ; st[S] = True; d[S] = INF
    while( hh <= tt):
        t = q[hh]; hh += 1;
        i = h[t]
        while(~i):
            ver = e[i]
            if((not st[ver]) and f[i]):
                st[ver] = True
                d[ver] = min(f[i],d[i])
                pre[ver] = i
                if(ver == T):
                    return True
                t += 1
                q[t] = ver
            i = ne[i]
    return False

def EK():
    r = 0
    while(bfs()):
        r += d[T]
        i = T
        while(i != S):
            f[pre[i]] -= d[T]
            f[pre[i] ^ 1] += d[T]
            i = e[pre[i] ^ 1]
    return r