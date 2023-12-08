#include "map.h"

sf::ConvexShape InitializeTriangle()
{
    sf::ConvexShape triangle;

    triangle.setPointCount(9);

    triangle.setOutlineColor(sf::Color::Blue);
    triangle.setFillColor(sf::Color::Transparent);
    triangle.setOutlineThickness(.75f);
    triangle.setOrigin(0, 0);
    
    triangle.setPoint(0, sf::Vector2f(0, -10));
    triangle.setPoint(1, sf::Vector2f(5, -3.333333333333f));
    triangle.setPoint(2, sf::Vector2f(10, 3.33333333333333f));

    triangle.setPoint(3, sf::Vector2f(15, 10));
    triangle.setPoint(4, sf::Vector2f(5, 10));
    triangle.setPoint(5, sf::Vector2f(-5, 10));

    triangle.setPoint(6, sf::Vector2f(-15,10));
    triangle.setPoint(7, sf::Vector2f(-10, 3.33333333333333f));
    triangle.setPoint(8, sf::Vector2f(-5, -3.333333333333f));

    return triangle;
}

sf::ConvexShape InitializeSquare() {
    sf::ConvexShape square;

    square.setPointCount(8);

    square.setOutlineColor(sf::Color::Blue);
    square.setFillColor(sf::Color::Transparent);
    square.setOutlineThickness(.75f);
    square.setOrigin(0, 0);

    square.setPoint(0, sf::Vector2f(0,-10));
    square.setPoint(1, sf::Vector2f(+10,-10));
    square.setPoint(2, sf::Vector2f(+10,0));
    square.setPoint(3, sf::Vector2f(+10,+10));
    square.setPoint(4, sf::Vector2f(0,+10));
    square.setPoint(5, sf::Vector2f(-10,+10));
    square.setPoint(6, sf::Vector2f(-10,0));
    square.setPoint(7, sf::Vector2f(-10,-10));
    
    return square;
}

sf::ConvexShape InitializePentagon() {
    sf::ConvexShape pentagon;

    pentagon.setPointCount(5);

    pentagon.setOutlineColor(sf::Color::Blue);
    pentagon.setFillColor(sf::Color::Transparent);
    pentagon.setOutlineThickness(.75f);
    pentagon.setOrigin(0, 0);

    pentagon.setPoint(0, sf::Vector2f(0,-9.5f));
    pentagon.setPoint(1, sf::Vector2f(10,0));
    pentagon.setPoint(2, sf::Vector2f(6,10));
    pentagon.setPoint(3, sf::Vector2f(-6,10));
    pentagon.setPoint(4, sf::Vector2f(-10,0));

    return pentagon;
}

void DrawLevel(sf::RenderWindow& window, sf::ConvexShape shape, sf::Vector2f Position, float minScale, float maxScale,sf::Color color, sf::Color lineColor) {

    //center of the screen
    //int centerX = window.getSize().x / 2;
    //int centerY = window.getSize().y / 2;

    shape.setOutlineColor(color);


    shape.setPosition(Position);
    
    shape.setScale(maxScale, maxScale);
    window.draw(shape);

    shape.setScale(minScale, minScale);
    window.draw(shape);

    //line point position
    for (int i = 0; i < shape.getPointCount(); i++) 
    {
        float startX = Position.x + shape.getPoint(i).x * (minScale);
        float startY = Position.y + shape.getPoint(i).y * (minScale);
        float endX = Position.x + shape.getPoint(i).x * maxScale;
        float endY = Position.y + shape.getPoint(i).y * (maxScale);


        sf::Color drawColor = color;
        if(playerPos != -1)
            if (i == playerPos || i - 1 == playerPos || (i == 0 && playerPos == shape.getPointCount() - 1))
                drawColor = playerColor;

        sf::Vertex line[] =
        {
            sf::Vertex(sf::Vector2f(startX, startY), drawColor),
            sf::Vertex(sf::Vector2f(endX, endY), drawColor)
        };

        for (int j = 0; i < shape.getPointCount(); j++) {
            //line->color = sf::Color::Yellow;
            sf::Vertex(sf::Vector2f(startX, startY), lineColor);
            sf::Vertex(sf::Vector2f(endX, endY), lineColor);
        }

        window.draw(line, 2, sf::Lines);
    }
}

void AddLevel(levelShape& level) 
{
    int newLevel = (int)level + 1;
    if (newLevel > 2)
        newLevel = 0;
    level = (levelShape)newLevel;
}

void changeLevel(sf::ConvexShape& map, std::vector<sf::Vector3f>& positionList, levelShape currentShape)
{
    //Init player position list
    sf::Vector3f TrianglePositionList[9] = {
    {1090,330,55},
    {1220,500,60},
    {1360,730,55},
    {1250,890,180},
    {960,890,180},
    {690,890,180},
    {560,730,-50},
    {690,510,-55},
    {830,330,-55}
    };
    sf::Vector3f SquarePositionList[8] = {
    {1100,195,0},
    {1300,400,90},
    {1300,650,90},
    {1100,875,180},
    {800,875,180},
    {620,650,-90},
    {620,400,-90},
    {820,195,0}
    };
    sf::Vector3f PentagonPositionList[5] = {
    {1150,370,54},
    {1240,700,108},
    {975,890,175},
    {680,700,-108},
    {775,370,-54}
    };

    positionList.clear();
    switch (currentShape)
    {
    case levelShape::triangle:
        map = InitializeTriangle();
        for (int i = 0; i < 9; i++) {
            positionList.push_back(TrianglePositionList[i]);
        }
        break;

    case levelShape::square:
        map = InitializeSquare();
        for (int i = 0; i < 8; i++) {
            positionList.push_back(SquarePositionList[i]);
        }
        break;

    case levelShape::pentagon:
        map = InitializePentagon();
        for (int i = 0; i < 5; i++) {
            positionList.push_back(PentagonPositionList[i]);
        }
        break;
    }
}

void Background::InitializeBackground(sf::Vector2f centerWindow)
{
    backgroundCircleShape.setPointCount(16);
    backgroundCircleShape.setRadius(1);
    backgroundCircleShape.setFillColor(sf::Color::Transparent);
    backgroundCircleShape.setOrigin(backgroundCircleShape.getRadius(), backgroundCircleShape.getRadius());
    backgroundCircleShape.setPosition(centerWindow);
}

void Background::DrawBackground(sf::RenderWindow& window, Effect& effect, float deltaTime)
{
    backgroundCircleShape.setOutlineColor(effect.RandomColor());
    backgroundCircleShape.rotate(deltaTime * 30);

    for (int i = 1; i < 10; i++) {
        backgroundCircleShape.setOutlineThickness(0.05f);
        backgroundCircleShape.setScale(sf::Vector2f(i * 100, i * 100));
        window.draw(backgroundCircleShape);
    }
}