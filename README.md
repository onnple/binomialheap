# 二项堆(binomial heap)
二项堆使用优先队列（二项队列），原文地址：  
优先队列调用代码实例图解:  
![优先队列调用代码实例图解](https://github.com/onnple/binomialheap/blob/master/%E4%BA%8C%E9%A1%B9%E5%A0%86%E8%B0%83%E7%94%A8%E5%AE%9E%E4%BE%8B.png)

## 二项堆优先队列操作函数说明

### 1、创建并初始化二项队列
extern BinomialHeap *bheap_init();

### 2、检查二项队列是否已满
extern int bheap_is_full(BinomialHeap *bheap);

### 3、检查二项队列是否为空
extern int bheap_is_empty(BinomialHeap *bheap);

### 4、往二项队列插入数据
extern int bheap_push(BinomialHeap *bheap, int key, Area *value);

### 5、获取顶部元素（最小元素）
extern ANode *bheap_top(BinomialHeap *bheap);

### 6、释放最小元素
extern void bheap_pop(BinomialHeap *bheap);

### 7、遍历二项队列
extern void bheap_traverse(BinomialHeap *bheap);

### 8、清空二项队列
extern int bheap_clear(BinomialHeap *bheap);
