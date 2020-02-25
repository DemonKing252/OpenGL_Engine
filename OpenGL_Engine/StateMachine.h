#pragma once
class State
{
private:
	// Members
public:
	
	virtual void Enter() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Exit() = 0;

	// Abstract Class
};

class GameState : public State
{
public:
	void Enter();
	void Update();
	void Draw();
	void Exit();

};
class TitleState : public State
{
public:
	void Enter();
	void Update();
	void Draw();
	void Exit();

};

class StateMachine
{
private:
	State* mActiveState = nullptr;

public:
	void ChangeState(State* pNextState);
	void Draw();
	void Update();

	StateMachine();
	~StateMachine();
};

