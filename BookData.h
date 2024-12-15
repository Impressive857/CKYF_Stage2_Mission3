#define _CRT_SECURE_NO_WARNINGS

#ifndef _BOOK_DATA_H_
#define _BOOK_DATA_H_

#include <string>
#include <iostream>
#include <format>

namespace constant {
	constexpr size_t isbnLength = 14;
	constexpr size_t bookTitleLength = 51;
	constexpr size_t authorLength = 51;
	constexpr size_t publisherLength = 51;
	constexpr double saleTax = 0.06;
	constexpr int doubleMaxLength = 16;
	constexpr int intMaxLength = 10;
	constexpr int dateMaxLength = 10;
}

class BookData {
public:
	BookData();
	explicit BookData(const char* isbn, const char* bookTitle, const char* author, const char* publisher, const std::tm& dateAdded, int qtyOnHand, double retail, double wholesale);
	explicit BookData(const char* isbn, const char* bookTitle, const char* author, const char* publisher, int year, int month, int day, int qtyOnHand, double retail, double wholesale);
	BookData(const BookData& other);
	BookData(BookData&& other) noexcept;
	BookData& operator=(const BookData& other);
	BookData& operator=(BookData&& other) noexcept;
	~BookData();
	const char* Isbn() const;
	const char* BookTitle() const;
	const char* Author() const;
	const char* Publisher() const;
	const std::tm& DateAdded() const;
	int QtyOnHand() const;
	double Retail() const;
	double Wholesale() const;
	void SetIsbn(const char* isbn);
	void SetBookTitle(const char* bookTitle);
	void SetAuthor(const char* author);
	void SetPubliser(const char* publisher);
	void SetDateAdded(int year, int month, int day);
	void SetDateAdded(const std::tm& dateAdded);
	void SetQtyOnHand(int qtyOnHand);
	void SetRetail(double retail);
	void SetWholesale(double wholesale);
	std::string GetDateString() const;
	void PrintDate() const;
	void PrintInfo() const;
private:
	char* isbn_;
	char* bookTitle_;
	char* author_;
	char* publisher_;
	std::tm* dateAdded;
	int qtyOnHand_;
	double retail_;
	double wholesale_;
};

#endif //!_BOOK_DATA_H_