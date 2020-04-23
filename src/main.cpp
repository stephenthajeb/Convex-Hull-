#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "adt.h"
#include "time.h"
#include <string>
#include <GL/glut.h>

//Global variable
struct Array CHull;//Array of points that contruct a convex hull
struct Array CHullSet;//Set of points that construct a Convex Hull
struct Array arr_P;//Array of random points

void drawText(const char *text,int length, int x,int y){
    glMatrixMode(GL_PROJECTION);
    double *matrix = new double[14];
    glGetDoublev(GL_PROJECTION_MATRIX,matrix);
    glLoadIdentity();
    glOrtho(0,800,0,600,-5,5);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glLoadIdentity();
    glRasterPos2i(x,y);
    for(int i=0;i<length;i++){
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15,(int)text[i]);
    }
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixd(matrix);
    glMatrixMode(GL_MODELVIEW);
}

void display(void)
{   
    glClear(GL_COLOR_BUFFER_BIT);//clear screen
    glLoadIdentity();
    glPointSize(5.0);
    // draw

    glBegin(GL_LINES);
        for (int i=1;i<=Neff(CHull)-1;i++){
            if (i%2){
                glVertex2i(ElmtX(CHull,i),ElmtY(CHull,i));
                glVertex2i(ElmtX(CHull,i+1),ElmtY(CHull,i+1));
            } else {
                continue;
            }
            
        }
    glEnd();

    glBegin(GL_LINES);
         glVertex2i(0,105);
         glVertex2i(0,-105);
    glEnd();
    
    glBegin(GL_LINES);
         glVertex2i(105,0);
         glVertex2i(-105,0);
    glEnd();

    glBegin(GL_POINTS);
        for (int i=1;i<=Neff(arr_P);i++){
            glVertex2i(ElmtX(arr_P,i),ElmtY(arr_P,i));
        }
    glEnd();

    std::string text1,text2;
    text1 = "Stephen Thajeb";
    // text2 = "  13518150   ";
    drawText(text1.data(),text1.size(),575,30);
    // drawText(text2.data(),text2.size(),575,15);

    glFlush();
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, ( GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-105,105,-105,105);
    glMatrixMode(GL_MODELVIEW);
}

void init(){
    glClearColor(0.1, 0.2,0.7, 0.7);
}
    
int main (int argc,char**argv){
    //Variable
    int n;
    clock_t start,end;
    double cpu_time_used;

    printf("Masukkan jumlah titik :");
    scanf("%d",&n);
    
    start = clock();

    srand(time(NULL));
    MakeEmpty(&CHull);
    GenerateNPoint(&arr_P,n);
    printf("Titik Uji :\n");
    PrintGeneratedPoint(arr_P,n);

    ConvexHullPoints(&CHull,&CHullSet,arr_P, n); //Mencari titik dalam arr_P yang membentuk convex hull dan menyimpan di dalam array CHull dengan array berisi elemen unik
    printf("Output :\n");
    TulisIsi(CHullSet);//Menampilkan himpunan titik Convex Hull 
    
    end=clock();
    cpu_time_used = (((double) (end - start)) / CLOCKS_PER_SEC)*1000;
    printf("\nRun time : %.31f ms\n", cpu_time_used); 

    //GUI
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB);

    glutInitWindowPosition(200,100);
    glutInitWindowSize(500,500);
    glutCreateWindow("Convex Hull");
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    init();//Clear Screen
    glutMainLoop();//Terminate the program
    
    

    return 0;
}
