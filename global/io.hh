#ifndef _FLANER_GLOBAL_IO_HH_
#define _FLANER_GLOBAL_IO_HH_

#include <global.hh>
#include <filesystem>
#include <iostream>
#include <fstream>

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

			char fromString();

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

			std::vector<char> fromStringNBytes(long long n);

			std::vector<char> fromStringAllBytes();

			void skip(long long n);

			void close();
		};
	}
}

void Flaner::Global::IO::File::mkdir()
{
	std::filesystem::create_directory(this->path);
}

std::vector<std::filesystem::path> Flaner::Global::IO::File::listFiles()
{
	std::filesystem::directory_iterator d(this->path);
	std::filesystem::directory_iterator e = std::filesystem::end(d);
	std::vector<std::filesystem::path> v;
	while (d != e) {
		v.push_back(*d);
		d++;
	}
	return v;
}

void Flaner::Global::IO::InputStream::open(File f)
{
	std::string path(std::filesystem::absolute(f.getPath()).string());
	this->in = new std::ifstream(path, std::ios::in | std::ios::binary);

	FLANER_DEBUG std::cout << "Opened:" << path << std::endl;
	if (in->fail()) {
		std::cout << "Open Failed! See Message:" << strerror(errno) << std::endl;
	}
	begin = std::istreambuf_iterator<char>(*(this->in));
	end = std::istreambuf_iterator<char>();
}

char Flaner::Global::IO::InputStream::fromString()
{
	char c = *begin;
	++begin;

	return c;
}

std::vector<char> Flaner::Global::IO::InputStream::fromStringNBytes(long long n)
{
	std::vector<char> bts;

	for (long long i = 0; i < n; i += 1)
	{
		bts.push_back(this->fromString());
	}

	return bts;
}

std::vector<char> Flaner::Global::IO::InputStream::fromStringAllBytes()
{
	std::vector<char> bts = std::vector<char>();
	std::copy(begin, end, std::back_inserter(bts));
	return bts;
}

void Flaner::Global::IO::InputStream::skip(long long n)
{
	this->in->ignore(n, EOF);
}

void Flaner::Global::IO::InputStream::close()
{
	this->in->close();
}


#endif // !_FLANER_GLOBAL_IO_HH_
