#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
#define INF 1000000000
#define MAXN 1024
#define MAXM 10485760
using namespace std;
struct edge{
    int x, y, f, c, next;
}e[MAXM];
int eid, p[MAXN];//�ڽӱ����ݽṹ
int n, m, source, sink;//source���Դ�㣬sink��ǻ��
int d[MAXN], pre[MAXN], path[MAXN];//pre������·���Ͻڵ��ǰ����path��¼������������չ������
queue<int> q;//SPFAʹ�õĶ���
bool use[MAXN];//����Ƿ��ڶ�����
void insert(int x, int y, int f, int c)
{
    e[eid].x = x;
    e[eid].y = y;
    e[eid].f = f;
    e[eid].c = c;
    e[eid].next = p[x];
    p[x] = eid++;
}
void insert1(int x, int y, int f, int c)
{
    insert(x, y, f, c);
    insert(y, x, 0, -c);
}
void insert2(int x, int y, int f, int c)
{
    insert1(x, y, f, c);
    insert1(y, x, f, c);
}
void mapinit()
{
    memset(p, -1, sizeof(p));
    eid = 0;
}
bool spfa(int s)
{
    memset(use, false, sizeof(use));
    int u, v;
    for (int i = 1; i <= n; ++i) d[i] = INF;
    while (!q.empty()) q.pop();
    q.push(s);
    d[s] = 0;
    pre[s] = -1;
    use[s] = true;
    while (!q.empty())
    {
        u = q.front();
        q.pop();
        for (int i = p[u]; i != -1; i = e[i].next)
        {
            v = e[i].y;
            if ((e[i].f != 0) && (d[u] + e[i].c < d[v])){
                d[v] = d[u] + e[i].c;
                pre[v] = u;
                path[v] = i;
                if (!use[v]){
                    use[v] = true;
                    q.push(v);
                }
            }
        }
        use[u] = false;
    }
    return (d[sink] != INF);
}
int argument()
{
    int delta = INF, res = 0;
    for (int i = sink; pre[i] != -1; i = pre[i])
        delta = min(delta, e[path[i]].f);
    for (int i = sink; pre[i] != -1; i = pre[i])
    {
        e[path[i]].f -= delta;
        e[path[i] ^ 1].f += delta;
        res += e[path[i]].c * delta;
    }
    return res;
}
int maxcostflow()
{
    int sum = 0;
    while (spfa(source)) sum += argument();
    return sum;
}