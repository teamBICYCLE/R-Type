#include <cstring>
#include <stdexcept>
#include <system/log/Log.hh>
#include "Unit.hh"
#include "gamestate/GameState.hh"

using namespace TBSystem;

Unit::Unit(int id, const Vector2D& pos, const Vector2D& dir)
  : _lastPacketSequence(0)
  , _pos(pos)
  , _dir(dir)
  , _id(id)
  , _hitboxCenter(_pos)
  , _hitboxRadius(10.f)
  , _isDead(false)
  , _othersNotifiedOfDeath(false)
  , _resourceId(1)
  , _pv(1)
  , _munition(UNLIMITED)
  , _timeToReload(0)
  , _fireFrequence(10)
{
}

Unit::Unit(void)
  : _lastPacketSequence(0)
  , _pos()
  , _dir()
  , _id()
  , _hitboxCenter()
  , _hitboxRadius(10.f)
  , _isDead(false)
  , _othersNotifiedOfDeath(false)
  , _resourceId()
  , _pv()
  , _munition()
  , _timeToReload()
  , _fireFrequence()
{
}

Unit::Unit(const Unit& other)
  : _lastPacketSequence(other._lastPacketSequence)
  , _pos(other._pos)
  , _dir(other._dir)
  , _id(other._id)
  , _hitboxCenter(other._hitboxCenter)
  , _hitboxRadius(other._hitboxRadius)
  , _isDead(other._isDead)
  , _othersNotifiedOfDeath(other._othersNotifiedOfDeath)
  , _resourceId(other._resourceId)
  , _pv(other._pv)
  , _munition(other._munition)
  , _timeToReload(other._timeToReload)
  , _fireFrequence(other._fireFrequence)
{
}

Unit::~Unit()
{
}

Unit::Unit(Unit&& other)
{
  swap(*this, other);
}

Unit&  Unit::operator=(Unit other)
{
  swap(*this, other);
  return *this;
}

void    swap(Unit& lhs, Unit& rhs)
{
    std::swap(lhs._lastPacketSequence, rhs._lastPacketSequence);
    std::swap(lhs._pos, rhs._pos);
    std::swap(lhs._dir, rhs._dir);
    std::swap(lhs._id, rhs._id);
    std::swap(lhs._hitboxCenter, rhs._hitboxCenter);
    std::swap(lhs._hitboxRadius, rhs._hitboxRadius);
    std::swap(lhs._isDead, rhs._isDead);
    std::swap(lhs._othersNotifiedOfDeath, rhs._othersNotifiedOfDeath);
    std::swap(lhs._resourceId, rhs._resourceId);
    std::swap(lhs._pv, rhs._pv);
    std::swap(lhs._munition, rhs._munition);
    std::swap(lhs._timeToReload, rhs._timeToReload);
    std::swap(lhs._fireFrequence, rhs._fireFrequence);
}

uint32_t	Unit::getLastPacketSequence(void) const
{
  return _lastPacketSequence;
}

uint32_t  Unit::getId(void) const
{
    return _id;
}

const Vector2D& Unit::getPos(void) const
{
    return _pos;
}

const Vector2D& Unit::getDir(void) const
{
    return _dir;
}

const Vector2D& Unit::getHitboxCenter(void) const
{
  return _hitboxCenter;
}

float Unit::getHitboxRadius(void) const
{
  return _hitboxRadius;
}

bool  Unit::isDead(void) const
{
  return _isDead;
}

bool  Unit::wereOthersNotifiedOfDeath(void) const
{
  return _othersNotifiedOfDeath;
}

// const std::string &Unit::getSpritePath(void) const
// {
//   return _spritePath;
// }

void  Unit::move(void)
{
    _pos += _dir;
    _hitboxCenter = _pos;
}

bool  Unit::collideWith(Unit& other)
{
  float dist = _hitboxCenter.distanceSquared(other.getHitboxCenter());

  return dist <= (((_hitboxRadius + other.getHitboxRadius()) / GameState::WINDOW_WIDTH) *
                 ((_hitboxRadius + other.getHitboxRadius()) / GameState::WINDOW_WIDTH));
}

