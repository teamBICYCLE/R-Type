#ifndef     __INPUTDATA_HH__
# define    __INPUTDATA_HH__

#include <stdint.h>
#include "utilities/Vector2D.hh"

namespace Input {
struct   Data
{
    public:
        Data();
        explicit Data(int packet);
        ~Data();

    public:
        Data(const Data& other);
        Data(Data && other);
        Data&  operator=(Data other);
        friend void swap(Data& lhs, Data& rhs);

    public:
        int         getId() const;
        Vector2D    getVector() const;
        bool        isFiring() const;

    public:
        unsigned int     getPacket(void) const;

    public:
        void    setId(int v);
        void    setTop(bool v);
        void    setBot(bool v);
        void    setLeft(bool v);
        void    setRight(bool v);
        void    setFire(bool v);

    private:
        union {
            uint32_t _packet;
			struct {
				unsigned _top    :1;
				unsigned _bot    :1;
				unsigned _left   :1;
				unsigned _right  :1;
				unsigned _fire   :1;
				unsigned _id     :24;
			};
        };
};
}

#endif /* !__INPUTDATA_HH__ */
