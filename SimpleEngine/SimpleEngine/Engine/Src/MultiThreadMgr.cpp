#include "MultiThreadMgr.h"

void MultiThreadMgr::QueueOnMainThread(std::function<void(void)> action)
{
	// lock_guard ʵ������ʱ�᳢�Գ��� mutex( ���ʻ��ǵ��� mutex::lock )
	// lock_guard ʵ������ʱ�Զ��ͷ� mutex( mutex::unlock )
	// �˴� lg Ϊջ���󣬻��ں�������ʱ�Զ�����
	// lock_guard ��ʵ��˼��: RAII => ����Ĺ��캯�������Դ�Ļ�ȡ, �������������Դ���ͷ�
	// C++ Runtime ��֤������ջ��������������ڽ���ʱ��������������( ��ʹ�����׳��쳣 )
	// RAII ��֤�˺�����ʹ�׳��쳣, ��ԴҲ�������ͷ� =>
	// �������Դ�ͷŵ�����һ�������ں������, һ���׳��쳣, �߲������һ��, ��Դ�ͱ�������
	// ������Ҫд try-finally
	std::lock_guard<std::mutex> lg(getInstance().actionsMutex);

	getInstance()._actions.push_back(action);
}

void MultiThreadMgr::RunAsyncInDetach(std::function<void(void)> action)
{
	// std::thread ��Ϊһ����, ������д��Ӧ���� std::thread t(action)
	// ������д���������������һ����������( ��������Ϊ std::thread �ĺ��� )
	// ���Ը��ô�����
	// �̺߳���֮�����߳� = main() ����֮�����߳�
	std::thread t{ action };
	t.detach();
}

void MultiThreadMgr::Update()
{
	std::lock_guard<std::mutex> lg(actionsMutex);

	for (size_t i = 0; i < _actions.size(); i++)
	{
		_actions[i]();
	}
	_actions.clear();
}