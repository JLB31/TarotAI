#pragma once
#include <SFML/Graphics.hpp>
#include <string>

enum class Suit {
    Hearts, Diamonds, Clubs, Spades, Trump, Excuse,None
};

enum class Rank {
    One = 1, Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten,
    Jack, Cavalier, Queen, King,

    Trump1 = 101, Trump2, Trump3, Trump4, Trump5, Trump6, Trump7,
    Trump8, Trump9, Trump10, Trump11, Trump12, Trump13, Trump14,
    Trump15, Trump16, Trump17, Trump18, Trump19, Trump20, Trump21,

    Excuse = 200
};


class Card {
public:
    Card();
    Card(const std::string& name, int index, Suit suit, Rank rank, float points,
         const sf::Texture& texture, sf::Vector2f position);

    bool operator==(const Card &other) const;

    void draw(sf::RenderTarget& target) const;
    void setPosition(sf::Vector2f position);
    void setScale(sf::Vector2f scale);
    void setRotation(sf::Angle angle);
    const std::string& getName() const;
    Suit getSuit() const;
    Rank getRank() const;
    float getPoints() const;
    bool isOudler() const;
    bool isFaceCard() const;
    int getIndex() const;
    sf::Vector2f getSize() const;

private:
    std::string name;
    int index;
    Suit suit;
    Rank rank;
    float points;
    sf::Sprite sprite;
};

