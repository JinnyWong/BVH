# 📂数据结构课 - BVH文件解析器实验项目报告

- 黄婧媛 21300246010

- 本项目完成了 base 部分

## 代码运行

In project root file:

```bash
cd src
make base
./base sample.bvh
```

## 完成思路

#### 1. 理解BVH文件架构

BVH 文件里的内容分为 Hierarchy 和 Motion 两个部分：

- Hierarchy部分是描述虚拟角色的树形结构

- Motion部分是记录每一帧虚拟角色的姿态

其中的CHANNELS描述了平移和旋转属性，记为Xrotation, Yrotation, Zrotation。

#### 2. 编写 Base部分 `bvh_parser.cpp`

我从base（parser）部分的开始编写代码。这部分主要是读入一个BVH文件，并创建一个关节树来表示BVH文件的结构。然后再读入BVH文件中的metadata和每个joint的motion data，并将这些数据存储在树形结构中。



**读取文件**

在主函数中，首先通过`std::ifstream file(argv[1])` 来使用命令行中指定的文件名打开一个输入文件流。

**创建树形结构**

接下来，通过调用 `create_joint_tree` 函数来创建树的root。该函数从输入文件流中读入joint的结构，并返回一个指向root的指针。`create_joint_tree` 中使用了stack来记录每个joint的信息。函数从文件流中依次读入token标记，并利用循环检查其值：

- 如果token标记为"ROOT"，则将stack当前关节的名称和类型设置为适当的值并继续读取下一个token标记。

- 如果token标记为"JOINT"，就会创建一个新的child joint，将其类型设置为"JOINT"，并将其推入stack中。

- 如果token标记为"OFFSET"，就会读入和存储`offset_x`, `offset_y` 和 `offset_z` 的值。

- 如果token标记为“CHANNELS”, 就会读入当前joint的Channel vector大小，然后读入channels的值并将其存储。

- 如果token标记为"End"，就会创建一个新的child joint，将其名称和类型设置为“当前joint的名字+ _End”。

- 如果token标记为"}", 就从stack中pop出当前的joint。

**读取Metadata**

`read_meta` 函数读入BVH文件中的元数据，包括帧数和帧时间，并将这些存储在META结构中。

**填充Motion data**

`populate_motion_data` 函数读入树中每个joint的motion data。这个函数使用的是stack以深度优先的方式遍历之前创建好的树，将已读入的每个joint的motion data填充存储在关节树当中。

#### 3. 编写 Bonus部分 `json.cpp`

完成 base部分后就不幸感染了新冠肺炎，因此 bonus部分只编写了一点内容，未能及时完成。

## 心得和收获

从完全不知道一个parser是什么，到自己写出了一个parser的过程对我来说是漫长且充满困难的。我只能一边看网上的资料学习，一边写代码；遇到不明白的地方就请教老师、助教和学长姐们，努力搞懂每一个陌生概念。虽然最终很遗憾地没能完成 bonus部分，但是我觉得 base部分有尽到全力就挺好了。希望我阳康后能有精力继续写完bonus部分！

非常感谢老师、助教们以及宇悦学长在我学习和完成项目时给予的指导！

## 参考资料

- [BVH文件架构](https://zhuanlan.zhihu.com/p/539522515)

- [BVH文件格式解析](https://zhuanlan.zhihu.com/p/386591298)

- [What is a Parser?](https://www.techtarget.com/searchapparchitecture/definition/parser)

- [使用Java编写BVH文件解析器](https://blog.csdn.net/u012336923/article/details/50979894)

- [Explanation of `getline()` and `stringstream`](https://ee.usc.edu/~redekopp/cs103/slides/Unit14_Streams.pdf)

- [Examples of using nlohmann JSON library](https://gist.github.com/lyandut/98d4eb75add96fafdc06c6f94c9317fe)
