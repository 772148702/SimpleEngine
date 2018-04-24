#include <fstream>
#include "XmlHelper.h"
#include "rapidxml_print.hpp"

using namespace XmlHelper;

XMLNode XMLDocument::Parse(const char *filename)
{
	std::ifstream inputfile;
	inputfile.open(filename);

	// ��ȡ�ļ�����
	inputfile.seekg(0, std::ios_base::end);
	int fileLength = inputfile.tellg();

	// ��������
	inputfile.seekg(0, std::ios_base::beg);
	xml_content.resize(fileLength + 1, 0);	// rapidxml Ҫ���������һ�� zero-terminated string
	inputfile.read(&xml_content[0], fileLength);

	inputfile.close();

	// xml ����
	doc.parse<0>(&xml_content[0]);
	root = XMLNode(doc.first_node());

	return root;
}

void XMLDocument::Save(const char *filename)
{
	std::ofstream outputfile;
	outputfile.open(filename);

	// ���� xml string �������
	outputfile << doc;

	outputfile.close();
}