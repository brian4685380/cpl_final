#pragma once
class player_money {
   public:
	// constructor
	player_money();
	player_money(int n);
	~player_money();

	// set and get
	void money_set(int n);
	int money_get();

	// +
	void operator+=(int n);									// _money +=
	player_money operator+(player_money& m);				// _money + _money
	player_money operator+(int n);							// _money + int
	friend player_money operator+(int n, player_money& m);	// int + _money (global)

	// -
	bool is_positive();										// if money < 0, set money to 0
	void operator-=(int n);									// _money -=
	player_money operator-(player_money& m);				// _money - _money
	player_money operator-(int n);							// _money - int
	friend player_money operator-(int n, player_money& m);	// int - _money (global)

   private:
	int _money = 0;
};