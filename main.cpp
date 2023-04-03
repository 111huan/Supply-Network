#include<iostream>
#include<stack>


using namespace std;

using namespace std;
//vector<int> loc(4,0);//int loc[4]; //����ʹ��4������ֵ���
struct state {
    int loc[4];
};
class FarmerProblem {
public:
    bool safe(state st);//��鵱ǰ״̬�Ƿ�ȫ
    int  farmer(state st) const; //ũ������λ��
    int cabbage(state st)const;//������λ��
    int sheep(state st)const;//������λ��
    int wolf(state st)const;//������λ��
    void doit();//Ѱ���ƶ�����
    void display() const;//������ܵ��ƶ�����


private:
    int route[16]; //�洢·������

};

//loc��λ����Ϊũ�򣬰ײˣ����ǡ�


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
{   //ũ��û�п��ΰײˣ���������Ͱײ���һ��Σ�գ�
    if (farmer(st) != cabbage(st) && cabbage(st) == sheep(st)) return false;
    //ũ��û�п����򣬲������������һ��Σ�գ�
    if (farmer(st) != sheep(st) && sheep(st) == wolf(st)) return false;
    //�����������ȫ��
    return true;
}

void FarmerProblem::doit()
{//���д��һ����ʵ�����е��㷨

    stack<state> st;
    state now;//now��ʾ����
    int d = 0;
    for (int i = 1; i <= 15; i++)//��ʼ��route����
        route[i] = -1;

    for (int i = 0; i < 4; i++) {//���ó�ֵ
        now.loc[i] = 0;
    }
    st.push(now);//����ʼ״̬����ջ
    route[0] = 0;//��ǳ�ʼ״̬�Ծ���
    //int test1 = 0, test2 = 0;//test1��ʾ��ǰ״̬(ʮ����)��test2��ʾ����״̬(ʮ����)
    while (!st.empty() && route[15] == -1)//���ջ���ջ��߶�û�е���԰��ͼ�������
    {
        now = st.top();//��ȡջ����ǰ״̬
        int test1 = 8 * (now.loc[0]) + 4 * (now.loc[1]) + 2 * (now.loc[2]) + 1 * (now.loc[3]);//��״̬ת��Ϊʮ����

        while (d < 4) {//ũ��������ѡ�񣬴��ˡ����ǻ��߲���

            if (d >= 1) {//d>1��ʾ���ˡ������е�һ��
                state c = now;//Ϊ�˲��ƻ�״̬��c������
                if (now.loc[0] == now.loc[d])//���ũ�������һ��������ͬһ���ط�
                {
                    if (c.loc[0] == 0)//�����0�͹��ӻ�Ϊ1
                    {
                        c.loc[0] = 1;
                        c.loc[d] = 1;
                    }
                    else//�����1�͹��ӻ�Ϊ0
                    {
                        c.loc[0] = 0;
                        c.loc[d] = 0;
                    }
                    int test2 = 8 * (c.loc[0]) + 4 * (c.loc[1]) + 2 * (c.loc[2]) + 1 * (c.loc[3]);//������״̬ת��Ϊʮ����

                    if (safe(c) && route[test2] == -1)//�������������Ӻ�״̬�ǺϷ���ͬʱ����״̬��û�о������ж�û�о������Ա�֤һ��״ֻ̬����һ�Σ�
                    {
                        st.push(c);//������״̬����ջ��
                        route[test2] = test1;//�������״̬�Ѿ�����
                        d = 0;//����״̬���У����Խ�����һ��״̬���ж���
                        break;
                    }
                }

            }

            if (d == 0) {
                state c = now;//��������ǿ���ũ�򲻴��κζ������ӣ��������ж������ͬ
                if (c.loc[0] == 0)
                {
                    c.loc[0] = 1;
                }
                else
                {
                    c.loc[0] = 0;
                }
                int test2 = 8 * (c.loc[0]) + 4 * (c.loc[1]) + 2 * (c.loc[2]) + 1 * (c.loc[3]);//������״̬ת��Ϊʮ����
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

        if (d == 4) {//����ѡ�񶼲��У���ջ�ص���һ��״̬
            st.pop();
        }

    }
    if (route[15] != -1)//�������ȫ�������˺ӣ�����������Ӳ���
    {
        display();
    }



}


void FarmerProblem::display() const
{  //��ʾ�ƶ�·��
    cout << "1111" << endl;//15���û�к��ֱ�����
    for (int i = 15; i > 0; i = route[i])
    {
        switch (route[i])//�����״̬ʮ��������Ӧ�Ķ�������
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
