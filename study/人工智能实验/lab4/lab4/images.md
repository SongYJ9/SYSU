### Season

![截屏2020-10-14 上午10.55.11](/Users/songyujie/Library/Application Support/typora-user-images/截屏2020-10-14 上午10.55.11.png)

### month

![截屏2020-10-14 上午10.58.37](/Users/songyujie/Library/Application Support/typora-user-images/截屏2020-10-14 上午10.58.37.png)

### hour

![截屏2020-10-14 上午11.00.00](/Users/songyujie/Library/Application Support/typora-user-images/截屏2020-10-14 上午11.00.00.png)

### holiday

![截屏2020-10-14 上午11.16.45](/Users/songyujie/Library/Application Support/typora-user-images/截屏2020-10-14 上午11.16.45.png)

### weekday

![截屏2020-10-14 上午11.16.45](/Users/songyujie/Library/Application Support/typora-user-images/截屏2020-10-14 上午11.18.39.png)

### workingday、weathersit

![截屏2020-10-14 上午11.09.18](/Users/songyujie/Library/Application Support/typora-user-images/截屏2020-10-14 上午11.09.18.png)

### pre

![截屏2020-10-14 上午11.30.59](/Users/songyujie/Library/Application Support/typora-user-images/截屏2020-10-14 上午11.30.59.png)

### python

```python
    season = [72,157,187,152]
    month = [55,74,87,131,182,199,189,186,177,166,142,118]
    hour = [43,26,18,10,5,14,57,157,263,164,130,155,189,190,182,188,234,350,322,236,173,134,104,69]
    holiday = [144,125]
    weekday = [143,145,147,137,142,147,142]
    workingday = [141,144]
    weathersit = [155,135,86,36]
    
    line[0] = season[int(line[0])-1]/100
    line[2] = month[int(line[2])-1]/100
    line[3] = hour[int(line[3])]/100
    line[4] = holiday[int(line[4])]/100
    line[5] = weekday[int(line[5])]/100
    line[6] = workingday[int(line[6])]/100
    line[7] = weathersit[int(line[7])-1]/100
```

