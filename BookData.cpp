#include "BookData.h"

BookData::BookData()
    :qtyOnHand_(0),retail_(0.0),wholesale_(0.0)
{
    this->isbn_ = new char[constant::isbnLength];
    this->isbn_[0] = '\0';

    this->bookTitle_ = new char[constant::bookTitleLength];
    this->bookTitle_[0] = '\0';

    this->author_ = new char[constant::authorLength];
    this->author_[0] = '\0';

    this->publisher_ = new char[constant::publisherLength];
    this->publisher_[0] = '\0';

    this->dateAdded = new std::tm;
}

BookData::BookData(const char* isbn, const char* bookTitle, const char* author, const char* publisher, const std::tm& dateAdded, int qtyOnHand, double retail, double wholesale)
{
    this->isbn_ = new char[constant::isbnLength];
    strncpy(this->isbn_, isbn, constant::isbnLength - 1);
    this->isbn_[constant::isbnLength - 1] = '\0';

    this->bookTitle_ = new char[constant::bookTitleLength];
    strncpy(this->bookTitle_, bookTitle, constant::bookTitleLength - 1);
    this->bookTitle_[constant::bookTitleLength - 1] = '\0';

    this->author_ = new char[constant::authorLength];
    strncpy(this->author_, author, constant::authorLength - 1);
    this->author_[constant::authorLength - 1] = '\0';

    this->publisher_ = new char[constant::publisherLength];
    strncpy(this->publisher_, publisher, constant::publisherLength - 1);
    this->publisher_[constant::authorLength - 1] = '\0';

    this->dateAdded = new std::tm(dateAdded);

    this->qtyOnHand_ = qtyOnHand;
    if (0 > qtyOnHand) {
        std::cout << "设置的库存量小于零，已重新设置为零!\n";
        this->qtyOnHand_ = 0;
    }
    this->retail_ = retail;
    if (0.0 > retail) {
        std::cout << "设置的零售价小于零，已重新设置为零!\n";
        this->retail_ = 0.0;
    }
    this->wholesale_ = wholesale;
    if (0.0 > wholesale) {
        std::cout << "设置的批发价小于零，已重新设置为零!\n";
        this->wholesale_ = 0.0;
    }
}

BookData::BookData(const char* isbn, const char* bookTitle, const char* author, const char* publisher, int year, int month, int day, int qtyOnHand, double retail, double wholesale)
{
    this->isbn_ = new char[constant::isbnLength];
    strncpy(this->isbn_, isbn, constant::isbnLength - 1);
    this->isbn_[constant::isbnLength - 1] = '\0';

    this->bookTitle_ = new char[constant::bookTitleLength];
    strncpy(this->bookTitle_, bookTitle, constant::bookTitleLength - 1);
    this->bookTitle_[constant::bookTitleLength - 1] = '\0';

    this->author_ = new char[constant::authorLength];
    strncpy(this->author_, author, constant::authorLength - 1);
    this->author_[constant::authorLength - 1] = '\0';

    this->publisher_ = new char[constant::publisherLength];
    strncpy(this->publisher_, publisher, constant::publisherLength - 1);
    this->publisher_[constant::authorLength - 1] = '\0';

    this->dateAdded = new std::tm;
    this->dateAdded->tm_year = year - 1900;
    this->dateAdded->tm_mon = month - 1;
    this->dateAdded->tm_mday = day;

    this->qtyOnHand_ = qtyOnHand;
    if (0 > qtyOnHand) {
        std::cout << "设置的库存量小于零，已重新设置为零!\n";
        this->qtyOnHand_ = 0;
    }
    this->retail_ = retail;
    if (0.0 > retail) {
        std::cout << "设置的零售价小于零，已重新设置为零!\n";
        this->retail_ = 0.0;
    }
    this->wholesale_ = wholesale;
    if (0.0 > wholesale) {
        std::cout << "设置的批发价小于零，已重新设置为零!\n";
        this->wholesale_ = 0.0;
    }
}

BookData::BookData(const BookData& other)
{
    this->isbn_ = new char[constant::isbnLength];
    strncpy(this->isbn_, other.isbn_, constant::isbnLength - 1);
    this->isbn_[constant::isbnLength - 1] = '\0';

    this->bookTitle_ = new char[constant::bookTitleLength];
    strncpy(this->bookTitle_, other.bookTitle_, constant::bookTitleLength - 1);
    this->bookTitle_[constant::bookTitleLength - 1] = '\0';

    this->author_ = new char[constant::authorLength];
    strncpy(this->author_, other.author_, constant::authorLength - 1);
    this->author_[constant::authorLength - 1] = '\0';

    this->publisher_ = new char[constant::publisherLength];
    strncpy(this->publisher_, other.publisher_, constant::publisherLength - 1);
    this->publisher_[constant::publisherLength - 1] = '\0';

    this->dateAdded = new std::tm(*other.dateAdded);
    *this->dateAdded = *other.dateAdded;

    this->qtyOnHand_ = other.qtyOnHand_;
    this->retail_ = other.retail_;
    this->wholesale_ = other.wholesale_;
}

BookData::BookData(BookData&& other) noexcept
{
    this->isbn_ = other.isbn_;
    other.isbn_ = nullptr;

    this->bookTitle_ = other.bookTitle_;
    other.bookTitle_ = nullptr;

    this->author_ = other.author_;
    other.author_ = nullptr;

    this->publisher_ = other.publisher_;
    other.publisher_ = nullptr;

    this->dateAdded = other.dateAdded;
    other.dateAdded = nullptr;

    this->qtyOnHand_ = other.qtyOnHand_;
    this->retail_ = other.retail_;
    this->wholesale_ = other.wholesale_;
}

