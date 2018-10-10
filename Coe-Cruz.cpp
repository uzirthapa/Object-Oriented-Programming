// Uzir Thapa - Coe Cruz cpp
// Object Oriented Programming CS-355
// Terry Hostetler
// HW 3
// Wednesday December 7 

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <time.h>
#include <iomanip>
#include <sstream>

using namespace std;

class RideType{		// class type
public:
   void setDate(string d){
	   date = d;
	   setYear(d);
	   setMonth(d);
	   setDay(d);
   }
   string getDate(){
	   return date;
   }
   void setTime(string t){
	   time = t;
	   setHour(t);
	   setMin(t);
   }
   string getTime(){
	   return time;
   }
   void setUser(string u){
	   user = u;
   }
   string getUser(){
	   return user;
   }
   void setFromLoc(string f){
	   fromLoc = f;
   }
   string getFromLoc(){
	   return fromLoc;
   }
   void setToLoc(string t){
	   toLoc = t;
   }
   string getToLoc(){
	   return toLoc;
   }
   void setNumPas(int n){
	   numPas = n;
   }
   int getNumPas(){
	   return numPas;
   }
   // Polymorphic print
   virtual string toString(){
	   char buffer[4];
	  return getUser() + " " + getFromLoc() 
		   + " " + getToLoc() + " " + itoa(getNumPas(),buffer,10);
   }

   // Time Functions
    void setHour(string h){
	   int len;
	   len = getTime().find(":");
	   hour = stoi(getTime().substr(0, len));
   }
   int getHour(){
	   return hour;
   }
   void setMin(string m){
	   int len;
	   len = getTime().find(":");
	   minute = stoi(getTime().substr(len+1,'\n'));
   }
   int getMin(){
	   return minute;
   }
   void setMonth(string m){
	   int len;
	   len = getDate().find("/");
	   month = stoi(getDate().substr(0,len));
   }
   int getMonth(){
	   return month;
   }
   void setDay(string d){
	   int len;
	   len = getDate().find("/");
	   day = stoi(getDate().substr(len+1,2));
   }
   int getDay(){
	   return day;
   }
   void setYear(string y){
	   int len;
	   len = getDate().find_last_of("/");
	   year = stoi(getDate().substr(len+1,2));
   }
   int getYear(){
	   char buffer[4];
	   if (year < 16){
		   string str= itoa(year, buffer,10);
		   str.insert(0,"21");
		   int yearNum = stoi(str);
		   return yearNum;
	   }
	   else{
		   string str= itoa(year, buffer,10);
		   str.insert(0,"20");
		   int yearNum = stoi(str);
		   return yearNum;
	   }
   }
   void setTimeDiff(time_t t){
	   timeDiff = t;
   }
   time_t getTimeDiff(){
	   return timeDiff;
   }

private:
	string date;
	string time;
	string user;
	string fromLoc;
	string toLoc;
	int numPas;

	// Time Function Variables
	int hour;
	int minute;
	int month;
	int day;
	int year;
	time_t timeDiff;
};

// Inherit from RideType
class onCallType : public RideType{
public:
	void setPrice(double p){
		price = p;
	}
	double getPrice(){
		return price;
	}
	// polymorphic
	virtual string toString() override {
		stringstream stream;
		stream << fixed << setprecision(2) << getPrice();
		string s = stream.str();
		char buffer[4];
		return  RideType::toString() + " " + s;
	}

private:
	double price;
};

class Account{
public:
	void setUser(string x){
		user = x;
	}
	string getUser(){
		return user;
	}
	void setPhone(string x){
		phone = x;
	}
	string getPhone(){
		return phone;
	}
	void setEmail(string x){
		email = x;
	}
	string getEmail(){
		return email;
	}
	
private:
	string user;
	string phone;
	string email;
};

bool userSort(RideType &s1, RideType &s2){	// comparator for sorting time difference in matchVec
    return s1.getUser() < s2.getUser();
}

bool TimeSort(RideType &s1, RideType &s2){	// comparator for sorting time difference in matchVec
    return s1.getTimeDiff() < s2.getTimeDiff();
}

bool priceSort(onCallType &i, onCallType &j)	// Comparator for sorting price difference in priceVec
{
	return i.getPrice() > j.getPrice();
}

