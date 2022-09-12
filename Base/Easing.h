#pragma once

class Easing final
{
private:
	Easing() = default;
	~Easing() = default;
	Easing(const Easing & obj) = delete;
	Easing& operator=(const Easing & obj) = delete;

public: //Ã“Iƒƒ“ƒoŠÖ”
	static Easing* GetIns() {
		static Easing instans;
		return &instans;
	}

public: //ƒƒ“ƒoŠÖ”
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

