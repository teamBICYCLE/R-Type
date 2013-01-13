#ifndef     __UNIT_HH__
# define    __UNIT_HH__

# include   <ostream>
# include   "network/IPackable.hh"
# include   "network/Packet.hh"
# include   "utilities/Vector2D.hh"

typedef union {
    struct _content {
        uint16_t    x;
        uint16_t    y;
        uint16_t    dx;
        uint16_t    dy;
    } info;
    uint8_t         whole[sizeof(_content)];
} UnitPacket_u;

class   Unit : public IPackable
{
    public:
        Unit(int id, const Vector2D& pos, const Vector2D& dir);
        virtual ~Unit();

    public:
        Unit(const Unit& other);
        Unit(Unit&& other);
        Unit&  operator=(Unit other);
        friend void    swap(Unit& lhs, Unit& rhs);

    public:
        int             getLastPacketSequence(void) const;
        int             getId(void) const;
        const Vector2D& getPos(void) const;
        const Vector2D& getDir(void) const;

    public:
        void    move(void);
        void    setDirection(const Vector2D& dir);
        void    setLastPacketSequence(uint32_t newPacketSequence);

    public:
        virtual size_t  pack(uint8_t *out, size_t outSize) const;
        virtual void    unpack(const uint32_t newPacketSequence,
                               const uint8_t* content);

    public:
        friend std::ostream&    operator<<(std::ostream& stream, const Unit& unit);

    protected:
        uint32_t    _lastPacketSequence;
        Vector2D		_pos;
        Vector2D		_dir;
        uint32_t  	_id;
};

#endif /* !__UNIT_HH__ */
