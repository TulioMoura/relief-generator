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
    float x, y;
};

vec2 randomVector(int vx, int vy, int seed){
    srand(seed*vx*vy);
    float xt = rand()%1000;
    float yt = rand()%1000;
    float x = cos(xt)* sin(yt) * 0.4;
    float y = cos(yt) * sin(xt) * 0.4;
    vec2 v;
    v.x = x;
    v.y = y;
    //printf("%fx %fy \n", v.x, v.y);
    return v;
}

float dotProduct(float x, float y, float px, float py){
    float distancex = abs(x - px);
    float distancey = abs(y - py) ;

    //printf("%f # %f \n", x, px);

    float dotProductx = distancex * x;
    float dotProducty = distancey * y;

    return (dotProductx+dotProducty);
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
    float d0 = dotProduct(x,y, v0.x,v0.y);
    float d1 = dotProduct(x,y, v1.x,v1.y);
    float d2 = dotProduct(x,y, v2.x,v2.y);
    float d3 = dotProduct(x,y, v3.x,v3.y);

    float i0 = (d1 - d0) * 0.5 + d0;
    float i1 = (d3 -d2) *0.5 + d2;
    float n = (i1 - i0) * 0.5 + i0;
    //printf("%f * %f* %f * %f #%f \n",d0,d1,d2,d3, n);
    return n;


}

int main(){
    std::ofstream file;
    std::ofstream log_file;
    file.open("img.ppm");
    log_file.open("log.txt");
    file<<"P3 300 300 255\n";
    for(float i =0; i< 300; i++ ){
        for( float j = 0; j< 300; j++){
            int terrain_heigth = ((perlin(i/100, j/100,75)) *512);
            int red;
            int green;
            if(terrain_heigth > 255){
                green = floor(terrain_heigth-255);
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