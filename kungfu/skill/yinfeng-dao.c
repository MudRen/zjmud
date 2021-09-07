inherit SKILL;

mapping *action = ({
([      "action" : "$N���μ��Σ�һԾ����$n��ǰ�����ƴ����йǺ�������$n��$l",
	"force" : 160,
	"attack": 25,
	"dodge" : 15,
	"parry" : 15,
	"damage": 10,
	"lvl"   : 0,
	"skill_name" : "�йǺ���",
	"damage_type" : "����"
]),
([      "action" : "$N����Ծ��˫�����϶���б����������ʱ��ǧ�����纮��������˷�ϯ��$n",
	"force" : 220,
	"attack": 40,
	"dodge" : 20,
	"parry" : 15,
	"damage": 20,
	"lvl"   : 30,
	"skill_name" : "���纮��",
	"damage_type" : "����"
]),
([      "action" : "$Nƽ��Ϊ����бб�������ƾ��ó�һƬƬ�йǺ�����쫷�����$n��ȫ��",
	"force" : 280,
	"attack": 50,
	"dodge" : 20,
	"parry" : 25,
	"damage": 28,
	"lvl"   : 60,
	"skill_name" : "�йǺ���",
	"damage_type" : "����"
]),
([      "action" : "$N��ת���ƶ�׼�Լ���סȫ��ͻȻһ�������$n��ǰ�����ƺ���$n������ȥ",
	"force" : 360,
	"attack": 60,
	"dodge" : 80,
	"parry" : 60,
	"damage": 35,
	"lvl"   : 80,
	"skill_name" : "��ת����",
	"damage_type" : "����"
]),
([      "action" : "$N���ƺ󳷣�����һ�����͵ػ��ƿ������ó�һ����âֱն��$n��$l",
	"force" : 420,
	"attack": 110,
	"dodge" : 45,
	"parry" : 40,
	"damage": 50,
	"lvl"   : 100,
	"skill_name" : "��âֱն",
	"damage_type" : "����"
]),
});

int valid_enable(string usage) { return usage=="strike" || usage=="parry"; }

int valid_combine(string combo) { return combo=="tougu-zhen"; }

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("�����絶������֡�\n");

	if ((int)me->query_skill("force") < 200)
		return notify_fail("����ڹ���򲻹����޷���ϰ���絶��\n");

	if ((int)me->query("max_neili") < 1400)
		return notify_fail("�������̫�����޷���ϰ���絶��\n");

	if ((int)me->query_skill("strike", 1) < 100)
		return notify_fail("��Ļ����Ʒ���򲻹����޷���ϰ���絶��\n");

	if ((int)me->query_skill("strike", 1) < (int)me->query_skill("yinfeng-dao", 1))
		return notify_fail("��Ļ����Ʒ�ˮƽ���ޣ��޷�������������絶��\n");

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
	level   = (int) me->query_skill("yinfeng-dao",1);
	for(i = sizeof(action); i > 0; i--)
		if(level > action[i-1]["lvl"])
			return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
	if ((int)me->query("qi") < 100)
		return notify_fail("�������̫���ˡ�\n");

	if ((int)me->query("neili") < 100)
		return notify_fail("����������������絶��\n");

	me->receive_damage("qi", 80);
	me->add("neili", -80);
	return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
	int lvl;
	int flvl;

	lvl  = me->query_skill("yinfeng-dao", 1);
	flvl = me->query("jiali");
	if (lvl < 80 || flvl < 10 || ! damage_bonus)
		return;

	if (flvl * 2 + random(lvl) > victim->query_skill("force") &&
	    victim->affect_by("yinfeng_dao",
			      ([ "level" : flvl + random(flvl),
				 "id"    : me->query("id"),
				 "duration" : lvl / 100 + random(lvl / 10) ])))
	{
		return "$nֻ��һ��ι�֮ʹ�����������˶Է����絶�ھ��ĸ��š�\n";
	}
}

string perform_action_file(string action)
{
	return __DIR__"yinfeng-dao/" + action;
}

