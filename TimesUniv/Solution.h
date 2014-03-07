#pragma once

struct Asignation //Needs to be modified, adding the quota and professor hours
{
	int classroom;
	int hour;
	int professor;
	int course;
	int classhours;
	int quota;
	wchar_t group[2];
	int full_time;
};

struct errorCourse
{
	int course_id;
	char grupo;
	wstring descr;
};


class Solution : public Math::ISimAnneal
{
public:
	Solution(void);
	Solution(int nHours, int nRooms, int nCourse);
	~Solution(void);
	void filterData(void);
	bool checkData(vector<valarray<Asignation>> matrix, int hour, int room); //How Pass a Matrix through a function?
	int compareProfessorMondays(int prof, int hour, int classroom);
	int compareProfessorThursdays(int prof, int hour, int classroom);
	std::map<int, int> classrooms;
	vector<valarray<Asignation> > solMon,solThu;
	vector <errorCourse> errorCourses;
	

	//___________________________________________ Solution variables
	double error;
	int n;
	int nHours;
	int nRooms;
	std::vector<struct Asignation> sol;
	double x;
	double y;
	int period_id;
	std::tr1::minstd_rand randomGenerator; //This is a "vector" to do a random generation performance, it's necessary initialize on the class consctructor
	//___________________________________________ Math::ISimAnneal
	void SimAnnealInitialize();
	void SimAnnealPerturb(Math::ISimAnneal& original, double temperature, double initialTemperature);
	void SimAnnealCopy(const Math::ISimAnneal& source);
	double SimAnnealGetError();
};