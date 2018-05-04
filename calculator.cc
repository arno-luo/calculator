// A simple calculation implemented by C++
// arno-luo
//

#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Token
{
    char kind;
    double value;
    
    Token(char ch)
	    :kind(ch),value(0) {};
    Token(char ch,double v)
	    :kind(ch),value(v) {};
};

void error(string str)
{
    cout << "error:" << str << endl;
    throw "error";
}

class Token_stream
{
public:
    Token_stream()
        :m_full(false),m_buffer(0) {};
    Token get();
    void putback(Token t);
private:
    bool m_full;
    Token m_buffer;
};

Token Token_stream::get()
{
    if(m_full)
    {
    	m_full = false;
	return m_buffer;
    }
    char ch;
        cin >> ch;
        switch(ch)
        {
	case ';':
        case '+':
        case '-':
        case '*':
	case '/':
	case '(':
	case ')':
	    return Token(ch);
	case '.':
	case '0':case '1':case '2':case '3':case '4':
	case '5':case '6':case '7':case '8':case '9':
            cin.putback(ch);
	    double val;
	    cin >> val;
	    return Token('8',val);
	default:
	    error("bad token");
	}
}

void Token_stream::putback(Token t)
{
    m_buffer = t;
    m_full = true;
}

Token_stream ts;
double expression();

double element()
{
    Token t = ts.get();
    switch(t.kind)
    {
    case '(':{
	    double e = expression();
	    t = ts.get();
	    if(')' != t.kind) error("')' expected");
	    return e;}
    case '8':
	    return t.value;
    default:
	    error("element expected");
    }
}

double term()
{
    double left = element();
    Token t = ts.get();
    while(true)
    {
        switch(t.kind)
	{
	case '*':
		left *= element();
		break;
	case '/':{
		double e = element();
		if(0 == e) error("divide by zero");
		left /= e;
		break;}
	default:
		ts.putback(t);
		return left;
	}
	t = ts.get();
    }    
}

double expression()
{
    double left = term();
    Token t = ts.get();
    while(true)
    {
        switch(t.kind)
	{
	case '+':
		left += term();
		break;
	case '-':
		left -= term();
		break;
	case ';':
		return left;
	default:
		ts.putback(t);
		return left;
	}
	t = ts.get();
    }
}

int main()
{
    while(true)
    {
        cout << "Please enter the expression, end by ';'" << endl;
	try
	{
            while(cin)
	        cout << expression() << endl;
	}
	catch(...) {}
    }
}
