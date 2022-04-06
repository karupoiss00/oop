#pragma once
#include <map>
#include <functional>
#include "Body.h"

class CBodyFactory
{
public:
	CBodyFactory();

	void CreateBodies(Bodies& bodies, std::istream& strm);
	void SetPrintIndent(unsigned nestingLevel);
	void SetDelimiters(char openDelimiter, char closeDelimiter);

protected:
	using ActionMap = std::map<std::string, std::function<body_ptr()>>;

	ActionMap m_actionMap;
	unsigned m_nestingLevel;

	char m_openDelimiter;
	char m_closeDelimiter;

	void CreateActionMap(const std::vector<double>& args, std::istream& strm);

	body_ptr CreateSphere(const std::vector<double>& args);
	body_ptr CreateCone(const std::vector<double>& args);
	body_ptr CreateCylinder(const std::vector<double>& args);
	body_ptr CreateParallelepiped(const std::vector<double>& args);
	body_ptr CreateCompound(std::istream& strm);

	std::string GetAction(std::string& line);
	void GetActionArgs(std::vector<double>& args, const std::string& line);
	bool ExecuteAction(Bodies& bodies, const std::string& action, const std::vector<double>& args);

	bool IsOpenDelimiter(const std::string& line);
	bool IsCloseDelimiter(const std::string& line);
};
