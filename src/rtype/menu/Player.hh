#ifndef _PLAYER_HH__
# define _PLAYER_HH__

# include <string>
# include <sstream>

class Player {
public:
  Player(const std::string& infos);
  ~Player();

  int	getId() const;

private:
  int	_id;
};

#endif // !_PLAYER_HH__
