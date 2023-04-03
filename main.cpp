#include<iostream>
#include<stack>


using namespace std;

using namespace std;
//vector<int> loc(4,0);//int loc[4]; //这里使用4个整型值标记
struct state {
    int loc[4];
};
class FarmerProblem {
public:
    bool safe(state st);//检查当前状态是否安全
    int  farmer(state st) const; //农夫所在位置
    int cabbage(state st)const;//菜所在位置
    int sheep(state st)const;//羊所在位置
    int wolf(state st)const;//狼所在位置
    void doit();//寻找移动序列
    void display() const;//输出可能的移动序列


private:
    int route[16]; //存储路径或者

};

//loc中位依次为农夫，白菜，羊，狼。


int FarmerProblem::farmer(state st) const
{
    return  !(st.loc[0] == 0);
}

int FarmerProblem::cabbage(state st) const
{
    return  !(st.loc[1] == 0);
}

int FarmerProblem::sheep(state st) const
{
    return  !(st.loc[2] == 0);
}

int FarmerProblem::wolf(state st) const
{
    return  !(st.loc[3] == 0);
}

bool FarmerProblem::safe(state st)
{   //农夫没有看牢白菜，并且让羊和白菜在一起，危险！
    if (farmer(st) != cabbage(st) && cabbage(st) == sheep(st)) return false;
    //农夫没有看牢羊，并且让羊和狼在一起，危险！
    if (farmer(st) != sheep(st) && sheep(st) == wolf(st)) return false;
    //其他情况，安全！
    return true;
}

void FarmerProblem::doit()
{//请编写找一个可实现序列的算法

    stack<state> st;
    state now;//now表示现在
    int d = 0;
    for (int i = 1; i <= 15; i++)//初始化route数组
        route[i] = -1;

    for (int i = 0; i < 4; i++) {//设置初值
        now.loc[i] = 0;
    }
    st.push(now);//将初始状态放入栈
    route[0] = 0;//标记初始状态以经过
    //int test1 = 0, test2 = 0;//test1表示当前状态(十进制)，test2表示假设状态(十进制)
    while (!st.empty() && route[15] == -1)//如果栈不空或者都没有到达对岸就继续搜索
    {
        now = st.top();//获取栈顶当前状态
        int test1 = 8 * (now.loc[0]) + 4 * (now.loc[1]) + 2 * (now.loc[2]) + 1 * (now.loc[3]);//将状态转化为十进制

        while (d < 4) {//农夫有四种选择，带菜、羊、狼或者不带

            if (d >= 1) {//d>1表示带菜、羊、狼中的一个
                state c = now;//为了不破坏状态用c来代替
                if (now.loc[0] == now.loc[d])//如果农夫和其中一个对象在同一个地方
                {
                    if (c.loc[0] == 0)//如果是0就过河换为1
                    {
                        c.loc[0] = 1;
                        c.loc[d] = 1;
                    }
                    else//如果是1就过河换为0
                    {
                        c.loc[0] = 0;
                        c.loc[d] = 0;
                    }
                    int test2 = 8 * (c.loc[0]) + 4 * (c.loc[1]) + 2 * (c.loc[2]) + 1 * (c.loc[3]);//将假设状态转化为十进制

                    if (safe(c) && route[test2] == -1)//如果假设情况过河后状态是合法的同时这种状态还没有经过（判断没有经过可以保证一种状态只经过一次）
                    {
                        st.push(c);//将这种状态放入栈中
                        route[test2] = test1;//标记这种状态已经经过
                        d = 0;//假设状态可行，可以进行下一个状态的判断了
                        break;
                    }
                }

            }

            if (d == 0) {
                state c = now;//这种情况是考虑农夫不带任何东西过河，与上面判断情况相同
                if (c.loc[0] == 0)
                {
                    c.loc[0] = 1;
                }
                else
                {
                    c.loc[0] = 0;
                }
                int test2 = 8 * (c.loc[0]) + 4 * (c.loc[1]) + 2 * (c.loc[2]) + 1 * (c.loc[3]);//将假设状态转化为十进制
                if (safe(c) && route[test2] == -1)
                {
                    st.push(c);
                    route[test2] = test1;
                    d = 0;
                    break;
                }
            }
            d++;
        }

        if (d == 4) {//四种选择都不行，出栈回到上一个状态
            st.pop();
        }

    }
    if (route[15] != -1)//如果最终全部都过了河，倒序输出过河步骤
    {
        display();
    }



}


void FarmerProblem::display() const
{  //显示移动路径
    cout << "1111" << endl;//15情况没有后继直接输出
    for (int i = 15; i > 0; i = route[i])
    {
        switch (route[i])//输出该状态十进制数对应的二进制数
        {
            case 0:cout << "0000" << endl; break;
            case 1:cout << "0001" << endl; break;
            case 2:cout << "0010" << endl; break;
            case 3:cout << "0011" << endl; break;
            case 4:cout << "0100" << endl; break;
            case 5:cout << "0101" << endl; break;
            case 6:cout << "0110" << endl; break;
            case 7:cout << "0111" << endl; break;
            case 8:cout << "1000" << endl; break;
            case 9:cout << "1001" << endl; break;
            case 10:cout << "1010" << endl; break;
            case 11:cout << "1011" << endl; break;
            case 12:cout << "1100" << endl; break;
            case 13:cout << "1101" << endl; break;
            case 14:cout << "1110" << endl; break;
        }
        if (i == 0)
            break;
    }
}

int main() {

    FarmerProblem a;
    a.doit();

    return 0;


}
