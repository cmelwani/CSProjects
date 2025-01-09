#include <iostream>
#include <fstream>

using namespace std;

const double PI = 3.1415926;

float circle_area(float diameter);
float disc_area(float disc_diamater, float hole_diamater);
float cd_capacity(float disc_diameter, float hole_diameter, float disc_density);

int main(){
    // Part I: Functions
    float area, capacity;
    float cd_disc_diam = 4.7;
    float cd_hole_diam = 0.9;
  /*  float cd_disc_area = PI * ( cd_disc_diam / 2.0) * ( cd_disc_diam / 2.0);
    float cd_hole_area = PI * ( cd_hole_diam / 2.0) * ( cd_hole_diam / 2.0);
    float cd_area = cd_disc_area - cd_hole_area;
    cout << cd_area * 46.0 << endl; */
    area = disc_area(cd_disc_diam, cd_hole_diam);
    capacity = cd_capacity(cd_disc_diam, cd_hole_diam, 46.0);
    cout << "This is the disc area " << area << endl;
    cout << "This is the capacity of the disk " << capacity << endl;



    // Part II: Pointers
    int trix[4][6];
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 6; j++){
            trix[i][j] = (i * 6) + j;
        }
    }

    int *x = &trix[1][1];
    int **y = &x;
    int ***z = &y;

    // DO NOT UNCOMMENT THESE UNTIL YOU HAVE COMPUTED THE ANSWER ON PAPER
    cout << trix[3][5] << endl;
    cout << *(x + 2) << endl;
    cout << x[6] << endl;
    cout << *((*y) - 1) << endl;
    cout << (*(*z))[1] << endl;
    cout << *((*(&x)) + 12) << endl;
    cout << z << endl;
    //cout << *(&trix[0][0] + 6) << endl; ---> equals 6

    return 0;
}

float circle_area(float diameter) {
  float area;
  area = PI * (diameter / 2.0) * (diameter / 2.0);
  return area;
}

float disc_area(float disc_diamater, float hole_diamater) {
  float total_area, disc_area, hole_area;
  disc_area = circle_area(disc_diamater);
  hole_area = circle_area(hole_diamater);
  total_area = disc_area - hole_area;
  return total_area;
}

float cd_capacity(float disc_diameter, float hole_diameter, float disc_density){
  float total_area, capacity;
  total_area = disc_area(disc_diameter, hole_diameter);
  capacity = total_area * disc_density;
  return capacity;
}
