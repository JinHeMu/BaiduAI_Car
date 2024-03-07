# BaiduAI_Car
 第十九届智能车模型组



## 图像处理方法

### 预处理(preprocess.cpp)

**preprocess**类

方法:

- 通过从 XML 文件中读取来初始化相机标定参数

- **`binaryzation` 方法**：将输入的彩色图像转换为灰度图像，然后使用 Otsu 的阈值法进行二值化处理。

- **`correction` 方法**：根据相机标定参数对输入的图像进行畸变矫正，如果标定参数可用的话。它首先检查是否启用了标定。如果启用了，它会初始化图像矫正所需的矩阵，然后进行重映射

### 识别元素(recognition)

#### 十字路口(crossroad.cpp)











## 2024/2/29

已经初步将硬件主板和驱动板完成


## 2024/3/5

config edgeboard ssh and git 





