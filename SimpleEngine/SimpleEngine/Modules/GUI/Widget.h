#ifndef UI_WIDGET_H_
#define UI_WIDGET_H_

#pragma once

#include <memory>
#include <vector>

#include <GUI/UICommon.h>

namespace SimpleEngine
{
	namespace UI
	{
		class BaseLayout;
		class ISkin;

		// ���ֶ���, �������ؼ���λ������ͳߴ��С
		// ����һ�� UI ����ϵ: ����Ļ���Ͻ�Ϊԭ��, X������Ϊ������, Y������Ϊ������
		// ���ֶ�����������: �� LayoutNode ���Ͻ�Ϊ��׼����бȽ�
		class LayoutNode
		{
		public:
			explicit LayoutNode(LayoutNode *parent = nullptr);
			virtual ~LayoutNode();

			bool IsRootWidget();
			void AddChild(LayoutNode *child);

			virtual void OnResize(float resize_scale);
			virtual void OnRender(Point<int> parent_absolute_position = Point<int>());

			Size<int> GetSize()
			{
				return relative_coord_.GetSize();
			}

			// ��Щ public API ���ǰ��ս������ʱ�ı�׼�ֱ��������ÿؼ��ĳߴ�, ���ڷֱ���������ʵ������, ���� API ��������͸����
			void SetCoord(Rect<int> anchor_offset,
				Point<float> anchor_min = Point<float>(0.5, 0.5), Point<float> anchor_max = Point<float>(0.5, 0.5));

			std::shared_ptr<ISkin> GetSkin() { return owned_skin_; }

			void SetSkin(std::shared_ptr<ISkin> skin);

		protected:
			// left, top ��ê�� [0, 1]
			Point<float> anchor_min_{ 0.5,0.5 };
			// right, bottom ��ê�� [0, 1]
			Point<float> anchor_max_{ 0.5,0.5 };
			// �������ʱ���ο���ı������ê��ľ���
			Rect<int> anchor_offset_;
			// ����ڸ��ؼ����Ͻǵĳߴ����� (�ֱ��������Ľ��)
			Coord<int> relative_coord_;

			LayoutNode *node_parent_{ nullptr };
			std::vector<LayoutNode*> node_children_;
			std::shared_ptr<ISkin> owned_skin_;
		};
	}
}

#endif // UI_WIDGET_H_