#include <iostream>

#include <GUI/LayoutNode.h>
#include <GUI/Skin.h>
#include <GUI/BaseLayout.h>
#include <NativePlatform/NativePlatform.h>
#include <GUI/GUIManager.h>

namespace SimpleEngine
{
	namespace UI
	{
		LayoutNode::LayoutNode(LayoutNode *parent) :
			node_parent_(parent)
		{
			if (node_parent_)
			{
				node_parent_->AddChild(this);
			}
		}

		LayoutNode::~LayoutNode()
		{
			for (size_t i = 0; i < node_children_.size(); i++)
			{
				delete node_children_[i];
				node_children_[i] = nullptr;
			}
		}

		bool LayoutNode::IsRootWidget()
		{
			return nullptr == node_parent_;
		}

		void LayoutNode::AddChild(LayoutNode *child)
		{
			node_children_.push_back(child);
		}

		void LayoutNode::OnResize(float resize_scale)
		{
			// ȡ���ؼ��Ĵ�С
			Size<int> parent_size;
			if (node_parent_)
			{
				parent_size = node_parent_->GetSize();
			}
			else
			{
				parent_size = Size<int>(NativePlatform::Instance().GetScreenWidth(), NativePlatform::Instance().GetScreenHeight());
			}

			relative_coord_.left = parent_size.width * anchor_min_.left + anchor_offset_.left * resize_scale;
			relative_coord_.top = parent_size.height * anchor_min_.top + anchor_offset_.top * resize_scale;
			relative_coord_.width = parent_size.width * anchor_max_.left + anchor_offset_.right * resize_scale - relative_coord_.left;
			relative_coord_.height = parent_size.height * anchor_max_.top + anchor_offset_.bottom * resize_scale - relative_coord_.top;

			// �����ӿؼ���Ҫ���½��ж�λ
			for (auto widget : node_children_)
			{
				widget->OnResize(resize_scale);
			}
		}

		void LayoutNode::OnRender(Point<int> parent_absolute_position)
		{
			// ��Ȼ UI ϵͳ�ڲ�����ʱ�õ����������, ����Ⱦʱ����Ҫ����ɾ�������
			Point<int> absolute_position = parent_absolute_position;
			absolute_position += Point<int>(relative_coord_.left, relative_coord_.top);

			// ��� owned_skin_ Ϊ��, �ͱ�ʾ������ֶ���������������������ߴ�λ�õ�, ����������Ⱦ
			if (owned_skin_)
			{
				owned_skin_->DoRender(Coord<int>(absolute_position.left, absolute_position.top,
					relative_coord_.width, relative_coord_.height));
			}

			for (auto node : node_children_)
			{
				node->OnRender(absolute_position);
			}
		}

		void LayoutNode::SetRelativePosition(Point<int> left_top)
		{
			relative_coord_.left = left_top.left;
			relative_coord_.top = left_top.top;
		}

		void LayoutNode::SetCoord(Rect<int> anchor_offset, Point<float> anchor_min, Point<float> anchor_max)
		{
			anchor_offset_ = anchor_offset;
			anchor_min_ = anchor_min;
			anchor_max_ = anchor_max;
		}

		void LayoutNode::SetSkin(std::shared_ptr<ISkin> skin)
		{
			owned_skin_ = skin;
		}
	}
}