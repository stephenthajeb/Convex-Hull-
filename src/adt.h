/*ADT Points*/
struct Point {
  int X; /* absis   */
  int Y; /* ordinat */
};

/*ADT ARRAY of Points*/
struct Array {
    struct Point TI[101];
    int Neff;
};

#define Neff(T)   (T).Neff
#define TI(T)     (T).TI
#define Elmt(T,i) (T).TI[(i)]
#define ElmtX(T,i) (T).TI[(i)].X
#define ElmtY(T,i) (T).TI[(i)].Y

void MakeEmpty(struct Array *T);

void TulisIsi (struct Array T);

int Search(struct Array T, struct Point P); // Mengecek apakah ada point P di dalam array T

void AddAsLastEl (struct Array * T, struct Point P);

void AddElUnik (struct Array * T, struct Point P);

void PrintPoint(struct Point P);

int ValueofA(struct Point acuan,struct Point random); //Mengkalkulasi nilai a dalam persamaan ax+by=c dari garis dibentuk 2 titik

int ValueofB(struct Point acuan,struct Point random);//Mengkalkulasi nilai b dalam persamaan ax+by=c dari garis dibentuk 2 titik

int ValueofC(struct Point acuan,struct Point random);//Mengkalkulasi nilai c dalam persamaan ax+by=c dari garis dibentuk 2 titik

int Calculate(int A,int B,int C,struct Point P);//Mengkalkulasi nilai Ax+By-C untuk titik P(x,y) 

int IsAllSameSign (int counterPos, int counterMin);//Mengecek apakah counterPos == counterMin

void GenerateNPoint (struct Array *T,int n);//Membentuk array of random point 

void PrintGeneratedPoint (struct Array T,int n);

void ConvexHullPoints (struct Array *CHull,struct Array *ChullSet,struct Array arr_P, int n);//menyimpan semua titik convex hull dari sejumlah titik sembarang
