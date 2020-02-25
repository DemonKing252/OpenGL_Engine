#include "StateMachine.h"

void GameState::Enter()
{
}

void GameState::Update()
{
}

void GameState::Draw()
{
}

void GameState::Exit()
{
}

void TitleState::Enter()
{
}

void TitleState::Update()
{
}

void TitleState::Draw()
{
}

void TitleState::Exit()
{
}

void StateMachine::ChangeState(State * pNextState)
{
	if (mActiveState != nullptr)
	{
		mActiveState->Exit();
	}
	pNextState->Enter();
	mActiveState = pNextState;

}

void StateMachine::Draw()
{
	mActiveState->Draw();
}

void StateMachine::Update()
{
	mActiveState->Update();
}

StateMachine::StateMachine()
{
	mActiveState = nullptr;
}

StateMachine::~StateMachine()
{
}
