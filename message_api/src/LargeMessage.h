#include <cstring>

#include <boost/array.hpp>


#define baz_SIZE 1024*1024

struct LargeMessage_Struct
{
    char baz[baz_SIZE];
    void operator=(const LargeMessage_Struct& other)
    {
        memcpy(&this->baz, &other.baz, sizeof(this->baz));
    }
};


struct LargeMessage_Method
{
public:
    inline char* get_baz() { return baz; }
    inline const char* get_baz() const { return baz; }
    inline void set_baz(const char* v) {
        memcpy(&this->baz, v, sizeof(this->baz));
    }
    void operator=(const LargeMessage_Struct& other)
    {
        memcpy(&this->baz, &other.baz, sizeof(this->baz));
    }
private:
    char baz[baz_SIZE];
};


struct LargeBoostMessage_Method
{
public:
    inline boost::array<char, baz_SIZE>& get_baz() { return baz; }
    inline const boost::array<char, baz_SIZE>& get_baz() const { return baz; }
    inline void set_baz(const boost::array<char, baz_SIZE>& v) {
        baz = v;
    }
    void operator=(const LargeBoostMessage_Method& other)
    {
        this->baz = other.baz;
    }
private:
    boost::array<char, baz_SIZE> baz;
};


template<typename T>
struct LargeBoostMessage_Backend
{
public:
    inline boost::array<char, baz_SIZE>& get_baz() { return this->backend.baz(); }
    inline const boost::array<char, baz_SIZE>& get_baz() const { return this->backend.baz(); }
    inline void set_baz(const boost::array<char, baz_SIZE>& v) {
        this->backend.set_baz(v);
    }
    void operator=(const LargeBoostMessage_Backend& other)
    {
        this->backend = other.backend;
    }
private:
    T backend;
};


struct LargeBoostPlainStorage
{
public:
    inline boost::array<char, baz_SIZE>& baz() { return baz_; }
    inline const boost::array<char, baz_SIZE>& baz() const { return baz_; }
    inline void set_baz(const boost::array<char, baz_SIZE>& v) {
        baz_ = v;
    }
    void operator=(const LargeBoostPlainStorage& other)
    {
        this->baz_ = other.baz_;
    }
private:
    boost::array<char, baz_SIZE> baz_;
};


struct LargeBoostProtobufStorage
{
public:
    inline boost::array<char, baz_SIZE>& baz() { return baz_; }
    inline const boost::array<char, baz_SIZE>& baz() const { return baz_; }
    inline void set_baz(const boost::array<char, baz_SIZE>& v) {
        baz_ = v;
    }
    void operator=(const LargeBoostProtobufStorage& other)
    {
        this->baz_ = other.baz_;
    }
private:
    boost::array<char, baz_SIZE> baz_;
};