int main(){
   
	// for input
   int num, numPas; 
   string type;
   string user, phone, email, date, 
	   time, fromLoc, toLoc; 
   double price;

   // time struct
   struct tm match;
   struct tm offTime = {0};
   struct tm reqtime = {0};
   
   // Account Types
   Account Rider;
   Account Driver;

   //Ride Types
   RideType offer;
   RideType request;

   //OnCall Type
   onCallType onCall;

  //vector for account types
   vector<Account> driverAcct;
   vector<Account> riderAcct;

   // vector for Ride Types
   vector<RideType> offerVec;
   vector<RideType> requestVec;
   vector<onCallType> onCallVec;

   //open file
   ifstream file;
   file.open("transactions.in");		
   file >> num;
   //Add data to RideTypes
   while(!file.eof()){
	   file >> type;
	   if (type == "RIDR"){
		   file >> user >> phone >> email;
		   Rider.setUser(user);
		   Rider.setPhone(phone);
		   Rider.setEmail(email);
		   riderAcct.push_back(Rider);
	   }
	   else if (type == "DRVR"){
		   file >> user >> phone >> email;
		   Driver.setUser(user);
		   Driver.setPhone(phone);
		   Driver.setEmail(email);
		   driverAcct.push_back(Driver);
	   }
	   else if (type == "REQU"){
		   file >> date >> time >> user >> 
			   fromLoc >> toLoc >> numPas;
		   request.setDate(date);
		   request.setTime(time);
		   request.setUser(user);
		   request.setFromLoc(fromLoc);
		   request.setToLoc(toLoc);
		   request.setNumPas(numPas);
		   requestVec.push_back(request);
	   }
	    else if (type == "TOFR"){
		   file >> date >> time >> user >> 
			   fromLoc >> toLoc >> numPas;
		   offer.setDate(date);
		   offer.setTime(time);
		   offer.setUser(user);
		   offer.setFromLoc(fromLoc);
		   offer.setToLoc(toLoc);
		   offer.setNumPas(numPas);
		   offerVec.push_back(offer);
		}
		else if (type =="ONCL"){
			file >> user >> fromLoc 
				>> toLoc >> numPas >> price;
			onCall.setUser(user);
			onCall.setFromLoc(fromLoc);
			onCall.setToLoc(toLoc);
			onCall.setNumPas(numPas);
			onCall.setPrice(price);
			onCallVec.push_back(onCall);
		}
   }

   ofstream outfile;
   outfile.open("transactions.out");

   // Print to File
   outfile << "Rider accounts:" << endl;
   for (int i = 0; i < riderAcct.size(); i++){
	   outfile << "        " << riderAcct[i].getUser() <<  " " << riderAcct[i].getPhone() 
		   << " " << riderAcct[i].getEmail() << endl;
   }
   outfile << endl << "Driver accounts:" << endl;
   for (int i = 0; i < driverAcct.size(); i++){
	   outfile << "        " << driverAcct[i].getUser() << " " << driverAcct[i].getPhone() 
		   << " " << driverAcct[i].getEmail() << endl;
   }
   outfile << endl << "Requests for rides:" << endl;
   for (int i = 0; i < requestVec.size(); i++){

	   // Time Adding
		if (requestVec[i].getYear() <= 2016){	// check for less than 2016 to convrt to correct time
								// in 2100
				reqtime.tm_year = requestVec[i].getYear() - 1900;	
			}
		else{
				reqtime.tm_year = requestVec[i].getYear() - 2000;
			}

			reqtime.tm_mon = requestVec[i].getMonth() - 1;
			reqtime.tm_mday = requestVec[i].getDay();
			reqtime.tm_hour = requestVec[i].getHour();
			reqtime.tm_min = requestVec[i].getMin();
			requestVec[i].setTimeDiff(mktime(&reqtime));
   }
   //sort Request vector according to time
   std::sort(requestVec.begin(), requestVec.end(), TimeSort);

    for (int i = 0; i < requestVec.size(); i++){
	   outfile << "        " << requestVec[i].getDate() << " " << requestVec[i].getTime() 
		   << " " << requestVec[i].getUser() << " " << requestVec[i].getFromLoc() 
		   << " " << requestVec[i].getToLoc() << " " << requestVec[i].getNumPas() << endl;
   }
   outfile << endl<<  "Offers (time-specific) for rides:" << endl;
   for (int i = 0; i < offerVec.size(); i++){

	   if (offerVec[i].getYear() <= 2016){	// check for less than 2016 to convrt to correct time
								// in 2100
				offTime.tm_year = offerVec[i].getYear() - 1900;	
			}
		else{
				offTime.tm_year = offerVec[i].getYear() - 2000;
			}

			offTime.tm_mon = offerVec[i].getMonth() - 1;
			offTime.tm_mday = offerVec[i].getDay();
			offTime.tm_hour = offerVec[i].getHour();
			offTime.tm_min = offerVec[i].getMin();
			offerVec[i].setTimeDiff(mktime(&offTime));
   }
   //sort offer Vector according to time
   std::sort(offerVec.begin(), offerVec.end(), TimeSort); 

   // Print Offer Vec
   //Print Polymorphically using dynamic binding
   for (int i = 0; i < offerVec.size(); i++){
	   outfile << "        "  << offerVec[i].getDate() << " " <<  offerVec[i].getTime() 
		   << " "<< offerVec[i].toString() << endl;
   }

   outfile << endl<<  "On call offers for rides:" << endl;
   std::sort(onCallVec.begin(), onCallVec.end(), userSort);

   //print polymorphically using dynamic binding
   for (int i = 0; i < onCallVec.size(); i++){
	   outfile << "        "  << onCallVec[i].toString() << endl;
   }

   //Ride Matching 

   // Match vectors
   vector<RideType> matchVec;
   vector<onCallType> matchOnCallVec;
   vector<RideType> printVec;

   int count = 0;

   // loop for matching request with rides
   outfile << endl << "Ride Matches:" << endl;
   for (int i = 0; i < requestVec.size(); i++)		
	{
		outfile << requestVec[i].getUser() << " requesting for ride for " <<
			requestVec[i].getNumPas()<< " from " <<requestVec[i].getFromLoc() << " to " <<
			requestVec[i].getToLoc() << " on "<< requestVec[i].getDate() << " at time " << 
			requestVec[i].getTime() << endl;

		for (int j = 0; j < onCallVec.size(); j++)
		{
			if (onCallVec[j].getFromLoc() == requestVec[i].getFromLoc() &&
				onCallVec[j].getToLoc() == requestVec[i].getToLoc() &&		//check if same from, to, more number of passengers
				requestVec[i].getNumPas() <= onCallVec[j].getNumPas())
				{
					matchOnCallVec.push_back(onCallVec[j]);
					count++;
				}
		}

		for (int j = 0; j < offerVec.size(); j++)		// loop for matching rides with request
		{
			if (offerVec[j].getFromLoc() == requestVec[i].getFromLoc() &&
				offerVec[j].getToLoc() == requestVec[i].getToLoc() &&		//check if same from, to, more number of passengers
				requestVec[i].getNumPas() <= offerVec[j].getNumPas())
				{
					matchVec.push_back(offerVec[j]);		// vector for matches to print late
				}
		}

		//Calculate Time difference
		for (int j = 0; j < matchVec.size(); j++){
			matchVec[j].setTimeDiff(difftime(requestVec[i].getTimeDiff(),matchVec[j].getTimeDiff()));	
		}

		// for inbetween 1 hour check and add to Print Vector
		for (int j = 0; j < matchVec.size(); j++){
			if(matchVec[j].getTimeDiff() <= 3600 && matchVec[j].getTimeDiff() >= -3600){
				printVec.push_back(matchVec[j]);
				count++;
			}
		}
		
		if (count == 0){
			outfile << "    Sorry, no matches found" << endl;		//if count == 0 then no matches 
			}
		else{
			outfile << "    " << count << " Matches found!" << endl;	

			std::sort(printVec.begin(), printVec.end(), TimeSort);	// sort the rides
			std::sort(matchOnCallVec.begin(), matchOnCallVec.end(), priceSort);	//sort according to prices

			int b=0;
			while ( b < printVec.size())
			{

				outfile << "         #" << b+1 << " Ride with " 
					<< printVec[b].getUser() << " - leaving at "				// output
					<< printVec[b].getTime() << " on " << printVec[b].getDate() << " - " << printVec[b].getNumPas() 
					<< " seats available" <<endl;
				b++;
			}

			int c= 0;
			while(c < matchOnCallVec.size())	//print on-call rides after all the other rides
			{
				outfile << 	"         #" << b+1 << " Ride with "
					<< matchOnCallVec[c].getUser() << " " << matchOnCallVec[c].getNumPas() 
					<< " seats available anytime at $" 
					<< fixed << setprecision(2) << matchOnCallVec[c].getPrice() <<  endl; // vector for onCall to print 
				c++;
				b++;
			}

			// clear vectors so no repeats
			matchOnCallVec.clear();
			matchVec.clear(); 
			printVec.clear();
			count = 0;		// reset count
			}
		outfile << endl;
   }
    return 0;
}
