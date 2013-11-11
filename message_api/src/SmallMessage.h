
struct SmallMessage_Struct
{
    int foo;
    bool bar;
    void operator=(const SmallMessage_Struct& other)
    {
        this->foo = other.foo;
        this->bar = other.bar;
    }
};


struct SmallMessage_Method
{
public:
    inline int get_foo() const { return foo; }
    inline int get_bar() const { return bar; }
    inline void set_foo(int v) { this->foo = v; }
    inline void set_bar(bool v) { this->bar  = v; }
    void operator=(const SmallMessage_Struct& other)
    {
        this->foo = other.foo;
        this->bar = other.bar;
    }
private:
    int foo;
    bool bar;
};
