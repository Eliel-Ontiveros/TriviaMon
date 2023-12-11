/*
#pragma once

class trivia
{
private:
    bool isNpcInteracting = false;
    int npcInteractionDistance = 50;
    int currentMessageIndex = 0;
    std::vector<std::string> npcMessages = {
        "Hello there! Welcome to the world of Pokemon!",
        "My name is Oak! People call me the Pokemon Prof!",
        "This world is inhabited by creatures called Pokemon!",
        "For some people, Pokemon are pets.",
        "Others use them for fights.",
        "Myself...",
        "I study Pokemon as a profession."
    };

public:
public:
    void checkNpcInteraction()
    {
        Vector2D playerPos = player.getComponent<TransformComponent>().position;
        Vector2D npcPos = npc.getComponent<TransformComponent>().position;
        float distance = Vector2D::distance(playerPos, npcPos);

        if (distance < npcInteractionDistance)
        {
            startNpcInteraction();
        }
    }

    void startNpcInteraction()
    {
        isNpcInteracting = true;
        currentMessageIndex = 0;
    }

    void updateNpcInteraction()
    {
        if (isNpcInteracting)
        {
            if (currentMessageIndex < npcMessages.size())
            {
                npcMessage = npcMessages[currentMessageIndex];
                currentMessageIndex++;
            }
            else
            {
                isNpcInteracting = false;
                npcMessage.clear();
            }
        }
    }

    void renderNpcMessage()
    {
        if (isNpcInteracting && !npcMessage.empty())
        {
            TTF_Font* Sans = TTF_OpenFont("assets/arial.ttf", 24);
            SDL_Color White = { 255, 255, 255 };

            SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, npcMessage.c_str(), White);
            SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

            // Configurar la posición y tamaño del mensaje
            SDL_Rect Message_rect;
            Message_rect.x = npc.getComponent<TransformComponent>().position.x;
            Message_rect.y = npc.getComponent<TransformComponent>().position.y - 50;
            Message_rect.w = 200;
            Message_rect.h = 50;

            // Renderizar el mensaje
            SDL_RenderCopy(renderer, Message, NULL, &Message_rect);

            // Liberar la superficie y textura
            SDL_FreeSurface(surfaceMessage);
            SDL_DestroyTexture(Message);

            // Limpiar el mensaje para evitar parpadeos
            npcMessage.clear();

            // Cerrar la fuente después de usarla
            TTF_CloseFont(Sans);
        }
    }
};

*/