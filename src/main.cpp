/*
** EPITECH PROJECT, 2020
** Irrlicht Fedora 28
** File description:
** main
*/

#include "Game.hpp"
#include <SFML/Audio.hpp>

/*
cmake --build . && cd Release && ./bomberman && cd ..
*/
int main()
{
    Game game;

    std::shared_ptr<IScene> sceneOption = std::shared_ptr<IScene>(
        new SceneOption(game.getVisualManager(), game.getConfig(),
            game.getGameConfig()));
    std::shared_ptr<IScene> sceneMenu = std::shared_ptr<IScene>(
        new SceneMenu(game.getVisualManager(), game.getConfig(),
            game.getGameConfig()));
   std::shared_ptr<IScene> sceneMapSelection = std::shared_ptr<IScene>(
        new SceneMapSelection(game.getVisualManager(), game.getConfig(),
            game.getGameConfig()));
    std::shared_ptr<IScene> scenePlayerSelection = std::shared_ptr<IScene>(
        new ScenePlayerSelection(game.getVisualManager(), game.getConfig(),
            game.getGameConfig()));
    std::shared_ptr<IScene> sceneGame = std::shared_ptr<IScene>(
        new SceneGame(game.getVisualManager(), game.getConfig(),
            game.getGameConfig()));

    game.registerNewScene(MENU, sceneMenu);
    game.registerNewScene(MAP_SELECTION, sceneMapSelection);
    game.registerNewScene(PLAYER_SELECTION, scenePlayerSelection);
    game.registerNewScene(OPTIONS, sceneOption);
    game.registerNewScene(GAME, sceneGame);
    game.setSceneIndex(MENU);

    game.run();
    return 0;
}