// bianfu-bu.c �ϻ�����
// by jeeny
 
#include <ansi.h> 
      
inherit SKILL; 
	
string *dodge_msg = ({ 
	"����$n���м��٣�$N��һ�в��˳���\n", 
	"ȴ��$n����΢�Σ���������֮�⡣\n", 
	"$n�����㣬�����ܿ���$N��һ�С�\n", 
	"$n�߸߰����ڿ�����ת��Ȧ�����������ɿ��⡣\n", 
	"$n����ת�����𾢷磬�Ƶ�$N�޷�����\n", 
	"$N��һ���ۿ���Ҫ���У�����$n��һ�����ܹ�$N�ľ�����ʵ��������˼��\n", 
	"$n���˷�������$N���������ǡǡ�ܿ���һ�С�\n", 
}); 
       
int valid_enable(string usage)  
{  
	return usage == "dodge"; 
} 
       
int valid_learn(object me) 
{ 
	int lvl; 
       
	lvl = me->query_skill("bianfu-bu", 1); 
	if (lvl > 300) lvl = 300; 
       
	if (me->query("max_neili") < 2000 + lvl * 10) 
		return notify_fail("���������Ϊ��Ƿ���\n");
 
	if (me->query("dex") < 26)
		return notify_fail("�����ʲ���,ѧ������"
				   "�˸�����Ṧ��\n");
	if ((me->query("str") + me->query("relife/zhuanshi"))> 25)
		return notify_fail("��ʵ��̫���أ��޷�ѧϰ�����ӯ�Ĳ�����\n"); 
	if ((me->query("static/sadly")-me->query("relife/zhuanshi")) > 2)
		return notify_fail("��ֻ������һ��������Ϯ��������������𲽷���ˮƽ��\n");   

	return 1; 
} 
       
string query_dodge_msg(string limb) 
{ 
	return dodge_msg[random(sizeof(dodge_msg))]; 
} 
       
mixed valid_damage(object ob, object me, int damage, object weapon) 
{ 
	mixed result; 
	int ap, dp; 
       
	if ((int)me->query_skill("bianfu-bu", 1) < 100 || 
	    ! living(me)) 
		return; 
	
	ap = ob->query_skill("dodge") * 4 / 3; 
	dp = me->query_skill("dodge", 1) / 2 + me->query_skill("bianfu-bu", 1); 
       
	if (ap / 2 + random(ap) < dp) 
	{ 
		result = ([ "damage": -damage ]); 
       
		switch (random(4)) 
		{ 
		case 0: 
			result += (["msg" : HIW "����$n" HIW "��¶΢Ц������һ�죬$N" 
					    HIW "ֻ����ǰһ�����ƺ�������ǧ�ٸ�$n��" 
					    HIW "��Ӱ��"NOR"\n"]); 
			break; 
		case 1: 
			result += (["msg" : HIW "$N" HIW "ֻ����ǰһ����Ӱ��һ��һ�Σ�"
					    HIW "��ʱ������$n����Ӱ��"NOR"\n"]); 
			break; 
		case 2: 
			result += (["msg" : HIW "$N" HIW "��һ��Ѹ���ޱȣ�Ȼ��$n" 
					    HIW "����һŤ���ƺ����Ѱ��������ȴ��" 
					    HIW "$N��һ�ж��˿�ȥ��"NOR"\n"]); 
			break; 
		default: 
			result += (["msg" : HIW "����$n" HIW "����һ������󵹷ɳ�ȥ��$N" 
					    HIW "�����͹���ȴ�ּ�$n" HIW "һ��ɲ������ת" 
					    "$N��󣬵������˷�����˼��"NOR"\n"]); 
			break; 
		} 
		return result; 
	}
 
} 
      
int query_effect_dodge(object attacker, object me) 
{ 
	int lvl; 
      
	lvl = me->query_skill("bianfu-bu", 1); 
	if (lvl < 50)  return 0; 
	if (lvl < 100) return 40; 
	if (lvl < 150) return 60; 
	if (lvl < 200) return 90; 
	if (lvl < 250) return 110; 
	if (lvl < 300) return 130; 
	if (lvl < 350) return 150; 
	return 160; 
} 
      
int practice_skill(object me) 
{ 
	int cost;

	cost = 60 + (int) me->query_skill("bianfu-bu", 1) / 3;
	if ((int)me->query("qi") < 70) 
		return notify_fail("�������̫���ˣ�������ϰ�ϻ����𲽡�\n"); 
     
	if ((int)me->query("neili") < cost) 
		return notify_fail("������������ˣ��޷���ϰ�ϻ����𲽡�\n"); 
      
	me->receive_damage("qi", 50); 
	me->add("neili", -cost); 
	return 1; 
} 
      
string perform_action_file(string action) 
{ 
	return __DIR__"bianfu-bu/" + action; 
} 

void skill_improved(object me)
{
	int lvl;
	lvl = me->query_skill("bianfu-bu", 1);

	if (lvl < 200)
	{
		me->apply_condition("bianfu-except", lvl / 2 +
				    (int)me->query_condition("bianfu-except"));
	}
}	     
