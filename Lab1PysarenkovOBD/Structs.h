#pragma once

struct Date{
	int day;
	int month;
	int year;
};

struct SongTime {
	int min;
	int sec;
};

struct SongNode {
	int num;
	int id;
	char name[20];
	char band[20];
	char genre[20];
	SongTime t;
	int next;
	SongNode(int num, int id, char* name, char* band, char* genre, SongTime t, int next);
};

struct Fest {
	int num;
	char name[20];
	Date d1;
	Date d2;
	char org[30];
	char loc[30];
	int song;
	Fest(int num, char* name, Date d1, Date d2, char* org, char* loc);
	Fest(int num, char* name, Date d1, Date d2, char* org, char* loc, int song);
};

struct FestAddress {
	int id;
	int num;
};

void insert_f();

void insert_s();

Fest* get_f();

SongNode* get_s();

void update_f();
void update_f(Fest* f);

void update_s();
void update_s(SongNode* s);

void remove_f();

void remove_s();
void remove_s(SongNode* s);

void output_f(int id);

void output_s(int id);

int fest_count(FILE* f);

void output_ind();

void sort();
