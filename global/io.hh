#ifndef _FLANER_GLOBAL_IO_HH_
#define _FLANER_GLOBAL_IO_HH_

#include <global/global.hh>
#include <filesystem>

namespace Flaner::Global
{
	namespace IO
	{
		/*
		* A base class to operate files.
		*/

		class File {
			std::filesystem::path path;
		public:

			File(std::string str) {
				this->path = str;
			}

			File(std::string str, std::string child) {
				this->path = str;
				this->path += child;
			}

			std::filesystem::path getPath() {
				return this->path;
			}

			void mkdir();

			std::vector<std::filesystem::path> listFiles();
			
		};

		class InputStream {
			std::ifstream *in;
			std::istreambuf_iterator<char> begin;
			std::istreambuf_iterator<char> end;
		public:

			InputStream(File f) {
				this->open(f);
			}

			InputStream(std::string f) {
				this->open(f);
			}

			void open(std::string f) {
				this->open(File(f));
			}

			void open(File f);

			char read();

			std::istreambuf_iterator<char> getBegin() const {
				return begin;
			}

			void setBegin(std::istreambuf_iterator<char> begin) {
				this->begin = begin;
			}

			std::istreambuf_iterator<char> getEnd() const {
				return end;
			}

			void setEnd(std::istreambuf_iterator<char> end) {
				this->end = end;
			}

			std::ifstream *getIn() const {
				return this->in;
			}

			void setIn(std::ifstream *in) {
				this->in = in;
			}

			std::vector<char> readNBytes(long long n);

			std::vector<char> readAllBytes();

			void skip(long long n);

			void close();
		};
	}
}

#endif // !_FLANER_GLOBAL_IO_HH_
