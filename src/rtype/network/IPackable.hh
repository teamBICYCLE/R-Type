#ifndef     __IPACKABLE_HH__
# define    __IPACKABLE_HH__

# include   <cstdint>

class   IPackable
{
    public:
        virtual ~IPackable() {}

    public:
        virtual size_t      pack(uint8_t *out, size_t outSize) const = 0;
        virtual void        unpack(const uint8_t* content) = 0;
};

#endif /* !__IPACKABLE_HH__ */
