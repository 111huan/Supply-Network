#include "ClassFile.h"

int loc::GetX() {
    return x;
}

int loc::GetY() {
    return y;
}

int loc::GetZ() {
    return z;
}

loc::loc() {
    x = -1,y = -1,z = -1;

}

loc::loc(int a) {
    z = (a)/(XLength *YLength);
    y = (a)%(XLength *YLength)/YLength;
    x = (a)%(XLength *YLength)%YLength;
    num = a;
}

loc::loc(int i, int j, int k) {
    x = i;
    y = j;
    z = k;
    if(z==0){
        num = YLength * y + x ;
    }
    else{
        num = XLength * YLength * (z-1)+ YLength * y + x;
    }


}

int loc::GetNum() {
    return num;
}
void fill_in_iB(vector<string> tmp,vector<double> &Isum){
    int x,y,z;
    double I;
    stringstream ss(tmp[1]);
    vector<string> sub;
    string tmp_str;
    while (getline(ss,tmp_str,'_')){
        sub.push_back(tmp_str);
    }
    z = atof(sub[0].substr(1,1).c_str())-1;
    y = atof(sub[1].c_str())/scale;
    x =atof(sub[2].c_str())/scale;
    I = atof(tmp[3].substr(0,tmp[3].length()).c_str());

    loc loc1(x,y,z);
    Isum[loc1.GetNum()] = I;
}
void fill_in_RorV(vector<string> tmp,vector<vector<double>> &GArr){
    int x1,y1,z1,x2,y2,z2;
    double G;
    stringstream ss1(tmp[1]);
    stringstream ss2(tmp[2]);
    vector<string> sub1,sub2;
    string tmp_str = "\0";

    while(getline(ss1,tmp_str,'_')){
        sub1.push_back(tmp_str);
    }
    while(getline(ss2,tmp_str,'_')){
        sub2.push_back(tmp_str);
    }
    z1 = atof(sub1[0].substr(1).c_str())-1;
    x1 = atof(sub1[1].c_str())/scale;
    y1 = atof(sub1[2].c_str())/scale;
    z2 = atof(sub2[0].substr(1).c_str())-1;
    x2 = atof(sub2[1].c_str())/scale;
    y2 = atof(sub2[2].c_str())/scale;
    G = atof(tmp[3].c_str());


    loc loc1(x1,y1,z1);
    loc loc2(x2,y2,z2);
    GArr[loc1.GetNum()][loc2.GetNum()] = G;

//    for(int i=0;i<NodeNum;i++){
//        for(int j=0;j<NodeNum;j++){
//            cout<<GArr[i][j]<<" ";
//        }
//        cout<<endl;
//    }
//    cout<<endl;
}
void fill_in_pads(vector<string> tmp,vector<double> &pads) {
    tmp[1] = tmp[1].substr(tmp[1].find('n') + 1);
    int x, y, z;
    double V;
    stringstream ss(tmp[1]);
    vector<string> sub;
    string tmp_str;
    while (getline(ss, tmp_str, '_')) {
        sub.push_back(tmp_str);
    }
        z = atof(sub[0].c_str()) - 1;
        y = atof(sub[1].c_str()) / scale;
        x = atof(sub[2].c_str()) / scale;
        V = atof(tmp[2].c_str());
        loc loc1(x,y,z);
        pads[loc1.GetNum()] = V;
}
void ReadFile(string Address,vector<vector<double>> &GArr,vector<double> &Isum,vector<double> &pads){
    std::vector<double> TempSTL;//初始化GArr、Isum
    for(int i=0;i<NodeNum;i++){
        TempSTL.push_back(0);
    }
    for(int i=0;i<NodeNum;i++){
        GArr.push_back(TempSTL);
    }
    for(int i=0;i<NodeNum;i++){
        Isum.push_back(0);
    }
    for(int i=0;i<NodeNum;i++){
        pads.push_back(0);
    }

    vector<vector<string>> tmp;
    vector<string> tmp_vec;
    string tmp_str,tmp_str1;
    ifstream DataFile(Address,ios::in);
    int n = 0;
    while (getline(DataFile,tmp_str)){
        stringstream ss(tmp_str);
        while(getline(ss,tmp_str1,' ')){
            tmp_vec.push_back(tmp_str1);
        }
        tmp.push_back(tmp_vec);
        char kd = tmp[n][0].c_str()[0];
        n++;
        if(kd=='R' or kd=='V'){
            fill_in_RorV(tmp_vec,GArr);
        }
        else if(kd=='i'){
            fill_in_iB(tmp_vec,Isum);
        }
        else if(kd=='v'){
            fill_in_pads(tmp_vec,pads);
        }
        tmp_vec.clear();
    }
//    for(int i=0;i<NodeNum;i++){
//        for(int j=0;j<NodeNum;j++){
//            cout<<GArr[i][j]<<" ";
//        }
//        cout<<endl;
//    }
 //   cout<<endl;
}

