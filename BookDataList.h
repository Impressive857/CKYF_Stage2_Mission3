#ifndef _BOOK_DATA_LIST_H_
#define _BOOK_DATA_LIST_H_

#include "BookData.h"

#include <list>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <utility>
#include <functional>
#include <algorithm>
#include <optional>

class BookDataList
{
public:
	BookDataList() = default;
	BookDataList(std::initializer_list<BookData> initList);
	BookDataList(const BookDataList& other);
	BookDataList(BookDataList&& other) noexcept;
	~BookDataList() = default;
	BookDataList& operator=(const BookDataList& other);
	BookDataList& operator=(BookDataList&& other) noexcept;
	std::optional<std::list<BookData>::iterator> GetBookByBookTitle(const char* bookTitle);
	std::optional<std::list<BookData>::iterator> GetBookByIsbn(const char* isbn);
	void AddBook(BookData&& bookData);
	void AddBook(const char* isbn, const char* bookTitle, const char* author, const char* publisher, const std::tm& dateAdded, int qtyOnHand, double retail, double wholesale);
	void AddBook(const char* isbn, const char* bookTitle, const char* author, const char* publisher, int year, int month, int day, int qtyOnHand, double retail, double wholesale);
	void RemoveBook(std::list<BookData>::iterator it);
	void Clear();
	void ForEach(std::function<void(std::list<BookData>::iterator)> function);
	bool IsEmpty() const;
	bool IsbnIsExist(const char* isbn) const;
	bool BookTitleIsExist(const char* bookTitle) const;
	void Sort(std::function<bool(const BookData&, const BookData&)> method);
	bool ReadFormFile(const char* filename);
	bool SaveToFile(const char* filename);
private:
	std::list<BookData> bookDataList_;
};

#endif //!_BOOK_DATA_LIST_H_