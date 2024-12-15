#include "BookDataList.h"

BookDataList::BookDataList(std::initializer_list<BookData> initList)
{
	this->bookDataList_.insert(this->bookDataList_.begin(), initList.begin(), initList.end());
}

BookDataList::BookDataList(const BookDataList& other)
{
	this->bookDataList_.insert(this->bookDataList_.begin(), other.bookDataList_.begin(), other.bookDataList_.end());
}

BookDataList::BookDataList(BookDataList&& other) noexcept
{
	this->bookDataList_ = std::move(other.bookDataList_);
}

BookDataList& BookDataList::operator=(const BookDataList& other)
{
	this->bookDataList_.resize(other.bookDataList_.size());
	std::copy(other.bookDataList_.begin(), other.bookDataList_.end(), this->bookDataList_.begin());
	return *this;
}

BookDataList& BookDataList::operator=(BookDataList&& other) noexcept
{
	if (this != &other) {
		this->bookDataList_ = std::move(other.bookDataList_);
	}
	return *this;
}

std::optional<std::list<BookData>::iterator> BookDataList::GetBookByBookTitle(const char* bookTitle)
{
	for (auto it = bookDataList_.begin(); it != bookDataList_.end(); ++it) {
		if (!strncmp(bookTitle, it->BookTitle(), constant::bookTitleLength - 1)) {
			return it;
		}
	}
	return std::nullopt;
}

std::optional<std::list<BookData>::iterator> BookDataList::GetBookByIsbn(const char* isbn)
{
	for (auto it = bookDataList_.begin(); it != bookDataList_.end(); ++it) {
		if (!strncmp(isbn, it->Isbn(), constant::isbnLength - 1)) {
			return it;
		}
	}
	return std::nullopt;
}

void BookDataList::AddBook(BookData&& bookData)
{
	bookDataList_.push_back(std::move(bookData));
}

void BookDataList::AddBook(const char* isbn, const char* bookTitle, const char* author, const char* publisher, const std::tm& dateAdded, int qtyOnHand, double retail, double wholesale)
{
	bookDataList_.emplace_back(isbn, bookTitle, author, publisher, dateAdded, qtyOnHand, retail, wholesale);
}

void BookDataList::AddBook(const char* isbn, const char* bookTitle, const char* author, const char* publisher, int year, int month, int day, int qtyOnHand, double retail, double wholesale)
{
	bookDataList_.emplace_back(isbn, bookTitle, author, publisher, year, month, day, qtyOnHand, retail, wholesale);
}

void BookDataList::RemoveBook(std::list<BookData>::iterator it)
{
	bookDataList_.erase(it);
}

void BookDataList::Clear()
{
	bookDataList_.clear();
}

void BookDataList::ForEach(std::function<void(std::list<BookData>::iterator)> function)
{
	for (auto it = bookDataList_.begin(); it != bookDataList_.end(); ++it) {
		function(it);
	}
}

bool BookDataList::IsEmpty() const
{
	return bookDataList_.begin() == bookDataList_.end();
}

bool BookDataList::IsbnIsExist(const char* isbn) const
{
	for (auto it = bookDataList_.begin(); it != bookDataList_.end(); ++it) {
		if (!strncmp(isbn, it->Isbn(), constant::isbnLength - 1)) {
			return true;
		}
	}
	return false;
}

bool BookDataList::BookTitleIsExist(const char* bookTitle) const
{
	for (auto it = bookDataList_.begin(); it != bookDataList_.end(); ++it) {
		if (!strncmp(bookTitle, it->BookTitle(), constant::bookTitleLength - 1)) {
			return true;
		}
	}
	return false;
}

void BookDataList::Sort(std::function<bool(const BookData&, const BookData&)> method)
{
	this->bookDataList_.sort(method);
}

bool BookDataList::ReadFormFile(const char* filename)
{
	std::ifstream infile(filename);
	if (!infile.is_open()) {
		std::cerr << filename << "：此文件打开失败！\n";
		system("pause");
		return false;
	}
	std::string line;
	std::getline(infile, line);//去掉表头
	std::string item;
	std::istringstream iss;
	char delimiter;
	int year, month, day;
	while (std::getline(infile, line)) {
		BookData newBookData;
		iss.clear();
		iss.str(line);
		iss >> item;
		newBookData.SetIsbn(item.c_str());
		iss >> item;
		newBookData.SetBookTitle(item.c_str());
		iss >> item;
		newBookData.SetAuthor(item.c_str());
		iss >> item;
		newBookData.SetPubliser(item.c_str());
		iss >> year >> delimiter >> month >> delimiter >> day;
		newBookData.SetDateAdded(year, month, day);
		iss >> item;
		newBookData.SetQtyOnHand(std::atoi(item.c_str()));
		iss >> item;
		newBookData.SetRetail(std::atoi(item.c_str()));
		iss >> item;
		newBookData.SetWholesale(std::atoi(item.c_str()));
		bookDataList_.push_back(std::move(newBookData));
	}
	infile.close();
	return true;
}

bool BookDataList::SaveToFile(const char* filename)
{
	std::ofstream outfile(filename, std::ios::trunc);
	if (!outfile.is_open()) {
		std::cerr << filename << "：此文件打开失败！\n";
		system("pause");
		return false;
	}
	outfile << "ISBN号\t书名\t作者\t出版社\t进书日期\t库存量\t零售价\t批发价\n";
	for (auto it = bookDataList_.begin(); it != bookDataList_.end(); ++it) {
		outfile
			<< it->Isbn() << '\t'
			<< it->BookTitle() << '\t'
			<< it->Author() << '\t'
			<< it->Publisher() << '\t'
			<< it->GetDateString() << '\t'
			<< it->QtyOnHand() << '\t'
			<< it->Retail() << '\t'
			<< it->Wholesale() << '\n';
	}
	outfile.close();
	return true;
}