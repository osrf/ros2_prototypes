#include <iostream>

template <typename S>
class _Foo {
    public:
        bool getBar() {
            return storage.getBar();
        }

        void setBar(bool bar_) {
            storage.setBar(bar_);
        }

        int getBaz() {
            return storage.getBaz();
        }

        void setBaz(int baz_) {
            storage.setBaz(baz_);
        }

     private:
        S storage;
};

class _FooPlainStorage {
    public:
        bool getBar() {
            return bar;
        }

        void setBar(bool bar_) {
            bar = bar_;
        }

        int getBaz() {
            return baz;
        }

        void setBaz(int baz_) {
            baz = baz_;
        }

    private:
        bool bar;
        int baz;
};

typedef _Foo<_FooPlainStorage> Foo;

int main(void) {
    Foo f;
    f.setBar(true);
    std::cout << f.getBar() << std::endl;

    f.setBaz(42);
    std::cout << f.getBaz() << std::endl;
    return 0;
}
