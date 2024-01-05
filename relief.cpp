#include<stdio.h>
#include<fstream>
#include<math.h>
 float reliefGenerator(int x, int y, int seed){
    srand(x*seed);
    float reference = cos((x*y)/10) * sin((y-x)/10);
    printf("%f ref \n" , reference);
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
    float return_value = abs(a/2 + b/2 + c/2 );
    if(return_value<=0){
        printf("%f || %i # %i\n",return_value,x,y);
    }
    return return_value;

}

int main(){
    std::ofstream file;
    std::ofstream log_file;
    file.open("img.ppm");
    //log_file.open("log.txt");
    file<<"P3 100 100 255\n";
    for(int i =0; i< 100; i++ ){
        for( int j = 0; j< 100; j++){
            int terrain_heigth = reliefGenerator(i, j,252525) *512;
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