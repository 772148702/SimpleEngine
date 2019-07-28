#include <GUI/BaseLayout.h>
#include <GUI/LayoutNode.h>
#include <GUI/GUIManager.h>

namespace SimpleEngine
{
	namespace UI
	{
		BaseLayout::BaseLayout(float scale_weight) :
			scale_weight_(scale_weight)
		{
		}

		BaseLayout::~BaseLayout()
		{
			if (root_node_)
			{
				delete root_node_;
				root_node_ = nullptr;
			}
		}

		// ����ؼ����ű��� = ʵ����Ļ�����ű� * (1-scale_weight_) + ʵ����Ļ�����ű� * scale_weight_
		// scale_weight_ == 0 ʱ��ʾ��ȫ�Կ��Ϊ��׼��������,
		// scale_weight_ == 1 ʱ��ʾ��ȫ�Ը߶�Ϊ��׼��������
		float BaseLayout::GetResizeScale()
		{
			return GUIManager::Instance().GetWidthResizeScale() * (1 - scale_weight_) +
				GUIManager::Instance().GetHeightResizeScale() * scale_weight_;
		}

		void BaseLayout::RegisterRootNode(LayoutNode *node)
		{
			root_node_ = node;
		}

		// ע�ᵽ GUIManager ��ʱ�����һ�γ�ʼ��
		void BaseLayout::OnRegister()
		{
			OnResize();
		}

		void BaseLayout::OnResize()
		{
			root_node_->OnResize(GetResizeScale());
		}

		void BaseLayout::OnRender()
		{
			root_node_->OnRender();
		}
	}
}