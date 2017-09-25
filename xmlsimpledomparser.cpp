#include "xmlsimpledomparser.h"
#include <iostream>
#include <strsafe.h>
#include <handle.h>
#include <algorithm>

using namespace std;
using namespace std::xml;

XMLSimpleDomParser::XMLSimpleDomParser(wchar_t const* xml_file_path, const int max_mem_usage) : max_mem_usage_ { max_mem_usage } {

	build_version_string();

	auto file = invalid_handle
	{
			CreateFileW(xml_file_path,
					   GENERIC_READ,
					   FILE_SHARE_READ,
					   nullptr,
					   OPEN_EXISTING,
					   FILE_ATTRIBUTE_NORMAL,
					   nullptr)
	};

	if (!file) return;

	auto map = null_handle
	{
			CreateFileMapping(file.get(), nullptr, PAGE_READONLY, 0, 0, nullptr)
	};

	if (!map) return;

	auto size = LARGE_INTEGER{}; // union

	if (!GetFileSizeEx(file.get(), &size)) return;

	file_begin_ = static_cast<char const*>(MapViewOfFile(map.get(), FILE_MAP_READ, 0, 0, 0));

	if (!file_begin_) return;

	file_end_ = file_begin_ + size.QuadPart;

	file_size_ = static_cast<long>(size.QuadPart);	

	file_unmapped_ = false;

}

XMLSimpleDomParser::XMLSimpleDomParser(XMLSimpleDomParser&& other) noexcept : max_mem_usage_{other.max_mem_usage_}, data_{std::move(other.data_)}, 
file_begin_{other.file_begin_}, file_end_{other.file_end_}, file_size_{other.file_size_}, file_unmapped_{other.file_unmapped_}
{
	other.file_begin_ = nullptr;
	other.file_end_ = nullptr;
}

// move assignment operator
XMLSimpleDomParser& XMLSimpleDomParser::operator=(XMLSimpleDomParser&& other) noexcept
{
	if (this != &other)			
	{
		const_cast<int&>(max_mem_usage_) = other.max_mem_usage_;
		data_ = std::move(other.data_);
		unmap_mapped_file();

		file_begin_ = other.file_begin_;
		file_end_ = other.file_end_;

		file_size_ = other.file_size_;
		file_unmapped_ = other.file_unmapped_;

		other.file_begin_ = nullptr;
		other.file_end_ = nullptr;

	}

	return *this;
}

XMLSimpleDomParser::~XMLSimpleDomParser() {

	unmap_mapped_file();

}

void XMLSimpleDomParser::build_version_string() {

	StringCchPrintfW(version_string_, 256, L"%d.%d", major_version_, minor_version_);

}

void XMLSimpleDomParser::unmap_mapped_file() noexcept {

	if (file_begin_ && !file_unmapped_)
	{
		VERIFY(UnmapViewOfFile(file_begin_));
		
		file_unmapped_ = true;
	}

}

vector<CustomXMLTag> XMLSimpleDomParser::getXMLElementByTagName(const wstring& tag_name, const int number_of_elements_to_return) const
{
	vector<CustomXMLTag> xml_elements{};



	return xml_elements;
}

vector<CustomXMLTag> XMLSimpleDomParser::getChildrenOfXMLElement(const wstring& tag_name, const int number_of_children_elements_to_return) const
{
	vector<CustomXMLTag> xml_children_elements{};



	
	return xml_children_elements;
}

bool XMLSimpleDomParser::processXMLDocument() {

	auto xml_string_buffer = wstring{file_begin_, file_end_};

	removeNewLineCharactersFromXMLDocument(xml_string_buffer);

	auto xml_data_buffer_ = wistringstream(xml_string_buffer);

	wstring line{}, start_tag{}, end_tag{}, xml_tag_data;

	size_t found_start_pos{}, found_end_pos{};

	getline(xml_data_buffer_, line);

	while (!(xml_data_buffer_.eof()))
	{
		
		if ((found_start_pos = line.find(L"<")) != wstring::npos)

		


	}

	const wchar_t* start_pos = reinterpret_cast<const wchar_t*>(file_begin_);
	const wchar_t* end_pos = reinterpret_cast<const wchar_t*>(file_end_);

	
	// auto tag_end{start_pos};

	const wchar_t* current_pos{ start_pos };

	while (current_pos < end_pos) {

			while (*current_pos != L'\n') ++current_pos;

			wstring line_of_xml_data(start_pos, current_pos);

			line_of_xml_data = trim(line_of_xml_data);

			auto xml_tag_attributes = parseXMLTagAttributes(line_of_xml_data, start_tag);

			start_pos = ++current_pos;

			const wchar_t * tag_start = ++current_pos;

			while (*current_pos != L'>') ++current_pos;

			start_tag.assign(tag_start, current_pos);

			start_tag = trim(start_tag);

			// auto start_tag_found = true;

			// auto xml_tag_attributes = parseXMLTagAttributes(start_tag);

			current_pos++;

			while ((*current_pos != L'<') && (*(current_pos + 1) != L'/')) ++current_pos;

			// while (*end_line != L'\n') end_line++;

			// auto line = wstring(start_line, end_line);

			// line = trim(line);

			/*if (start_tag.empty()) {

				auto start_itr = begin(line);

				while (*start_itr != L'<') ++start_itr;

			}*/

	}

	return true;

}

