#ifndef     __PACKET_HH__
# define    __PACKET_HH__

# include   "IPackable.hh"

namespace   network_packet {

enum class Type : uint8_t
{
    POSITION = 0,
    INPUTS,
    DEATH
};

const size_t    MAX_PACKET_SIZE = 256;

class   Packet
{
    public:
        Packet(Type type, uint8_t *rawData, size_t dataSize);
        Packet(uint8_t *dataFromNetwork, size_t size);
        ~Packet();

    public:
        Packet(const Packet& other);
        Packet(Packet&& other);
        Packet&     operator=(Packet other);
        friend void swap(Packet& lhs, Packet& rhs);

    public:
        Type            getType(void) const;
        const uint8_t   *getContent(void) const;
        size_t          getContentSize(void) const;
        const uint8_t   *getData(void) const;
        size_t          getDataSize(void) const;

    private:
        Type    _type;
        uint8_t _data[MAX_PACKET_SIZE];
        size_t  _dataSize;
};

}

#endif /* !__PACKET_HH__ */
