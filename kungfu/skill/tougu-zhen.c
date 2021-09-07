inherit SKILL;

mapping *action = ({
([      "action" : "$N���ھ���סָ�⣬Я����˿˿����һ���������$n��$l",
	"force" : 140,
	"attack": 25,
	"dodge" : 15,
	"parry" : 15,
	"damage": 10,
	"lvl"   : 0,
	"skill_name" : "˿˿����",
	"damage_type" : "����"
]),
([      "action" : "$N������ľ������Ծ���������ʳָ���ż���֮��ֱ��$n��$l",
	"force" : 180,
	"attack": 40,
	"dodge" : 20,
	"parry" : 15,
	"damage": 25,
	"lvl"   : 30,
	"skill_name" : "����֮��",
	"damage_type" : "����"
]),
([      "action" : "$N�ֽ�һ�������ڰ�շ��������Ҫ����֮ʱ��ͻȻ��׼$n��$l����쬡���һָ���",
	"force" : 220,
	"attack": 50,
	"dodge" : 20,
	"parry" : 25,
	"damage": 38,
	"lvl"   : 60,
	"skill_name" : "һָ���",
	"damage_type" : "����"
]),
([      "action" : "$N�������ߣ���¶��ɫ����$n����͵Ķ�׼$n$lһָ�����$n��Ҫ�ص���ȴ��"
		   "\n�ִ����������У�$N������һָ�ѵ���$n�ĺ���",
	"force" : 280,
	"attack": 80,
	"dodge" : 80,
	"parry" : 60,
	"damage": 55,
	"lvl"   : 80,
	"skill_name" : "��������",
	"damage_type" : "����"
]),
([      "action" : "$N��������ߣ��͵��ֱ���$n��ǰ������ʳָ������������$n��$l",
	"force" : 360,
	"attack": 140,
	"dodge" : 45,
	"parry" : 40,
	"damage": 80,
	"lvl"   : 100,
	"skill_name" : "������ԭ",
	"damage_type" : "����"
]),
});

int valid_enable(string usage) { return usage=="finger" || usage=="parry"; }

int valid_combine(string combo) { return combo=="yinfeng-dao"; }

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("��͸���������֡�\n");

	if ((int)me->query_skill("force") < 200)
		return notify_fail("����ڹ���򲻹����޷���ϰ͸���롣\n");

	if ((int)me->query("max_neili") < 1400)
		return notify_fail("�������̫�����޷���ϰ͸���롣\n");

	if ((int)me->query_skill("finger", 1) < 100)
		return notify_fail("��Ļ���ָ����򲻹����޷���ϰ͸���롣\n");

	if ((int)me->query_skill("finger", 1) < (int)me->query_skill("tougu-zhen", 1))
		return notify_fail("��Ļ���ָ��ˮƽ���ޣ��޷����������͸���롣\n");

	return 1;
}

string query_skill_name(int level)
{
	int i;
	for(i = sizeof(action)-1; i >= 0; i--)
		if(level >= action[i]["lvl"])
			return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
	int i, level;
	level   = (int) me->query_skill("tougu-zhen",1);
	for(i = sizeof(action); i > 0; i--)
		if(level > action[i-1]["lvl"])
			return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
	if ((int)me->query("qi") < 100)
		return notify_fail("�������̫���ˡ�\n");

	if ((int)me->query("neili") < 100)
		return notify_fail("�������������͸���롣\n");

	me->receive_damage("qi", 80);
	me->add("neili", -80);
	return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
	int lvl;
	int flvl;

	lvl  = me->query_skill("tougu-zhen", 1);
	flvl = me->query("jiali");
	if (lvl < 80 || flvl < 10 || ! damage_bonus)
		return;

	if (flvl * 2 + random(lvl) > victim->query_skill("force") &&
	    victim->affect_by("tougu_zhen",
			      ([ "level" : flvl + random(flvl),
				 "id"    : me->query("id"),
				 "duration" : lvl / 100 + random(lvl / 10) ])))
	{
		return "$nֻ�е����˿ڴ�����һ���й�֮ʹ�����������˶Է�͸�����ھ��ĸ��š�\n";
	}
}

string perform_action_file(string action)
{
	return __DIR__"tougu-zhen/" + action;
}

