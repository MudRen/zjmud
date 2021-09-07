// rankd.c 
// 1996-02-15 dts ranking related to "shen"
//modified by macrohard@sdyx
#pragma save_binary
#include <tomud.h>
#include <ansi.h> 
string query_rank(object ob)
{
	mapping fam;
	int shen,exp;
	int budd;
	string set_title,menpai;
	
	exp = (int)ob->query("level");
	menpai=ob->query("family/family_name");
	shen = ob->query("shen");
	if(wizardp(ob)&&ob->query("env/own_rank"))
	       return NOR"��"HIW+ob->query("env/own_rank")+NOR" ��"; 
	if( ob->is_ghost() ) 
		return NOR "��"HIB"�»�Ұ��"NOR"��";


	if ( (fam = ob->query("family")) && fam["family_name"] == "������" ) 
		budd = ob->query_skill("buddhism",1);
	
	if( (int) ob->query("fight_rank") == 1 )
	{
		if( strlen((string) ob->query("env/my_title")) ==2)
		     {
			  set_title = ob->query("env/my_title");
			  return NOR"��"HIW"���µ�һ"+set_title+NOR" ��";
		      }
		else 
			  return NOR"��"HIW"���µ�һ"NOR"��";
	}
	if( (int) ob->query("fight_rank") == 2 )
	{
		if( strlen((string) ob->query("env/my_title")) ==2)
		     {
			  set_title = ob->query("env/my_title");
			  return NOR"��"HIR"���µڶ�"+set_title+NOR" ��";
		      }
		else 
			  return NOR"��"HIR"���µڶ�"NOR"��";
	}
	if( (int) ob->query("fight_rank") == 3)
	{
		if( strlen((string) ob->query("env/my_title")) ==2)
		     {
			  set_title = ob->query("env/title_race");
			  return NOR"��"HIG"���µ���"+ set_title +NOR" ��";
		     }
		else 
			  return NOR"��"HIG"���µ���"NOR"��";
	}
	
	switch(ob->query("gender")) {
	case "Ů��":
		switch(wizhood(ob)) {
		case "(admin)": 
			return NOR "��"HIW"������Ů"NOR"��";       
		case "(wizard)":	
			return NOR "��"HIC"������Ů"NOR"��";
		case "(immortal)":      
			return NOR "��"CYN"�λþ���"NOR"��";
		default:
			if( ((int)ob->query("PKS") > 30) )
				return  "��"HIB"��ѪŮħ"NOR"��";    
			else if (shen >= 1000000)
				return  "��"HIC"һ���콿"NOR"��";
			else if (shen >= 500000)
				return  "��"HIM"����Ů��"NOR"��";
			else if (shen >= 100000)
				return  "��"HIY"����Ӣ��"NOR"��";
			else if (shen >= 50000)
				return  "��"YEL"Ů�к���"NOR"��";
			else if (shen >= 10000)
				return  "��"HIC"Ů �� ��"NOR"��";
			else if (shen >= 5000)
				return  "��"HIG"�糾��Ů"NOR"��";
			else if (shen <= -1000000)
				return  "��"HIW"��ѪŮħ"NOR"��";
			else if (shen <= -500000)
				return  "��"HIR"����ħŮ"NOR"��";
			else if (shen <= -100000)
				return  "��"HIM"��ѪħŮ"NOR"��";
			else if (shen <= -50000)
				return  "��"GRN"������Ů"NOR"��";
			else if (shen <= -10000)
				return  "��"RED"Ů �� ħ"NOR"��" ;
			else if (shen <= -5000)
				return  "��"CYN"������Ů"NOR"��" ;
			else if( (int)ob->query("thief") > 10 ) 
				return  "��"HIW"Ů �� ��"NOR"��";    
			else
			switch(menpai) {
					case "�䵱��":
						if (exp>99){
							if (shen >= 0)
								return NOR "��"HIR"Ů �� ʦ"NOR"��";
							else
								return NOR "��"HIR"Ůħ��ʦ"NOR"��";
							}

						if (exp>79)
								return NOR "��"RED"Ů �� ʦ"NOR"��";
						if (exp>59)
								return NOR "��"GRN"Ů �� ��"NOR"��";
						if (exp>49)
								return NOR "��"YEL"Ů��ʦ"NOR"��";
						if (exp>39)
								return NOR "��"GRN"Ů �� ʦ"NOR"��";
						if (exp>29)
								return NOR "��"CYN"Ů �� ��"NOR"��";
						if (exp>24)
								return NOR "��"MAG"Ů �� ��"NOR"��";
						if (exp>19)
								return NOR "��"HIB"Ů �� ��"NOR"��";
						if (exp>9)
								return NOR "��"HIB" Ů  �� "NOR"��";
						return "��Ů �� �ڡ�";
					case "��ɽ��":
						if (exp>99) {
							if (shen >= 0 )
								return NOR "��"HIW"����һ��"NOR"��";
							else
								return NOR "��"HIW"��ħһ��"NOR"��";
							}
						if (exp>59) {
							if (shen >= 0)
								return NOR "��"HIR"Ů �� ʥ"NOR"��";
							else
								return NOR "��"HIM"Ů �� ħ"NOR"��";
							}	
						if (exp>59) {
							if (shen >= 0)
								return NOR "��"GRN"Ů �� ��"NOR"��";
							else
								return NOR "��"GRN"Ů а ��"NOR"��";
							}
						if (exp>49)
								return NOR "��"YEL"Ů �� ��"NOR"��";
						if (exp>39)
								return NOR "��"CYN"Ů �� ��"NOR"��";
						if (exp>29)
								return NOR "��"CYN"Ů�󽣿�"NOR"��";
						if (exp>24)
								return NOR "��"RED"Ů �� ��"NOR"��";
						if (exp>19)
								return NOR "��"MAG"Ů��ʿ"NOR"��";
						if (exp>9)
								return NOR "��"MAG" ��  ʿ "NOR"��";
						return "��Ů �� ͯ��";

					case "ؤ��":
						if (exp>99)
								return NOR "��"HIR"Ů������"NOR"��" NOR;
						if (exp>79)
								return NOR "��"HIM"Ů����"NOR"��" NOR;
						if (exp>59)
								return NOR "��"HIM"Ů �� ��"NOR"��" NOR;
						if (exp>49)
								return NOR "��"YEL"Ů����ʹ"NOR"��" NOR;
						if (exp>39)
								return NOR "��"YEL"Ůִ��ʹ"NOR"��" NOR;
						if (exp>29)
								return NOR "��"RED"Ů �� ؤ"NOR"��" NOR;
						if (exp>24)
								return NOR "��"RED"ŮС��ؤ"NOR"��" NOR;
						if (exp>14)
								return HIW "��"GRN"Ů �� ؤ"NOR"��" NOR;
						if (exp>9)
								return NOR "��"MAG"ŮС��ؤ"NOR"��" NOR;
						return "�� �� �� �� ��" ;

					case "������":
					case "�һ���":
						if (exp>99) {
							if (shen >= 0)
								return NOR "��"HIR"ħ �� ��"NOR"��";
							else
								return NOR "��"HIR" ��  ħ "NOR"��";
							}	
						if (exp>79)
								return NOR "��"HIM"������Ů"NOR"��";
						if (exp>59)
								return NOR "��"GRN"����Ů��"NOR"��";
						if (exp>49)
								return NOR "��"YEL"�� �� Ů"NOR"��";
						if (exp>39)
								return NOR "��"RED"Ů �� ��"NOR"��";
						if (exp>29)
								return NOR "��"MAG"Ů �� ��"NOR"��";
						if (exp>24)
								return NOR "��"MAG" Ů  �� "NOR"��";
						if (exp>14)
								return NOR "��"CYN" Ů  �� "NOR"��";
						if (exp>9)
								return NOR "��"CYN"С Ů ��"NOR"��";
						return "���糾Ů�ӡ�"NOR ;

					case "����":
						if (exp>99)
								return NOR "��"HIR"Ů������"NOR"��";
						if (exp>79)
								return NOR "��"HIM" ��  �� "NOR"��";
						if (exp>59)
								return NOR "��"GRN"Ů�ܻ���"NOR"��";
						if (exp>49)
								return NOR "��"YEL"Ů �� ��"NOR"��";
						if (exp>39)
								return NOR "��"YEL"Ů������"NOR"��";
						if (exp>29)
								return NOR "��"CYN"Ů������"NOR"��";
						if (exp>24)
								return NOR "��"CYN"Ů �� ��"NOR"��";
						if (exp>19)
								return NOR "��"MAG"Ů������"NOR"��";
						if (exp>9)
								return NOR "��"MAG"Ů �� ��"NOR"��";
						return "��  ��  ��  ��" ;
				      default:
			switch(ob->query("class")) {
			case "bonze":   
				return "�� Ů  �� ��";
			case "yishi":   
				return "��Ů �� ʿ��";
			case "taoist":  
				return "�� Ů  �� ��";			       
			case "bandit":  
				return "��Ů �� ����";
		       case "dancer":  
				return "����ɫ�輧��";				 
			case "scholar": 
				return "��ңң���ˡ�";		  
			case "officer": 
				return "�� Ů  �� ��";
			case "fighter": 
				return "���糾Ů�ӡ�";		    
			case "swordsman":       
				return "���轣��Ů��";		    
			case "alchemist":       
				return "��Ů �� ʿ��";		   
			case "shaman":  
				return "��Ů �� ҽ��";
			case "beggar":  
				return "��Ů�л��ӡ�";      
			case "shiny":
       case "huanu":       return "���ƻ�����ū��"; 
       case "yihuashinv":     return "���ƻ�����Ů��"; 
       case "chuanren":      return "���ƻ������ˡ�"; 
				return "������Ůʹ��";
			default:			
				return "��ܷܷ��Ů��";	      
			}
		}}
	default:
 switch(wizhood(ob)) {
		case "(admin)":		 
			return NOR "��"HIR"����ܹ�"NOR"��" ;
		case "(wizard)":		
			return NOR "��"HIC"��������"NOR"��" ;
		case "(immortal)":	      
			return NOR "��"HIB"��ңɢ��"NOR"��" ;
		default:
			if( ((int)ob->query("PKS") > 50) )
				return "��ɱ��ħ����";
			else if (shen >= 1000000)
				return  "��"HIG"����̩��"NOR"��" ;
			else if (shen >= 500000)
				return HIC "��"HIC"��������"NOR"��" ;
			else if (shen >= 100000)
				return HIC "��"HIC"��������"NOR"��" ;
			else if (shen >= 50000)
				return  "��"HIY"����һʱ"NOR"��";
			else if (shen >= 10000)
				return  "��"HIY"��������"NOR"��";
			else if (shen >= 5000)
				return  "��"HIG"��������"NOR"��";
			else if (shen >= 1000)
				return  "��"HIG"С������"NOR"��";	
			else if (shen >= 500)
				return NOR"��"CYN"С������"NOR"��";
			else if (shen <= -1000000)
				return "��"HIW"�����Ϲ�"NOR"��" ;
			else if (shen <= -500000)
				return "��"HIR"����ħͷ"NOR"��";
			else if (shen <= -100000)
				return "��"RED"���һ��"NOR"��";
			else if (shen <= -50000)
				return "��"YEL"����Զ��"NOR"��";
			else if (shen <= -10000)
				return "��"YEL"С�ж���"NOR"��";	
			else if (shen <= -500)
				return "��"HIB"����а��"NOR"��";
			else if( (int)ob->query("thief") > 10 ) 
				return NOR"��"YEL" ��  ͵ "NOR"��";
			else
			       switch(menpai) {
					case "�䵱��":
						if (exp>99){
							if (shen >= 0 )
								return NOR "��"HIR" ��  ʦ "NOR"��";
							else
								return NOR "��"HIW"�� �� ʦ"NOR"��";
							}
						if (exp>79)
								return NOR "��"HIM" ��  ʦ "NOR"��";
						if (exp>59)
								return NOR "��"GRN" ��  �� "NOR"��";
						if (exp>49)
								return NOR "��"YEL"�� �� ʦ"NOR"��";
						if (exp>39)
								return NOR "��"YEL" ��  ʦ "NOR"��";
						if (exp>29)
								return NOR "��"CYN" ��  �� "NOR"��";
						if (exp>24)
								return NOR "��"CYN" ��  ʿ "NOR"��";
						if (exp>19)
								return NOR "��"HIB" ��  ʿ "NOR"��";
						if (exp>9)
								return NOR "��"HIB"�� �� ͯ"NOR"��";
						return "�� ��  ͯ ��" ;	

					case "��ɽ��":
						if (exp>99) {
							if (shen >= 0 )
								return NOR "��"HIW"����һ��"NOR"��";
							else
								return NOR "��"HIW"��ħһ��"NOR"��";
							}
						if (exp>79) {
							if (shen >= 0)
								return NOR "�� "HIR"��  ʥ"NOR" ��";
							else
								return NOR "�� "HIM"��  ħ"NOR" ��";
							}	
						if (exp>59) {
							if (shen >= 0)
								return NOR "�� "GRN"��  ��"NOR" ��";
							else
								return NOR "�� "GRN"а  ��"NOR" ��";
							}
						if (exp>49)
								return NOR "�� "YEL"��  ��"NOR" ��";
						if (exp>39)
								return NOR "�� "CYN"��  ��"NOR" ��";
						if (exp>29)
								return NOR "��"CYN"�� �� ��"NOR"��";
						if (exp>24)
								return NOR "�� "RED"��  ��"NOR" ��";
						if (exp>19)
								return NOR "��"MAG"�� �� ʿ"NOR"��";
						if (exp>9)
								return NOR "��"MAG" ��  ʿ "NOR"��";
						return "�� ��  ͯ ��";

					case "ؤ��":
						if (exp>99)
								return NOR "��"HIR"�� �� ��"NOR"��";
						if (exp>79)
								return NOR "��"HIW"ʮ������"NOR"��";
						if (exp>59)
								return NOR "��"HIM"�Ŵ�����"NOR"��";
						if (exp>49)
								return NOR "��"YEL"��������"NOR"��";
						if (exp>39)
								return NOR "��"YEL"ִ������"NOR"��";
						if (exp>29)
								return NOR "��"RED" ��  ؤ "NOR"��";
						if (exp>24)
								return NOR "��"CYN"С �� ؤ"NOR"��";
						if (exp>19)
								return NOR"��"CYN"  ��  ؤ "NOR"��";
						if (exp>9)
								return NOR "��"HIB"С �� ؤ"NOR"��";
						return "���� �� �ӡ�"NOR ;

					case "������":
					case "�һ���":
						if (exp>99) {
							if (shen >= 0)
								return NOR "��"HIR"ħ �� ��"NOR"��";
							else
								return NOR "��"HIR" ��  ħ "NOR"��";
							}	
						if (exp>79)
								return NOR "��"CYN"�������"NOR"��";
						if (exp>59)
								return NOR "��"GRN"��������"NOR"��";
						if (exp>49)
								return NOR "��"YEL"�� �� ��"NOR"��";
						if (exp>39)
								return NOR "��"YEL" ��  �� "NOR"��";
						if (exp>29)
								return NOR "��"GRN" ��  �� "NOR"��";
						if (exp>24)
								return NOR "��"GRN" ��  ʿ "NOR"��";
						if (exp>19)
								return NOR "��"CYN" ��  �� "NOR"��";
						if (exp>9)
								return NOR "��"HIC" ��  �� "NOR"��";
						return "���������"NOR ;

					case "����":
						if (exp>99)
								return NOR "��"HIR"�� �� ��"NOR"��";
						if (exp>79)
								return NOR "��"HIM" ��  �� "NOR"��";
						if (exp>59)
								return NOR "��"GRN"�� �� ��"NOR"��";
						if (exp>49)
								return NOR "��"YEL" ��  �� "NOR"��";
						if (exp>39)
								return NOR "��"YEL"�� �� ��"NOR"��";
						if (exp>29)
								return NOR "��"CYN"�� �� ��"NOR"��";
						if (exp>24)
								return NOR "��"CYN" ��  �� "NOR"��";
						if (exp>19)
								return NOR "��"GRN"�� �� ��"NOR"��";
						if (exp>9)
								return NOR "��"HIB" ��  �� "NOR"��";
						return "�� ��  �� ��" ;

					default:
				switch(ob->query("class")) {
				case "bonze":	   
					if (budd >= 150)
						return  "��"HIY" ��  ��"NOR" ��";
					else if (budd >= 120)
						return  "��"HIY" ʥ  ɮ"NOR" ��" ;
					else if (budd >= 90)
						return  "��"HIY" ��  ��"NOR" ��" ;
					else if (budd >= 60)
						return  "��"YEL" ��  ��"NOR" ��" ;
					else if (budd >= 40)
						return "�� "YEL"��  ʦ"NOR" ��" ;
					else if (budd >= 30)
						return  "��"YEL" ��  ��"NOR" ��" ;
					else
						return "�� ɮ  �� ��";
				case "yishi":   
						return "��������ʿ��";
				case "taoist":  
						return "�����ε�ʿ��";			       
				case "bandit":  
						return "�����Ͼ��ӡ�";
				case "scholar": 
						return "��������ӡ�";		  
				case "officer": 
						return "����    �ˡ�";
				case "swordsman":       
						return "�����齣�͡�";		    
				case "alchemist":       
						return "�� ��  ʿ ��";		   
				case "shaman":  
						return "�� ��  ҽ ��";
				case "beggar":  
						return "����л��ӡ�";      
				case "shiny":
						return "������ʹ�ߡ�";
				default:		
					return "������ƽ��";
				}
		}
	}
}
}
string query_respect(object ob)
{
	int age;
	string str;

	if( stringp(str = ob->query("rank_info/respect")) )
		return str;

	age = ob->query("age");
	switch(ob->query("gender")) {
		case "Ů��":
			switch(ob->query("class")) {
			case "bonze":
				if( age < 18 ) return "Сʦ̫";
				else return "ʦ̫";
				break;
			case "taoist":
				if( age < 18 ) return "С�ɹ�";
				else return "�ɹ�";
				break;
			default:
				if( age < 18 ) return "С����";
				else if( age < 50 ) return "����";
				else return "����";
				break;
			}
		case "����":
		default:
			switch(ob->query("class")) {
			case "bonze":
				if( age < 18 ) return "Сʦ��";
				else return "��ʦ";
				break;
			case "taoist":
				if( age < 18 ) return "����";
				else return "����";
				break;
			case "fighter":
			case "swordsman":
				if( age < 18 ) return "С�ϵ�";
				else if( age < 50 ) return "׳ʿ";
				else return "��ǰ��";
				break;
			default:
				if( age < 20 ) return "С�ֵ�";
				else if( age < 50 ) return "׳ʿ";
				else return "��ү��";
				break;
			}
	}
}

