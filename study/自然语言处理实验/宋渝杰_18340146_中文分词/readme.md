### 代码环境：

GPU（CUDA Version: 10.2）



### 代码文件：

`train.py` 集成了训练、验证（计算训练中时验证集的 F1 得分）、生成分词结果、计算最后分词结果的 F1 指标，即本次实验所用到的所有代码

`fenci.py` 分离出了生成分词结果部分代码，可以通过加载 `model.pkl` 文件形成已训练好的模型，并将验证集通过模型生成 `result.txt` 文件（即最终分词结果）

`score.py` 分离出了计算最后分词结果的 F1 指标，可以通过打开 `result.txt` 和 `msr_test_gold.utf8` 两个文件并计算 F1 指标值并输出



### 结果文件：

`model.pkl` 为训练好的模型，可用于服务 `fenci.py` 

`result.txt` 为最终的分词结果



### 如何运行代码：

**训练、训练过程中的验证：**需要把代码 `train.py` 与训练和测试文件 `msr_training.utf8`、 `msr_test.utf8`、 `msr_test_gold.utf8` 放置于同一目录下（GPU 约两个小时），训练完后同时也在该目录下生成了分词结果 `result.txt` 并输出最终分词结果文件的 F1 值

**仅生成分词结果：**需要把代码 `fenci.py` 与训练好的模型 `model.pkl`、训练和测试文件 `msr_training.utf8`、 `msr_test.utf8` 放置于同一目录下，运行代码后在该目录下生成了分词结果 `result.txt` 

**仅计算最后分词结果的 F1 指标：**需要把代码 `score.py` 与 `result.txt` 和 `msr_test_gold.utf8` 两个文件放置于同一目录下，运行代码后输出最终 F1 结果（此步骤可在 CPU 环境下进行）



