/**
 * 题目地址:http://118.190.20.162/view.page?gpid=T86
 * 该题输入若干组样例 每个样例包含若干个进程的指令,以此来进行进程间的通信
 * 最终判断并且输出通信过程中是否发生死锁
 * 1. 使用的数据结构:
 *   用队列存储每个进程的收发指令 由于有n个进程 因此用一个队列数组queue<Command>process[n]存储所有进程的收发指令
 *   用数组waits[n]代表n个进程的状态: 0表示就绪状态(正常状态), 1表示等待状态
 * 
 * 2. 模拟进程间进行通信的过程:
 * 如果某一个进程执行时,能找到与队首的指令相匹配的指令
 * 此时考虑到相匹配的两个指令所在的进程可能有一者是之前处于等待状态 因此需要到数组waits中进行检测:
 * 若收发的两个指令中有一者为之前等待进程的指令 则该进程变恢复为就绪状态
 * 更新waits相应元素的值 使相应的进程状态标记为就绪状态(置0)
 * 然后分别弹出该次匹配的收发指令,即在该次成功收发所关联的两个进程中的弹出各自的队首指令
 * 此时需要检测成功进行该次收发所关联的两个的进程各自的指令队列是否为空 以此更新指令队列非空的进程个数workProcess
 * 如果某一个进程执行时,未能找到与队首指令相匹配的指令
 * 若该进程之前为正常状态,此时应变为等待状态 否则继续保持等待状态
 * 同时对于之前处于等待状态的进程:更新数组waits相应元素的值 将这些之前处于就绪状态的进程的状态标记为等待状态(置1)
 * 此时等待进程个数增加,更新waitProcess的值:waitProcess++
 * 
 * 3. 判断最终是否发生死锁:
 * 引入变量workProcess记录队列数组中非空队列的个数 即需要与其他进程通信的进程的个数
 * 当某一个进程的指令队列非空时,代表该进程仍然需要与其他进程进行通信
 * 当某一个进程的指令队列为空时,代表该进程已经成功执行
 * 若最终所有的进程都成功执行,未发生死锁,此时每一个进程的指令队列都为空(workProcess为0) 即所有进程均成功执行,未发生死锁的条件为workProcess==0
 * 引入变量waitProcess代表等待进程的个数
 * 若等待进程的个数和指令队列非空的进程个数相同(waitProcess等于workProcess) 则所有进行通信(指令队列非空)的进程将发生死锁
 * 即死锁的触发条件为waitProcess == workProcess
 */


#include <bits/stdc++.h>
using namespace std;

struct Command
{
    char signal;
    int id;
    Command(char ch, int num) : signal(ch), id(num){};
};

int main()
{

    int T, n, i, j, k;
    scanf("%d%d", &T, &n);
    getchar();
    for (i = 0; i < T; i++)
    {
        string str;
        queue<Command> process[n];                              //队列数组存储每一个进程的指令
        int workProcess = n, waits[n] = {0}, waitProcess = 0;
        bool deadLock = false;                                  //判断死锁的标志
        //初始化队列数组 使得process存储所有进程的指令
        for (j = 0; j < n; j++)
        {
            getline(cin, str);
            for (unsigned int tempi = 0; tempi < str.size(); tempi++)
            {
                if (isalpha(str[tempi]))
                {
                    char ch = str[tempi];
                    int sum = 0;
                    while (str[tempi] != ' ' && isdigit(str[++tempi]))
                    {
                        sum = str[tempi] - '0' + sum * 10;
                    }
                    process[j].push(Command(ch, sum));
                }
            }
        }
        // 模拟进程间的通信的过程并且判断通信过程中是否发生死锁
        for (k = 0; workProcess; k = (k + 1) % n)
        {
            // 等待进程个数与通信进程个数相等 发生死锁
            if (waitProcess == workProcess)
            {
                deadLock = true;
                break;
            }
            // 该进程需要进行通信 其指令队列非空
            if (!process[k].empty())
            {
                // 该进程的队首指令找到与之匹配的指令
                if (!process[process[k].front().id].empty() && process[process[k].front().id].front().id == k && process[k].front().signal != process[process[k].front().id].front().signal)
                {
                    // 该进程之前处于等待状态 更新其为(正常)就绪状态
                    if (waits[k])
                    {
                        waits[k] ^= 1;
                        waitProcess--;
                    }
                    // 与该进程通信的进程之前处于等待状态 更新其为(正常)就绪状态
                    if (waits[process[k].front().id])
                    {
                        waits[process[k].front().id] ^= 1;
                        waitProcess--;
                    }

                    // 弹出两个成功匹配的指令时 注意顺序:
                    // 先弹出与当前进程的队首指令匹配的指令 然后弹出当前进程的队首指令

                    // 弹出与该指令匹配的指令 并且检测其所在的进程的指令队列是否为空 以此确定是否更新通信进程的个数
                    process[process[k].front().id].pop();
                    if (process[process[k].front().id].empty())
                    {
                        workProcess--;
                    }

                    // 弹出该指令 并且检测其所在的进程的指令队列是否为为空 以此确定是否更新通信进程的个数
                    process[k].pop();
                    if (process[k].empty())
                    {
                        workProcess--;
                    }
                }
                // 未找到匹配指令
                else
                {
                    // 若该进程之前处于就绪状态 则该进程变为等待状态 等待进程个数增加
                    if (!waits[k])
                    {
                        waits[k] ^= 1;
                        waitProcess++;
                    }
                }
            }
        }
        printf("%d\n", deadLock);
    }
    return 0;
}
