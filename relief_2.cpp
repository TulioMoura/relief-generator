#include<stdio.h>
#include<fstream>
#include<math.h>


 float reliefGenerator(int x, int y, int seed){
    srand(x*seed);
    float temp = cos( ((x*y)/5) * ((y*x)/2));
    float reference = temp;
    printf(" %f  * %f ref \n" ,temp, reference);
     float a = (rand()%100);
     a=a/100;
     a = a +reference ;
    srand(y*seed/2);
     float b = (rand()%100);
     b=b/100;
     b=b +reference ;
    srand(x*y*(seed/4));
     float c =  (rand()%100);
     c=c/100;
     c=c + reference;
    float return_value = abs(a/4 + b/4 + c/4 );
    if(return_value<=0){
        printf("%f || %i # %i\n",return_value,x,y);
    }
    return return_value;

}

struct vec2{
    double x, y;
};

vec2 randomVector(int vx, int vy, int seed){
   srand(seed + (vx *vx)+ (vy * vy)  + ( + vx * (+ vy)));
    int xtemp = rand()%1000;
    int ytemp = rand()%1000;
    double x = xtemp/100.0;
    double y = ytemp/100.0;
    vec2 v;
    v.x  = cos(x)+vx;
    v.y = cos(y)+vy; 
    return v; 
    
}

float dotProduct(float x, float y, float px, float py,float fx, float fy){
    float distancex = abs(x -px-fx);
    float distancey = abs(y -py-fy);

    float dotProductx = (distancex)* px ;
    float dotProducty = (distancey) * py ;

    //printf("%f dx %f dy ");
    return (dotProductx+dotProducty);
    }

float distance(float x, float y, float tx, float ty){
    float dx =abs(x)-abs(tx);
    float dy = abs(y)+abs(ty);
    float distance = sqrt((dx*dx)+(dy*dy));
    //printf("%f distance %f dx %f dy \n", distance, dx,dy);
    return distance;
}

float perlin(float x, float y, int seed){
    int x0 = floor(x);
    int y0 = floor(y);

    vec2 v0 = randomVector(x0, y0,seed);
    vec2 v1 = randomVector(x0+1, y0, seed);
    vec2 v2 = randomVector(x0,y0+1, seed);
    vec2 v3 = randomVector(x0+1,y0+1, seed);
    //printf("%f,\t %f \n",v3.x, v3.y);

    //printf("%f # %i *** %f # %i \n", x, x0, y, y0);
    /*float d0 = dotProduct(x,y, v0.x,v0.y, x0,y0);
    float d1 = dotProduct(x,y, v1.x,v1.y, x0+1,y0);
    float d2 = dotProduct(x,y, v2.x,v2.y, x0,y0+1);
    float d3 = dotProduct(x,y, v3.x,v3.y, x0+1,y0+1);
    */

    //printf("%f %f %f %f \n", d0,d1,d2,d3);

   /*  float i0 = (d1 - d0) * 0.5 + d0;
    float i1 = (d3 -d2) * 0.5 + d2;
    float n = (i1 - i0) * 0.5 + i0; */

    //printf("%f * %f* %f * %f #%f \n",d0,d1,d2,d3, n);
    float d0,d1,d2,d3;
    d0 = distance(x,y,v0.x,v0.y);
    d1 = distance(x,y,v1.x,v1.y);
    d2 = distance(x,y,v2.x,v2.y);
    d3 = distance(x,y,v3.x,v3.y);

    printf("%f x, %f y %f d0 %f d1 %f d2 %f d3\n [%f %f] [%f %f] [%f %f] [%f %f]\n ", x, y,d0,d1,d2,d3,v0.x,v0.y,v1.x, v1.y, v2.x, v2.y, v3.x, v3.y);
    return abs(d0-d1)+abs(d2-d3);


}

float random_heigth(int x, int y, int seed){
    srand(seed*x*y);
    int xtemp = rand()%1000;
    double r = xtemp/1000.0;
    printf("%f -- H \n",r);
    return r;
}

float height_gen(float x, float y, int seed  ){
    float h1,h2,h3,h4;
    int x0 = floor(x);
    int y0 = floor(y);

    printf("-=========-heigths\n");
    h1=random_heigth(x0,y0,seed);
    h2=random_heigth(x0+1,y0,seed);
    h3=random_heigth(x0,y0+1,seed);
    h4=random_heigth(x0+1,y0+1,seed);

    printf("deltas ============\n");
    float deltaA = abs(h1-h2);
    float deltaB = abs(h3-h4);
    printf("%f\n",deltaA);
    printf("%f\n",deltaB);

    float refA = h1<h2?h2:h1; //maior entre os pontos;
    float refB = h3<h3?h4:h3; //maior entre os pontos;

    float hx1 = (x-x0)*(refA-deltaA);
    float hx2 = (x-x0)*(refB - deltaB); 

    float hi1 = hx1 + deltaA;  //altura na interseção
    float hi2 = hx2 + deltaB;  //altura na interseção

    printf("intesection heights\n %f %f",hi1, hi2);

    deltaA = abs(hi1 - hi2);
    refA = hi1<hi2?hi2:hi1;

    float r = ((y-y0) * (refA - deltaA))+deltaA;

    printf("%f\n",r);
    return r;


}


int main(){
    std::ofstream file;
    std::ofstream log_file;
    file.open("img.ppm");
    log_file.open("log.txt");
    file<<"P3 200 200 255\n";
    printf("gulugulu");
    for(float i =0; i< 200; i++ ){
        for( float j = 0; j< 200; j++){
            float heigth = (height_gen(i/50.0, j/50.0,75));
            //printf("%f \n", perlin_res);

            log_file<<heigth<<"\n";
            
            int terrain_heigth = (heigth * 512);
            int red;
            int green;
            if(terrain_heigth > 255){
                green = 256-floor(terrain_heigth-255);
                red = 255;
            }
            else{
                green = 255;
                red = floor(terrain_heigth);
            }

            file<<red<<" "<<green<<" "<<0<<std::endl;
            log_file<<(terrain_heigth/512)<<std::endl;
        }
        //printf("%i\n",i);
    }
    file.close();
    log_file.close();
    return 0;
}