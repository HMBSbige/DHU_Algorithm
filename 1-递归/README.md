# 2017 算法 第一次练习 (递归)
## Problem A : Pizza Cutting

From: [UVa 10079](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=11&page=show_problem&problem=1020)

题目求二维空间被n条直线最多被分为几块

利用递归或者简化成等差数列求和公式直接求。

[My solution](https://github.com/HMBSbige/DHU_Algorithm/blob/master/1-%E9%80%92%E5%BD%92/UVa%2010079.cpp)

附：k维空间被n条直线最多被分为![](https://raw.githubusercontent.com/HMBSbige/DHU_Algorithm/master/1-%E9%80%92%E5%BD%92/picture/1.png)或![](https://raw.githubusercontent.com/HMBSbige/DHU_Algorithm/master/1-%E9%80%92%E5%BD%92/picture/2.png)块

## Problem B : Bee

From: [UVa 11000](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1941)

由题意得
```
♀[n]=♂[n-1]+1
♂[n]=♀[n-1]+♂[n-1]
```
∴
```
♂[n]=♂[n-1]+♂[n-2]+1
♀[n]+♂[n]=♂[n+1]
```
其中♂[1]=1，♂[2]=2

有没有很像斐波那契数列的递推式？用递归或迭代即可~

题目限制结果必小于 1LL<<32 ,则n<=47，用long long即可

[My solution](https://github.com/HMBSbige/DHU_Algorithm/blob/master/1-%E9%80%92%E5%BD%92/UVa%2011000.cpp)

附：求斐波那契数列的三种方法

经测试运行效率：
迭代>通项公式>>递归

```cpp
uLL _(int n) //通项公式 general formula n<=71
{
	return (uLL)((1 / sqrt(5)) * (powl((1 + sqrt(5)) / 2.0, n) - powl((1 - sqrt(5)) / 2.0, n)));
}
uLL __(int n)//迭代 recursion n<=93
{
	uLL result_2;
	uLL result_1 =0, result = 1;
	if (n == 0)
		return 0;
	while (n > 2) {
		n -= 1;
		result_2 = result_1;
		result_1 = result;
		result = result_1 + result_2;
	}
	return result;
}
uLL ___(int n)//递归 iteration
{
	if (n == 0)
		return 0;
	else if (n <= 2)
		return 1;
	return ___(n - 1) + ___(n - 2);
}
```

## Problem C : Brick Wall Patterns

From: [UVa 900](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=11&page=show_problem&problem=841)

题目可以化简为：把正整数n分解为由一组1、2相加的数的排列的个数

把有 0 个2到 n/2 个2的排列数加起来就是答案

当然这个式子可以化简合并为第n+1个斐波那契数

[My solution](https://github.com/HMBSbige/DHU_Algorithm/blob/master/1-%E9%80%92%E5%BD%92/UVa%20900.cpp)

## Problem D : Critical Mass

From: [UVa 580](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&category=11&problem=521)

题目可化简为：n个由U、L组成的cube，求存在连续U的个数>=3的排列的个数

设补集个数为F(n)

可分为三种情况：

* ``L...``		个数为F(n-1)
* ``UL...``		个数为F(n-2)
* ``UUL...``	个数为F(n-3)

所以	**F(n)=F(n-1)+F(n-2)+F(n-3)**

利用递归或迭代即可轻松解决

[My solution](https://github.com/HMBSbige/DHU_Algorithm/blob/master/1-%E9%80%92%E5%BD%92/UVa%20580.cpp)
