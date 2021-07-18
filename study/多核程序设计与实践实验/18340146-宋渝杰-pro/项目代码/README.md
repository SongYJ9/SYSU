实验源码在本文件夹下，其中：

- TSP 文件夹放置的是 TSP 问题有关的程序：
  - CPU_algorithm 文件夹放置的是 CPU 程序，包括精确解求解（dfs.cpp）、贪心求近似解（greedy.cpp）、模拟退火单线程程序（Serial.cpp），以及它们的 Linux 环境可执行程序
  - CUDA_algorithm 文件夹放置的是 CUDA 程序，包括本次实验的 Baseline 程序（TSP_baseline.cu）、Final 程序及其头文件（TSP_final.cu, TSP_final.h），以及它们的 Linux 环境可执行程序
  - in 文件夹放置的是 TSP 问题的测试输入文件（in1.txt ~ in5.txt），以及生成测试输入文件的 python 代码（generate_input_file.py）
  - out 文件夹放置的是运行程序后的结果，将会被保存在 out.txt 文件内
- SteinerTree 文件夹放置的是最小斯坦纳树问题有关的程序：
  - CPU_algorithm 文件夹放置的是 CPU 程序，包括精确解求解（DP.cpp）、贪心求近似解（Greedy.cpp）、模拟退火单线程程序（Serial.cpp），以及它们的 Linux 环境可执行程序
  - CUDA_algorithm 文件夹放置的是 CUDA 程序，包括本次实验的 Final 程序及其头文件（SteinerTree.cu, SteinerTree.h），以及它们的 Linux 环境可执行程序
  - in 文件夹放置的是最小斯坦纳树问题的测试输入文件（in1.txt ~ in5.txt），以及生成测试输入文件的 python 代码（generate_input_file.py）
  - out 文件夹放置的是运行程序后的结果，将会被保存在 out.txt 文件内
- TSP 可视化交互程序文件夹放置的是我们设计的 TSP 问题可视化交互程序（index.html）

