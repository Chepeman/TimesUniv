#include "StdAfx.h"
#include ".\Solution.h"

Solution::Solution(void)
{	
}
Solution::Solution(int nHours, int nRooms, int nCourse)
{
	this->nHours=nHours;
	this->nRooms=nRooms;
	this->n=nCourse;
	//sol.reserve(this->n);
	randomGenerator.seed(::GetTickCount());
}
Solution::~Solution(void)
{	
}
void Solution::SimAnnealInitialize()
{
	filterData();
}
void Solution::SimAnnealPerturb(Math::ISimAnneal& original, double temperature, double initialTemperature)
{

	Solution& soriginal = (Solution&) original;
	int solSize;
	int temp=(int)temperature;
	solSize=sol.size()/2;
	int r1,h1,r2,h2,auxr,auxh,auxp,auxc,auxch,auxq;
	char auxg;
	std::tr1::uniform_int<int> classDis(1, nRooms);
	std::tr1::uniform_int<int> hourDis(1, nHours);
	for(int i=0; i<solSize; i++)
	{
		//Code for Mondays
		r1=classDis(Math::Statistics::random_generator);
		h1=hourDis(Math::Statistics::random_generator);
		r2=classDis(Math::Statistics::random_generator);
		h2=hourDis(Math::Statistics::random_generator);

		auxh=solMon[r1][h1].hour;
		auxr=solMon[r1][h1].classroom;
		auxp=solMon[r1][h1].professor;
		auxc=solMon[r1][h1].course;
		auxch=solMon[r1][h1].classhours;
		auxq=solMon[r1][h1].quota;
		auxg=(char)solMon[r1][h1].group[0];

		solMon[r1][h1].classroom=solMon[r2][h2].classroom;
		solMon[r1][h1].hour=solMon[r2][h2].hour;
		solMon[r1][h1].professor=solMon[r2][h2].professor;
		solMon[r1][h1].course=solMon[r2][h2].course;
		solMon[r1][h1].classhours=solMon[r2][h2].classhours;
		solMon[r1][h1].quota=solMon[r2][h2].quota;
		solMon[r1][h1].group[0]=solMon[r2][h2].group[0];

		solMon[r2][h2].classroom=auxr;
		solMon[r2][h2].hour=auxh;
		solMon[r2][h2].professor=auxp;
		solMon[r2][h2].course=auxc;
		solMon[r2][h2].classhours=auxch;
		solMon[r2][h2].quota=auxq;
		solMon[r2][h2].group[0]=auxg;


		//Code for Thursdays
		auxh=solThu[r1][h1].hour;
		auxr=solThu[r1][h1].classroom;
		auxp=solThu[r1][h1].professor;
		auxc=solThu[r1][h1].course;
		auxch=solThu[r1][h1].classhours;
		auxq=solThu[r1][h1].quota;
		auxg=(char)solThu[r1][h1].group[0];

		solThu[r1][h1].classroom=solThu[r2][h2].classroom;
		solThu[r1][h1].hour=solThu[r2][h2].hour;
		solThu[r1][h1].professor=solThu[r2][h2].professor;
		solThu[r1][h1].course=solThu[r2][h2].course;
		solThu[r1][h1].classhours=solThu[r2][h2].classhours;
		solThu[r1][h1].quota=solThu[r2][h2].quota;
		solThu[r1][h1].group[0]=solThu[r2][h2].group[0];

		solThu[r2][h2].classroom=auxr;
		solThu[r2][h2].hour=auxh;
		solThu[r2][h2].professor=auxp;
		solThu[r2][h2].course=auxc;
		solThu[r2][h2].classhours=auxch;
		solThu[r2][h2].quota=auxq;
		solThu[r2][h2].group[0]=auxg;
	}
}
void Solution::SimAnnealCopy(const Math::ISimAnneal& source)
{
	Solution& ssource((Solution&)source);
	/*x = ssource.x;
	y = ssource.y;*/
	nHours=ssource.nHours;
	period_id=ssource.period_id;
	n=ssource.n;
	nRooms=ssource.nRooms;
	sol.resize(ssource.sol.size());
	std::copy(ssource.sol.begin(),  ssource.sol.end(), sol.begin());
	solMon=ssource.solMon;
	solThu=ssource.solThu;
}
double Solution::SimAnnealGetError()
{
	errorCourse err;
	int solSize=sol.size();
	errorCourses.clear();
	int aux=-1;
	int sSizei, sSizej;
	
	if(solSize==0) return error;
	error=0;
	for(int i=0; i<solSize; i++)
	{
		if(classrooms[sol[i].classroom]<sol[i].quota)
		{
			error++;
			err.course_id=sol[i].course;
			err.grupo=(char)sol[i].group[0];
			err.descr=L"The classroom don't support the quota";
			errorCourses.push_back(err);
		}
	}
	sSizei=solMon.size();
	sSizej=solMon[0].size();
	//Check error when a Professor if teaching a class in a different classroom but at the same hour
	for(int i=0;i<sSizei;i++)
		for(int j=0;j<sSizej;j++)
		{
			if(solMon[i][j].professor!=0)
			{
				aux=(int)error;
				error+=compareProfessorMondays(solMon[i][j].professor,solMon[i][j].hour, solMon[i][j].classroom);
				if(error>aux)
				{
					err.course_id=solMon[i][j].course;
					err.grupo=(char)solMon[i][j].group[0];
					err.descr=L"The Professor is already teaching other class at this time";
					errorCourses.push_back(err);
				}
			}
		}
	sSizei=solThu.size();
	sSizej=solThu[0].size();
	for(int i=0;i<sSizei;i++)
		for(int j=0;j<sSizej;j++)
		{
			if(solThu[i][j].professor!=0)
			{
				aux=(int)error;
				error+=compareProfessorThursdays(solThu[i][j].professor,solThu[i][j].hour, solThu[i][j].classroom);
				if(error>aux)
				{
					err.course_id=solThu[i][j].course;
					err.grupo=(char)solThu[i][j].group[0];
					err.descr=L"The Professor is already teaching other class at this time";
					errorCourses.push_back(err);
				}
			}
		}

	sSizei=solMon.size();
	sSizej=solMon[0].size();
	//Check error when a professor is not Base Professor on Mondays
	for(int i=0;i<sSizei;i++)
		for(int j=0;j<sSizej;j++)
		{
			if(solMon[i][j].professor!=0)
			{
				aux=(int)error;
				if(solMon[i][j].hour>=5 && solMon[i][j].full_time==1)
				error++;
				if(error>aux)
				{
					err.course_id=solMon[i][j].course;
					err.grupo=(char)solMon[i][j].group[0];
					err.descr=L"The Professor is full time";
					errorCourses.push_back(err);
				}
			}
		}

	sSizei=solThu.size();
	sSizej=solThu[0].size();
	//Check error when a professor is not Base Professor on Thursday
	for(int i=0;i<sSizei;i++)
		for(int j=0;j<sSizej;j++)
		{
			if(solThu[i][j].professor!=0)
			{
				aux=(int)error;
				if(solThu[i][j].hour>=5 && solThu[i][j].full_time==1)
				error++;
				if(error>aux)
				{
					err.course_id=solThu[i][j].course;
					err.grupo=(char)solThu[i][j].group[0];
					err.descr=L"The Professor is full time";
					errorCourses.push_back(err);
				}
			}
		}

	
	return error;
}
void Solution::filterData()
{
	wstring cmd;
	Asignation hor;
	int c,p,room,hour;
	int rom, quot;
	int solSize=-1;
	//needs to be modified, adding the period
	Sys::Format(cmd,L"SELECT a.course_id, a.professor_id, c.week_hours, a.cupo, a.grupo, pf.isbase FROM assignment a, course c, period p, professor pf WHERE c.course_id=a.course_id AND p.period_id=a.period_id AND a.professor_id=pf.professor_id AND a.period_id=%d",period_id);
	
	try  
	{
		/*Here we full the solution vector with the course and professor ID from the Database*/
		Sql::SqlConnection conn;
		conn.OpenSession(DSN,USERNAME,PASSWORD);
		conn.ExecuteSelect(cmd);
		conn.BindColumn(1,hor.course); 
		conn.BindColumn(2,hor.professor);
		conn.BindColumn(3,hor.classhours);
		conn.BindColumn(4,hor.quota);
		conn.BindColumn(5,hor.group,2);
		conn.BindColumn(6,hor.full_time);
		while(conn.Fetch())
		{
			sol.push_back(hor);
		}
		conn.CloseSession();
	}
	catch (Sql::SqlException e)
	{
		//Wintempla library it's no included here, a way to show an error? 
		//this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
	}
	try  
	{
		Sys::Format(cmd,L"SELECT classroom_id, seat_count FROM classroom");
		Sql::SqlConnection conn;
		conn.OpenSession(DSN,USERNAME,PASSWORD);
		//room=conn.GetInt(cmd);
		conn.ExecuteSelect(cmd);
		conn.BindColumn(1,rom);
		conn.BindColumn(2,quot);
		while(conn.Fetch())
			classrooms[rom]=quot;
		room=classrooms.size();
		Sys::Format(cmd,L"SELECT COUNT(DISTINCT classtime_id) FROM classtime");
		hour=conn.GetInt(cmd);
		conn.CloseSession();
	}
	catch (Sql::SqlException e)
	{
		//Wintempla library it's no included here, a way to show an error? 
		//this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
	}
	std::tr1::uniform_int<int> classDis(1, room);// uniform integer distribution, change number of the constructor, had to be the classroom range
	std::tr1::uniform_int<int> hourDis(1, hour); // uniform integer distribution, change number of the constructor, had to be the hours range
	solSize=sol.size();
	for(int i=0; i<solSize; i++)
	{
		if(sol[i].full_time==1)
		{
			std::tr1::uniform_int<int> hourDis(1, 4);
			p=hourDis(randomGenerator);

		}
		else
		{
			std::tr1::uniform_int<int> hourDis(1, hour);
			p=hourDis(randomGenerator);
		}

		if(i!=0)
		{
			if(sol[i-1].course==sol[i].course && sol[i-1].professor!=sol[i].professor)
			{
				p=sol[i-1].hour;
			}
		}
		c=classDis(randomGenerator); //Generate the c(classroom), p(professor) with TR1 library
		sol[i].classroom=c;
		sol[i].hour=p;
	}
	//Create a Matrix professorsxhours size, and full it with the data solution
	//Get a count of clasrooms and professors to create the MATRIX
	//Initialize the MATRIXs
	room++;
	hour++;
	solMon.resize(room);
	for(int i=0;i<room;i++)
		solMon[i].resize(hour);
	solThu.resize(room);
	for(int i=0;i<room;i++)
		solThu[i].resize(hour);
	for(int i=0; i<solSize; i++)
	{	

		if(sol[i].classhours==6 && checkData(solMon,sol[i].hour,sol[i].classroom)==true)
		{
			solMon[sol[i].classroom][sol[i].hour]=sol[i];
		}
		else if(sol[i].classhours==4 && checkData(solThu,sol[i].hour,sol[i].classroom)==true)
		{
			solThu[sol[i].classroom][sol[i].hour]=sol[i];
		}
		else
		{
			sol[i].classroom=classDis(randomGenerator);
			sol[i].hour=hourDis(randomGenerator);
			i--;
		}
	}
}
bool Solution::checkData(vector<valarray<Asignation>> matrix, int hour, int room)
{
	if(matrix[room][hour].course==0 && matrix[room][hour].classroom==0)
		return true;
	else
		return false;
}
int Solution::compareProfessorMondays(int prof, int hour, int classroom)
{
	int count=0;
	for(int i=1;i<nRooms;i++)
	{
		if(solMon[i][hour].professor==prof && classroom!=i)
			count++;
	}
	return count;
}
int Solution::compareProfessorThursdays(int prof, int hour, int classroom)
{
	int count=0;
	for(int i=1;i<nRooms;i++)
	{
		if(solThu[i][hour].professor==prof && classroom!=i)
			count++;
	}
	return count;
}