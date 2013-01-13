#ifndef     __PACKET_HH__
# define    __PACKET_HH__

# include   "IPackable.hh"

namespace   communication {

class   Packet
{
public:
  static const size_t    MAX_PACKET_SIZE = 256;

  enum class Type : uint8_t
  {
    POSITION = 0,
    INPUT,
    DEATH
  };

public:
  Packet(Type type, uint32_t id, const uint8_t *rawData, size_t dataSize);
  Packet(const uint8_t *dataFromNetwork, size_t size);
  ~Packet();

public:
  Packet(const Packet& other);
  Packet(Packet&& other);
  Packet&     operator=(Packet other);
  friend void swap(Packet& lhs, Packet& rhs);

public:
  Type            getType(void) const;
  uint32_t        getId(void) const;
  const uint8_t   *getContent(void) const;
  size_t          getContentSize(void) const;
  const uint8_t   *getData(void) const;
  size_t          getDataSize(void) const;

private:
  struct {
    Type      type;
    uint32_t  id;
  } _header;
  uint8_t   _data[MAX_PACKET_SIZE];
  size_t    _dataSize;
};

}

#endif /* !__PACKET_HH__ */
