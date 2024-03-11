#pragma once

#ifndef BULLET_OBJECT_H_
#define BULLET_OBJECT_H_	

#include "BaseObject.h"
#include "CommonFunction.h"

class BulletObject : public BaseObject
{
public:
	BulletObject();
	~BulletObject();

	void set_x_val(const int& xval) { x_val_ = xval; }
	void set_y_val(const int& yval) { y_val_ = yval; }
	int get_x_val() const { return x_val_; }
	int get_y_val() const { return y_val_; }

	void set_is_move(const bool& ismove) { is_move_ = ismove; }
	bool get_is_move()const { return is_move_; }

	void HandleMove(const int& x_border, const int& y_border);

	void Show(SDL_Renderer * des);
private:
	int x_val_;
	int y_val_;
	bool is_move_;
};

#endif
