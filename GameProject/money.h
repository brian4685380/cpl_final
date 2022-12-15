#pragma once
class Money {
   public:
	// constructor
	Money();
	Money(int);
	~Money();

	// set and get
	void money_set(int);
	int money_get();

	// +
	void operator+=(Money&);	
	void operator+=(int);									// _money +=
	Money operator+(Money&);				// _money + _money
	Money operator+(int);							// _money + int
	friend Money operator+(int, Money&);	// int + _money (global)

	// -
	bool is_positive();										// if money < 0, set money to 0
	void operator-=(Money&);	
	void operator-=(int);									// _money -=
	Money operator-(Money&);				// _money - _money
	Money operator-(int);							// _money - int
	friend Money operator-(int, Money&);	// int - _money (global)

   private:
	int _money = 0;
};