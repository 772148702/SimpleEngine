#include <GUI/ExampleLayout.h>
#include <GUI/Image.h>
#include <GUI/Widget.h>

namespace SimpleEngine
{
	namespace UI
	{
		ExampleLayout::ExampleLayout(float scale_weight) :
			BaseLayout(scale_weight)
		{
			LayoutNode *widget_a = new LayoutNode();
			RegisterRootNode(widget_a);
			std::shared_ptr<Image> image_a = std::make_shared<Image>(L"./media/Textures/4.jpg");
			widget_a->SetSkin(image_a);
			// �� widget_a ������ʲô�ֱ����¶�����ȫ��
			widget_a->SetCoord(Rect<int>(0, 0, 0, 0), Point<float>(0, 0), Point<float>(1.0f, 1.0f));

			LayoutNode *widget_c = new LayoutNode(widget_a);
			std::shared_ptr<Image> image_c = std::make_shared<Image>(L"./media/Textures/2.jpg");
			widget_c->SetSkin(image_c);
			// �� widget_c ʼ�տ��ڴ������½�, ���Сһֱ���Ŵ��ڵȱ�����
			widget_c->SetCoord(Rect<int>(-718, -1000, 0, 0), Point<float>(1.0f, 1.0f), Point<float>(1.0f, 1.0f));
		}
	}
}