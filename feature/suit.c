//��װЧ���� ���� ʵ��
//angelus �� 2010�� 03/28
//angelus �� 2010�� 04/12 ������
//  ʵ��˼·�� ��ҪӦ��mpping
/*
	  �򵥵���װ����   ,, mappingԭ��ܼ򵥣���д����ʮ�ָ��ӡ�
*/
#pragma save_binary
#include <tomud.h>
#include <ansi.h> 
#include <command.h>

string dis_lvl(int lvl);			  //����������װ�ȼ�����ʾ
string dis_count(int count,int suit_count);	//���������Ŷ�����ʾͼ����ɫ��Ϣ
string suit_dis(mapping suit_eff_last,mapping suit_map,mapping suit_lvl,mapping suit_count,mapping suit_skill_last); //��ʾ��װĬ��Ч��

mapping sum_eff(object ob,mapping suit_eff);

//��Ҫ�ж���װ����
mixed suit(object ob,string arg)
{
	//������ϵĸ���λ����
	string *armor_type=({"armor/armor","armor/cloth","armor/boots","armor/head","armor/face",
	"armor/wrists","armor/neck","armor/hands","armor/shield","armor/waist","armor/pants",
	"armor/finger","weapon","secondary_weapon",});

	string suit="",str="";   //��װ����
	object obj;		  //װ�����������
	mixed map ;  //KEY��ͳ����װ�ļ���mapping
	mixed map_eff; //KEY�� ȫ������װЧ��mapping
	mixed map_eff_key; //KEY�� ȥ���� ��װЧ��������mapping


	mapping suit_eff=([ ]);  //�洢��װȫ��Ч��
	mapping suit_count=([ ]);  //�洢��װ��󲿼�
	mapping suit_map=([ ]);   //�洢����װ�����׼�����
	mapping suit_lvl=([ ]);	 //�洢����װ�ȼ�

	mapping suit_eff_start=([ ]);  // ������װЧ�����м丨��mapping 
	mapping suit_eff_mid=([ ]);	 //������װЧ�����м丨��mapping
	mapping suit_eff_last=([ ]);   // ��������װЧ��
   
	mapping suit_skill=([ ]); //
	mapping suit_skill_last=([ ]);//
	//50
	int i;  //ѭ��ʱ�ı��� //��Ϊ�ж��ѭ�������Զ���������
	int j;
	int k;
   
	//��������װ���ĸ���װ ���Ե����������ƣ���󲿼������ȣ��洢�ڸ���mapping ��
	for(i=0;i < sizeof(armor_type);i++)
	{
		if(objectp(obj=ob->query_temp(armor_type[i])))
		{
			if(suit=obj->query("suit"))
			{
				suit_map += ([ suit : suit_map[suit]+1 ]);	 //���㴩�Ÿ���װ������
				suit_eff +=([ suit : obj->query("suit_eff") ])  ;   //����Ч�� KEY:mapping
				suit_count +=([ suit : obj->query("suit_count") ])  ;   //��װ��󲿼�����
				suit_lvl +=([ suit : obj->query("suit_lvl") ])  ;	//��װ�ĵȼ�
				if(obj->query("suit_eff_skill"))
				{
					suit_skill +=([ suit : obj->query("suit_eff_skill") ])  ;  //����
				}
			}  
		}
	}
	//----------������װЧ��----------------------------------------------------------------
	if(sizeof(suit_map))
	{
		map=keys(suit_map); //��ֵ�� suit_map;
		map_eff=keys(suit_eff); //��ֵ�� suit_map;
		for(i=0;i < sizeof(suit_map);i++)	//ѭ�����д��ŵ���װ 
		{
			if(suit_count[map[i]]<=2)
			{
				continue;
			}
			//װ���㹻һ�׵Ļ����������и���Ч������
			if(suit_map[map[i]] == suit_count[map[i]])   
			{
				suit_eff_last += ([ map[i] :  suit_eff[ map[i]] ]);	
				if(sizeof(suit_skill))
				{
					suit_skill_last += ([ map[i] :  suit_skill[ map[i] ] ]); 
				}  
			}
			//װ����3���ĸ���Ч�����涨Ϊ�� һ�� �����Ӳ���
			if(suit_map[map[i]] < suit_count[map[i]] && suit_map[map[i]] >=3)   
			{
				suit_eff_start=([]);   //100
				suit_eff_mid= suit_eff[ map[i] ];   
				map_eff_key=keys(suit_eff_mid);
				for(j=0;j < 1;j++)
				{
					suit_eff_start += ([ map_eff_key[j] : suit_eff_mid[ map_eff_key[j] ] ]);			
				}
				suit_eff_last += ([ map[i] : suit_eff_start ]);   
			}
			//װ����5���ĸ���Ч�����涨Ϊ�� ���� �����Ӳ���
			if(suit_map[map[i]] < suit_count[map[i]] && suit_map[map[i]] >=5)   
			{
				suit_eff_start=([]);
				suit_eff_mid= suit_eff[ map[i] ];  
				map_eff_key=keys(suit_eff_mid);
				for(j=0;j < 2;j++)
				{
					suit_eff_start += ([ map_eff_key[j] : suit_eff_mid[ map_eff_key[j] ] ]);		 
				}
				suit_eff_last += ([ map[i] : suit_eff_start ]);	 
			}
			//װ����7���ĸ���Ч�����涨Ϊ�� ���� �����Ӳ���
			if(suit_map[map[i]] < suit_count[map[i]] && suit_map[map[i]] >=7)   
			{
				suit_eff_start=([]);
				suit_eff_mid= suit_eff[ map[i] ];  
				map_eff_key=keys(suit_eff_mid);
				for(j=0;j < 3;j++)
				{   //150
					suit_eff_start += ([ map_eff_key[j] : suit_eff_mid[ map_eff_key[j] ] ]);		
				}
				suit_eff_last += ([ map[i] : suit_eff_start ]);	
			}
			//װ����9���ĸ���Ч�����涨Ϊ�� �ĸ� �����Ӳ���
			if(suit_map[map[i]] < suit_count[map[i]] && suit_map[map[i]] >=9)   
			{
				suit_eff_start=([]);	
				suit_eff_mid= suit_eff[ map[i] ];	 
				map_eff_key=keys(suit_eff_mid);
				for(j=0;j < 4;j++)
				{
					suit_eff_start += ([ map_eff_key[j] : suit_eff_mid[ map_eff_key[j] ] ]);		 
				}
				suit_eff_last += ([ map[i] : suit_eff_start ]);	  
			}
			//װ����10���ĸ���Ч�����涨Ϊ�� ��� �����Ӳ���
			if(suit_map[map[i]] < suit_count[map[i]] && suit_map[map[i]] >=10)   
			{   
				suit_eff_start=([]);	
				suit_eff_mid= suit_eff[ map[i] ];  
				map_eff_key=keys(suit_eff_mid);
				for(j=0;j < 5;j++)
				{
					suit_eff_start += ([ map_eff_key[j] : suit_eff_mid[ map_eff_key[j] ] ]);	 
				}
				suit_eff_last += ([ map[i] : suit_eff_start ]);   
		 
			}	//200
			//װ����12���ĸ���Ч�����涨Ϊ�� ���� �����Ӳ���
			if(suit_map[map[i]] < suit_count[map[i]] && suit_map[map[i]] >=12)   
			{  
				suit_eff_start=([]);	   
				suit_eff_mid= suit_eff[ map[i] ];  
				map_eff_key=keys(suit_eff_mid);	
				for(j=0;j < 6;j++)
				{
					suit_eff_start += ([ map_eff_key[j] : suit_eff_mid[ map_eff_key[j] ] ]);		   
				}
				suit_eff_last += ([ map[i] : suit_eff_start ]);	
			} 
			//װ����13���ĸ���Ч�����涨Ϊ�� �߸� �����Ӳ���
			if(suit_map[map[i]] < suit_count[map[i]] && suit_map[map[i]] >=13)   
			{
				suit_eff_start=([]);
				suit_eff_mid= suit_eff[ map[i] ];  
				map_eff_key=keys(suit_eff_mid);
				for(j=0;j < 7;j++)
				{
					suit_eff_start += ([ map_eff_key[j] : suit_eff_mid[ map_eff_key[j] ] ]);		 
				}
				suit_eff_last += ([ map[i] : suit_eff_start ]);   
			}	   
		}
	}
	//-------------------------------------------------------------------------------------
   
	//���� ������װ������
	if(arg=="suit_map")
	{	
		return suit_map;	
	}
	//���� ������װ ��󲿼�������
	if(arg=="suit_count")
	{ 
		return suit_count;	
	}
	//���� ������װ�ȼ���
	if(arg=="suit_lvl")
	{
		return suit_lvl;	
	}
	//���� ������װЧ��
	if(arg=="suit_eff")
	{ 
	return suit_eff_last;	  
	}
	//���� ������װ����Ч��
	if(arg=="suit_skill")
	{ 
		return suit_skill_last;	  
	}
	if(!arg)
	{
		return suit_dis(suit_eff_last,suit_map,suit_lvl,suit_count,suit_skill_last);  
	}
 
} 
 
