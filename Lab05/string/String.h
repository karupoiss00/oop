#pragma once
#include <string>

class CString
{
public:
	CString();

	CString(const char* pString);
	CString(const char* pString, size_t length);
	CString(CString const& other);
	CString(CString&& other) noexcept;
	CString(std::string const& stlString);

	~CString();

	size_t GetLength() const;
	const char* GetStringData() const;
	CString SubString(size_t start, size_t length = SIZE_MAX) const;
	void Clear();

	CString& operator=(const CString& str);
	CString& operator=(CString&& str) noexcept;

	CString operator+(const CString& str) const;
	CString& operator+=(const CString& str);

	bool operator==(const CString& str) const;
	bool operator!=(const CString& str) const;

	bool operator<(const CString& str) const;
	bool operator>(const CString& str) const;
	bool operator<=(const CString& str) const;
	bool operator>=(const CString& str) const;
private:
	explicit CString(size_t length);

	int Compare(const CString& str) const;

	size_t m_length;
	char* m_chars;
};

const CString operator+(const std::string& stlString, const CString& str);
const CString operator+(const char* chars, const CString& str);

std::ostream& operator<<(std::ostream& strm, CString const& str);
std::istream& operator>>(std::istream& strm, CString& str);