// kuihua-shengong ����ħ��

inherit FORCE;

string *dodge_msg = ({
	"$n΢΢һ������ȻԶȥ��ʹ$N�Ľ���ȫȻ���á�\n",
	"$n��ʱ��ƽ����������������ȣ�ʹ$NȫȻ�޷����ա�\n",
	"$n����һ�ˣ���ȥ�����κ�׷����\n",
	"$n�㲻��أ���֫�Ͱڣ���Ȼ��$N�Ľ���ȫ�������\n",
});

int query_neili_improve(object me)
{
	int lvl;

	lvl = (int)me->query_skill("kuihua-mogong", 1);
	return lvl * lvl * 20 * 15 / 100 / 200;
}

mapping *actionf = ({
([      "action":"$Nٿ�Ľ�ǰ�����ο켫����ָ����$n��$l",
	"force" : 410,
	"attack": 172,
	"dodge" : 120,
	"parry" : 60,
	"damage": 150,
	"damage_type":  "����"
]),
([      "action":"$N����ǰ����������ͬ���ȣ���������׽������ָ���Ĵ���$n��$l",
	"force" : 410,
	"attack": 180,
	"dodge" : 90,
	"parry" : 70,
	"damage": 160,
	"damage_type":  "����"
]),
([      "action":"$N����һת����ָ�̳���ֱָ$n��$l",
	"force" : 430,
	"attack": 175,
	"dodge" : 90,
	"parry" : 50,
	"damage": 170,
	"damage_type":  "����"
]),
([      "action":"$NƮȻԶȥ�����ֽ�ǰ���ٶȿ�Ĳ���˼�飬һָ����������$n��$l",
	"force" : 425,
	"attack": 180,
	"dodge" : 85,
	"parry" : 65,
	"damage": 150,
	"damage_type":  "����"
]),
([      "action":"$N����һ�Σ�ͻȻ����һ�ţ�����$n��$l",
	"force" : 430,
	"attack": 170,
	"dodge" : 90,
	"parry" : 55,
	"damage": 160,
	"damage_type":  "����"
]),
([      "action":"$N���¼��ߣ����α��Ī�⣬ͻȻһָ����$n��$l",
	"force" : 440,
	"attack": 185,
	"dodge" : 115,
	"parry" : 55,
	"damage": 180,
	"damage_type":  "����"
]),
});

mapping *actionw = ({
([      "action":"$Nٿ�Ľ�ǰ�����ο켫�����е�$w����$n��$l",
	"force" : 330,
	"attack": 200,
	"dodge" : 130,
	"parry" : 40,
	"damage": 160,
	"damage_type":  "����"
]),
([      "action":"$N����ǰ����������ͬ���ȣ���������׽�������е�$w���Ĵ���$n��$l",
	"force" : 330,
	"attack": 185,
	"dodge" : 120,
	"parry" : 45,
	"damage": 190,
	"damage_type":  "����"
]),
([      "action":"$N����һת��$w�̳���ֱָ$n��$l",
	"force" : 355,
	"attack": 210,
	"dodge" : 120,
	"parry" : 45,
	"damage": 200,
	"damage_type":  "����"
]),
([      "action":"$NƮȻԶȥ�����ֽ�ǰ���ٶȿ�Ĳ���˼�飬$w����������$n��$l",
	"force" : 345,
	"attack": 190,
	"dodge" : 135,
	"parry" : 55,
	"damage": 180,
	"damage_type":  "����"
]),
([      "action":"$N����һ�Σ�ͻȻ����һ������$n��������������ջأ�����$w����$n��$l",
	"force" : 360,
	"attack": 180,
	"dodge" : 120,
	"parry" : 57,
	"damage": 210,
	"damage_type":  "����"
]),
([      "action":"$N���¼��ߣ����α��Ī�⣬ͻȻһ���֣�$w��Ҳ�ƵĲ���$n��$l",
	"force" : 340,
	"attack": 200,
	"dodge" : 135,
	"parry" : 50,
	"damage": 190,
	"damage_type":  "����"
]),
});

string *usage_skills = ({ "sword", "dodge",
			  "parry", "force" });

int valid_enable(string usage)
{
	return (member_array(usage, usage_skills) != -1) ||
	       usage == "unarmed" || usage == "finger";
}

int valid_combo(string combo)
{
	return combo == "kuihua-mogong";
}

int valid_force(string force) { return 1; }

int double_attack() { return 1; }

mapping query_action(object me, object weapon)
{
	return weapon ? actionw[random(sizeof(actionw))] :
			actionf[random(sizeof(actionw))];
}

string query_dodge_msg(string limb)
{
	return dodge_msg[random(sizeof(dodge_msg))];
}

int valid_learn(object me)
{
	int level;
	int i;

	if ((int)me->query("combat_exp") < 3000000 && !me->query("relife/zhuanshi"))
		return notify_fail("����ÿ���ħ�����֮����"
				   "ƾ�Լ���ս������һʱ��������ᡣ\n");

	if ((int)me->query_skill("martial-cognize", 1) < 50)
		return notify_fail("����ÿ���ħ���������֮������"
				   "�Լ�����ѧ����ȫȻ�޷����ס�\n");

	if (me->query("character") != "���ռ�թ")
		return notify_fail("�㿴�˿���ħ����Щ���ն������书����"
				   "�ɵ��ľ�������������ᡣ\n");

	if (me->query("dex") < 22 && me->query_dex() < 63)
		return notify_fail("������Լ��������У�������������ôƮ�"
				   "����Ŀ���ħ����\n");

	level = me->query_skill("kuihua-mogong", 1);

	if ((int)me->query_skill("martial-cognize", 1) < 300 &&
	    (int)me->query_skill("martial-cognize", 1) < level && !me->query("relife/zhuanshi"))
		return notify_fail("������Լ�����ѧ�������ޣ�������������Ŀ���ħ����\n");

	for (i = 0; i < sizeof(usage_skills); i++)
		if (me->query_skill(usage_skills[i], 1) < level)
			return notify_fail("���" + to_chinese(usage_skills[i]) +
					   "����⻹�������޷�������������Ŀ���ħ����\n");

	if (me->query_skill("finger", 1) < level &&
	    me->query_skill("unarmed", 1) < level)
		return notify_fail("����Ҫ�����߾����ָ����ȭ�Ź�����ܼ����о�����ħ����\n");

	return 1;
}

int practice_skill(object me)
{
	return notify_fail("����ħ��������޷��򵥵�ͨ����ϰ������\n");
}

int difficult_level()
{
     object me; 
     int lv;
     me = this_player(); 
     lv = me->query_skill("pixie-jian", 1) - 180; 
     if (lv > 100) lv = 100; 
     
     if (! me->query("special_skill/ghost"))
	return 1000;
     else
	return 500 - lv;
}

string perform_action_file(string action)
{
	return __DIR__"kuihua-mogong/perform/" + action;
}

string exert_function_file(string action)
{
	return __DIR__"kuihua-mogong/exert/" + action;
}