//Ĭ����ʾ��װ������Ч��
string suit_dis(mapping suit_eff_last,mapping suit_map,mapping suit_lvl,mapping suit_count,mapping suit_skill_last)
{
	int i,k;
	string str="";
	mixed map ;  //KEY��ͳ����װ�ļ���mapping
	mixed map_eff_dis;  //KEY�� ȡ��������װ��Ч��
	mixed map_eff_str;  //KEY�� ȥȡ���������װЧ��100
	mixed map_skill_last; //
	mixed map_skill_str;  //

	mapping suit_eff_string=([ ]);  //��ʾ��װЧ��ʱ�м丨��mapping
	mapping suit_skill_dis=([ ]); //
	if(sizeof(suit_map))
	{
		map=keys(suit_map);	 //��ֵ�� suit_map;
		for(i=0;i<sizeof(suit_map);i++)
		{  
			str+= sprintf(HIM"��"NOR"<%s>  %s\n�����ȼ���:%s \n",map[i],dis_count(suit_map[map[i]],suit_count[map[i]]),dis_lvl((int)suit_lvl[map[i]]));  
		} 
		if(sizeof(suit_eff_last))
		{
			map_eff_dis=keys(suit_eff_last);	  
			for(i=0;i < sizeof(suit_eff_last);i++)
			{	 
				suit_eff_string=suit_eff_last[map_eff_dis[i]];
				map_eff_str=keys(suit_eff_string);
				str+=HIM"��"NOR"<"+map_eff_dis[i]+"> "HIM"�� "NOR;
				for(k=0;k < sizeof(suit_eff_string);k++)
				{
					if(k==4)
					{
						str+=HIM"��"NOR"\n"+HIM+HIM"��"NOR"	 "HIM"  �� "NOR;
					}
					str+=to_chinese(map_eff_str[k])+HIG" ��"NOR+ suit_eff_string[map_eff_str[k]]+"  ";
				}
				str+=HIM"��"NOR"\n";
			}
		}
		if(sizeof(suit_skill_last))
		{
			map_skill_last=keys(suit_skill_last);
			for(i=0;i<sizeof(suit_skill_last);i++)
			{
				suit_skill_dis=suit_skill_last[map_skill_last[i]];
				map_skill_str=keys(suit_skill_dis);
				str+=HIM"��"NOR"<"+map_skill_last[i]+"> "HIC"�� "NOR;
				for(k=0;k < sizeof(suit_skill_dis);k++)
				{
					str+=to_chinese(map_skill_str[k])+HIG" ��"NOR+ suit_skill_dis[map_skill_str[k]]+" ";	
				}
				str+=HIC"��"NOR"\n";
			}
		}
		return str;
	}
	else return HIM"��"NOR" ��װ�� -----	 \n";
}

