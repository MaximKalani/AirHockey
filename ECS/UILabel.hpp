#ifndef UILABEL_HPP_INCLUDED
#define UILABEL_HPP_INCLUDED

#include "ECS.hpp"
#include "../TextureManager.hpp"
#include "../engine.hpp"
#include <string>

//component draws a text with TTF font at certain position

class UILabel : public Component
{
public:
    UILabel(int xpos, int ypos, int size, std::string text, std::string fontpath) :
        labelText(text), labelFont(fontpath), textSize(size)
    {
        position.x = xpos;
        position.y = ypos;
        font = TTF_OpenFont(labelFont.c_str(), size);
        setLabelText();

    }

    ~UILabel()
    {

    }

    void setLabelText()
    {
        SDL_Surface* surf = TTF_RenderText_Blended(font, labelText.c_str(), textColor);
        labelTexture = SDL_CreateTextureFromSurface(Game::renderer, surf);
        SDL_FreeSurface(surf);

        SDL_QueryTexture(labelTexture, nullptr, nullptr, &position.w, &position.h);
    }

    void update() override
    {
        char buff[100];
        snprintf(buff, sizeof(buff), "Player %.0f - %.0f Bot", Game::score.x, Game::score.y);
        labelText = buff;
        setLabelText();
    }

    void draw() override
    {
        SDL_RenderCopy(Game::renderer, labelTexture, nullptr, &position);
    }

private:
    SDL_Rect position;
    std::string labelText;
    std::string labelFont;
    SDL_Color textColor = {0,0,0};
    SDL_Texture* labelTexture;
    TTF_Font* font;
    int textSize;
};


#endif