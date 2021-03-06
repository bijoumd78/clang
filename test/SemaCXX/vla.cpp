// RUN: %clang_cc1 -verify %s

// PR11925
int n;
int (&f())[n]; // expected-error {{function declaration cannot have variably modified type}}

namespace PR18581 {
  template<typename T> struct pod {};
  template<typename T> struct error {
    typename T::error e; // expected-error {{cannot be used prior to '::'}}
  };
  struct incomplete; // expected-note {{forward declaration}}

  void f(int n) {
    pod<int> a[n];
    error<int> b[n]; // expected-note {{instantiation}}
    incomplete c[n]; // expected-error {{incomplete}}
  }
}

void pr23151(int (&)[*]) { // expected-error {{variable length array must be bound in function definition}}
}
