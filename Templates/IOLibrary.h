#ifndef IOLIBRARY_H
#define IOLIBRARY_H

#define m1(x) template<class T, class... U> void x(T&& a, U&&... b) 
#define m2(x) (int[]){(x forward<U>(b),0)...}

m1(pr) { cout << forward<T>(a);  m2(cout << " " <<); cout << "\n"; } 
m1(re) { cin >> forward<T>(a); m2(cin >>); }

#endif