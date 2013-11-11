
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


template<typename T>
struct SmallMessage_Backend
{
public:
    inline int get_foo() const { return this->backend.foo(); }
    inline int get_bar() const { return this->backend.bar(); }
    inline void set_foo(int v) { this->backend.set_foo(v); }
    inline void set_bar(bool v) { this->backend.set_bar(v); }
    void operator=(const SmallMessage_Backend& other)
    {
        this->backend = other.backend;
    }
private:
    T backend;
};


struct SmallPlainStorage
{
public:
    inline int foo() const { return foo_; }
    inline int bar() const { return bar_; }
    inline void set_foo(int v) { this->foo_ = v; }
    inline void set_bar(bool v) { this->bar_  = v; }
    void operator=(const SmallPlainStorage& other)
    {
        this->foo_ = other.foo_;
        this->bar_ = other.bar_;
    }
private:
    int foo_;
    bool bar_;
};
