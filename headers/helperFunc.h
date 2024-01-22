#ifndef HELPERFUNC_H
#define HELPERFUNC_H


struct Time ConvertTime(int time){
	struct Time rtrn;
	int temp;
	
	temp= time% 60;
	rtrn.minute=temp;
	time = time - (temp);
	temp = time;
	rtrn.hour=(temp/60)%24;
	temp = time /1440;
	rtrn.days=temp;
	
	return rtrn;
}




#endif
