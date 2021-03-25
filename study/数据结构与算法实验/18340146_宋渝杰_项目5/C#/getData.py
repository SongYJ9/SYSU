# -*- coding: UTF-8 -*-
import pandas as pd
import numpy as np
import random

dic = ["家人", "朋友" ,"小学同学", "初中同学" ,"高中同学", "大学同学" ,"姐妹", "前男友","路人"]
dic2 = ["男","女"]
dic3 = ["越秀区","番禺区","萝岗区","从化区","荔湾区","花都区","白云区","黄浦区","南沙区","增城区","海珠区","天河区"]
dic4 = ["510000","511400","510000","510900","510100","510800","510400","510700","511400","511300","510200","510600"]

#设置信息：
length = 2000

#生成csv
data = []
for i in range(length):
    name = ''.join(random.sample(['z','y','x','w','v','u','t','s','r','q','p','o','n','m','l','k','j','i','h','g','f','e','d','c','b','a'], 5))
    fen = random.randint(0,100)
    if fen < 2:
        fen = 7
    elif fen < 5:
        fen = 6
    elif fen < 12:
        fen = 0
    elif fen < 20:
        fen = 1
    elif fen < 50:
        fen  = random.randint(2,5)
    else:
        fen = 8
    xin = random.randint(0,1)
    if fen == 6:
        xin = 1
    elif fen == 7:
        xin = 0
    di = random.randint(0,len(dic3)-1)
    zhuzhi = dic3[di]
    youbian = dic4[di]
    dianhua = random.randint(13100000000,15100000000)
    qq = random.randint(10000000,1000000000)
    youxiang = str(qq) + "@qq.com"
    shengri = str(random.randint(1998,2018)) + "/" + str(random.randint(1,12)) + "/" + str(random.randint(1,28))
    weixin = "B" + str(qq)
    row = [i+1,dic[fen],name,dic2[xin],dianhua,youxiang,zhuzhi,youbian,qq,weixin,shengri]
    data.append(row)
df = pd.DataFrame(data)
print(df)
df.to_csv("data.csv",encoding='utf-8-sig',index = None,header = ["序号","分类","姓名","性别","电话","邮箱","住址","邮编","QQ","微信","生日"])
