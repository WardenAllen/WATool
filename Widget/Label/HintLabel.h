
/*
 * @author WardenAllen
 * @date   2020/10/22 20:36:49
 * @brief  
 */

#pragma once

#include "Header.h"

enum HINT_MODE
{
	HM_NONE = 0,
	HM_MODE_2,
	HM_MODE_3,
};

enum HINT_STATE
{
	HS_INIT = 0,
	HS_0,
	HS_1,
	HS_2
};

class HintLabel : public QLabel
{
	Q_OBJECT
public:
	HintLabel(HINT_MODE m = HM_MODE_2, HINT_STATE s = HS_0);

	void SetState(HINT_STATE _s);
	inline int GetState() { return _state; }

private:
	HINT_MODE _mode;
	HINT_STATE _state;

};