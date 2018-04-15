#pragma once

#ifndef __MULTITHREADMGR_H
#define __MULTITHREADMGR_H

#include <vector>
#include <functional>
#include <mutex>

class MultiThreadMgr
{
public:
	static MultiThreadMgr& getInstance()
	{
		// �ֲ���̬����
		// lifetime =>
		// begins the first time the program flow encounters the declaration
		// ends at program termination( main ��������������������� )
		// ��֤���ʵ���ܹ����ų����˳� correctly destroyed
		// ֻ�е�һ�� declare ������ڴ沢��ʼ��( ���ù��캯�� )��֮��ֱ�ӷ����ѳ�ʼ���ľ�̬����
		static MultiThreadMgr instance;
		return instance;
	}

	// ��ʽָʾ�����������ɺ�����Ĭ�ϰ汾
	// deleting the methods we don't want
	MultiThreadMgr(MultiThreadMgr const&) = delete;
	void operator=(MultiThreadMgr const&) = delete;

private:
	// �������º���: ����ͨ�� GetInstance() ����ʵ��
	MultiThreadMgr() {}

public:
	// Queues an action on the main thread
	static void QueueOnMainThread(std::function<void(void)> action);

	// Runs an action on another thread
	static void RunAsyncInDetach(std::function<void(void)> action);

	// Update is called once per frame on the main thread
	void Update();

private:
	// ԭ���ĺ���ָ��̫����ª, std::function ��������ϼ���һ���װ
	std::vector<std::function<void(void)>> _actions;
	std::vector<std::function<void(void)>> runActions;

	std::mutex actionsMutex;
};

#endif // !__MULTITHREADMGR_H