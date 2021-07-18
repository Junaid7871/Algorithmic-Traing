#include<iostream>
#include<conio.h>
#include<fstream>
#include<vector>
#include<sstream>
#include<string>
#include<math.h>

using namespace std;

// GET THE DAY FROM THE DATE
int get_day(string date)
{
	int  day, d1i, d2i;
	string d1, d2;
	d1 = date[8];
	stringstream c1(d1);
	c1 >> d1i;
	d2 = date[9];
	stringstream c2(d2);
	c2 >> d2i;
	
	day = (d1i)*10 + int(d2i);
	//cout<<day<<endl;
	
	
	
	return day;
}

//GET THE TIME FROM THE DATE
string get_time(string date)
	{
		string t1,t2,t3,t4,t5, time;
		t1 = date[11];
		t2 = date[12];
		t3 = date[13];
		t4 = date[14];
		t5 = date[15];
		
		time = t1+t2+t3+t4+t5;
		return time;
	
	}

int main()
{

ifstream fin; 

fin.open("data.csv", ios::in); //read excel file

int count = 0, count1 = 0, trade_counter =0; //internal and external counters

vector<string> row;

string line, word, trade_status = "INACTIVE"; //variable declarations

int prev_day = 0, prev_high =0, buy_price, prev_low, target_price, stop_loss, buy=0, cost, gain, profit=0, prev_price;

while(fin.good())
{
	row.clear();  //clear the row after each read

	getline(fin, line);  // read an entire row and store it in a string variable 'line'
	
	

	stringstream s(line);

	while(getline(s, word, ',')) // read every column data of a row and store it in a string variable, 'word'
	{
		row.push_back(word); // add all the column data of a row to a vector

	}
     
     
	string date, open, high, low, close;
	int day, openi, highi, lowi, closei, highest, lowest;
	
	
	if( day != prev_day && buy == 1 && count1>1)  //  If trade status is active before the end of the previous day, sell all the stocks (Starts from second day only)
		{
			buy = 0;
			trade_counter++;
			cout<<"SELLING";
			trade_status = "INACTIVE";
			cout<<"(Time = "<<get_time(date)<<")"<<endl;
			
			gain = highi*10;
			
			profit += (gain - cost);
		}

	// divide the columns of a row from the excel sheet
	count++;
	date  = row[0];
	open  = row[1];
	high  = row[2];
	low   = row[3];
	close = row[4];
	
	//convert string values of excel data to integer
	stringstream s1(open);
	s1 >> openi;         // current Open price
	stringstream s2(high);
	s2 >> highi;          // current High price
	stringstream s3(low);
	s3 >> lowi;			// curent Low price
	stringstream s4(close);
	s4 >> closei; 		// current Close price
	
	
	
	day = get_day(date);
	
	
	if(day != prev_day) // when trading starts on a new day
	{
		count1++;
		prev_day = day;
		prev_high = highest; //store the highest price of the previous day
		highest = 0;
		prev_low = lowest; //store the lowest price of previous day
		lowest = lowi;
		
		
		
	}
	
	if (highest < highi) //store the highest price if it is more then the current high
		highest = highi;
	
	if (lowest < lowi) // store the lowest price if it is less than the current low
	lowest = lowi;

	
	
	
	
	if(count1 > 1) //as we don't know the previous high of 26th October 2020 (i.e. the high of 25th October), we start calculations from 27th October 2020
	{
		if(highi > prev_high && buy == 0) // if strategy 1 occured when trade_status is inactive
		{
			buy = 1;
		cout<<"BUY NOW";
		trade_status = "ACTIVE";
		
		cout<<"(Time = "<<get_time(date)<<")"<<endl;
		
		buy_price = highi;
		target_price = buy_price + (prev_high - prev_low);
		
		stop_loss = buy_price - ((prev_high - prev_low)/4);
		cost = buy_price * 10;
		
		}
		
		
		
		
		
		if((highi >= target_price || highi <= stop_loss ) && buy == 1) // When Target is met or loss is more than the threshold(stop_loss)
		{
			buy = 0;
			trade_counter++;
			cout<<"SELLING";
			trade_status = "INACTIVE";
			cout<<"(Time = "<<get_time(date)<<")"<<endl;
			
			gain = highi*10;
			
			profit += (gain - cost);
			
		}
		
		
		
		

	}
	

}
cout<<"Total times trading done = "<<trade_counter<<endl;
cout<<"Total Profit made = "<<profit<<endl;

cout<<"Enter any key to exit..."<<endl;

char x = getch();

return 0;
}
