#include <iostream>

// True and False
class True {};
class False {};

// Or type inference rules
template<typename T1, typename T2> 
struct Or {};

template<>
struct Or<False, False> {
	typedef False value;
};

template<>
struct Or<False, True> {
	typedef True value;
};

template<>
struct Or<True, False> {
	typedef True value;
};

template<>
struct Or<True, True> {
	typedef True value;
};

// If type inference rules
template<typename T1, typename T2, typename T3>
struct If {};

template<typename Then, typename Else>
struct If<True, Then, Else> {
	typedef Then value;
};

template<typename Then, typename Else>
struct If<False, Then, Else> {
	typedef Else value;
};

// Natural numbers
class Zero {
	public: enum { value = 0 };
	int eval(void) const { return value; }
};

template<class T>
class Succ {
	public: enum { value = T::value + 1 };
	int eval(void) const { return value; }
};

// Addition type inference rules
template<typename T1, typename T2>
struct Add {};

template<typename T1, typename T2>
struct Add<Succ<T1>, T2> {
	typedef typename Add<T1, Succ<T2> >::value value;
};

template<typename T>
struct Add<Zero, T> {
	typedef T value;
};

// Multiple of 3 type inference rules
template<typename T>
struct MultipleOf3 {};

template<typename T>
struct MultipleOf3<Succ<Succ<Succ<T> > > > {
	typedef typename MultipleOf3<T>::value value;
};

template<typename T>
struct MultipleOf3<Succ<T> > {
	typedef False value;
};

template<>
struct MultipleOf3<Zero> {
	typedef True value;
};

// Multiple of 5 type inference rules
template<typename T>
struct MultipleOf5 {};

template<typename T>
struct MultipleOf5<Succ<Succ<Succ<Succ<Succ<T> > > > > > {
	typedef typename MultipleOf5<T>::value value;
};

template<typename T>
struct MultipleOf5<Succ<T> > {
	typedef False value;
};

template<>
struct MultipleOf5<Zero> {
	typedef True value;
};

// finding the sum of all multiples of 3 and 5 under a given number
template<typename T>
struct SumOfMultiples {};

template<typename T>
struct SumOfMultiples<Succ<T> > {
	typedef typename MultipleOf3<Succ<T> >::value is_multiple_3;
	typedef typename MultipleOf5<Succ<T> >::value is_multiple_5;
	typedef typename Or<is_multiple_3, is_multiple_5>::value test;
	typedef typename If<test, typename Add<Succ<T>, typename SumOfMultiples<T>::sum >::value, 
	                          typename SumOfMultiples<T>::sum >::value sum;
};

template<>
struct SumOfMultiples<Zero> {
	typedef Zero sum;
};

// transforming from an integer to an unary number
template<int n>
struct ConstructNum {
	typedef Succ<typename ConstructNum<n-1>::value> value;
	value type;
};

template<>
struct ConstructNum<0> {
	typedef Zero value;
	value type;
};

int main() 
{
	typedef typename ConstructNum<100>::value n;
	typedef typename SumOfMultiples<n>::sum Total; 
	Total m;
	std::cout << m.eval() << std::endl;
	return 0;
}
