// bianfu-except.c
// by jeeny 
      
#include <ansi.h> 
      
inherit F_CLEAN_UP; 
      
int dispel(object me, object ob, int duration) 
{ 
	int n; 
 
	if (me != ob) 
	{ 
		if (me->query_skill_mapped("force") != "jiuyang-shengong")
		{
			tell_object(ob, "�㷢��" + me->name() + "������ԴԴӿ������" 
				    "���ﻹ�Ǳ��䣬���ް�����\n");
			tell_object(me, "����ͼ����" + ob->name() + "����������������" 
				    "ȴ��Ȼ��������ԴԴ���ϵش��������ɴ󾪣���" 
				    "æס�֡�\n");
			return -1;
		}
 
	} else
	if (me->query_skill_mapped("force") != "jiuyang-shengong")
	{
		tell_object(me, "����õ�����䣬�޷�����������\n");
			     
		return -1; 
	} 
      
	n = ob->query_condition("bianfu-except") -
	    (int)me->query_skill("jiuyang-shengong", 1);

	if (n < 1) 
		ob->clear_condition("bianfu-except"); 
	else 
		ob->apply_condition("bianfu-except", n); 
  
	tell_object(me, "��ĬĬ�������񹦣�����" + ob->name() + "�������ڵ�������\n"); 
   
	return 1; 
} 
   
int update_condition(object me, int duration) 
{ 
	int limit; 
  
	if (! living(me) && (me->query("eff_qi") < 20 || me->query("eff_jing") < 10)) 
	{  
		me->unconcious(); 
		return 0; 
	} else 
	{ 
		me->receive_wound("qi", 100); 
		me->receive_wound("jing", 50); 
		tell_object(me, HIW"��ֻ����һ�ɺ���Ϯ����ͷ����"
			    "��˵���������ܡ�"NOR"\n");
		message("vision", HIB + me->name() + HIB "��Ȼһ"
			"������ɫ���ֱ࣬����¡�"NOR"\n", 
		       environment(me), ({ me }));
	} 
 
	return 1; 
} 
