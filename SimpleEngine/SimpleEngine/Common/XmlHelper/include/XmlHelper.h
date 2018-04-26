#pragma once

#ifndef XML_HELPER_H_
#define XML_HELPER_H_

#include <string>
#include <vector>
#include <memory>
#include "rapidxml.hpp"


// Ϊ�˷�ֹ֮������ rapidxml ʱ, һ�� rapidxml �ӿڷ����仯, �������Ŀ������Ҫ������޸ĵ����
// �� rapidxml ����һ����װ
// �ⲿ��Ŀ��Ҫ�õ� rapidxml ʱ, ֻ�������һ��ͷ�ļ�
namespace XmlHelper
{
	enum XMLNodeType
	{
		XNT_Document,      //!< A document node. Name and value are empty.
		XNT_Element,       //!< An element node. Name contains element name. Value contains text of first data node.
		XNT_Data,          //!< A data node. Name is empty. Value contains data text.
		XNT_CData,         //!< A CDATA node. Name is empty. Value contains data text.
		XNT_Comment,       //!< A comment node. Name is empty. Value contains comment text.
		XNT_Declaration,   //!< A declaration node. Name and value are empty. Declaration parameters (version, encoding and standalone) are in node attributes.
		XNT_Doctype,       //!< A DOCTYPE node. Name is empty. Value contains DOCTYPE text.
		XNT_PI             //!< A PI node. Name contains target. Value contains instructions.
	};

	class XMLAttribute
	{
	public:
		XMLAttribute(rapidxml::xml_attribute<char>* attr);
		XMLAttribute(rapidxml::xml_document<char>& doc, char* name, char* value);

		std::string Value() const;

		rapidxml::xml_attribute<char>* GetStoredXmlAttribute();

	private:
		rapidxml::xml_attribute<char>* _attr;
	};

	class XMLNode
	{
	public:
		XMLNode(rapidxml::xml_node<char>* node);	// ��ȡ
		XMLNode(rapidxml::xml_document<char>& doc, XMLNodeType type, char* name);	// д��

		void AppendNode(std::shared_ptr<XMLNode> const & node);
		void AppendAttribute(std::shared_ptr<XMLAttribute> const & attr);

		std::shared_ptr<XMLNode> FirstNode(std::string name) const;
		std::shared_ptr<XMLNode> NextSibling(std::string name) const;

		std::shared_ptr<XMLAttribute> FirstAttribute(std::string name) const;
		
		rapidxml::xml_node<char>* GetStoredXmlNode();

	private:
		rapidxml::xml_node<char>* _node;
		std::string _name;
	};


	class XMLDocument
	{
	public:
		XMLDocument();

		// ����һ�� xml �ļ�
		std::shared_ptr<XMLNode> Parse(const char *filename);

		// ��Ϊһ�� xml �ļ�
		void Save(const char *filename);

		std::shared_ptr<XMLNode> AllocateNode(XMLNodeType type, std::string name);
		std::shared_ptr<XMLAttribute> AllocateAttribute(std::string name, std::string value);

		// һ�� xml �ļ�ֻ��һ�����ڵ�
		void AssignRootNode(std::shared_ptr<XMLNode> const & root_node);

	private:
		std::vector<char> xml_content;
		std::shared_ptr<rapidxml::xml_document<char>> _doc;
		std::shared_ptr<XMLNode> _root;
	};

}

#endif // XML_HELPER_H_
