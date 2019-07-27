#include "GUIManager.h"
#include <Graphics/DirectXPlatformManager.h>
#include <GUI/ExampleLayout.h>
#include <NativePlatform/NativePlatform.h>

namespace SimpleEngine
{
	namespace UI
	{
		void GUIManager::Initialize()
		{
			camera_ = std::make_shared<Camera>();
			camera_->SetPosition(0.0f, 0.0f, -100.0f);
			camera_->Render();

			GUIManager::Instance().SetStandardWindowSize(1920, 1080);

			std::shared_ptr<BaseLayout> layout_a = std::make_shared<ExampleLayout>(1);
			RegisterLayout(layout_a);
		}

		float GUIManager::GetWidthResizeScale()
		{
			return static_cast<float>(NativePlatform::Instance().GetScreenWidth()) / standard_window_size_.width;
		}

		float GUIManager::GetHeightResizeScale()
		{
			return static_cast<float>(NativePlatform::Instance().GetScreenHeight()) / standard_window_size_.height;
		}

		void GUIManager::OnWindowResized()
		{
			for (auto layout : layout_list_)
			{
				layout->OnResize();
			}
		}

		void GUIManager::OnRender()
		{
			// �ر� Z buffer = �ر���Ȳ��� = ����д��ָ������λ�õ����ݶ������Ը��ǵ�ԭ�������� = ��֤�� 2D UI �ܸ����� 3D ����֮��
			// TODO: Make sure to use the painter's algorithm and draw from the back to the front to ensure you get your expected rendering output.
			DirectXPlatformManager::Instance().TurnZBufferOff();

			for (auto layout : layout_list_)
			{
				layout->OnRender();
			}

			// ���� 2D UI ��Ⱦ���, ���¿��� Z buffer, ��ֹӰ�������Ⱦ
			DirectXPlatformManager::Instance().TurnZBufferOn();
		}

		void GUIManager::RegisterLayout(std::shared_ptr<BaseLayout> layout)
		{
			layout_list_.push_back(layout);
			layout->OnRegister();
		}
	}
}