/**
 * 题目链接:http://118.190.20.162/view.page?gpid=T88
 * 思路:
 * 通过计算输入的表达式的值 然后判断是否为24
 *  
 * 采用双栈法求表达式的值
 * 1. 使用的数据结构:
 * 一个存储运算符的栈ops 一个存储运算数的栈nums
 * 
 * 2. 运算过程:
 * 遍历表达式
 * 遇到运算符将其压入ops中 并且获取其运算优先级 
 * 遇到运算数将其压入nums中
 * 
 * 进行一次运算的条件:存储运算符的栈非空时 当前的表达式中的运算符的优先级不大于运算符栈顶的优先级
 * 此时从运算数栈中弹出两个数字进行一次计算 再将运算结果压入nums中 然后弹出栈顶运算符
 * 重复该过程
 * 该过程结束后将表达式中当前的运算符入栈
 * 遍历完成后 若运算符栈中仍然存在运算符 则逐个进行运算 将结果压入nums中 从ops中弹出该运算符
 * 重复该过程 直到运算符栈ops为空 
 * 
*/

#include <bits/stdc++.h>
using namespace std;

struct Oper
{
    char name;
    int priority;
    Oper(char ch):name(ch), priority(0){};
};

int cal(stack<int>& nums, char ch)
{
    int a, b;
    a = nums.top();
    nums.pop();
    b = nums.top();
    nums.pop();
    if(ch == '+')
    {
        return a + b;
    }
    else if(ch == '-')
    {
        return b - a;
    }
    else if(ch == 'x')
    {
        return a * b;
    }
    else
    {
        return b / a;
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; i++)
    {
        string str;
        stack<Oper>ops;
        stack<int>nums;
        cin>>str;
        for(auto item : str)
        {
            if(isdigit(item))
            {
                nums.push(item - '0');
            }
            else
            {
                Oper temp(item);
                if(item == '+' || item == '-')
                {
                    temp.priority = 1;
                }
                else
                {
                    temp.priority = 2;

                }
                while(!ops.empty() && ops.top().priority >= temp.priority)
                {
                    nums.push(cal(nums, ops.top().name));
                    ops.pop();
                }
                ops.push(temp);
            }
        }
        while(!ops.empty())
        {
            nums.push(cal(nums, ops.top().name));
            ops.pop();
        }

        if(nums.top() == 24)
        {
            printf("Yes");
        }
        else
        {
            printf("No");
        }
        printf("\n");
    }
    return 0;
}