string query_rude(object ob)
{
	int age;
	string str;

	if( stringp(str = ob->query("rank_info/rude")) )
		return str;

	age = ob->query("age");
	switch(ob->query("gender")) {
		case "Ů��":
			switch(ob->query("class")) {
			case "bonze":
				return "����";
				break;
			case "taoist":
				return "��Ů";
				break;
			default:
				if( age < 30 || ob->query("special_skill/youth") ) return "С����";
				else return "����̫��";
				break;
			}
		case "����":
		default:
			switch(ob->query("class")) {
			case "bonze":
				if( age < 50 ) return "��ͺ¿";
				else return "��ͺ¿";
				break;
			case "taoist":
				return "��ţ����";
				break;
			default:
				if( age < 20 ) return "С���˵�";
				if( age < 50 ) return "����";
				else return "��ƥ��";
				break;
			}
	}
}

string query_self(object ob)
{
	int age;
	string str;

	if( stringp(str = ob->query("rank_info/self")) )
		return str;

	age = ob->query("age");
	switch(ob->query("gender")) {
		case "Ů��":
			switch(ob->query("class")) {
			case "bonze":
				if( age < 50 ) return "ƶ��";
				else return "����";
				break;
			default:
				if( age < 30 ) return "СŮ��";
				else return "���";
				break;
			}
		case "����":
		default:
			switch(ob->query("class")) {
			case "bonze":
				if( age < 50 ) return "ƶɮ";
				else return "����";
				break;
			case "taoist":
				return "ƶ��";
				break;
			default:
				if( age < 50 ) return "����";
				else return "��ͷ��";
				break;
			}
	}
}

