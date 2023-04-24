#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using std::ostream;
using std::istream;


class String {

private:
    static int num_strings;
    static const int CINLIM = 80;
    int len;
    char* m_data;
    size_t m_size;

public:

    String() : m_data(nullptr), m_size(0) {}
    String(const char* str) : m_data(nullptr), m_size(0) {

        if (str) {
            m_size = strlen(str);
            m_data = new char[m_size + 1];
            memcpy(m_data, str, m_size + 1);
        }
    }

    String(const String& other) : m_data(nullptr), m_size(0) {
        if (other.m_data) {
            m_size = other.m_size;
            m_data = new char[m_size + 1];
            memcpy(m_data, other.m_data, m_size + 1);
        }
    }
    String(String&& other) : m_data(other.m_data), m_size(other.m_size) {
        other.m_data = nullptr;
        other.m_size = 0;
    }
    ~String() {
        if (m_data) {
            delete[] m_data;
        }
    }

    String& operator=(const String& other) {
        if (this != &other) {
            if (m_data) {
                delete[] m_data;
            }
            if (other.m_data) {
                m_size = other.m_size;
                m_data = new char[m_size + 1];
                memcpy(m_data, other.m_data, m_size + 1);
            } else {
                m_data = nullptr;
                m_size = 0;
            }
        }
        return *this;
    }

    String& operator=(String&& other) {
        if (this != &other) {
            if (m_data) {
                delete[] m_data;
            }
            m_data = other.m_data;
            m_size = other.m_size;
            other.m_data = nullptr;
            other.m_size = 0;
        }
        return *this;
    }

    char& operator[](size_t index) {
        return m_data[index];
    }

    const char& operator[](size_t index) const {
        return m_data[index];
    }

    friend String operator+(const String& lhs, const String& rhs) {
        String result;
        result.m_size = lhs.m_size + rhs.m_size;
        result.m_data = new char[result.m_size + 1];
        memcpy(result.m_data, lhs.m_data, lhs.m_size);
        memcpy(result.m_data + lhs.m_size, rhs.m_data, rhs.m_size + 1);
        return result;
    }

    friend bool operator<(const String& lhs, const String& rhs) {
        size_t min_size = std::min(lhs.m_size, rhs.m_size);
        for (size_t i = 0; i < min_size; ++i) {
            if (tolower(lhs[i]) < tolower(rhs[i])) {
                return true;
            } else if (tolower(lhs[i]) > tolower(rhs[i])) {
                return false;
            }
        }
        return lhs.m_size < rhs.m_size;
    }

    friend ostream & operator<<(ostream & os, const String & st)
    {
        os << st.m_data;
        return os;
    }

    friend istream & operator>>(istream & is, String & st) {
      char temp[String::CINLIM];
      is.get(temp, String::CINLIM);
      if (is)
          st = temp;
      while (is && is.get() != '\n')
          continue;
      return is;
    }

  int length() const { return len; }


};

int main() {
    std::vector<String> strings;
    String myStr;
    while (std::cin >> myStr) {
        strings.emplace_back(myStr);
    }

    std::sort(strings.begin(), strings.end(), [](const String& lhs, const String& rhs) {
        return rhs < lhs;
     });

    for (auto &Str : strings) {

        std::cout << Str << std::endl;
    }
    return 0;
}
