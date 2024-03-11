
#ifndef MAIN_OBJECT_H_
#define MAIN_OBJECT_H_

#include <Vector>
#include "CommonFunction.h"
#include "BaseObject.h"
#include "BulletObject.h"


#define Gravity_speed 0.8
#define MAX_FALL_SPEED 10
#define PLAYER_SPEED 10
#define PLAYER_JUMP 18



class MainObject : public BaseObject
{
public:
	MainObject();
	~MainObject();
	
	enum Walktype
	{
		WALK_NONE = 0,
		WALK_RIGHT = 1,	
		WALK_LEFT = 2,
	};

	bool LoadImg(std::string path, SDL_Renderer* screen);
	void Show(SDL_Renderer* des);
	void HandelInputAction(SDL_Event events, SDL_Renderer* screen);
	void set_clips();
	void DoPlayer(Map& map_data);
	void CheckToMap(Map& map_data);
	void SetMapXY(const int map_x, const int map_y) { map_x_ = map_x; map_y_ = map_y; };
	void CenterEntityOnMap(Map& map_data);
	void UpdateImgPlayer(SDL_Renderer* des);
	void increase_coins() ;
	int return_coins() { return coins; };
	void exept_coins(int coins_) { coins = coins_; };
	bool return_collision() { return collision; };
	void HandleBullet(SDL_Renderer* des);
	void set_bullet_list(std::vector<BulletObject*> bullet_list)
	{
		p_bullet_list = bullet_list;
	}
	std::vector<BulletObject*> get_bullet_list() const { return p_bullet_list; }

private:

	std::vector<BulletObject*> p_bullet_list;


	float x_val_;
	float y_val_;

	float x_pos_;
	float y_pos_;

	int width_frame_;
	int height_frame_;

	SDL_Rect frame_clip_[8];
	
	Input input_type_;
	int frame_;
	int status_;
	bool on_land;
	int map_x_;
	int map_y_;
	int jum_times;
	int jum_times_;
	int come_back_time_;
	int coins;
	int ld_jum;
	bool collision;
	bool first_call_dbjum;
};

#endif