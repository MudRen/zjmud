// pixie-jian.c ��а����
// Jay 4/5/96
// modified by Venus Oct.1997
// updated by Doing Lu 4/11/2000
inherit FORCE;
#include <ansi.h>

string *dodge_msg = ({
    "ͻȻ֮�䣬��Ӱ���ϣ�$n��󻬳����࣬��ʱ�ֻص���ԭ�أ������$N��һ�С�\n",
    "$n�ֱۻ�ת����$N������һ�ƣ�˳������һ�ԡ�\n",
    "$n�����������$N������Ѹ���ޱȵ�һ����˳������һ�ԡ�\n",
    "$n����Ʈ����������ȣ�ת�˼�ת���Ʋ���$N����󣬶����$N��һ�С�\n",
    "$Nֻ����ǰһ�����ƺ�����$n����һ�ϣ����漴�ּ�$n�ص�ԭ�أ�ȴ�ƴ�δ�뿪��\n",
    "$N�۾�һ����$n��û����Ӱ��ͻȻ$n���������һ��$N��ͷ������Ծ����\n",
    "$n��ȻһЦ������֮����$N����֪����Ǻã�ͣס�˹�����\n",
});

mapping *weapon_action = ({
([  "action":"ͻȻ֮�䣬��Ӱ���ϣ�$N��󻬳����࣬��ʱ�ֻص���ԭ��",
    "force" : 100,
    "attack": 40,
    "parry" : 20,
    "dodge" : 70,
    "damage": 50,
    "lvl" : 0,
    "skill_name" : "��Ӱ����",
    "damage_type":  "����"
]),
([  "action":"$N�����������$n������Ѹ���ޱȵ�һ����$n��Щ�����Լ�С��",    
    "force" : 120,
    "attack": 50,
    "parry" : 30,
    "dodge" : 65,
    "damage": 60,
    "lvl" : 12,
    "skill_name" : "�Լ�С��",
    "damage_type":  "����"
]),
([  "action":"�����$N�����ϣ��ڵ�$n�������Ծ��ԭ��",
    "force" : 125,
    "attack": 60,
    "parry" : 35,
    "dodge" : 85,
    "damage": 70,
    "lvl" : 25,
    "skill_name" : "������",
    "damage_type":  "����"
]),
([  "action":"$NͻȻ���з�һ�䣬$w�����������ʽ������ס�$n����֮�з������",
    "force" : 130,
    "attack": 70,
    "parry" : 40,
    "dodge" : 60,
    "damage": 80,
    "lvl" : 5,
    "skill_name" : "�з�һ��",
    "damage_type":  "����"
]),
([  "action":"$N����Ʈ����������ȣ�ת�˼�ת���Ʋ���$n�����",
    "force" : 140,
    "attack": 80,
    "parry" : 50,
    "dodge" : 70,
    "damage": 100,
    "lvl" : 35,
    "skill_name" : "�������",
    "damage_type":  "����"
]),
([  "action":"$Nһ����Ц������Ｒ����ǰ��һ˲֮�䣬��$n����Ѳ���һ�ߣ�$w�漴�ݳ�",
    "force" : 160,
    "attack": 70,
    "parry" : 40,
    "dodge" : 65,
    "damage": 120,
    "lvl" : 45,
    "skill_name" : "������ǰ",
    "damage_type":  "����"
]),
([  "action":"$N�ȵ������ã������㼴�γ�$w�����ִ̳�������ת����ȥ",
    "force" : 200,
    "attack": 90,
    "parry" : 45,
    "dodge" : 80,
    "damage": 130,
    "lvl" : 55,
    "skill_name" : "���ִ̳�",
    "damage_type":  "����"
]),
([  "action":"$nֻ����ǰһ�����ƺ�����$N����һ�ϣ����漴�ּ�$N�ص�ԭ�أ�ȴ�ƴ�δ�뿪",
    "force" : 190,
    "attack": 80,
    "parry" : 40,
    "dodge" : 85,
    "damage": 150,
    "lvl" : 65,
    "skill_name" : "��ǰһ��",
    "damage_type":  "����"
]),
([  "action":"$N����ˣ�$n��׷������ͻȻ��$N����$n��ǰ������$wֱָ$n��$l",
    "force" : 180,
    "attack": 100,
    "parry" : 50,
    "dodge" : 70,
    "damage": 160,
    "lvl" : 75,
    "skill_name" : "�����",
    "damage_type":  "����"
]),
([  "action":"$N��س嵽$n��ǰ������$wֱ��$n���ۣ�$n��æ�мܣ�����$N��$wͻȻת��",
    "force" : 250,
    "attack": 130,
    "parry" : 55,
    "dodge" : 74,
    "damage": 180,
    "lvl" : 85,
    "skill_name" : "ֱ������",
    "damage_type":  "����"
]),
([  "action":"$N����Ծ��$ņ��һ����������$N����ֱ����£�����$w����$n��$l",
    "force" : 340,
    "attack": 130,
    "parry" : 50,
    "dodge" : 80,
    "damage": 190,
    "lvl" : 94,
    "skill_name" : "����Ծ��",
    "damage_type":  "����"
]),
([  "action":"$N��֦�Ͱڣ�$n��ǰ�·�ͻȻ�������߰˸�$N���߰�ֻ$wһ�����$n",
    "force" : 400,
    "attack": 140,
    "parry" : 60,
    "dodge" : 110,
    "damage": 210,
    "lvl" : 120,
    "skill_name" : "��֦�Ͱ�",
    "damage_type":  "����"
]),
});

