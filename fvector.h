#ifndef FVECTOR_HPP
#define FVECTOR_HPP
#include <fstream>
#include <string>
#include "string.hpp"
template<class K , class T>
class fvector
{
    template<typename A, typename B>
    struct MYPAIR{
        A first;
        B second;
        MYPAIR(A st, B nd):first(st), second(nd){}
    };
private:

        tstring<20> fileName;
	fstream f;

public:
        ~fvector(){
            f.close();
        }
	void init(const char *_fileName)
	{
                fileName = tstring<20>(_fileName);
                fileName += ".bin";
                f.open(fileName, ios_base::in);
		if (!f) {
                        f.close();
                        f.open(fileName, ios_base::out | ios_base::trunc | ios_base::binary);
			int tot = 0;
			f.write(reinterpret_cast<char*>(&tot), sizeof(int));
		}
                else{
                    f.close();
                    f.open(fileName, ios_base::in | ios_base::out | ios_base::binary);
                }
	}

	int size()
	{
                if(f.fail()) f.close();
                if(!f.is_open()) f.open(fileName, ios_base::in | ios_base::out | ios_base::binary);
                f.seekg(0);
                int tot = 0;
                f.read(reinterpret_cast<char*>(&tot), sizeof(int));
                f.flush();
		return tot;
	}

        void insert(const K &key, const T &x)
	{
            if(f.fail()) f.close();
            if(!f.is_open()) f.open(fileName, ios_base::in | ios_base::out | ios_base::binary);
		int tot;
		f.seekg(0, ios::beg);
		f.read(reinterpret_cast<char*>(&tot), sizeof(int));
		f.seekp(sizeof(int) + sizeof(T) * tot, ios::beg);
                f.write(reinterpret_cast<const char*>(&x), sizeof(T));
		f.seekp(0, ios::beg);
		++tot;
		f.write(reinterpret_cast<char*>(&tot), sizeof(int));
                f.flush();
	}

        MYPAIR<T*, bool> find(const int &pos)
        {
            if(f.fail()) f.close();
            if(!f.is_open()) f.open(fileName, ios_base::in | ios_base::out | ios_base::binary);
                T *tmp = new T;
                f.seekg(0);
                int sz = 0;
                f.read((char*)&sz, sizeof(int));
                if(pos >= sz) return MYPAIR<T*, bool>(nullptr, 0);
		f.seekg(sizeof(int) + sizeof(T) * pos, ios::beg);
                f.read(reinterpret_cast<char*>(tmp), sizeof(T));
                f.flush();
                return MYPAIR<T*, bool>(tmp, 1);
	}

	void modify(int pos, const T &x)
	{
            if(f.fail()) f.close();
            if(!f.is_open()) f.open(fileName, ios_base::in | ios_base::out | ios_base::binary);
                if(f.fail()) f.close();
                if(!f.is_open()) f.open(fileName, ios_base::out | ios_base::binary | ios_base::in);
		f.seekp(sizeof(int) + sizeof(T) * pos, ios::beg);
                f.write(reinterpret_cast<const char*>(&x), sizeof(T));
                f.flush();
	}

        bool trunc(){
            f.close();
            f.open(fileName, ios_base::trunc |ios_base::in | ios_base::out | ios_base::binary);
            int tot = 0;
            f.write((char*)&tot, sizeof(int));
            return 1;
        }
};
#endif
