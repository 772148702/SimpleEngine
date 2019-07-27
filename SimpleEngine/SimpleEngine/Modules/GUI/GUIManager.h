#ifndef UI_GUI_MANAGER_H_
#define UI_GUI_MANAGER_H_

#pragma once

#include <vector>
#include <memory>

#include <GUI/UICommon.h>

class Camera;

namespace SimpleEngine
{
	namespace UI
	{
		class BaseLayout;

		class GUIManager
		{
		public:
			static GUIManager& Instance()
			{
				static GUIManager instance;
				return instance;
			}
			GUIManager(GUIManager const&) = delete;
			void operator=(GUIManager const&) = delete;

			void Initialize();

			// ʵ�ʴ��ڵĿ� / ��׼�ֱ��ʵĿ�
			float GetWidthResizeScale();
			// ʵ�ʴ��ڵĸ� / ��׼�ֱ��ʵĸ�
			float GetHeightResizeScale();

			void SetStandardWindowSize(unsigned int width, unsigned int height)
			{
				standard_window_size_.width = width;
				standard_window_size_.height = height;
			}

			std::shared_ptr<Camera> GetCamera() { return camera_; }

			void OnWindowResized();
			void OnRender();

			void RegisterLayout(std::shared_ptr<BaseLayout> layout);

		private:
			GUIManager() { }

		private:
			std::shared_ptr<Camera> camera_;
			// �������ʱ���ο��ĵı�׼���ڴ�С
			Size<int> standard_window_size_;
			std::vector<std::shared_ptr<BaseLayout>> layout_list_;
		};
	}
}

#endif // !UI_GUI_MANAGER_H_