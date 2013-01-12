#ifndef     __AUNIT_HH__
# define    __AUNIT_HH__

# include   <ostream>
# include   "IPackable.hh"
# include   "Packet.hh"
# include   "../utilities/Vector2D.hh"

typedef union {
    struct {
        uint32_t    id;
        uint16_t    x;
        uint16_t    y;
        uint16_t    dx;
        uint16_t    dy;
    };
    uint8_t         whole[sizeof(id) + sizeof(x) +
                          sizeof(y) + sizeof(dx) +
                          sizeof(dy)];
} UnitPacket_u;

class   AUnit : public IPackable
{
    public:
        AUnit(int id, const Vector2D& pos, const Vector2D& dir);
        virtual ~AUnit();

    public:
        AUnit(const AUnit& other);
        AUnit(AUnit&& other);
        AUnit&  operator=(AUnit other);
        friend void    swap(AUnit& lhs, AUnit& rhs);

    public:
        int             getId(void) const;
        const Vector2D& getPos(void) const;
        const Vector2D& getDir(void) const;

    public:
        void    move(void);
        void    setDirection(const Vector2D& dir);
        void    update(network_packet::Packet packet);

    public:
        virtual size_t  pack(uint8_t *out, size_t outSize) const;

    public:
        friend std::ostream&    operator<<(std::ostream& stream, const AUnit& unit);

    protected:
        Vector2D		_pos;
        Vector2D		_dir;
        unsigned int	_id;
};

#endif /* !__AUNIT_HH__ */
