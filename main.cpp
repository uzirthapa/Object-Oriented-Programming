#include<iostream>
#include <string>
#include <iomanip>

using namespace std; 


class Person{
	string name;
	string address;
	string city;
	string state;
	string zip;

public:
	void setPerson(){

	}
	void setName(string n){
		name = n;
	}
	string getName(){
		return name;
	}
	void setAddress(string a){
		address = a;
	}
	string getAddress(){
		return address;
	}
	void setCity(string c){
		city = c;
	}
	string getCity(){
		return city;
	}
	void setState(string s){
		state = s;
	}
	string getState(){
		return state;
	}
	void setZip(string z){
		zip = z;
	}
	string getZip(){
		return zip;
	}
};

class Package{
	Person sender;
	Person recvr;

	double weight;		//weight in ounces
	double cost;		// per ounce

public:
	Package(){
		weight = 0;
		cost = 0;	
	}
	Package(double w, double c){
		weight = w;
		cost = c;
	}
	void setWeight(double w){
		weight = w;
	}
	double getWeight(){
		return weight;
	}
	void setCost(double c){
		cost = c;
	}
	double getCost(){
		return cost;
	}
	void setPackage(double w, double c){
		setWeight(w);
		setCost(c);
	}

	double calculateCost(){
		return weight * cost;
	}
	

	void setSender(){
		sender.setPerson(); // set the person
	}
	Person getSender(){
		return sender;
	}

	void setRecvr(){
		recvr.setPerson(); // set the receiver
	}
	Person getRecvr(){
		return recvr;
	}
	
};

class TwoDayPackage : public Package{

	double flatFee;
public:
	TwoDayPackage(double w, double c){
		setPackage(w, c);
		flatFee = 20;
	}
	void setFlatFee(double f){
		flatFee = f;
	}
	double getFlatFee(){
		return flatFee;
	}
};

class OvernightPackage : public Package{
	double overNight;

public: 
	OvernightPackage(double w, double c){
		setPackage(w, c);
		overNight = 0;
	}
	void setOvernight(){
		overNight = getWeight() * (getCost()*0.75);
	}
	double getOvernight(){
		setOvernight();
		return overNight;
	}
	
};



int main(){

	Package Cloth(5, 2);
	TwoDayPackage Shoes(10, 4);
	OvernightPackage Acc(5, 10);

	Person Sender;
	Person Recvr;

	Sender.setName("Comp Inc.");
	Sender.setAddress("1220 First Ave NE");
	Sender.setCity("Cedar Rapids");
	Sender.setState("IA");
	Sender.setZip("52402");

	Recvr.setName("Uzir Thapa");
	Recvr.setAddress("123 Main St");
	Recvr.setCity("New York City");
	Recvr.setState("NY");
	Recvr.setZip("25602");

	double total;

	total = Cloth.calculateCost();
	
	cout << "Clothes: $" << fixed  << setprecision(2) << Cloth.calculateCost() << endl;

	total += Shoes.calculateCost();

	cout << "Shoes: $" << Shoes.calculateCost() << endl;

	total += Acc.calculateCost();

	cout << "Accessories: $" << Acc.calculateCost() << endl;

	cout << "Subtotal: $" << total << endl;

	total += Shoes.getFlatFee();

	total += Acc.getOvernight();

	cout << "Flat Fee 2 day Shipping: $" << Shoes.getFlatFee() << endl;
	cout << "Overnight shipping: $" << Acc.getOvernight() << endl;

	cout << "Grand Total: $" << total << endl;

	return 0;
}