mapping *unarmed_action = ({
([  "action":"ͻȻ֮�䣬��Ӱ���ϣ�$N��󻬳����࣬��ʱ�ֻص���ԭ��",
    "force" : 100,
    "attack": 40,
    "parry" : 20,
    "dodge" : 70,
    "damage": 40,
    "lvl" : 0,
    "skill_name" : "��Ӱ����",
    "damage_type":  "����"
]),
([  "action":"$N�����������$n������Ѹ���ޱȵ�һ����$n��Щ�����Լ�С��",    
    "force" : 120,
    "attack": 50,
    "parry" : 30,
    "dodge" : 65,
    "damage": 50,
    "lvl" : 12,
    "skill_name" : "�Լ�С��",
    "damage_type":  "����"
]),
([  "action":"�����$N�����ϣ��ڵ�$n�������Ծ��ԭ��",
    "force" : 125,
    "attack": 60,
    "parry" : 35,
    "dodge" : 85,
    "damage": 60,
    "lvl" : 25,
    "skill_name" : "������",
    "damage_type":  "����"
]),
([  "action":"$NͻȻ���з�һ�䣬�ֱۺ����������ʽ������ס�$n����֮�з������",
    "force" : 130,
    "attack": 70,
    "parry" : 40,
    "dodge" : 60,
    "damage": 70,
    "lvl" : 5,
    "skill_name" : "�з�һ��",
    "damage_type":  "����"
]),
([  "action":"$N����Ʈ����������ȣ�ת�˼�ת���Ʋ���$n�����",
    "force" : 140,
    "attack": 80,
    "parry" : 50,
    "dodge" : 70,
    "damage": 80,
    "lvl" : 35,
    "skill_name" : "�������",
    "damage_type":  "����"
]),
([  "action":"$Nһ����Ц������Ｒ����ǰ��һ˲֮�䣬��$n����Ѳ���һ�ߣ���ָ�漴�̳�",
    "force" : 160,
    "attack": 70,
    "parry" : 40,
    "dodge" : 65,
    "damage": 90,
    "lvl" : 45,
    "skill_name" : "������ǰ",
    "damage_type":  "����"
]),
([  "action":"$N�ȵ������ã������㼴���ִ̳�һָ������ת����ȥ",
    "force" : 200,
    "attack": 90,
    "parry" : 45,
    "dodge" : 80,
    "damage": 100,
    "lvl" : 55,
    "skill_name" : "���ִ̳�",
    "damage_type":  "����"
]),
([  "action":"$nֻ����ǰһ�����ƺ�����$N����һ�ϣ����漴�ּ�$N�ص�ԭ�أ�ȴ�ƴ�δ�뿪",
    "force" : 190,
    "attack": 80,
    "parry" : 40,
    "dodge" : 85,
    "damage": 120,
    "lvl" : 65,
    "skill_name" : "��ǰһ��",
    "damage_type":  "����"
]),
([  "action":"$N����ˣ�$n��׷������ͻȻ��$N����$n��ǰ�����ƺ�������$n��$l",
    "force" : 180,
    "attack": 100,
    "parry" : 50,
    "dodge" : 70,
    "damage": 130,
    "lvl" : 75,
    "skill_name" : "�����",
    "damage_type":  "����"
]),
([  "action":"$N��س嵽$n��ǰ��ָ��ֱ��$n���ۣ�$n��æ�мܣ�����$N������ͻȻת��",
    "force" : 250,
    "attack": 130,
    "parry" : 55,
    "dodge" : 74,
    "damage": 160,
    "lvl" : 85,
    "skill_name" : "ֱ������",
    "damage_type":  "����"
]),
([  "action":"$N����Ծ��$ņ��һ����������$N����ֱ����£����ƿ���$n��$l",
    "force" : 340,
    "attack": 130,
    "parry" : 50,
    "dodge" : 80,
    "damage": 180,
    "lvl" : 94,
    "skill_name" : "����Ծ��",
    "damage_type":  "����"
]),
([  "action":"$N��֦�Ͱڣ�$n��ǰ�·�ͻȻ�������߰˸�$N���߰�ֻ����һ������$n",
    "force" : 400,
    "attack": 140,
    "parry" : 60,
    "dodge" : 110,
    "damage": 200,
    "lvl" : 120,
    "skill_name" : "��֦�Ͱ�",
    "damage_type":  "����"
]),
});

