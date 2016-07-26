#include <stdio.h>
#include <stdlib.h>
#include <math.h>
 
typedef struct Complex {
    float Re;
    float Im;
} Complex;
 
Complex* complex(float Re, float Im) {
    Complex* _this = (Complex*) malloc(sizeof(Complex));
    _this->Im = Im;
    _this->Re = Re;
    return _this;
}
 
Complex* copy(const Complex *origin) {
    Complex* _this = complex(origin->Re, origin->Im);
    return _this;
}
 
void set(Complex *_this, float Re, float Im) {
    _this->Re = Re;
    _this->Im = Im;
}
 
void addTo(Complex *_this, const Complex *summand) {
    _this->Re += summand->Re;
    _this->Im += summand->Im;
}
 
void subFrom(Complex *_this, const Complex *subtrahend) {
    _this->Re -= subtrahend->Re;
    _this->Im -= subtrahend->Im;
}
 
void mulBy(Complex *_this, const Complex *factor) {
    float tmpRe = (_this->Re * factor->Re) - (_this->Im * factor->Im);
    _this->Im = (_this->Im * factor->Re) + (_this->Re * factor->Im);
    _this->Re = tmpRe;
}
 
void divBy(Complex *_this, const Complex *divisor) {
    float tmp = divisor->Im * divisor->Im + divisor->Re * divisor->Re;
    float tmpRe = _this->Re = (_this->Re*divisor->Re + _this->Im * divisor->Im) / tmp;
    _this->Im = (_this->Im*divisor->Re - _this->Re * divisor->Im) / tmp;
    _this->Re = tmpRe;
}
 
void deleteComplex(Complex **cmp) {
    free(*cmp);
    cmp = NULL;
}
 
void main() {
    Complex *a = complex(1, 3);
    Complex *b = complex(-1, 2);
    addTo(a, b);
    printf("a + b = %.3f, %.3fi}\n", a->Re, a->Im);
    set(a, 1, 3);
    subFrom(a, b);
    printf("a - b = %.3f, %.3fi}\n", a->Re, a->Im);
    set(a, 1, 3);
    mulBy(a, b);
    printf("a * b = %.3f, %.3fi}\n", a->Re, a->Im);
    set(a, 1, 3);
    divBy(a, b);
    printf("a / b = %.3f, %.3fi}", a->Re, a->Im);
    set(a, 1, 3);
    deleteComplex(&a);
    deleteComplex(&b);
    exit(0);
}