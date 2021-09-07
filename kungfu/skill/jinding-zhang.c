// jinding-zhang.c ������
// Oct. 9 1997 by That
inherit SKILL;

mapping *action = ({
([      "skill_name" : "������̩" ,
	"action": "$N����΢�Σ�һ�С�������̩�������������$nֻ����һ��ů��Ϯ��$l",
	"force" : 100,
	"dodge" : 10,
	"lvl"   : 0,
	"damage_type" : "����",
]),
([      "skill_name" : "��������" ,
	"action": "$N˫�ֱ�ã���ָ�ᵯ��һ�С��������项��������·������ʮ����ץ��$n��$l",
	"force" : 120,
	"dodge" : 10,
	"lvl"   : 20,
	"damage_type" : "����",
]),
([      "skill_name" : "�����" ,
	"action": "$N����ǰ��������ٿ��������ͷ�һ�С�����ơ�����ץ��$n��$l",
	"force" : 150,
	"dodge" : 15,
	"lvl"   : 30,
	"damage_type" : "����",
]),
([      "skill_name" : "������ɳ" ,
	"action": "$N����Ȧת�����$n�����֣������Ƴ������������Ļ���һ�С�������ɳ�����͵ػ���$n���°�",
	"force" : 200,
	"dodge" : 25,
	"lvl"   : 40,
	"damage_type" : "����",
]),
([      "skill_name" : "�׶�����" ,
	"action": "$N�������ף�һ�����ȣ���$nһ㶼䣬����һ�С��׶���������ֱ��$n��$l",
	"force" : 100,
	"dodge" : 10,
	"lvl"   : 50,
	"damage_type" : "����",
]),
([      "skill_name" : "�𶥷��" ,
	"action": "$N˫��ƽ����ȭ����¶΢Ц��$n��㱼俴��$N����Ϊ�������$N���������һ�С��𶥷�⡹��֪��������ʵ���Ʒ��Ѿ�Ϯ��",
	"force" : 200,
	"dodge" : 15,
	"lvl"   : 70,
	"damage_type" : "����",
]),
([      "skill_name" : "���Ľ�ħ" ,
	"action": "$Nһ������ׯ�ϣ�ʹ�������Ľ�ħ����������磬����$nƯ�Ʋ���",
	"force" : 230,
	"parry" : 20,
	"dodge" : 20,
	"lvl"   : 80,
	"damage_type" : "����",
]),
([      "skill_name" : "����˻�" ,
	"action": "$Nȫ�����ߣ�˫�ۼ��裬��Ϊ�����Ӱ��һ�С�����˻ġ�����ǵ�Ϯ��$nȫ�������Ѩ",
	"force" : 260,
	"parry" : 5,
	"dodge" : 30,
	"lvl"   : 100,
	"damage_type" : "����",
]),
});

int valid_enable(string usage) { return usage == "strike" ||  usage == "parry"; }

int valid_combine(string combo) { return combo == "tiangang-zhi"; }

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("�������Ʊ�����֡�\n");

	if (me->query_skill("force") < 50)
		return notify_fail("����ڹ���򲻹��������������ơ�\n");

	if (me->query("max_neili") < 150)
		return notify_fail("�������̫�����޷��������ơ�\n");

	if (me->query_skill("strike", 1) < me->query_skill("jinding-zhang", 1))
		return notify_fail("��Ļ����Ʒ�̫��޷���������Ľ����ơ�\n");

	return 1;
}

string query_skill_name(int level)
{
	int i;
	for(i = sizeof(action)-1; i >= 0; i--)
		if(level >= action[i-1]["lvl"])
			return action[i-1]["skill_name"];
}

mapping query_action(object me, object weapon)
{
	int i, level;
	level   = (int)me->query_skill("jinding-zhang",1);
	for(i = sizeof(action); i > 0; i--)
		if(level > action[i-1]["lvl"])
			return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
	if ((int)me->query("qi") < 50)
		return notify_fail("�������̫���ˡ�\n");

	if ((int)me->query("neili") < 60)
		return notify_fail("�������������ϰ�����ơ�\n");

	if (me->query_skill("jinding-zhang", 1) < 100)
		me->receive_damage("qi", 30);
	else
		me->receive_damage("qi", 45);

	me->add("neili", -48);
	return 1;
}
string perform_action_file(string action)
{
	return __DIR__"jinding-zhang/"+ action;
}
