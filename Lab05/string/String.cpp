#include <cassert>
#include <iostream>
#include "String.h"

using namespace std;

CString::CString()
	: m_length(0), m_chars(new char[1])
{
	SetChars("");
}

CString::CString(const char* chars)
	: m_length(strlen(chars)), m_chars(new char[m_length + 1])
{
	SetChars(chars);
}

CString::CString(const char* chars, size_t length)
	: m_length(length), m_chars(new char[m_length + 1])
{
	SetChars(chars);
}

CString::CString(CString const& other)
	: m_length(other.m_length), m_chars(new char[m_length + 1])
{
	SetChars(other.GetStringData());
}

CString::CString(CString&& other)
{
	m_chars = other.m_chars;
	m_length = other.m_length;

	other.m_chars = nullptr;
	other.m_length = 0;
}

CString::CString(std::string const& stlString)
	: m_length(stlString.size()), m_chars(new char[m_length + 1])
{
	SetChars(stlString.c_str());
}

CString::CString(size_t length)
	: m_length(length), m_chars(new char[m_length + 1])
{
}

CString::~CString()
{
	delete[] m_chars;
}

void CString::Clear()
{
	delete[] m_chars;
	m_chars = nullptr;
	m_length = 0;
}

size_t CString::GetLength() const
{
	return m_length;
}

const char* CString::GetStringData() const
{
	if (m_chars == nullptr)
	{
		return "";
	}

	return m_chars;
}

CString CString::SubString(size_t start, size_t length) const
{
	if (m_chars == nullptr || start >= m_length)
	{
		return CString();
	}

	if ((start + length > m_length) || (length == SIZE_MAX))
	{
		length = m_length - start;
	}

	return CString(&m_chars[start], length);
}

void CString::SetChars(const char* chars)
{
	assert(chars != nullptr);
	assert(m_chars != nullptr);

	if (chars != nullptr)
	{
		memcpy(m_chars, chars, m_length);
		m_chars[m_length] = '\0';
	}
}

CString& CString::operator=(const CString& str)
{
	if (this != &str)
	{
		CString tmp(str);

		std::swap(m_chars, tmp.m_chars);
		std::swap(m_length, tmp.m_length);
	}

	return *this;
}

CString& CString::operator=(CString&& str)
{
	if (this != &str)
	{
		delete[] m_chars;

		m_chars = str.m_chars;
		m_length = str.m_length;

		str.m_chars = nullptr;
		str.m_length = 0;
	}

	return *this;
}

CString CString::operator+(const CString& str) const
{
	if (!str.m_length)
	{
		return CString(*this);
	}

	CString result(m_length + str.m_length);

	memcpy(result.m_chars, GetStringData(), m_length);
	memcpy(result.m_chars + m_length, str.GetStringData(), str.m_length + 1);

	return result;
}

CString& CString::operator+=(const CString& str)
{
	if (str.m_chars != nullptr)
	{
		*this = *this + str;
	}

	return *this;
}

int CString::Compare(const CString& str) const
{
	auto cmpLength = std::min(m_length, str.m_length);
	auto cmp = memcmp(GetStringData(), str.GetStringData(), cmpLength);

	if (!cmp && m_length != str.m_length)
	{
		cmp = m_length < str.m_length ? -1 : 1;
	}

	return cmp;
}

bool CString::operator==(const CString& str) const
{
	return Compare(str) == 0;
}

bool CString::operator!=(const CString& str) const
{
	return Compare(str) != 0;
}

bool CString::operator<(const CString& str) const
{
	return Compare(str) < 0;
}

bool CString::operator<=(const CString& str) const
{
	return Compare(str) <= 0;
}

bool CString::operator>(const CString& str) const
{
	return Compare(str) > 0;
}

bool CString::operator>=(const CString& str) const
{
	return Compare(str) >= 0;
}

const CString operator+(const string& stlString, const CString& str)
{
	return CString(stlString) + str;
}

const CString operator+(const char* chars, const CString& str)
{
	return CString(chars) + str;
}

ostream& operator<<(ostream& strm, CString const& str)
{
	strm << str.GetStringData();

	return strm;
}

istream& operator>>(istream& strm, CString& str)
{
	string tmp;
	strm >> tmp;
	str = tmp;

	return strm;
}