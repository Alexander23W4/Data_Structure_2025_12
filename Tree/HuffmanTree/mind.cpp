/*


Application:
场景	Huffman 在哪
ZIP / 7z 压缩	文本、日志、代码压缩
PNG 图片	DEFLATE = LZ77 + Huffman
JPEG	DCT 后的系数再用 Huffman 编码
PDF	文本与对象压缩
HTTP / 网络传输	减少带宽
嵌入式日志	Flash / EEPROM 极小

e.g.日志系统:
方案 1：固定长度编码（愚蠢但常见）
每个单词用 3 bit（最多 8 种）
→ 总成本
3 bit × N 条日志

问题：
DEBUG 占 5%，却和 INFO 一样贵

Huffman 在干什么（工程视角）
它只干一件事
给“高频符号”更短的码，给“低频符号”更长的码，但保证可解码。

Huffman 编码后的效果（示意）
单词	Huffman Code
INFO	0
ERROR	10
WARNING	110
DEBUG	111

成本立刻下降
平均 bit 数：
0.5×1 + 0.3×2 + 0.15×3 + 0.05×3 = 1.85 bit

为什么用树:
Huffman Tree 的工程本质
用一棵二叉树，保证任何编码都不是另一个编码的前缀（Prefix-free）\

五、Huffman Tree 在系统里的真实形态
1?? 压缩时（Encoder）
统计频率
↓
建 Huffman Tree
↓
生成编码表（symbol → bitstring）
↓
按 bit 写入文件 / 网络

2?? 解压时（Decoder）
读 Huffman Tree（或 Canonical 版本）
↓
bit by bit 走树
↓
走到叶子 → 输出符号

树的三个真实用途
1?? 保证前缀无歧义（理论约束）

树结构天然保证：

没有编码是另一个编码的前缀

解码一定唯一

2?? 计算最优码长（信息论意义）

Huffman Tree 解决的是：

“在给定频率分布下，每个 symbol 应该分配多少 bit 才最省？”

这一步是算法层面的优化问题。

3?? 生成编码表（一次性）
Tree
 ↓
(symbol → code)
 ↓
编码表

之后树就可以被扔掉了。
*/ 