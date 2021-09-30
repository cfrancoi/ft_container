#ifndef __FOO_H__
#define __FOO_H__

#include <iostream>

class Foo
{
private:
	/* data */
	int _n;
public:
	Foo(int n) : _n(n) {}
	Foo(const Foo& x) { *this = x; }
	~Foo() {}

	Foo& operator=(const Foo& x) { _n = x.getN(); return *this; }


	const int &getN() const { return _n; }

};

bool operator==(const Foo& lhs, const Foo& rhs) { return lhs.getN() == rhs.getN();}
bool operator!=(const Foo& lhs, const Foo& rhs) { return lhs.getN() != rhs.getN();}
bool operator<(const Foo& lhs, const Foo& rhs) { return lhs.getN() < rhs.getN();}
bool operator<=(const Foo& lhs, const Foo& rhs) { return lhs.getN() <= rhs.getN();}
bool operator>(const Foo& lhs, const Foo& rhs) { return lhs.getN() > rhs.getN();}
bool operator>=(const Foo& lhs, const Foo& rhs) { return lhs.getN() >= rhs.getN();}

std::ostream & operator<<(std::ostream &o, const Foo& x)
{
	o << x.getN();
	return o;
}

#endif // __FOO_H__