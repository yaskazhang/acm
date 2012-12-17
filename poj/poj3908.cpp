/*
POJ3908
�����Ǹ���N����,�����ֲ������ϲ�����ѯ��ɾ��
(ɾ����ʾ��һ��������������ĵ�ָ���)
�ʲ�ѯ���Ľ���������Ͳ������Ľ���ֱ��ж���
***��������
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#define MAXN 1000000
using namespace std;
int fa[MAXN], loc[MAXN];
bool use[MAXN];
int n, s, x, y, fx, fy, res[2];
int father(int v)
{
    if (fa[v] != v) fa[v] = father(fa[v]);
    return fa[v];
}
char c;
int main()
{
    while ((scanf("%d", &n)) != EOF)
    {
    s = n;
    memset(use, false, sizeof(use));
    memset(res, 0, sizeof(res));
    for (int i = 1; i <= n; ++i)
    {
        fa[i] = i;
        loc[i] = i;
    }
    while (scanf("\n%c", &c))
    {
        if (c == 'e') break;
        if (c == 'c'){//���鼯�ĺϲ�
            scanf("%d%d", &x, &y);
            fx = father(loc[x]), fy = father(loc[y]);
            if (fx != fy){
                fa[fx] = fy;
                use[x] = true;
                use[y] = true;
            }
        }
        else if (c == 'q'){//���鼯�Ĳ�ѯ
            scanf("%d%d", &x, &y);
            fx = father(loc[x]), fy = father(loc[y]);
            ++res[fx == fy];
        }
        else{//���鼯��ɾ��
            scanf("%d", &x);
            if (use[x]){
                loc[x] = ++s;
                fa[s] = s;
                use[x] = false;
            }
        }
    }
    printf("%d , %d\n", res[1], res[0]);
    }
    return 0;
}