std::vector<std::vector<double>> ConverseGArr(std::vector<std::vector<double>>GArr,vector<double> &Isum,vector<double> pads){

//    for(int i=0;i<NodeNum;i++){
//        for(int j=0;j<NodeNum;j++){
//            cout<<GArr[i][j]<<" ";
//        }
//        cout<<endl;
//    }
//    cout<<endl;


    // Build and init the ret matrix
    std::vector<std::vector<double>> GArr1(0);
    vector<double> TempSTL;
    for(int i=0;i<NodeNum;i++){
        TempSTL.push_back(0);
    }
    for(int i=0;i<NodeNum;i++){
        GArr1.push_back(TempSTL);
    }


    for(int i=0;i<NodeNum;i++){
        for(int j=0;j<NodeNum;j++){
            if(GArr[i][j]!=0){
                GArr1[i][j] = GArr[i][j];
                GArr1[j][i] = GArr[i][j];
            }
            else if(GArr[j][i]!=0){
                GArr1[i][j] = GArr[j][i];
                GArr1[j][i] = GArr[j][i];
            }
            else{
                GArr1[i][j] = 0;
                GArr1[j][i] = 0;
            }

        }
    }
    for(int i=0;i<NodeNum;i++){
        for(int j=0;j<NodeNum;j++){
            if(pads[j]!=0){
                Isum[j] = GArr1[i][j]*pads[j]*(-1)+Isum[j];
            }
        }
    }

    double sum = 0;
    for(int i=0;i<NodeNum;i++){
        sum = 0;
        for(int j=0;j<NodeNum;j++){
            sum += GArr1[i][j];
        }
        GArr1[i][i] = -1*sum;
    }
    for(int i=0;i<NodeNum;i++){
        for(int j=0;j<NodeNum;j++){
            if(pads[j]!=0){
                GArr1[i][j] = 0;
            }
        }
    }



    int PadsNo = 0;
    for(int i=0;i<NodeNum;i++){
        if(pads[i]!=0){
            PadsNo++;
            GArr1.erase(GArr1.begin()+i-PadsNo);
            Isum.erase(Isum.begin()+i-PadsNo);
        }
    }
    PadsNo = 0;
    for(int i=0;i<GArr1.size();i++){
        for(int j=0;j<NodeNum;j++){
            if(pads[j]!=0){
                GArr1[i].erase(GArr1[i].begin()-PadsNo);
            }
        }
    }

//        cout<<endl;
//        for(int i=0;i<NodeNum;i++){
//        for(int j=0;j<NodeNum;j++){
//            cout<<GArr1[j][i]<<" ";
//
//        }
//            cout<<endl;
//    }
//    cout<<endl;
        return GArr1;
}
Eigen::VectorXd solve(std::vector<double> ISum,std::vector<std::vector<double>> GArr){
    Eigen::VectorXd b = Eigen::Map<Eigen::VectorXd> (ISum.data(),ISum.size());
    Eigen::MatrixXd A(GArr.size(), GArr[0].size());
    for(int ri=0; ri<GArr.size(); ri++)
        A.col(ri) = Eigen::Map<Eigen::VectorXd> (GArr[ri].data(), GArr[ri].size());
        Eigen::VectorXd x = A.fullPivLu().solve(b);
    cout<<"A="<<endl<<A<<endl;
    cout<<"b="<<endl<<b<<endl;
    cout<<"x="<<x<<endl;

    return x;
}

void write_in_txt(string address,vector<double> pads,Eigen::VectorXd x){
    ofstream ofs;
    ofs.open(address,ios::out);

    ofs<<"x"<<','<<"y"<<','<<"V"<<endl;
    for(int i=0;i<XLength*YLength;i++){
        loc loc1(i);
            ofs<<loc1.GetX()<<','<<loc1.GetY()<<','<<x.row(i)<<endl;
            cout<<endl;
    }

    ofs.close();
}



