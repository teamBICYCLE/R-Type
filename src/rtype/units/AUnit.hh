#ifndef     __AUNIT_HH__
# define    __AUNIT_HH__

# include   <ostream>
# include   "utilities/Vector2D.hh"

class   AUnit
{
    public:
        AUnit(int id, const Vector2D& pos, const Vector2D& dir);
        virtual ~AUnit() {}

    public:
        AUnit(const AUnit& other);
        AUnit(AUnit&& other);
        AUnit&  operator=(AUnit other);
        friend void    swap(AUnit& lhs, AUnit& rhs);

    public:
        void    move(void);
        void    setDirection(const Vector2D& dir);

    public:
        friend std::ostream&    operator<<(std::ostream& stream, const AUnit& unit);

    protected:
        Vector2D		_pos;
        Vector2D		_dir;
        unsigned int	_id;
};

#endif /* !__AUNIT_HH__ */
