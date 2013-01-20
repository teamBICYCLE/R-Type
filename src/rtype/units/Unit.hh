#ifndef     __UNIT_HH__
# define    __UNIT_HH__

# include <chrono>
# include <ostream>
# include <list>
# include "utilities/Vector2D.hh"
# include "network/IPackable.hh"
# include "network/Packet.hh"
# include "utilities/Vector2D.hh"

# define    UNLIMITED   (-1)

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
        Unit(void);
        virtual ~Unit();

    public:
        Unit(const Unit& other);
        Unit(Unit&& other);
        Unit&  operator=(Unit other);
        friend void    swap(Unit& lhs, Unit& rhs);

    public:
        uint32_t            getLastPacketSequence(void) const;
        uint32_t            getId(void) const;
        const Vector2D&     getPos(void) const;
        const Vector2D&     getDir(void) const;
        const Vector2D&     getHitboxCenter(void) const;
        float               getHitboxRadius(void) const;
        bool                isDead(void) const;
        bool                wereOthersNotifiedOfDeath(void) const;
        //const std::string & getSpritePath(void) const;
        unsigned int        getResourceId(void) const;
        unsigned int        getPv(void) const;
        int                 getMunition(void);
        const std::chrono::milliseconds &getTimeToReload(void) const;
        const std::chrono::milliseconds &getFireFrequence(void) const;

    public:
        virtual void    move(void);
        void    setDir(const Vector2D& dir);
        void    setLastPacketSequence(uint32_t newPacketSequence);
        void    setPos(const Vector2D& pos);
        void    setHitboxCenter(const Vector2D& center);
        void    setHitboxRadius(const float radius);
        void    setDead(bool b);
        void    setOthersNotifiedOfDeath(bool b);
        //void    setSpritePath(const std::string &);
        void    setResourceId(const unsigned int);
        void    setPv(const unsigned int);
        void    setMunition(const unsigned int);
        void    setTimeToReload(const std::chrono::milliseconds &);
        void    setFireFrequence(const std::chrono::milliseconds &);

    public:
        virtual size_t  pack(uint8_t *out, size_t outSize) const;
        virtual void    unpack(const uint32_t newPacketSequence,
                               const uint8_t* content);
        virtual Unit    *clone(void);
        virtual void    reset(void);

    public:
        friend std::ostream&    operator<<(std::ostream& stream, const Unit& unit);

    protected:
        uint32_t  _lastPacketSequence;
        Vector2D	_pos;
        Vector2D	_dir;
        uint32_t  _id;
        //Hitbox center is different from _pos so
        //that we can set it to be the head of the
        //rocket, for example
        Vector2D  _hitboxCenter;
        float     _hitboxRadius;
        bool      _isDead;
        bool      _othersNotifiedOfDeath;
        //std::string _spritePath;
        unsigned int _resourceId;
        unsigned int _pv;
        int _munition;
        std::chrono::milliseconds _timeToReload;
        std::chrono::milliseconds _fireFrequence;
};

#endif /* !__UNIT_HH__ */
