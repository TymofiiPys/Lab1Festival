#include <iostream>
#include "Structs.h"
#include <string>

SongNode::SongNode(int id, char* name, char* band, char* genre, SongTime t) {
	this->id = id;
	strcpy_s(this->name, name);
	strcpy_s(this->band, band);
	strcpy_s(this->genre, genre);
	this->t = t;
	this->next = nullptr;
}

Fest::Fest(int num, char* name, Date d1, Date d2, char* org, char* loc) {
	this->num = num;
	this->d1 = d1;
	this->d2 = d2;
	strcpy_s(this->name, name);
	strcpy_s(this->org, org);
	strcpy_s(this->loc, loc);
	this->song = nullptr;
}

Fest::Fest(int num, char* name, Date d1, Date d2, char* org, char* loc, SongNode* song) {
	this->num = num;
	this->d1 = d1;
	this->d2 = d2;
	strcpy_s(this->name, name);
	strcpy_s(this->org, org);
	strcpy_s(this->loc, loc);
	this->song = song;
}

struct Fest1 {
	//int id;
	int num;
	char name[20];
	Date d1;
	Date d2;
	char org[30];
	char loc[30];
	SongNode* song;
};

struct SongNode1 {
	int id;
	char name[20];
	char band[20];
	char genre[20];
	SongTime t;
	SongNode* next;
};

Date getDatefromchar(char date[11]) {
	char d[3], m[3], y[5];
	d[0] = date[0];
	d[1] = date[1];
	m[0] = date[3];
	m[1] = date[4];
	y[0] = date[6];
	y[1] = date[7];
	y[2] = date[8];
	y[3] = date[9];
	int id = atoi(d);
	int im = atoi(m);
	int iy = atoi(y);
	Date dd;
	dd.day = id;
	dd.month = im;
	dd.year = iy;
	return dd;
}

SongTime getTimefromchar(char time[6]) {
	char m[3], s[3];
	m[0] = time[0];
	m[1] = time[1];
	s[0] = time[3];
	s[1] = time[4];
	int im, is;
	im = atoi(m);
	is = atoi(s);
	SongTime t;
	t.min = im;
	t.sec = is;
	return t;
}

bool checkIdExists(int id, bool song) {
	if(song){
		FILE* fsong = fopen("song.dat", "r+b");
		SongNode1 s;
		while (fread(&s, sizeof(SongNode), 1, fsong)) {
			if (s.id == id)
			{
				fclose(fsong);
				return true;
			}
		}
		fclose(fsong);
		return false;
	}
	else {
		FILE* find = fopen("fest.ind", "r+b");
		FestAddress fa;
		while (fread(&fa, sizeof(FestAddress), 1, find)) {
			if (fa.id == id)
			{
				fclose(find);
				return true;
			}
		}
		fclose(find);
		return false;
	}
	return false;
}

int fest_count(FILE* f) {
	Fest1 fc;
	int c = 0;
	while (fread(&fc, sizeof(Fest), 1, f)) {
		c++;
	}
	return c;
}

int fest_max(FILE* f) {
	Fest1 fc;
	int c = 0;
	fseek(f, -1*sizeof(Fest), SEEK_END);
	fread(&fc, sizeof(Fest), 1, f);
	return fc.num;
}

Fest* createFest(int num, int *id) {
	char f_name[20], f_date1[11], f_date2[11], f_org[30], f_loc[30];
	//std::cout << "Введіть назву фестивалю: ";
	//fgets(c, 5, stdin);
	std::cout << "Введіть ID фестивалю: ";
	std::cin >> *id;
	if (checkIdExists(*id, 0)) {
		std::cout << "Фестиваль із даним ID вже існує.\n";
		return nullptr;
	}
	std::cout << "Введіть назву фестивалю: ";
	//fgets(f_name, 20, stdin);
	scanf("%19s", f_name);
	std::cout << "Введіть дату початку фестивалю: ";
	//fgets(f_date1, 11, stdin);
	scanf("%10s", f_date1);
	std::cout << "Введіть дату закінчення фестивалю: ";
	//fgets(f_date2, 11, stdin);
	scanf("%10s", f_date2);
	std::cout << "Введіть ім'я організатора фестивалю: ";
	//fgets(f_org, 30, stdin);
	scanf("%29s", f_org);
	std::cout << "Введіть місце проведення фестивалю: ";
	//fgets(f_loc, 30, stdin);
	scanf("%29s", f_loc);
	Date d1, d2;
	d1 = getDatefromchar(f_date1);
	d2 = getDatefromchar(f_date2);
	Fest* fe = new Fest(num, f_name, d1, d2, f_org, f_loc);
	/*Fest fe;
	strcpy_s(fe.name, f_name);
	strcpy_s(fe.org, f_org);
	strcpy_s(fe.loc, f_loc);
	fe.d1 = d1;
	fe.d2 = d2;*/
	return fe;
}