BookData& BookData::operator=(const BookData& other)
{
    strncpy(this->isbn_, other.isbn_, constant::isbnLength - 1);
    this->isbn_[constant::isbnLength - 1] = '\0';

    strncpy(this->bookTitle_, other.bookTitle_, constant::bookTitleLength - 1);
    this->bookTitle_[constant::bookTitleLength - 1] = '\0';

    strncpy(this->author_, other.author_, constant::authorLength - 1);
    this->author_[constant::authorLength - 1] = '\0';

    strncpy(this->publisher_, other.publisher_, constant::publisherLength - 1);
    this->publisher_[constant::publisherLength - 1] = '\0';

    *this->dateAdded = *other.dateAdded;

    this->qtyOnHand_ = other.qtyOnHand_;
    this->retail_ = other.retail_;
    this->wholesale_ = other.wholesale_;
    return *this;
}

BookData& BookData::operator=(BookData&& other) noexcept
{
    if (this != &other) {
        delete[] this->isbn_;
        this->isbn_ = other.isbn_;
        other.isbn_ = nullptr;

        delete[] this->bookTitle_;
        this->bookTitle_ = other.bookTitle_;
        other.bookTitle_ = nullptr;

        delete[] this->author_;
        this->author_ = other.author_;
        other.author_ = nullptr;

        delete[] this->publisher_;
        this->publisher_ = other.publisher_;
        other.publisher_ = nullptr;

        delete this->dateAdded;
        this->dateAdded = other.dateAdded;
        other.dateAdded = nullptr;

        this->qtyOnHand_ = other.qtyOnHand_;

        this->retail_ = other.retail_;

        this->wholesale_ = other.wholesale_;
    }
    return *this;
}

BookData::~BookData()
{
    if (nullptr != this->isbn_) {
        delete[] this->isbn_;
    }
    if (nullptr != this->bookTitle_) {
        delete[] this->bookTitle_;
    }
    if (nullptr != this->author_) {
        delete[] this->author_;
    }
    if (nullptr != this->publisher_) {
        delete[] this->publisher_;
    }
    if (nullptr != this->dateAdded) {
        delete this->dateAdded;
    }
}

const char* BookData::Isbn() const
{
    return this->isbn_;
}

const char* BookData::BookTitle() const
{
    return this->bookTitle_;
}

const char* BookData::Author() const
{
    return this->author_;
}

const char* BookData::Publisher() const
{
    return this->publisher_;
}

const std::tm& BookData::DateAdded() const
{
    return *this->dateAdded;
}

int BookData::QtyOnHand() const
{
    return this->qtyOnHand_;
}

double BookData::Retail() const
{
    return this->retail_;
}

double BookData::Wholesale() const
{
    return this->wholesale_;
}

void BookData::SetIsbn(const char* isbn)
{
    strncpy(this->isbn_, isbn, constant::isbnLength - 1);
    this->isbn_[constant::isbnLength - 1] = '\0';
}

void BookData::SetBookTitle(const char* bookTitle)
{
    strncpy(this->bookTitle_, bookTitle, constant::bookTitleLength - 1);
    this->bookTitle_[constant::bookTitleLength - 1] = '\0';
}

void BookData::SetAuthor(const char* author)
{
    strncpy(this->author_, author, constant::authorLength - 1);
    this->author_[constant::authorLength - 1] = '\0';
}

void BookData::SetPubliser(const char* publisher)
{
    strncpy(this->publisher_, publisher, constant::publisherLength - 1);
    this->publisher_[constant::publisherLength - 1] = '\0';
}

void BookData::SetDateAdded(int year, int month, int day)
{
    this->dateAdded->tm_year = year - 1900;
    this->dateAdded->tm_mon = month - 1;
    this->dateAdded->tm_mday = day;
}

void BookData::SetDateAdded(const std::tm& dateAdded)
{
    *this->dateAdded = dateAdded;
}

void BookData::SetQtyOnHand(int qtyOnHand)
{
    this->qtyOnHand_ = qtyOnHand;
}

void BookData::SetRetail(double retail)
{
    this->retail_ = retail;
}

void BookData::SetWholesale(double wholesale)
{
    this->wholesale_ = wholesale;
}

std::string BookData::GetDateString() const
{
    return std::format("{}-{}-{}", this->dateAdded->tm_year + 1900, this->dateAdded->tm_mon + 1, this->dateAdded->tm_mday);
}

void BookData::PrintDate() const
{
    std::cout << this->dateAdded->tm_year + 1900 << "-" << this->dateAdded->tm_mon + 1 << "-" << this->dateAdded->tm_mon + 1;
}

void BookData::PrintInfo() const
{
    std::cout <<
        "		   书的资料\n"
        "ISBN号：" << this->isbn_ << "\n" <<
        "书 名：" << this->bookTitle_ << "\n" <<
        "作 者：" << this->author_ << "\n" <<
        "出版社：" << this->publisher_ << "\n" <<
        "进书日期：" << (this->dateAdded->tm_year + 1900) << "-" << (this->dateAdded->tm_mon + 1) << "-" << this->dateAdded->tm_mday << "\n" <<
        "库存量：" << this->qtyOnHand_ << "\n" <<
        "零售价：" << this->retail_ << "\n"
        "批发价：" << this->wholesale_ << "\n";
}