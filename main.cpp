#include <iostream>
#include "Vector3.h"
using namespace std;

int main () {
    Vector3 a;
    Vector3 b(3,4,2,5, 2, 7);
    cout <<"a = " << a.getdx() <<a.getdy() <<a.getdz()<<  endl;
    cout <<"b = " << b.getdx() <<b.getdy() <<b.getdz()<<  endl;
    cout << "length a, b = "<< a.length()<<" , "<< b.length()<<endl;
}
