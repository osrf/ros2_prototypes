#include <cstring>

#include <boost/array.hpp>


#define baz_SIZE 1024*1024

struct LargeMessage_Struct
{
    char baz[baz_SIZE];
    void operator=(const LargeMessage_Struct& other)
    {
        memcpy(&this->baz, &other.baz, sizeof(this->baz));
        /*for (size_t i = 0; i < sizeof(baz); i++)
        {
            this->baz[i] = other.baz[i];
        }*/
    }
};


struct LargeMessage_Method
{
public:
    inline char* get_baz() { return baz; }
    inline const char* get_baz() const { return baz; }
    inline void set_baz(const char* v) {
        for (size_t i = 0; i < sizeof(baz); i++)
        {
            this->baz[i] = v[i];
        }
    }
    void operator=(const LargeMessage_Struct& other)
    {
        for (size_t i = 0; i < sizeof(baz); i++)
        {
            this->baz[i] = other.baz[i];
        }
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
        /*for (size_t i = 0; i < sizeof(baz); i++)
        {
            this->baz[i] = v[i];
        }*/
    }
    void operator=(const LargeBoostMessage_Method& other)
    {
        this->baz = other.baz;
        /*for (size_t i = 0; i < sizeof(baz); i++)
        {
            this->baz[i] = other.baz[i];
        }*/
    }
private:
    boost::array<char, baz_SIZE> baz;
};
