//
// Created by 19014 on 2022/4/21.
//

#ifndef UNTITLED1_CLASSFILE_H
#define UNTITLED1_CLASSFILE_H

#include <sstream>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <Eigen/Dense>
#include <numeric>

using namespace  std;
#define XLength 3
#define YLength 3
#define ZLength 3
#define NodeNum 18
#define scale 10
//class node{
//public:
//    node();
//    void SetNum(int n);
//    int GetNUm();
//    //vector<double> GetG();
//    //node** GetPNeigh();
//
//private:
//    int num;
//    //vector<double> G;
//    //node* pNeigh[4];
//    double ISum = 0;
//    double pad = 0;
//};

class loc {
public:
    loc(int a);
    loc(int i,int j,int k);
    loc();
    int GetX();
    int GetY();
    int GetZ();
    int GetNum();
private:
    int x,y,z,num;
};
void fill_in_iB(vector<string> tmp,vector<double> &Isum);
void fill_in_RorV(vector<string> tmp,vector<vector<double>> &GArr);
void fill_in_pads(vector<string> tmp,vector<double> &pads);
void ReadFile(string Address,vector<vector<double>> &GArr,vector<double> &Isum,vector<double> &pads);
//void ReadData(std::vector<std::vector<double>> &GArr,std::vector<double> &Isum,std::vector<int> &pads);

std::vector<std::vector<double>> ConverseGArr(std::vector<std::vector<double>>GArr,std::vector<double> &Isum,std::vector<double> pads);
Eigen::VectorXd solve(std::vector<double> ISum,std::vector<std::vector<double>> GArr);

void write_in_txt(string address,vector<double> pads,Eigen::VectorXd x);
#endif //UNTITLED1_CLASSFILE_H
