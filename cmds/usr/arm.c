//arm.c

#include <ansi.h>
#include <tomud.h>
#include <combat.h>
inherit F_CLEAN_UP;

string name_temp(object ob,string type);

int main(object me, string arg)
{
	int i;
	object ob;
	mapping prepare;
	int attack_points, dodge_points, parry_points,islook;
	object weapon,second_weapon;
	string line,tmp,wp1,wp2,skill_type;

	if (arg)
	{
		ob = find_player(arg);
		if (! ob) ob = find_living(arg);
		if (! ob) ob = present(arg, environment(me));
		if (! wizardp(me) && (! ob || me->query("couple/child") != ob->query("id"))) 
		{
		      islook=0;   //������ʦ���Ӳ��ܿ����幥��������ֵ
		}
		else
		{
		      islook=1;       //���Բ鿴ȫ����ֵ
		}
		if(!ob)
		{
		     return notify_fail("��Ҫ�쿴˭��װ����\n"); 
		}
	}
	if (! ob)
	{
		ob = me;
	      islook=1;       //���Բ鿴ȫ����ֵ
	}
	if( ob==me && me->is_ghost() ) 
		return notify_fail("��Щ����֮�����������������ȥ���������˰ɣ�\n");

	line="";
	tmp=ZJOBACTS2+ZJMENUF(2,2,10,30);
	wp1="��:null"ZJSEP;
	wp2="��:null"ZJSEP;

	weapon= ob->query_temp("weapon");
	second_weapon= ob->query_temp("secondary_weapon");
	if(weapon)
	{ 
		wp1=weapon->query("name")+":look "+file_name(weapon)+ZJSEP;
	}
	if(second_weapon)
	{
		  wp2=second_weapon->query("name")+":look "+file_name(weapon);
	}

	line += HIY+" ["+ob->query("name")+"] װ����������Ʒ��      "NOR"\n";		    
	line += sprintf(HIY"һһһһһһһһһһһһһһһһһһһһһһһ"NOR"\n");  
	//line += ob->suit(ob);   //��װ��Ϣ   
	//line += sprintf(HIY"һһһһһһһһһһһһһһһһһһһһһһһ"NOR"\n");
	if(islook)
	{
		prepare = me->query_skill_prepare();
		if( objectp(weapon = ob->query_temp("weapon")) )
			skill_type = weapon->query("skill_type");
		else if (prepare&&sizeof(prepare)>0)  skill_type = (keys(prepare))[0];
		else 
			skill_type = "unarmed";

		attack_points = COMBAT_D->skill_power(ob, skill_type, SKILL_USAGE_ATTACK);
		parry_points = COMBAT_D->skill_power(ob, skill_type, SKILL_USAGE_DEFENSE);
		dodge_points = COMBAT_D->skill_power(ob, "dodge", SKILL_USAGE_DEFENSE);
		line += sprintf("�� ս���������� " HIW "%8d  "NOR" ս���������� " HIW "%8d "NOR"\n",
		attack_points  + 1, (dodge_points + (weapon? parry_points: (parry_points/10)))  + 1);
		if(weapon)
			line += sprintf("�� �����˺����� " HIC "%8d  "NOR" װ���������� "HIC"%8d"NOR"\n", ob->query_temp("apply/damage"),(ob->query_temp("apply/armor")+ob->query_temp("apply/armor1")) );
		else
			line += sprintf("�� �����˺����� " HIC "%8d  "NOR" װ���������� "HIC"%8d"NOR"\n", ob->query_temp("apply/unarmed_damage"),(ob->query_temp("apply/armor")+ob->query_temp("apply/armor1")) );
		line += sprintf("�� ���������˺��� " HIC "%8d  "NOR"\n", ob->query_gain_damage() );
		line += sprintf(HIY"һһһһһһһһһһһһһһһһһһһһһһһ"NOR);  
	} 
	// ��������ɫ��������(���ɫ��Ų��ᱻ���ȥ�����ҵ�)
	tmp += "��������:wear all"ZJSEP"��������:remove all"ZJSEP;
	tmp += sprintf("[ͷ��]��%s[����]��%s",name_temp(ob,"armor/head"), wp1);
	tmp += sprintf("[����]��%s[����]��%s", name_temp(ob,"armor/armor"), wp2);
	tmp += sprintf("[�·�]��%s[�ֲ�]��%s", name_temp(ob,"armor/cloth"), name_temp(ob,"armor/hands"));
	tmp += sprintf("[����]��%s[����]��%s",name_temp(ob,"armor/waist"), name_temp(ob,"armor/wrists"));
	tmp += sprintf("[����]��%s[��ָ]��%s", name_temp(ob,"armor/pants"),name_temp(ob,"armor/finger"));
	tmp += sprintf("[Ь��]��%s[����]��%s",name_temp(ob,"armor/boots"), name_temp(ob,"armor/shield"));
	line = replace_string(line,"\n",ZJBR)+"\n";
	line += tmp;	
	write(ZJOBLONG+line+"\n");
 
	return 1;
}
string name_temp(object ob,string type)
{
	string name;
	object obj;
	if( objectp(obj=ob->query_temp(type)) ) 
	{
		name = obj->query("name")+":"+file_name(obj)+ZJSEP;
	}
	else
	{
		name = "��:null"ZJSEP;
	}
	return name;
}

int help (object me)
{
	write(@HELP
ָ���ʽ: arm
 
���г���(��)Ŀǰ������Я����������Ʒ��
 
 
HELP );
	return 1;
}