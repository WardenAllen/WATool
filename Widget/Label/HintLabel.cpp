
/*
 * @author WardenAllen
 * @date   2020/10/22 20:36:58
 * @brief  
 */

#include "HintLabel.h"

HintLabel::HintLabel(HINT_MODE m_, HINT_STATE s_)
{
	_mode = m_;
	_state = HS_INIT;
	clear();
	setAutoFillBackground(true);
	SetState(s_);
	_state = s_;
}

void HintLabel::SetState(HINT_STATE s_)
{
	if (s_ == _state) return;

	_state = s_;

	QPalette plt = palette();

	if (_mode == HM_MODE_2)
	{
		switch (s_) {
		case HS_0:
			plt.setColor(QPalette::Background, QColor(255, 0, 0));
			break;

		case HS_1:
			plt.setColor(QPalette::Background, QColor(0, 255, 0));
			break;

		default:
			break;
		}
	}
	else if (_mode == HM_MODE_3)
	{
		switch (s_) {
		case HS_0:
			plt.setColor(QPalette::Background, QColor(255, 0, 0));
			break;

		case HS_1:
			plt.setColor(QPalette::Background, QColor(0, 255, 0));
			break;

		case HS_2:
			plt.setColor(QPalette::Background, QColor(0, 0, 255));
			break;

		default:
			break;
		}
	}

	setPalette(plt);
}