void  Unit::setId(const uint32_t id)
{
    _id = id;
}

void  Unit::setDir(const Vector2D& dir)
{
    _dir = dir;
}

void  Unit::setLastPacketSequence(uint32_t newPacketSequence)
{
  _lastPacketSequence = newPacketSequence;
}

void  Unit::setPos(const Vector2D& pos)
{
  _pos = pos;
}

void    Unit::setHitboxCenter(const Vector2D& center)
{
  _hitboxCenter = center;
}

void    Unit::setHitboxRadius(const float radius)
{
  _hitboxRadius = radius;
}

void    Unit::setDead(bool b)
{
  _isDead = b;
}

void    Unit::setOthersNotifiedOfDeath(bool b)
{
  _othersNotifiedOfDeath = b;
}

void  Unit::setResourceId(const unsigned int v)
{
  _resourceId = v;
}

unsigned int Unit::getResourceId(void) const
{
  return _resourceId;
}

void  Unit::setPv(const unsigned int v)
{
  _pv = v;
}

unsigned int Unit::getPv(void) const
{
  return _pv;
}

void  Unit::setMunition(const unsigned int v)
{
  _munition = v;
}

int Unit::getMunition(void)
{
  return _munition;
}

void    Unit::setTimeToReload(const std::chrono::milliseconds &t)
{
  _timeToReload = t;
}

void    Unit::setFireFrequence(const std::chrono::milliseconds &t)
{
  _fireFrequence = t;
}

const std::chrono::milliseconds &Unit::getTimeToReload(void) const
{
  return _timeToReload;
}

const std::chrono::milliseconds &Unit::getFireFrequence(void) const
{
  return _fireFrequence;
}

inline int16_t  to_short(float f)
{
  return f * 10000;
}

inline float  to_float(short s)
{
  return s / 10000.f;
}

size_t  Unit::pack(uint8_t *out, size_t outSize) const
{
    UnitPacket_u            packetContent;

    packetContent.info.x = to_short(_pos.x);
    packetContent.info.y = to_short(_pos.y);
    packetContent.info.dx = to_short(_dir.x);
    packetContent.info.dy = to_short(_dir.y);

    communication::Packet packet(communication::Packet::Type::POSITION, _id, _resourceId,
                                  packetContent.whole, sizeof(packetContent.whole));

    if (outSize < packet.getDataSize())
        throw std::overflow_error("Output is too small for the packet to fit");
    if (_isDead == true)//if the player is dead...
    {
      packet.setType(communication::Packet::Type::DEATH);
      packet.setReliable(true);//the packet is set reliable so that the client must ack it
    }
    std::memcpy(out, packet.getData(), packet.getDataSize());
    return packet.getDataSize();
}

void    Unit::unpack(const uint32_t newPacketSequence, const uint8_t* content)
{
  const UnitPacket_u *info = reinterpret_cast<const UnitPacket_u*>(content);

  if (_lastPacketSequence < newPacketSequence)
  {
    _lastPacketSequence = newPacketSequence;
    _pos.x = to_float(info->info.x);
    _pos.y = to_float(info->info.y);
    _dir.x = to_float(info->info.dx);
    _dir.y = to_float(info->info.dy);
  }
  else
  {
    std::cout << "==============================================DROPPED. Last: " << _lastPacketSequence << ". New: " << newPacketSequence << std::endl;
    _lastPacketSequence = 0;
  }
}

std::ostream&   operator<<(std::ostream& stream, const Unit& unit)
{
  stream << "Unit #" << unit._id << " position: " << unit._pos.x << "-" << unit._pos.y;
	return stream;
}

Unit *Unit::clone(void)
{
  return (new Unit(*this));
}

void  Unit::reset(void)
{
    _pos = Vector2D();
    _dir = Vector2D();
    _id = uint32_t();
    _hitboxCenter = _pos;
    _isDead = false;
    _othersNotifiedOfDeath = false;
    _resourceId = 1;
    _pv = 1;
    _munition = UNLIMITED;
}

