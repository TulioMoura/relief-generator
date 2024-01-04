#include<stdio.h>
#include<fstream>
#include<math.h>
 float reliefGenerator(int x, int y){
    srand(x*10);
     float a = (rand()%100);
     a=a/100;
    srand(y*10);
     float b = (rand()%100);
     b=b/100;
    srand(x*y);
     float c =  (rand()%100);
     c=c/100;
    float return_value = (a/2 + b/2 + c/2 - ((a*b)/5 + (b*c)/5));
    if(return_value<=0){
        printf("%f\n",return_value);
    }
    return return_value;

}

int main(){
    std::ofstream file;
    std::ofstream log_file;
    file.open("img.ppm");
    log_file.open("log.txt");
    file<<"P3 200 200 255\n";
    for(int i =0; i< 200; i++ ){
        for( int j = 0; j< 200; j++){
            int terrain_heigth = reliefGenerator(i, j) *512;
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
            log_file<<(terrain_heigth/512)<<std::endl;
        }
        //printf("%i\n",i);
    }
    file.close();
    log_file.close();
    return 0;
}