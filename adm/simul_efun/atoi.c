// atoi.c

int atoi(string str)
{
	int v;

	if( !stringp(str) || !sscanf(str, "%d", v) ) return 0;
	return v;
}

int time()
{
	return efun::time();
}

int exp2lv(int exp)
{
	if(exp<134)
		return to_int(sqrt(exp))+1;
	else
		return to_int(pow(exp*10.0,1.0/3))+1;
}

int lv2exp(int lv)
{
	lv--;
	if(lv < 11)
		return lv*lv;
	return lv*lv*lv/10;
}

int rand2(int seed,int lv)
{
	int k,m,n;

	k = pow(seed,lv);
	m = random(k);
	n = to_int(pow(k,1.0/lv)-pow(m,1.0/lv));
	return n;
}

int same_week(int time1, int time2)
{
	int day;
	int monday1;
	int monday2;

	if (!time1)
		time1 = time();
	
	if (!time2)
		time2 = time();

	if (((time1+28800)/86400) != ((time2+28800)/86400)) {
		day = localtime(time1)[6];
		if (day == 0) day = 7;
		day--;
		monday1 = time1 - day*86400;

		day = localtime(time2)[6];
		if (day == 0) day = 7;
		day--;
		monday2 = time2 - day*86400;

		if (((monday1+28800)/86400) == ((monday2+28800)/86400))
			return 1;
		else
			return 0;
	} 
	return 1;
}
