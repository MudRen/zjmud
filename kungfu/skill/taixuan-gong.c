// taixuan-gong.c ���͵�̫����
// Jay 4/5/96
// modified by Venus Oct.1997
inherit FORCE;

string *dodge_msg = ({
	"$n�����ĳ������絽������$N��һ�ߡ�\n",
	"$n�ֱۻ�ת��ץס$N����һ�ƣ���$NԶԶ������\n",
	"$n������ţ���Ծ��������������ʮ�����⡣\n",
	"$Nֻ����ǰһ����ֻ����$n����һ�ϣ��Լ���������ȻĪ�����������ˡ�\n",
});

int query_neili_improve(object me)
{
	int lvl;

	lvl = (int)me->query_skill("taixuan-gong", 1);
	return lvl * lvl * 15 * 18 / 100 / 200;
}

mapping *action = ({
([      "action":"$N˫��һ�٣�һ�ɾ���������ӿ�������Ƶ�$n���Ժ���",
	"force" : 450,
	"attack": 150,
	"dodge" : 70,
	"parry" : 80,
	"damage": 95,
	"damage_type":  "����"
]),
([      "action":"$N�����������$n�۰���Ѹ���ޱȵ�һ����$nһ�ӵ��˳�ȥ",    
	"force" : 470,
	"attack": 140,
	"dodge" : 60,
	"parry" : 90,
	"damage": 110,
	"damage_type":  "����"
]),
([      "action":"$N���һ�����ſ�һ��������$n������ȥ",
	"force" : 440,
	"attack": 135,
	"dodge" : 55,
	"parry" : 85,
	"damage": 105,
	"damage_type":  "����"
]),
([      "action":"$N�����ϣ�˫���͵�����$n",
	"force" : 480,
	"attack": 170,
	"dodge" : 100,
	"parry" : 75,
	"damage": 95,
	"damage_type":  "����"
]),
([      "action":"$N����΢�࣬ͻȻ����һ�ţ�����$n����·���ŵ���;���͵�һ̧������$n����",
	"force" : 470,
	"attack": 175,
	"dodge" : 80,
	"parry" : 65,
	"damage": 110,
	"damage_type":  "����"
]),
([      "action":"$NͻȻ������һ�࣬��ס$n��·������������ӿ����",
	"force" : 460,
	"attack": 160,
	"dodge" : 75,
	"parry" : 85,
	"damage": 100,
	"damage_type":  "����"
]),

});

int valid_enable(string usage)
{
    return usage == "unarmed" ||
	   usage == "dodge" ||
	   usage == "parry" ||
	   usage == "force";
}

mapping query_action(object me, object weapon)
{
	return action[random(sizeof(action))];
}

string query_dodge_msg(string limb)
{
	return dodge_msg[random(sizeof(dodge_msg))];
}

int valid_learn(object me)
{
	if ((int)me->query_skill("literate", 1))
		return notify_fail("�����̫�������֮����һʱ��������ᡣ\n");

	if ((int)me->query("str") < 25)
		return notify_fail("����������Ȼ�������е㲻���ס�\n");
	if ((int)me->query("int") < 19)
		return notify_fail("����������Ȼ�������е㲻���ס�\n");
	if ((int)me->query("con") < 25)
		return notify_fail("����������Ȼ�������е㲻���ס�\n");
	if ((int)me->query("dex") < 25)
		return notify_fail("����������Ȼ�������е㲻���ס�\n");

	return ::valid_learn(me);
}

string perform_action_file(string action)
{
	return __DIR__"taixuan-gong/perform/" + action;
}
string exert_function_file(string action)
{
	return __DIR__"taixuan-gong/exert/" + action;
}