int valid_enable(string usage)
{
    	return usage == "sword" ||
	       usage == "dodge" ||
	       usage == "parry" ||
	       usage == "force" ||
	       usage == "unarmed";
}

int valid_force(string force)
{
	return force == "kuihua-mogong";
}

int double_attack() { return 1; }

int query_neili_improve(object me)
{
	int lvl;

	lvl = (int)me->query_skill("pixie-jian", 1);
	if (me->query("special_skill/ghost"))
		return lvl * lvl * 20 * 15 / 100 / 200;
	else
		return lvl * lvl * 17 * 15 / 100 / 200;
}

string query_skill_name(int level)
{
    	int i;
    	for (i = sizeof(weapon_action) - 1; i >= 0; i--)
    		if (level >= weapon_action[i]["lvl"])
       			return weapon_action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
	int i, level, index, lv_kuihua;
	mapping *action;

	if (objectp(weapon))
		action = weapon_action;
	else
		action = unarmed_action;

	level = (int) me->query_skill("pixie-jian", 1);
	lv_kuihua = (int) me->query_skill("kuihua-mogong", 1);
	for (i = sizeof(action); i > 0; i--)
		if (level > action[i-1]["lvl"])
		{
			index = NewRandom(i, 20, level/5);
			break;
		}

	if (! me->query("special_skill/ghost"))
		return action[index];

	return ([  "action"  : action[index]["action"],
		   "force"   : action[index]["force"] +  lv_kuihua / 4,
		   "attack"  : action[index]["attack"] + lv_kuihua / 6,
		   "parry"   : action[index]["parry"] +  lv_kuihua / 7,
		   "dodge"   : action[index]["dodge"] +  lv_kuihua / 7,
		   "damage"  : action[index]["damage"] + lv_kuihua / 4,
		   "skill_name"   : action[index]["skill_name"],
		   "damage_type"  : action[index]["damage_type"],
	       ]);	    
}

string query_dodge_msg(string limb)
{
    	return dodge_msg[random(sizeof(dodge_msg))];
}

int valid_learn(object me)
{
	if (me->query("gender") == "Ů��")
		return notify_fail("�Թ�����û��˵��Ů�˿�����ϰ�������䡣\n");

	if (me->query("gender") == "����")
		return notify_fail("�������Ϣ��Ȼ���ң���������\n");

	return 1;
}

