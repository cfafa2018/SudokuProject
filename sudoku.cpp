#include <iostream>
#include <algorithm>
#include <cstring>
#include <stdlib.h>
#include <fstream>
using namespace std;

bool AllisNum(string str)//判断输入是否全是数字
{
    for (int i = 0; i < str.size(); i++)
    {
        int tmp = (int)str[i];
        if (tmp >= 48 && tmp <= 57)
        {
            continue;
        }
        else
        {
            return false;
        }
    }
    return true;
}

void RightShift(int *arr, int N, int K){//对数据进行移位
    int pos =  K % N;
    if (pos == 0);
    else {
        while (pos--) {
            int temp = arr[N - 1];
            for (int i = N - 1; i > 0; i--) arr[i] = arr[i - 1];
            arr[0] = temp;
        }
    }
}

int map[9][9];
bool isPlace(int count){
    int row = count / 9;
    int col = count % 9;
    int j;
    //同一行
    for(j = 0; j < 9; ++j){
        if(map[row][j] == map[row][col] && j != col){
            return false;
        }
    }
    //同一列
    for(j = 0; j < 9; ++j){
        if(map[j][col] == map[row][col] && j != row){
            return false;
        }
    }
    //同一小格
    int tempRow = row / 3 * 3;
    int tempCol = col / 3 * 3;
    for(j = tempRow; j < tempRow + 3;++j){
        for(int k = tempCol; k < tempCol + 3; ++k){
            if(map[j][k] == map[row][col] && j != row && k != col){
                return false;
            }
        }
    }
    return true;
}
ofstream output;

void backtrace(int count){
    if(count == 81){
        for(int i = 0; i < 9; ++i){
            for(int j =  0; j < 8; ++j){
                
                output<<map[i][j];
                output<<" ";
            }
            output<<map[i][8]<<endl;
        }
        output<<"\n";
        return;
    }
    int row = count / 9;
    int col = count % 9;
    if(map[row][col] == 0){
        for(int i = 1; i <= 9; ++i){
            map[row][col] = i;//赋值
            if(isPlace(count)){//可以放
                backtrace(count+1);//进入下一层
            }
        }
        map[row][col] = 0;//回溯
    }
    else{
        backtrace(count+1);
    }
}

int main(int argc, const char * argv[]) {
    
    if(strcmp(argv[1], "-c") == 0){//判断是否是生成数独
        ofstream write;
        write.open("sudoku.txt", std::ios::out | ios::trunc);  //以写入和覆盖文件的方式打开.txt文件，没有的话就创建该文件。
        if (!write.is_open())
            return 0;
        
        if(AllisNum(argv[2])){
            int shudu[9][9]={0};
            int arr[]={1,2,3,4,5,6,7,8};
            shudu[0][0] = 9;//数独第一个数字为9
            for(int i = 0; i < atoi(argv[2]); i ++){
                next_permutation(arr, arr+8);//对1～8进行全排列
                for(int j =0; j < 8; j ++){//将arr数组里排列好的数赋给shudu第一行
                    shudu[0][j+1] = arr[j];
                }
                int num[9]={0,3,6,1,4,7,2,5,8};
                int temp[9];
                memcpy(&temp, &shudu[0], sizeof(shudu[0]));
                for(int j=0; j < 9; j ++){//通过第一行进行下面8列的移数
                    int n =9;
                    RightShift(shudu[0], n, num[j]);
                    int k;
                    for(k = 0; k < 8; k ++){//输出数据
                        write<<shudu[0][k];
                        write<<" ";
                    }
                    write<<shudu[0][k]<<endl;
                    memcpy(&shudu[0], &temp, sizeof(temp));
                }
                write<<"\n";
            }
        }
        else cout<<"Wrong input\n";
        if (write.is_open())
            write.close();
    }
    
    else if (strcmp(argv[1], "-s") == 0){//判断是否为解数独
            FILE *fp = fopen(argv[2], "r");//第一个参数包含欲打开的文件路径及文件名
            if(!fp) {
                cout<<"File open error!\n";
                return -1;
            }
            output.open("sudokuOutput.txt", ios::out | ios::trunc);
            int temp,i = 0, j = 0;
            while ((temp = getc(fp)) != EOF) {
                if(temp < '0' || temp > '9') continue;
                map[i][j] = temp - '0';
                j ++;
                if(j == 9){//将数字一个一个读入数组
                    i ++;
                    j = 0;
                }
                if(i == 9){//读满一个9X9的矩阵，进行一次解数独
                    backtrace(0);
                    i = 0;
                    j = 0;
                }
            }
        fclose(fp);
        output.close();
    }
    
    else printf("Wrong input\n");
    return 0;
}