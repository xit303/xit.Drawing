#pragma once

#include <Drawing/Container.h>
#include <Drawing/Label.h>
#include <Timers/Timer.h>

namespace xit::Drawing
{
	class ToolTip : public Container
	{
	private:
		Label textLabel;

		static Timer startTimer;
		static Timer stopTimer;

		static ToolTip &GetInstance();
		ToolTip();

	protected:
		int OnMeasureWidth(int available) override;
		int OnMeasureHeight(int available) override;

		void OnUpdate(const Rectangle &bounds) override;

	public:
		static void SetDPI(float scaleX, float scaleY);

		static void DoUpdate(Rectangle &bounds);
		static void DoRender();

		static void Show(const std::string &text, int x, int y, int duration = 0);
		static void Hide();
	};
}