SongNode* createSong(int *id) {
	char s_name[20], s_band[20], s_genre[20], s_time[6];
	std::cout << "Введіть ID пісні: ";
	std::cin >> *id;
	if (checkIdExists(*id, 1)) {
		std::cout << "Пісня із даним ID вже існує.\n";
		return nullptr;
	}
	std::cout << "Введіть назву пісні: ";
	scanf("%19s", s_name);
	std::cout << "Введіть виконавця: ";
	scanf("%19s", s_band);
	std::cout << "Введіть жанр: ";
	scanf("%19s", s_genre);
	std::cout << "Введіть тривалість: ";
	scanf("%5s", s_time);
	SongTime t = getTimefromchar(s_time);
	return new SongNode(*id, s_name, s_band, s_genre, t);
}

void insert_f() {
	if (FILE* FILEFEST = fopen("fest.dat", "r+b"))
	{
		int f_amt = fest_max(FILEFEST);
		int id;
		Fest* fe = createFest(f_amt, &id);
		if (fe)
		{
			FestAddress fa;
			fa.id = id;
			fa.num = f_amt + 1;
			FILE* find = fopen("fest.ind", "r+b");
			fseek(FILEFEST, 0, SEEK_END);
			fseek(find, 0, SEEK_END);
			/*fe.num = f_amt;*/
			fwrite(fe, sizeof(Fest), 1, FILEFEST);
			fwrite(&fa, sizeof(FestAddress), 1, find);
			fclose(find);
		}
		fclose(FILEFEST);
	}
	else {
		FILE* fc = fopen("fest.dat", "w+b");
		int id;
		Fest* fe = createFest(0, &id);
		//fe.num = 0;
		if (fe)
		{
			FILE* find = fopen("fest.ind", "w+b");
			FestAddress fa;
			fa.id = id;
			fa.num = 1;
			fwrite(fe, sizeof(Fest), 1, fc);
			fwrite(&fa, sizeof(FestAddress), 1, find);
			fclose(find);
		}
		fclose(fc);
	}
}

void insert_s() {
	if (FILE* FILESONG = fopen("song.dat", "r+b"))
	{
		Fest* f = get_f();
		int id;
		SongNode* s = createSong(&id);
		if (!f->song) {
			f->song = s;
			update_f(f);
		}
		else {
			SongNode* iter = f->song;
			while (iter->next) {
				iter = iter->next;
			}
			iter->next = s;
		}
		fseek(FILESONG, 0, SEEK_END);
		fwrite(s, sizeof(SongNode), 1, FILESONG);
		fclose(FILESONG);
	}
	else {
		FILE* fc = fopen("song.dat", "w+b");
		Fest* f = get_f();
		int id;
		SongNode* s = createSong(&id);
		if (!f->song) {
			f->song = s;
			update_f(f);
		}
		else {
			SongNode* iter = f->song;
			while (iter->next) {
				iter = iter->next;
			}
			iter->next = s;
		}
		fwrite(s, sizeof(SongNode), 1, fc);
		fclose(fc);
	}
	/*char s_name[20], s_band[20], s_genre[20], s_time[6];
	std::cout << "Введіть назву пісні: ";
	fgets(s_name, 20, stdin);
	std::cout << "Введіть виконавця пісні: ";
	fgets(s_band, 20, stdin);
	std::cout << "Введіть жанр пісні: ";
	fgets(s_genre, 20, stdin);
	std::cout << "Введіть тривалість пісні: ";
	fgets(s_time, 6, stdin);*/
	/*SongTime t = getTimefromchar(s_time);
	SongNode* s = new SongNode(s_name, s_band, s_genre, t);*/
}

