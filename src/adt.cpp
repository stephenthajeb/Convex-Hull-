#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "adt.h"

void MakeEmpty(struct Array *T){
    Neff(*T) = 0;
}

void TulisIsi (struct Array T){
    printf("[");
    for (int i=1;i<=Neff(T);i++){
        printf(" (%d,%d) ",ElmtX(T,i),ElmtY(T,i));
    }
    printf("]");
}

int Search(struct Array T, struct Point P){
    int i = 1;
    int found=0;
    while (i <= Neff(T) && (found==0)){
        if ((ElmtX(T,i)==P.X) && (ElmtY(T,i)==P.Y)){
            found = 1;
        } else {
            i ++;
        }
    }
    return found;
}

void AddAsLastEl (struct Array * T, struct Point P){
    Neff(*T) +=1;
    ElmtX(*T,Neff(*T)) = P.X;
    ElmtY(*T,Neff(*T)) = P.Y;
}

void AddElUnik (struct Array * T, struct Point P){
    if(! Search(*T,P)){
        AddAsLastEl (T,P);
    } 
}

void PrintPoint(struct Point P){
    printf("(%d,%d)",P.X,P.Y);
}

int ValueofA(struct Point acuan,struct Point random){
    return (random.Y-acuan.Y);
}

int ValueofB(struct Point acuan,struct Point random){
    return (acuan.X-random.X);
}

int ValueofC(struct Point acuan,struct Point random){
    return (acuan.X*random.Y) - (acuan.Y*random.X);
}

int Calculate(int A,int B,int C,struct Point P){//Calculate ax+by value
    return (A*P.X)+(B*P.Y)-C;
}

int IsAllSameSign(int counterPos, int counterMin){
   return (!((counterPos >0)&&(counterMin >0)));
}

void GenerateNPoint (struct Array *T,int n){
    for(int i=1;i<=n;i++){
       ElmtX(*T,i) = -100+ (rand() % (200+1));
       ElmtY(*T,i) = -100+ (rand() % (200+1));
       Neff(*T) += 1;
    }
}

void PrintGeneratedPoint (struct Array T,int n){
    for(int i=1;i<=n;i++){
        PrintPoint(Elmt(T,i));
    }
    printf("\n");
}

void ConvexHullPoints(struct Array *CHull,struct Array *CHullSet, struct Array T, int n){
    if (n==1){
        AddElUnik(CHull,Elmt(T,1));
        AddElUnik(CHullSet,Elmt(T,1));
    } else {
        for (int i=1;i<=n-1;i++){
            for (int j=i+1;j<=n;j++){
                int A = ValueofA(Elmt(T,i),Elmt(T,j));
                int B = ValueofB(Elmt(T,i),Elmt(T,j));
                int C = ValueofC(Elmt(T,i),Elmt(T,j));
                int k=1;
                int counterPos=0;
                int counterMin=0;
                while ((k<=n)){
                    if ((k!=i) && (k!=j) && (IsAllSameSign(counterMin,counterPos))){
                    // if ((k!=i) && (k!=j)){
                        int val = Calculate(A,B,C,Elmt(T,k));
                        if (val > 0){
                            counterPos +=1;
                        }
                        if (val < 0){
                            counterMin +=1;
                        }
                    }   
                    k++;
                }
                if ((counterMin== 0 ) || (counterPos==0)){//Memenuhi titik ke i dan j membentuk Convex Hull
                    AddAsLastEl(CHull,Elmt(T,i));
                    AddAsLastEl(CHull,Elmt(T,j));
                    AddElUnik(CHullSet,Elmt(T,i));
                    AddElUnik(CHullSet,Elmt(T,j));
                }
            }
        }
    }
}
