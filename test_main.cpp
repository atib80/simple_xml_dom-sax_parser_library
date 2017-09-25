#include <iostream>
// #include <fstream>
#include <string>
#include <vector>
#include <stl_helper.h>
// #include <stdexcept>

class CustomXMLTagAttribute {

		std::wstring attribute_name_;
		std::wstring attribute_value_;

	public:

		explicit CustomXMLTagAttribute(const std::wstring& attribute_name, const std::wstring& attribute_value) : attribute_name_{attribute_name}, attribute_value_{attribute_value} { }

		inline const std::wstring& get_attribute_name() const noexcept { return this->attribute_name_; }
		
		inline const std::wstring& get_attribute_value() const noexcept { return this->attribute_value_; }

		inline void set_attribute_name(const std::wstring& attribute_name) { this->attribute_name_ = attribute_name; }

		inline void set_attribute_value(const std::wstring& attribute_value) { this->attribute_value_ = attribute_value; }		

	};

using namespace std;

vector<CustomXMLTagAttribute> parseXMLTagAttributes(const wstring& line, wstring& start_tag_name) {

	vector<CustomXMLTagAttribute> attribute_key_value_pairs{};

	// example:
	// <book id="bk103" title="Helpful description" subject="machine/electrotechnical engineering">

	auto start_word = cbegin(line);

	auto end_of_line = cend(line);

	auto end_word = start_word + 1;

	while (!iswspace(*end_word)) ++end_word;

	start_tag_name.assign(start_word, end_word);

	while (start_word < end_of_line) {		

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

int wmain(int argc, wchar_t** argv) {

	unused_args(argc, argv);

	const wstring line{LR"(book id="bk103" title="Helpful description" subject="machine/electrotechnical engineering")"};
	wstring start_tag_name{};

	auto attribute_key_value_pairs = parseXMLTagAttributes(line, start_tag_name);

	if (attribute_key_value_pairs.empty()) {

		wcout << L"attribute_key_value_pairs (vector<>) is empty!" << endl;
		return 1;

	}

	wcout << L"start_tag_name: " << start_tag_name << L"\n\n";

	wcout << L"Attribute name = attribute value pairs:" << L"\n\n";

	for (auto const& kv : attribute_key_value_pairs) {

		wcout << kv.get_attribute_name() << L'=' << kv.get_attribute_value() << L'\n';

	}

	wcout << endl;

	return 0;
}