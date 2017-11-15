//
// 2playersGameOverState.cpp
// pong
//
// Created by Damien Bendejacq on 02/10/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#include "2playersGameOverState.hpp"
#include "../../menu/menuScene.hpp"
#include "../../const.hpp"

TwoPlayersGameOverState::TwoPlayersGameOverState(StateMachine& stateMachine, Scene& scene, TmxSceneLoader& sceneLoader)
    : SceneState(stateMachine, scene),
      m_leftScore {sceneLoader.entity("left_score")},
      m_rightScore {sceneLoader.entity("right_score")},
      m_leftResult {sceneLoader.entity("left_result")},
      m_rightResult {sceneLoader.entity("right_result")},
      m_gameOver {sceneLoader.entity("game_over")},
      m_terminateGameInstruction {sceneLoader.entity("terminate_game_instruction")}
{ }

void TwoPlayersGameOverState::enter()
{
    enableEntity(m_gameOver);
    enableEntity(m_leftResult);
    enableEntity(m_rightResult);
    enableEntity(m_terminateGameInstruction);

    auto& leftResultText = getComponent<Text>(m_leftResult);
    auto& rightResultText = getComponent<Text>(m_rightResult);

    auto& leftScore = getComponent<Numerical<int>>(m_leftScore);
    if (Const::ScoreToWin == leftScore.get())
    {
        leftResultText.setText(Const::WinText);
        leftResultText.setForeground(Const::WinColor);
        rightResultText.setText(Const::LoseText);
        rightResultText.setForeground(Const::LoseColor);
    }
    else
    {
        leftResultText.setText(Const::LoseText);
        leftResultText.setForeground(Const::LoseColor);
        rightResultText.setText(Const::WinText);
        rightResultText.setForeground(Const::WinColor);
    }
}

void TwoPlayersGameOverState::frame(float)
{
    if (input().keyPress(KeyboardKey::Space))
    {
        loadScene<MenuScene>();
    }
}