string query_self_rude(object ob)
{
	int age;
	string str;

	if( stringp(str = ob->query("rank_info/self_rude")) )
		return str;

	age = ob->query("age");
	switch(ob->query("gender")) {
		case "Ů��":
			switch(ob->query("class")) {
			case "bonze":
				if( age < 50 ) return "ƶ��";
				else return "����";
				break;
			default:
				if( age < 30 ) return "������";
				else return "����";
				break;
			}
		case "����":
		default:
			switch(ob->query("class")) {
			case "bonze":
				if( age < 50 ) return "�������";
				else return "�Ϻ�����";
				break;
			case "taoist":
				return "��ɽ��";
				break;
			default:
				if( age < 50 ) return "��ү��";
				else return "����";
				break;
			}
	}
}

string query_close(object ob, int age, string rgender)
{
	int a1, a2;
	string gender;
	if (objectp(ob) )       {
		if( !age )
			a1 = this_player()->query("age");
		else
			a1 = ob->query("age");
		if( !age)
			a2 = ob->query("age");
		else    a2 = age;
	}
	
	if( !rgender )
		gender = ob->query("gender");					   
	else    gender = rgender;

	switch ( gender ) {
	case "Ů��" :
		if (a1 > a2)
			return "����";
		else
			return "���";
		break;
	default :
		if (a1 > a2)
			return "�ܵ�";
		else
			return "���";
	}
}

