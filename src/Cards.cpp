#include "Card.hpp"

static sf::Texture dummy;

Card::Card() : suit(Suit::None), index(-1), points(0), name("Undefined"), sprite(dummy) {}

Card::Card(const std::string &name, int index, Suit suit, Rank rank, float points,
           const sf::Texture &texture, sf::Vector2f position)
    : name(name),
      index(index),
      suit(suit),
      rank(rank),
      points(points),
      sprite(texture) // ← constructeur explicite avec texture
{
    sprite.setPosition(position);
}

bool Card::operator==(const Card &other) const
{
    return this->suit == other.suit &&
           this->index == other.index &&
           this->name == other.name;
}

void Card::draw(sf::RenderTarget& target) const {
    target.draw(sprite);
}

void Card::setPosition(sf::Vector2f position) {
    sprite.setPosition(position);
    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.size / 2.f);
}

void Card::setScale(sf::Vector2f scale) {
    sprite.setScale(scale);
}

void Card::setRotation(sf::Angle angle) {
    sprite.setRotation(angle);
}

const std::string& Card::getName() const {
    return name;
}

Suit Card::getSuit() const {
    return suit;
}

Rank Card::getRank() const {
    return rank;
}

float Card::getPoints() const {
    return points;
}

bool Card::isOudler() const {
    return (suit == Suit::Trump && (rank == Rank::Trump1 || rank == Rank::Trump21)) ||
           (suit == Suit::Excuse);
}

bool Card::isFaceCard() const {
    return rank == Rank::Jack || rank == Rank::Cavalier || rank == Rank::Queen || rank == Rank::King;
}

int Card::getIndex() const {
    return index;
}

sf::Vector2f Card::getSize() const
{
    sf::FloatRect bounds = sprite.getLocalBounds();
    return bounds.size;
}
