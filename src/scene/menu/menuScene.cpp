//
//  menuScene.cpp
//  Pong
//
//  Created by Damien Bendejacq on 27/07/2015.
//  Copyright (c) 2015 Damien Bendejacq. All rights reserved.
//

#include "menuScene.h"

IMPORT_TEXT_RESOURCE(menu_768x576_tmx)

MenuScene::MenuScene()
{
}

MenuScene::~MenuScene()
{
    DELETE_SAFE(m_sceneLoader);
}

void MenuScene::frame(float delta)
{
    UNUSED(delta);

    // Nothing to do each frame!
}

const char* MenuScene::name()
{
    return "menu";
}

void MenuScene::onPlayClick(Scene *scene, void *data)
{
    UNUSED(data);

    scene->loadScene("game");
    scene->cursor()->setCursor(CursorType::Default);
}

void MenuScene::onQuitClick(Scene *scene, void *data)
{
    UNUSED(scene);
    UNUSED(data);

    scene->exit();
}

void MenuScene::onButtonEnter(Scene *scene, void *data)
{
    auto button = static_cast<Entity*>(data);

    auto text = button->getComponent<TextComponent>();
    if (text)
    {
        text->setForeground(Color_YellowGold);
    }

    scene->cursor()->setCursor(CursorType::Hand);
}

void MenuScene::onButtonExit(Scene *scene, void *data)
{
    auto button = static_cast<Entity*>(data);

    auto text = button->getComponent<TextComponent>();
    if (text)
    {
        text->setForeground(Color_White);
    }

    scene->cursor()->setCursor(CursorType::Default);
}

bool MenuScene::initContents()
{
    m_sceneLoader = new MenuSceneLoader(this);
    if (!m_sceneLoader->loadFromMemory(menu_768x576_tmx))
    {
        DELETE_SAFE(m_sceneLoader);
        LOG_ERROR("Could not load Menu scene");

        return false;
    }

    {
        auto playButton = GET_ENTITY("play");
        auto mouseListener = ADD_COMPONENT_FORWARD(playButton, MouseListenerComponent, this);
        mouseListener->onLeftClick(onPlayClick);
        mouseListener->onEnter(onButtonEnter, playButton);
        mouseListener->onExit(onButtonExit, playButton);
    }

    {
        auto quitButton = GET_ENTITY("quit");
        auto mouseListener = ADD_COMPONENT_FORWARD(quitButton, MouseListenerComponent, this);
        mouseListener->onLeftClick(onQuitClick);
        mouseListener->onEnter(onButtonEnter, quitButton);
        mouseListener->onExit(onButtonExit, quitButton);
    }

    return true;
}