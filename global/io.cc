#include "io.hh"

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

char Flaner::Global::IO::InputStream::read()
{
	char c = *begin;
	++begin;
	
	return c;
}

std::vector<char> Flaner::Global::IO::InputStream::readNBytes(long long n)
{
	std::vector<char> bts;

	for (long long i = 0; i < n; i += 1)
	{
		bts.push_back(this->read());
	}

	return bts;
}

std::vector<char> Flaner::Global::IO::InputStream::readAllBytes()
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