bool XMLSimpleDomParser::parseLine(const std::wstring& start_tag, std::wstring& line_data) {


	return true;
}

vector<CustomXMLTagAttribute> XMLSimpleDomParser::parseXMLTagAttributes(const wstring& line, wstring& start_tag_name) {

	vector<CustomXMLTagAttribute> attribute_key_value_pairs{};

	auto start_tag_name_found{ false };

	// example:
	// <book id="bk103" title="Helpful description" subject="machine/electrotechnical engineering">

	auto start_word{ cbegin(line) };

	auto end_word{ start_word };

	auto end_of_line = cend(line);

	while ((end_word < end_of_line) && (*end_word != L'<')) ++end_word;

	if (*end_word == L'<') start_tag_name_found = true;

	if ((end_word < (end_of_line - 3)) && (*(end_word + 1) == L'!') && (*(end_word + 2) == L'-') && (*(end_word + 3) == L'-'))
	{
		end_word += 4;

		while ((end_word < (end_of_line - 2)) && (*end_word != L'-') && (*(end_word + 1) != L'-') && ((*end_word + 2) != L'>')) ++end_word;

		end_word += 3;

		while ((end_word < end_of_line) && (*end_word != L'<')) ++end_word;

		if (*end_word == L'<') start_tag_name_found = true;
	}

	if (!start_tag_name_found) return attribute_key_value_pairs;

	while ((end_word < end_of_line) && !iswspace(*end_word)) ++end_word;

	if (end_word == end_of_line) return attribute_key_value_pairs;

	start_tag_name.assign(start_word, end_word);

	// start_word = end_word;

	while (end_word < end_of_line) {		

		start_word = end_word;

		while (iswspace(*start_word)) ++start_word;

		end_word = start_word;

		while (!iswspace(*end_word) && (*end_word != L'=')) ++end_word;

		wstring tag_name(start_word, end_word);

		start_word = ++end_word;

		while (iswspace(*start_word) || (*start_word == L'"')) ++start_word;

		end_word = start_word;

		while (*end_word != L'"') ++end_word;

		wstring tag_value(start_word, end_word);		

		attribute_key_value_pairs.emplace_back(tag_name, tag_value);

		start_word = ++end_word;
	}

	return attribute_key_value_pairs;
}

void XMLSimpleDomParser::processXMLDocumentLineProperties()
{
	xml_data_buffer_.seekg(0);
	//////////////////////////////////////////////////////////////////////////
	// TODO: Complete implementation of this member function


	

}

void XMLSimpleDomParser::processXMLDocumentCommentLines(bool is_remove_comments_from_xml_text)
{
	size_t start{}, end{};
	// bool found;

	while (true)
	{
		if ((start = xml_document_buffer_.find(L"<!--"), start) == wstring::npos) break;
		else {		

			if ((end = xml_document_buffer_.find(L"-->"), start + 4) == wstring::npos) break;

			else {

				end += 3;

				if (is_remove_comments_from_xml_text)
				{
						
				}

				// found = true;
			}
		}

	}


	return xml_comments;
}

void XMLSimpleDomParser::removeNewLineCharactersFromXMLDocument(wstring& xml_data_line)
{
	
	auto new_end_itr = remove(begin(xml_data_line), end(xml_data_line), L'\r');
	new_end_itr = remove(begin(xml_data_line), new_end_itr, L'\n');
	xml_data_line.assign(begin(xml_data_line), new_end_itr);

	/*
	auto current = begin(xml_data_line);
	auto end_pos = end(xml_data_line);

	while (current != end_pos)
	{
		if (*current == L'\r') xml_data_line.erase(current);
		else if (*current == L'\n') xml_data_line.erase(current);		
		end_pos = end(xml_data_line);
		++current;	

	}*/
}


wstring XMLSimpleDomParser::trim(const wstring& str) { 

	int begin = 0;
	int end = str.size() - 1;
	if (end < 0) return L"";
	// iswspace() -> true [L' ', L'\t', L'\n', L'\r', L'\f' L'\v'
	for (; ((begin <= end) && iswspace(str[begin])); ++begin) continue;
	if (begin > end) return L"";
	for (; ((end > begin) && iswspace(str[end])); --end) continue;
	return str.substr(begin, end - begin + 1);
}

