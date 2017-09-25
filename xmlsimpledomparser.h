#ifndef __XMLSIMPLEDOMPARSER__
#define __XMLSIMPLEDOMPARSER__

// #include <string>
#include <sstream>
#include <vector>
// #include <map>
#include <unordered_map>
#include <windows.h>
// #include <debug.h>
// #include <utility>
// #include <memory>

#define XMLSIMPLEDOMPARSER_MAJOR_VERSION 1
#define XMLSIMPLEDOMPARSER_MINOR_VERSION 0
#define XMLSIMPLEDOMPARSER_VERSION_STR "1.0"

namespace std {

	namespace xml {

		using XMLSimpleDomData = std::unordered_map<std::wstring, std::wstring>;

		class XMLDocumentLineProperties
		{		
			public:
				explicit XMLDocumentLineProperties(const std::wstring& xml_line, size_t const line_number, size_t const start_index, size_t const end_index) :
					xml_line_{ xml_line }, line_number_{}, start_index_{ start_index }, end_index_{ end_index } { }

				const std::wstring& get_xml_line() const noexcept { return xml_line_; }
				size_t get_line_number() const noexcept { return line_number_; }
				size_t get_line_start_index() const noexcept { return start_index_; }
				size_t get_line_end_index() const noexcept { return end_index_;  }

				void set_xml_line(const std::wstring& xml_line) { xml_line_ = xml_line; }
				void set_line_number(size_t const line_number) noexcept { line_number_ = line_number; }
				void set_line_start_index(size_t const start_index) noexcept { start_index_ = start_index; }
				void set_line_end_index(size_t const end_index) noexcept { end_index_ = end_index; }

			private:
				std::wstring xml_line_;
				size_t line_number_;
				size_t start_index_;
				size_t end_index_;
		};

		class XMLCommentLineProperties
		{
		public:
			explicit XMLCommentLineProperties(const std::wstring& comment, size_t const start_line_number, size_t const end_line_number, 
				size_t const start_line_index, size_t const end_line_index) : comment_{comment},
				start_line_number_{ start_line_number }, end_line_number_{ end_line_number }, 
				start_line_index_{ start_line_index }, end_line_index_{ end_line_index } { }

			const std::wstring& get_comment() const noexcept { return comment_; }			
			size_t get_start_line_number() const noexcept { return start_line_number_; }
			size_t get_end_line_number() const noexcept { return end_line_number_; }
			size_t get_start_line_index() const noexcept { return start_line_index_; }
			size_t get_end_line_index() const noexcept { return end_line_index_; }			

			void set_comment_text(const std::wstring& comment) { comment_ = comment; }
			void set_start_line_number(size_t const start_line_number) noexcept { start_line_number_ = start_line_number; }
			void set_end_line_number(size_t const end_line_number) noexcept { end_line_number_ = end_line_number; }
			void set_start_line_index(size_t const start_line_index) noexcept { start_line_index_ = start_line_index; }
			void set_end_line_index(size_t const end_line_index) noexcept { end_line_index_ = end_line_index; }

		private:
			wstring comment_;
			size_t start_line_number_;
			size_t end_line_number_;
			size_t start_line_index_;
			size_t end_line_index_;
		};

		class CustomXMLTagAttribute {

			std::wstring attribute_name_;
			std::wstring attribute_value_;

		public:

			explicit CustomXMLTagAttribute(const std::wstring& attribute_name, const std::wstring& attribute_value) : attribute_name_{ attribute_name }, attribute_value_{ attribute_value } { }

			inline const std::wstring& get_attribute_name() const noexcept { return this->attribute_name_; }

			inline const std::wstring& get_attribute_value() const noexcept { return this->attribute_value_; }

			inline void set_attribute_name(const std::wstring& attribute_name) { this->attribute_name_ = attribute_name; }

			inline void set_attribute_value(const std::wstring& attribute_value) { this->attribute_value_ = attribute_value; }

		};

		class XMLHeaderInformation {

			std::wstring xml_header_tag_name_;
			std::vector<CustomXMLTagAttribute> xml_header_tag_properties_;
			bool is_xml_document_valid_;

		public:

			XMLHeaderInformation() : is_xml_document_valid_{ true } {}

			explicit XMLHeaderInformation(const std::wstring& xml_header_tag_name, const std::vector<CustomXMLTagAttribute>& xml_header_tag_properties, bool is_xml_document_valid) :
				xml_header_tag_name_{ xml_header_tag_name }, xml_header_tag_properties_{ xml_header_tag_properties }, is_xml_document_valid_{ is_xml_document_valid } { }

			inline const std::wstring& get_xml_header_tag_name() const noexcept { return this->xml_header_tag_name_; }
			inline const std::vector<CustomXMLTagAttribute>& get_xml_header_tag_properties() const noexcept { return this->xml_header_tag_properties_; }
			inline bool get_is_xml_document_valid() const noexcept { return this->is_xml_document_valid_; }