Fest* get_f() {
	if (FILE* find = fopen("fest.ind", "rb"))
	{
		std::cout << "Введіть ID фестивалю: ";
		int id;
		std::cin >> id;
		FestAddress f;
		int num = -1;
		while (fread(&f, sizeof(FestAddress), 1, find)) {
			if (f.id == id) {
				num = f.num;
			}
		}
		if (num == -1)
			std::cout << "Фестиваль із введеним Вами ID відсутній у базі даних.\n";
		else {
			FILE* FILEFEST = fopen("fest.dat", "rb");
			/*fseek(FILEFEST, (num - 1) * sizeof(Fest), SEEK_SET);*/
			Fest1 f1;
			while (fread(&f1, sizeof(Fest), 1, FILEFEST)) {
				if (f1.num == num) {
					break;
				}
			}
			/*std::cout << "ID: " << f.id << std::endl;
			std::cout << "Назва: " << fe.name << std::endl;
			std::cout << "Дата початку: " << fe.d1.day << "." << fe.d1.month << "." << fe.d1.year << std::endl;
			std::cout << "Дата закінчення: " << fe.d2.day << "." << fe.d2.month << "." << fe.d2.year << std::endl;
			std::cout << "Організатор: " << fe.org << std::endl;
			std::cout << "Місце проведення: " << fe.loc << std::endl;*/
			fclose(FILEFEST); 
			fclose(find);
			return new Fest(f1.num, f1.name, f1.d1, f1.d2, f1.org, f1.loc, f1.song);
		}
		fclose(find);
	}
	return nullptr;
}

SongNode* get_s() {
	Fest* f = get_f();
	if (FILE* fsong = fopen("song.dat", "rb"))
	{
		std::cout << "Введіть ID пісні: ";
		int id;
		std::cin >> id;
		SongNode* iter = f->song;
		while (iter) {
			if (iter->id == id)
				return new SongNode(iter->id, iter->name, iter->band, iter->genre, iter->t);
			iter = iter->next;
		}
		return nullptr;
		//FestAddress f;
		//int num = -1;
		//while (fread(&f, sizeof(FestAddress), 1, find)) {
		//	if (f.id == id) {
		//		num = f.num;
		//	}
		//}
		//if (num == -1)
		//	std::cout << "Фестиваль із введеним Вами ID відсутній у базі даних.\n";
		//else {
		//	FILE* FILEFEST = fopen("fest.dat", "rb");
		//	fseek(FILEFEST, (num - 1) * sizeof(Fest), SEEK_SET);
		//	Fest1 f1;
		//	fread(&f1, sizeof(Fest), 1, FILEFEST);
		//	/*std::cout << "ID: " << f.id << std::endl;
		//	std::cout << "Назва: " << fe.name << std::endl;
		//	std::cout << "Дата початку: " << fe.d1.day << "." << fe.d1.month << "." << fe.d1.year << std::endl;
		//	std::cout << "Дата закінчення: " << fe.d2.day << "." << fe.d2.month << "." << fe.d2.year << std::endl;
		//	std::cout << "Організатор: " << fe.org << std::endl;
		//	std::cout << "Місце проведення: " << fe.loc << std::endl;*/
		//	fclose(FILEFEST);
		//	fclose(find);
		//	return new Fest(f1.num, f1.name, f1.d1, f1.d2, f1.org, f1.loc);
		//}
		//fclose(find);
	}
	return nullptr;
}

void update_f(Fest* f) {
	int num = f->num;
	FILE* fp = fopen("fest.dat", "r+b");
	FILE* ft = fopen("temp.dat", "wb");
	Fest1 f1;
	while (fread(&f1, sizeof(Fest), 1, fp)) {
		if (f1.num == num) {
			break;
		}
		fwrite(&f1, sizeof(Fest), 1, ft);
	}
	fwrite(f, sizeof(Fest), 1, ft);
	while (fread(&f1, sizeof(Fest), 1, fp)) {
		fwrite(&f1, sizeof(Fest), 1, ft);
	}
	fclose(fp);
	fclose(ft);
	remove("fest.dat");
	rename("temp.dat", "fest.dat");
}