//������װ��ʾ�ȼ�
string dis_lvl(int lvl)
{
	int i;
	string lvl_solid= "��";   
	string lvl_hollow= "��" ;
	string dis_str="";
	
	if(lvl)
	{
		for(i=0;i<lvl;i++)
		{
			dis_str+=lvl_solid;
		}
		for(i=0;i < (5-lvl);i++)
		{
			dis_str+=lvl_hollow;
		}
	} 
	switch (lvl)
	{
		case 1 : dis_str=HIG+dis_str+NOR;  break;   //һ��
		case 2 : dis_str=HIB+dis_str+NOR;  break;   //����
		case 3 : dis_str=HIM+dis_str+NOR;  break;   //����
		case 4 : dis_str=HIY+dis_str+NOR;  break;   //�Ļ�
		case 5 : dis_str=HIR+dis_str+NOR;  break;   //���
	}
	return dis_str;
}
//���ż�����ʾ
string dis_count(int count,int suit_count)
{ 
	string return_dis=""; 
	int i;
	string count_dis="��";
	string suit_count_dis="��";
   
	for(i=0;i<count;i++)
	{
		return_dis+=count_dis;
	}  
	for(i=0;i<suit_count-count;i++)
	{
		return_dis+=suit_count_dis;
	}
	switch (count)
	{
		case 1 : return_dis=return_dis;  break;
		case 2 : return_dis=HIG+return_dis+NOR+HIG;  break;
		case 3 : return_dis=HIC+return_dis+NOR+HIC;  break;
		case 4 : return_dis=HIB+return_dis+NOR+HIB;  break;
		case 5 : return_dis=HIR+return_dis+NOR+HIR;  break;
		case 6 : return_dis=HIM+return_dis+NOR+HIM;  break;
		case 7 : return_dis=HIY+return_dis+NOR+HIY;  break;
		case 8 : return_dis=YEL+return_dis+NOR+YEL;  break;
	}
	return_dis+=" ��"+count+"/"+suit_count+"��";
	return return_dis;
}

//��maping�ṹ�򵥻��������в����ܽ�������
mapping sum_eff(object ob,mapping suit_eff)
{
	int i,k;
	mixed map_key;
	mixed map_str_key;
	mapping sum_suit_eff=([]);
	mapping eff=([]);
	mapping eff_str=([]);

	eff=suit_eff;
	map_key=keys(eff);
	
	for(i=0;i<sizeof(eff);i++)
	{
		eff_str=eff[map_key[i]];
		map_str_key=keys(eff_str);
		for(k=0;k<sizeof(eff_str);k++)
		{
			if( undefinedp(sum_suit_eff[map_str_key[k]]) )  
				sum_suit_eff[map_str_key[k]] = eff_str[map_str_key[k]];   //����ӽ�sum_suit_eff��
			else
				sum_suit_eff[map_str_key[k]] += eff_str[map_str_key[k]];  //���ҵ����ͺϲ�����
		}	
	}
	return sum_suit_eff;  
}