#pragma once

#ifndef XML_HELPER_H_
#define XML_HELPER_H_

#include <string>
#include <vector>
#include "rapidxml.hpp"


// �� rapidxml ����һ����װ
namespace XmlHelper
{
	class XMLNode
	{
	public:
		XMLNode(rapidxml::xml_node<char>* node);
		~XMLNode();

	private:

	};


	class XMLDocument
	{
	public:
		XMLDocument();
		~XMLDocument();

		// ����һ�� xml �ļ�
		XMLNode Parse(const char *filename);

		// ��Ϊһ�� xml �ļ�
		void Save(const char *filename);

	private:
		std::vector<char> xml_content;
		rapidxml::xml_document<char> doc;
		XMLNode root;
	};

}

#endif // XML_HELPER_H_
