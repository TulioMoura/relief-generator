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
    srand(seed+vx);
    float x = rand()%1000;
    srand(seed+vy);
    float y = rand()%1000;
    x = cos(x);
    y = cos(y);
    vec2 v;
    v.x = x;
    v.y = y;
    //printf("%fx %fy \n", v.x, v.y);
    return v;
}

float dotProduct(int x, int y, float px, float py){
    float distancex = px-x;
    float distancey = py-y;

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
    
    float d0 = dotProduct(x,y, v0.x,v0.y);
    float d1 = dotProduct(x,y, v1.x,v1.y);
    float d2 = dotProduct(x,y, v2.x,v2.y);
    float d3 = dotProduct(x,y, v3.x,v3.y);

    
    float n = d0 * d1 * d2 * d3;
    printf("%f * %f* %f * %f #%f \n",d0,d1,d2,d3, n);
    return n;


}

int main(){
    std::ofstream file;
    std::ofstream log_file;
    file.open("img.ppm");
    //log_file.open("log.txt");
    file<<"P3 100 100 255\n";
    for(int i =0; i< 100; i++ ){
        for( int j = 0; j< 100; j++){
            int terrain_heigth = ((perlin(i/10, j/10,252525)*0.5)+0.5) *512;
            int red;
            int green;
            if(terrain_heigth > 256){
                green = floor(terrain_heigth-255);
                red = 255;
            }
            else{
                green = 255;
                red = floor(terrain_heigth);
            }

            file<<red<<" "<<green<<" "<<0<<std::endl;
            //log_file<<(terrain_heigth/512)<<std::endl;
        }
        //printf("%i\n",i);
    }
    file.close();
    //log_file.close();
    return 0;
}