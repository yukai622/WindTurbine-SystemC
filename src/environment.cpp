#include "environment.h"

void environment::set_attributes(){
  wind.set_timestep(0.001,sc_core::SC_SEC);
}

void environment::initialize(){
  int j;

  ifstream in("./wind_one_week.txt");
  
  if(!in) {
  cout << "Cannot open file."<<endl;
  exit(-1);
  }

  for(j=0;j<LENGTH;j++){
  in >> speed[j];  
  }

  in.close();

}

void environment::processing(){

	if(counter%1000 == 0 && number != 0){
	  number = number + 1;
  	  wind.write(speed[number]+0);
	  counter++;
	}else{
	  wind.write(speed[number]+0);
	  counter++;
	}

}