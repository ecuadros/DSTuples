#include <iostream>
#include <tuple>
#include <string>

// helper function to print a tuple of any size
template<class Tuple, size_t N>
struct TuplePrinter
{
    static void print(const Tuple& t) 
    {
        TuplePrinter<Tuple, N-1>::print(t);
        cout << ", " << get<N-1>(t);
    }
};
 
template<class Tuple>
struct TuplePrinter<Tuple, 1>
{
    static void print(const Tuple& t) 
    {
        cout << get<0>(t);
    }
};
 
template<typename... Args, enable_if_t<sizeof...(Args) == 0, int> = 0>
void print(const tuple<Args...>& t)
{
    cout << "()\n";
}
 
template<typename... Args, enable_if_t<sizeof...(Args) != 0, int> = 0>
void print(const tuple<Args...>& t)
{
    cout << "(";
    TuplePrinter<decltype(t), sizeof...(Args)>::print(t);
    cout << ")\n";
}
// end helper function
 
void demoTupleCat()
{
    tuple<int, string, float> t1(10, "Test", 3.14);
    int n = 7;
    auto t2 = tuple_cat(t1, make_tuple("Foo", "bar"), t1, tie(n));
    n = 42;
    print(t2);
}