string query_self_close(object ob, int age)
{
	int a1, a2;
	string gender;
	if( objectp(ob) ) 
	{
		if( !age )
			a1 = this_player()->query("age");
		else
			a1 = ob->query("age");
		if( !age)
			a2 = ob->query("age");
		else    a2 = age;
	}

	if( age )
		gender = ob->query("gender");
	else
		gender = this_player()->query("gender");

	switch (gender) 
       {

	case "Ů��" :
		if (a1 > a2)
			return "�����";
		else
			return "С����";
		break;
	default :
		if (a1 > a2)
			return "������";
		else
			return "С����";
	}
}
varargs string new_short( object ob ,int withshort)
{
	mixed tmp;
	string icon="", str;
	if(!objectp(ob))
	{
		CHANNEL_D->do_channel(this_player(),"chat","object��������");
		return "";
	}
	if(!ob->query_temp("apply/id")||!ob->query_temp("apply/name")||!ob->query_temp("apply/short"))
		str = ob->query("name") + "(" +ob->query("id") + ")" +(!withshort?"":ob->short());
	else
		str = ob->query_temp("apply/name")[0] + "(" +ob->query_temp("apply/id")[0] + ")" +(!withshort?"":ob->query_temp("apply/short")[0]);
   
     //�����ڸ����������Ʒͼ��
	 //-Ĭ��OBJECT��ͼ��--------------------------------------------------------------
     icon="";
     //������Ʒ���ж�
     if(ob->query("icon"))
     {
	     icon=ob->query("icon");
     }
     else
     {
	  if(living(ob)) icon= "00901";   //Ĭ������Ϊ00901
	  else icon ="00961";		 //Ĭ����ƷΪ00961
	  if(userp(ob) && !ob->query("icon")) 
	  icon=(ob->query("gender") == "����" )?"01174":"01173";  //Ĭ�����ͷ��
	  if(living(ob) && ob->query("family")!=0 && ob->query("gender") == "����") icon = "00744";  //�м��������
	  if(living(ob) && ob->query("family")!=0 && ob->query("gender") == "Ů��") icon = "00739";  //�м����Ů��
	//---��ͳ����Ʒͼ��--------------------------------------------------
	  if(ob->query("id")=="board")  icon="05025";	 //���԰� 
	  if(ob->query("id")=="boy") icon = "02149";   //�Ծ���Ű�����к��¾�
	  if(ob->query("id")=="girl") icon = "02111";   //Ů������ͬ�ȴ���	
	  if(ob->query("vendor_goods")) icon = "00988";  //������ȼ�Ϊ�����������ͬʱ�������⣩
	  if(ob->query("teacher")) icon = "05014";	//����   
	  if(ob->query("id")=="xiao er" || ob->query("id")=="xiaoer") icon = "05024";   //��¥	
	  if(ob->query("dealer")=="bank") icon = "00842"; //Ǯׯ
	  if(ob->query("dealer")=="pawn") icon = "00957"; //�䵱��
	  if(ob->query("id")=="zhuang jia") icon = "00923"; //�ĳ�
	  if(ob->query("id")=="yahuan" ) icon = "02121"; //Ѿ��
	  if(ob->query("id")=="guan bing" ) icon = "05016"; //�ٱ�
	  if(ob->query("id")=="wu jiang" ) icon = "05010"; //�佫
	  if(ob->query("unit")=="��") icon="00942";   //��
	  if(ob->query("unit")=="��") icon="00906";   //�鱾      
       //��Ʒͼ����ʾ---------------------------------------------
	  if(ob->query("id")=="coin") icon="01013";   //Ǯ������
	  if(ob->query("id")=="silver") icon="05012";   //Ǯ������
	  if(ob->query("id")=="cash") icon="00955";   //Ǯ����Ʊ
	  if(ob->query("id")=="gold") icon="05001";   //����
	  
       //����
	  if(ob->query("skill_type")=="sword") icon="05035";  //�������� 
	  if(ob->query("skill_type")=="pin") icon="01059";    //��������
	  //if(ob->query("skill_type")=="dagger") icon="05030"; //ì������
	  if(ob->query("skill_type")=="axe") icon="05029";    //��������
	  if(ob->query("skill_type")=="dagger") icon="05040"; //ذ������
	  if(ob->query("skill_type")=="staff") icon="05042";   //��������
	   if(ob->query("skill_type")=="club") icon="05042";   //��������
	  if(ob->query("skill_type")=="blade") icon="05038";  //�������� 
	  if(ob->query("skill_type")=="throwing") icon="05049";   //���� 
	  if(ob->query("skill_type")=="hammer") icon="05050";     //�� 
	   if(ob->query("skill_type")=="fork") icon="05034";     //��
       //����װ��
	  if(ob->query("armor_type")=="cloth") icon="05000";   //�·�
	   if(ob->query("armor_type")=="armor") icon="05044";   //װ��
	  if(ob->query("armor_type")=="pants") icon="05077";   //����
	  if(ob->query("armor_type")=="boots") icon="03007";   //Ь��
	  if(ob->query("armor_type")=="head") icon="03004";   //ͷ
	  if(ob->query("armor_type")=="hands") icon="01980";   //������
	  if(ob->query("armor_type")=="finger") icon="03002";   //��ָ��
	  if(ob->query("armor_type")=="shield") icon="05017";   //������
	  if(ob->query("armor_type")=="neck") icon="03006";   //����
	  if(ob->query("armor_type")=="wrists") icon="03003";  //����
   }
    return str + icon;
}