void update_f() {
	Fest* f = get_f();
	std::cout << "Яке поле Ви хочете оновити?\n";
	std::cout << "0 - Назва фестивалю\n";
	std::cout << "1 - Дата початку\n";
	std::cout << "2 - Дата закінчення\n";
	std::cout << "3 - Організатор\n";
	std::cout << "4 - Локація\n";
	int op;
	std::cin >> op;
	switch (op) {
		char f_name[20], f_date1[11], f_date2[11], f_org[30], f_loc[30];
	case 0:
		std::cout << "Введіть назву фестивалю: ";
		scanf("%19s", f_name);
		strcpy_s(f->name, f_name);
		break;
	case 1:
		std::cout << "Введіть дату початку фестивалю: ";
		scanf("%10s", f_date1);
		Date d1 = getDatefromchar(f_date1);
		f->d1 = d1;
		break;
	case 2:
		std::cout << "Введіть дату закінчення фестивалю: ";
		scanf("%10s", f_date2);
		Date d2 = getDatefromchar(f_date2);
		f->d2 = d2;
		break;
	case 3:
		std::cout << "Введіть ім'я організатора фестивалю: ";
		scanf("%29s", f_org);
		strcpy_s(f->org, f_org);
		break;
	case 4:
		std::cout << "Введіть місце проведення фестивалю: ";
		scanf("%29s", f_loc);
		strcpy_s(f->loc, f_loc);
		break;
	}
	int num = f->num;
	FILE* fp = fopen("fest.dat", "r+b");
	FILE* ft = fopen("temp.dat", "wb");
	Fest1 f1;
	while (fread(&f1, sizeof(Fest), 1, fp)) {
		if (f1.num == num) {
			break;
		}
		fwrite(&f1, sizeof(Fest), 1, ft);
	}
	fwrite(f, sizeof(Fest), 1, ft);
	while (fread(&f1, sizeof(Fest), 1, fp)) {
		fwrite(&f1, sizeof(Fest), 1, ft);
	}
	fclose(fp);
	fclose(ft);
	remove("fest.dat");
	rename("temp.dat", "fest.dat");
}

void update_s() {
	get_s();
	std::cout << "Яке поле Ви хочете оновити?\n";
	std::cout << "0 - Назва пісні\n";
	std::cout << "1 - Виконавець\n";
	std::cout << "2 - Жанр\n";
	std::cout << "3 - Тривалість\n";
	int op;
	std::cin >> op;
	switch (op) {
	case 0:
		break;
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	}
}

void remove_f() {
	Fest* f = get_f();
	int num = f->num;
	FILE* fp = fopen("fest.dat", "r+b");
	FILE* ft = fopen("temp.dat", "wb");
	Fest1 f1;
	while (fread(&f1, sizeof(Fest), 1, fp)) {
		if (f1.num == num) {
			break;
		}
		fwrite(&f1, sizeof(Fest), 1, ft);
	}
	while (fread(&f1, sizeof(Fest), 1, fp)) {
		fwrite(&f1, sizeof(Fest), 1, ft);
	}
	fclose(fp);
	fclose(ft);
	remove("fest.dat");
	rename("temp.dat", "fest.dat");
	FILE* fi = fopen("fest.ind", "r+b");
	FILE* fi2 = fopen("temp.ind", "r+b");
	FestAddress fa;
	while (fread(&fa, sizeof(FestAddress), 1, fi)) {
		if(fa.num != num)
			fwrite(&fa, sizeof(FestAddress), 1, fi2);
	}
	fclose(fi);
	fclose(fi2);
	remove("fest.ind");
	rename("temp.ind", "fest.ind");
}

void remove_s() {
	get_s();
}

void output_f(int id) {
	if (id == -1)
	{
		if (FILE* FILEFEST = fopen("fest.dat", "rb")) {
			Fest1 f;
			while (fread(&f, sizeof(Fest), 1, FILEFEST)) {
				std::cout << "Назва: " << f.name << std::endl;
				std::cout << "Дата початку: " << f.d1.day << "." << f.d1.month << "." << f.d1.year << std::endl;
				std::cout << "Дата закінчення: " << f.d2.day << "." << f.d2.month << "." << f.d2.year << std::endl;
				std::cout << "Організатор: " << f.org << std::endl;
				std::cout << "Місце проведення: " << f.loc << std::endl;
			}
			fclose(FILEFEST);
		}
		else {
			std::cout << "База даних пуста\n";
		}
	}
	else {
		Fest* f = get_f();
		if (f) {
			std::cout << "Назва: " << f->name << std::endl;
			std::cout << "Дата початку: " << f->d1.day << "." << f->d1.month << "." << f->d1.year << std::endl;
			std::cout << "Дата закінчення: " << f->d2.day << "." << f->d2.month << "." << f->d2.year << std::endl;
			std::cout << "Організатор: " << f->org << std::endl;
			std::cout << "Місце проведення: " << f->loc << std::endl;
		}
	}
}

void output_ind() {
	if (FILE* find = fopen("fest.ind", "rb"))
	{
		FestAddress f;
		while (fread(&f, sizeof(FestAddress), 1, find)) {
			std::cout << "Номер: " << f.num << std::endl;
			std::cout << "Ключ: " << f.id << std::endl;
		}
		fclose(find);
	}
}