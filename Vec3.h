#ifndef Vec3_H
#define Vec3_H
#include <cmath>
#include <iostream>

template <class T> class Vec3 {
public:
    T x, y, z;

    void set(const T &xt, const T &yt, const T &zt) {
        x = xt;
        y = yt;
        z = zt;
    }

    void set(const Vec3<T> &v) {
        set(v.x, v.y, v.z);
    }

    Vec3() : Vec3((T)0, (T)0, (T)0) {}
    
    Vec3(T x, T y, T z) {
        set(x, y, z);
    }

    Vec3(const Vec3<T> &v) {
        set(v.x, v.y, v.z);
    }

    static T dot(const Vec3<T> &v1, const Vec3<T> v2) {
        return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;    
    }

    T dot(const Vec3<T> &v2) const {
        return dot(*this, v2);  
    }

    T norm() const{
        return sqrt(dot(*this));
    }
   
    // Norm squared
    T norm2() {
        return dot(*this);
    }

    T length()  { return norm(); }
    T length2() { return norm2(); }
    
    Vec3<T> normalized() const{
        T len = norm();
        if (len == 0) len = 1.0;
        return *this/len;
    }

    Vec3<T> normalize() const{
        T len = norm();
        if (len > 0)
            this->set(*this/len);
        return *this;
    }

    static Vec3<T> cross(const Vec3<T> &v1, const Vec3<T> &v2) {
        return Vec3(v1.y*v2.z - v1.z*v2.y, v1.z*v2.x - v1.x*v2.z, v1.x*v2.y - v1.y*v2.x);
    }
    
    Vec3<T> cross(const Vec3<T> &v2) const{
        return cross(*this, v2);
    }

    static Vec3<T> cross2(const Vec3<T> &v1, const Vec3<T> &v2) {
        return Vec3(v1.x*v2.x, v1.y*v2.y, v1.z*v2.z);
    }

    Vec3<T> cross2(const Vec3<T> &v2){
        return cross2(*this, v2);
    }


    const Vec3<T> operator +(const Vec3<T> &v2) const{
        return Vec3(x + v2.x, y + v2.y, z + v2.z);
    }

    const Vec3<T> operator -(const Vec3<T> &v2) const {
        return Vec3(x - v2.x, y - v2.y, z - v2.z);
    }

    const Vec3<T> operator *(const T a) const {
        return Vec3(a * x, a * y, a * z);
    }

    const friend Vec3<T> operator *(const T a, const Vec3<T> &v1) {
        return v1 * a;
    }

    const T operator [](int idx) {
        if(idx == 0)
            return x;
        if(idx == 1)
            return y;
        else
            return z;
    }

    const Vec3<T> operator /(const T a) const {
        return Vec3(1/a * x, 1/a * y, 1/a * z);
    }

    const friend Vec3<T> operator /(const T a, const Vec3<T> &v1) {
        return v1 / a;
    }

    const bool operator ==(const Vec3<T> &v2) {
        return (x == v2.x && y == v2.y && z == v2.z);
    }

    const bool operator !=(const Vec3<T> &v2) {
        return !(x == v2.x && y == v2.y && z == v2.z);
    }

    Vec3<T> & operator +=(const Vec3<T> &v2) {
        x += v2.x;
        y += v2.y;
        z += v2.z;
        return *this;
    }
    
    Vec3<T> & operator -=(const Vec3<T> &v2) {
        x -= v2.x;
        y -= v2.y;
        z -= v2.z;
        return *this;
    }

    Vec3<T> & operator *=(const T &a) {
        x *= a;
        y *= a;
        z *= a;
        return *this;
    }

    Vec3<T> & operator /=(const T &a) {
        x /= a;
        y /= a;
        z /= a;
        return *this;
    }

    const void print() const{
        std::cout << "X: " << x << " Y: " << y << " Z: " << z << std::endl;
    }

    void setX(const T &xt){
        x = xt;
    }

    void setY(const T &yt){
        y = yt;
    }

    void setZ(const T &zt){
        z = zt;
    }

    double getX(){
        return x;
    }

    double getY(){
        return y;
    }

    double getZ(){
        return z;
    }

    void swap(Vec3<T> v2)
    {
        double temp = x;
        x = v2.getX();
        v2.setX(temp);
        temp = y;
        y = v2.getY();
        v2.setY(temp);
        temp = z;
        z = v2.getZ();
        v2.setZ(temp);
    }
};

#endif