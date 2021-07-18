## Computer vision

这里是 SYSU SDCS 计算机类本科计算机视觉实验内容

时间：2021 春；教师：lgb

- 期中实验：实现多种经典算法其中的一种（我选择的是边缘检测），并以论文的格式撰写报告
  - test.py 为实现的边缘检测 python 代码
- 期末实验：实现 seam carving 算法、Graph-based image segmentation 算法、以及解决一个综合问题。
  - seamCarving.py、segmentation.py、classification.py 分别为三个作业题目对应的代码
  - data 为结果文件夹，其中包含的原始图片以及原始前景图已移除，如果需要运行代码，需要加回 imgs 和 gt 文件夹及里面的图片和前景图
  - 文件夹 data/seamCarvingOut 为作业一结果，里面包含了 2 个 gif 和 10 张图的最终结果图 
  - 文件夹 data/segmentationOut 为作业二结果，里面包含了 10 张图的中间结果图和最终生成的前景图
  - 文件夹 data/classification 为作业三结果，里面包含了几个中间文件，分别代表 200 张图的 20 维特征、50 类聚类 visual word 的 20 维特征、整合成的训练集和验证集