			inline void set_xml_header_tag_name(std::wstring&& xml_header_tag_name) noexcept { this->xml_header_tag_name_ = std::move(xml_header_tag_name); }
			inline void set_xml_header_tag_properties(std::vector<CustomXMLTagAttribute>&& xml_header_tag_properties) noexcept {
				this->xml_header_tag_properties_ = std::move(xml_header_tag_properties);
			}
			inline void set_is_xml_document_valid(const bool is_xml_document_valid) noexcept { this->is_xml_document_valid_ = is_xml_document_valid; }

		};

		class CustomXMLTag {

			std::wstring element_name_;

			std::vector<CustomXMLTagAttribute> element_attributes_;

			std::vector<CustomXMLTag> element_children_;

		public:

			CustomXMLTag() = default;

			explicit CustomXMLTag(const std::wstring& element_name, const std::vector<CustomXMLTagAttribute>& element_attributes, const std::vector<CustomXMLTag> &element_children = std::vector<CustomXMLTag>{}) :
				element_name_{ element_name }, element_attributes_{ element_attributes }, element_children_{ element_children } { }

			inline const std::wstring& get_element_name() const noexcept { return this->element_name_; }

			inline const std::vector<CustomXMLTagAttribute>& get_element_attributes() const noexcept { return this->element_attributes_; }

			inline const std::vector<CustomXMLTag>& get_element_children() const noexcept { return this->element_children_; }

			inline void set_element_name(const std::wstring& element_name) noexcept { this->element_name_ = element_name; }

			inline void set_element_attributes(const std::vector<CustomXMLTagAttribute>& element_attributes) noexcept { this->element_attributes_ = element_attributes; }

			inline void set_element_children(const std::vector<CustomXMLTag>& element_children) noexcept { this->element_children_ = element_children; }

		};

		class XMLSimpleDomParser {

		public:
			XMLSimpleDomParser(wchar_t const* xml_file_path, const int max_mem_usage = -1);
			~XMLSimpleDomParser();

			XMLSimpleDomParser(XMLSimpleDomParser const&) = delete; // disable copy construction for new XMLSimpleDomParser objects
			XMLSimpleDomParser& operator=(XMLSimpleDomParser const&) = delete; // disable copy assigment operator

			// move constructor
			XMLSimpleDomParser(XMLSimpleDomParser&& other) noexcept;

			// move assignment operator
			XMLSimpleDomParser& operator=(XMLSimpleDomParser&& other) noexcept;

			inline const char* get_file_begin_position() const noexcept {

				return file_begin_;

			}

			inline const char* get_file_end_position() const noexcept {

				return file_end_;

			}

			inline explicit operator bool() const noexcept
			{
				return file_begin_ != nullptr;
			}

			inline auto get_file_size() const noexcept -> long
			{
				return file_size_;
			}

			std::vector<CustomXMLTag> getXMLElementByTagName(const std::wstring& tag_name, const int number_of_elements_to_return = -1) const;
			std::vector<CustomXMLTag> getChildrenOfXMLElement(const std::wstring& tag_name, const int number_of_children_elements_to_return = -1) const;

			bool processXMLDocument();

			static bool parseLine(const std::wstring& start_tag, std::wstring& line_data);

			static std::vector<CustomXMLTagAttribute> parseXMLTagAttributes(const std::wstring& line, std::wstring& start_tag_name);

			void processXMLDocumentLineProperties();

			void processXMLDocumentCommentLines(bool is_remove_comments_from_xml_text = true);

			static void removeNewLineCharactersFromXMLDocument(std::wstring& xml_data_line);

			static std::wstring trim(const std::wstring& str);

			static const wchar_t* get_version_string() { return version_string_; };
			static const size_t get_major_version_() { return major_version_; }
			static const size_t get_minor_version() { return minor_version_; }

		private:

			static void build_version_string();

			void unmap_mapped_file() noexcept;

			const int max_mem_usage_;			
			const char* file_begin_;
			const char* file_end_;
			std::wistringstream xml_data_buffer_;
			std::wstring xml_document_buffer_;
			std::wstring xml_document_buffer_without_new_lines_;
			long file_size_{};
			bool file_unmapped_{};
			CustomXMLTag data_;
			vector<XMLDocumentLineProperties> xml_document_lines;
			vector<XMLCommentLineProperties> xml_document_comments;
			

			static wchar_t version_string_[256];
			static const int major_version_ = XMLSIMPLEDOMPARSER_MAJOR_VERSION;
			static const int minor_version_ = XMLSIMPLEDOMPARSER_MINOR_VERSION;

		};

		wchar_t XMLSimpleDomParser::version_string_[256];
		const int XMLSimpleDomParser::major_version_;
		const int XMLSimpleDomParser::minor_version_;

	}

}

#endif