mixed valid_damage(object ob, object me, int damage, object weapon) 
{ 
	mixed result; 
	int ap, dp, mp, ratio; 
       
	if ((int)me->query_skill("pixie-jian", 1) < 100 || 
	    ! me->query("special_skill/ghost") ||
	    ! me->query_temp("dodge_valid_damage") ||
	    me->query_skill_mapped("force") != "pixie-jian" ||
	    me->query_skill_mapped("parry") != "pixie-jian" ||
	    me->query_skill_mapped("dodge") != "pixie-jian" ||
	    ! living(me)) 
		return; 
	
	mp = ob->query_skill("count", 1);
	if (sizeof(ob->query_skill_prepare()) 
          && ob->query_skill_prepared("unarmed") == "taixuan-gong"
          && !me->query_temp("weapon")
          && ob->query_skill_mapped("unarmed") == "taixuan-gong") 
                 mp += ob->query_skill("taixuan-gong", 1)/2;
	ap = ob->query_skill("dodge", 1) * 3 / 2 + mp; 
	dp = me->query_skill("dodge", 1) / 2 + 
	     me->query_skill("pixie-jian", 1); 
	     
	// ���ʣ��Լ����� dex �ߡ�str �ͣ��Է����� str �ߣ�dex �ͣ�����ǿ     
	ratio = me->query("dex") - ob->query("dex");
		
	dp = dp * (100 + ratio + 10) / 100;
	       
	if (ap / 2 + random(ap) < dp)
	{
		result = ([ "damage": -damage ]);

		switch (random(6))
		{
		case 0:
			result += (["msg" : HIR "$N" HIR "�۾�һ����$n" HIR "��û����"
					    "Ӱ��ͻȻ$n" HIR "���������һ��$N" HIR "��"
					    "ͷ������Ծ����"NOR"\n"]);
			break;
		case 1:
			result += (["msg" : HIR "$N" HIR "��ǰһ�����ƺ�����$n" HIR "��"
					    "��һ�Σ����漴�ּ�$n" HIR "�ص�ԭ�أ�ȴ��"
					    "��δ�뿪��"NOR"\n"]);
			break;
		case 2:
			result += (["msg" : HIR "$n" HIR "����Ʈ����������ȣ�ת�˼�ת"
					    "���Ʋ���$N" HIR "����󣬶����$N" HIR "��"
					    "һ�С�"NOR"\n"]);
			break;
		case 3:
			result += (["msg" : HIR "$n" HIR "��ȻһЦ������֮����$N" 
					    HIR "����֪����Ǻã�ͣס�˹�����"NOR"\n"]);
			break;
		case 4:
			result += (["msg" : HIR "$n" HIR "�����������$N" HIR "������"
					    "Ѹ���ޱȵ�һ����˳������һ�ԡ�"NOR"\n"]);
			break;			
		default:
			result += (["msg" : HIR "ͻȻ֮���Ӱ���Σ�$n" HIR "��󻬳���"
					    "�࣬��ʱ�ֻص���ԭ�أ������$N" HIR "��һ"
					    "�С�"NOR"\n"]);
			break;
		}
		return result;
	} else
	if (mp >= 100)
	{
		switch (random(4))
		{
		case 0:
			result = HIY "$N" HIY "�۾�һ����$n" HIY "��û����Ӱ"
				 "������$N" HIY "��ͨ����˿����Ϊ���ң�����"
				 "���С�"NOR"\n";
			break;
		case 1:
			result = HIY "$N" HIY "��ǰһ�����ƺ�����$n" HIY "��"
				 "��һ�Ρ�$N" HIY "һ����Ц����˲�俴��������"
				 "ʵ��"NOR"\n";
			break;
		case 2:
			result = HIY "$n" HIY "����Ʈ����������ȣ�ת�˼�ת��"
				 "����$N" HIY "��Ҳ�����������о�ֱ������"NOR"\n";
			break;
		default:
			result = HIY "ͻȻ���Ӱ���Σ�$n" HIY "��󻬳����࣬"
				 "����$N" HIY "����˼����׷���ϣ�����������"
				 "����"NOR"\n";
			break;
		}
		COMBAT_D->set_bhinfo(result);
	} 
} 

int query_effect_dodge(object attacker, object me)
{
	int lvl;
	
	if (! me->query("special_skill/ghost"))
		return 0;

	lvl = me->query_skill("pixie-jian", 1);
	if (lvl < 50)  return 0;
	if (lvl < 100) return 30;
	if (lvl < 150) return 40;
	if (lvl < 200) return 60;
	if (lvl < 250) return 80;
	if (lvl < 300) return 100;
	if (lvl < 350) return 120;
	return 130;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
	if (random(10) >= 5  && me->query("special_skill/ghost"))
	{
		if (random(3))
		{
			victim->receive_wound("qi", damage_bonus / 4, me);
			return HIR "ֻ��" + victim->name() +
			       HIR "�������������������ط�����Ѫ˿��"NOR"\n";
		}
		else
		{
			victim->receive_wound("qi", damage_bonus / 3, me);
			victim->receive_wound("jing", damage_bonus / 4, me);
			return HIR "ֻ��" + victim->name() +
			       HIR "�����㱣���Ѫ����������Ѩλ������"NOR"\n";
		}
	}
}

int practice_skill(object me)
{
    	return notify_fail("��а����ֻ��ͨ����ϰ����а���ס��򡶿���"
			   "���䡷��ѧϰ��\n");
}

string perform_action_file(string action)
{
    	return __DIR__"pixie-jian/perform/" + action;
}

int difficult_level()
{
     object me; 
     int lv;
     me = this_player(); 
     lv = me->query_skill("pixie-jian", 1) - 180; 
     if (lv > 200) lv = 200; 
     
     if (! me->query("special_skill/ghost"))
	return 1000;
     else
	return 500 - lv;

}

string exert_function_file(string action)
{
	return __DIR__"pixie-jian/exert/" + action;
}
