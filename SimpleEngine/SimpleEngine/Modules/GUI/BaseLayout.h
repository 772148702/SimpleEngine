#ifndef UI_BASELAYOUT_H_
#define UI_BASELAYOUT_H_

#pragma once

#include <memory>

namespace SimpleEngine
{
	namespace UI
	{
		class LayoutNode;

		// һ�������Ľ��� (�����̵���桢���������)
		class BaseLayout
		{
		public:
			BaseLayout(float scale_weight);
			virtual ~BaseLayout();

			float GetResizeScale();

			void OnRegister();
			void OnResize();
			void OnRender();

		protected:
			void RegisterRootNode(LayoutNode *node);

		private:
			// ������ͬһ������� widget ����ȱ����Ų��ܱ�֤�������
			float scale_weight_{ 1 };
			// ���ؼ�(û�и��ؼ��Ľڵ�), һ�� BaseLayout = һ����, ��Ӧһ�����ؼ�����������е��ӿؼ�
			LayoutNode *root_node_{ nullptr };
		};
	}
}

#endif // !UI_BASELAYOUT_H_