#pragma once

class Easing final
{
private:
	Easing() = default;
	~Easing() = default;
	Easing(const Easing & obj) = delete;
	Easing& operator=(const Easing & obj) = delete;

public: //静的メンバ関数
	static Easing* GetIns() {
		static Easing instans;
		return &instans;
	}

public: //メンバ関数
	inline float easeIn(float time, float maxTime, float maxPos, float nowPos) {
		maxPos -= nowPos;
		time /= maxTime;

		return maxPos * time * time + nowPos;
	}

	inline float easeOut(float time, float maxTime, float maxPos, float nowPos) {
		maxPos -= nowPos;
		time /= maxTime;

		return -maxPos * time * (time - 2.0f) + nowPos;
	}
};

