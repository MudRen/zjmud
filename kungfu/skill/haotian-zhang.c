// haotian-zhang �����
// By Lgg,1998.10

inherit SKILL;

mapping *action = ({
([      "action" : "$Nʹһ�С�"+HIM+"������ˮ"+NOR+"����˫�ֻ��˸���Ȧ������$n��$l",
	"force" : 60,
	"attack": 30,
	"dodge" : 20,
	"parry" : 31,
	"damage": 5,
	"skill_name" : HIM"������ˮ"NOR,
	"lvl" : 0,
	"damage_type" : "����"
]),
([      "action" : "$Nʹһ�С�"+BLU+"��������"+NOR+"������������һ�ӣ�����$n��$l",
	"force" : 65,
	"attack": 35,
	"dodge" : 38,
	"parry" : 33,
	"damage": 10,
	"skill_name" : BLU"��������"NOR,
	"lvl" : 5,
	"damage_type" : "����"
]),
([      "action" : "$N�����������⣬��������ʹһ�С�"+MAG+"�����沨"+NOR+"������$n��$l��ȥ",
	"force" : 70,
	"attack": 38,
	"dodge" : 36,
	"parry" : 35,
	"damage": 15,
	"skill_name" : MAG"�����沨"NOR,
	"lvl" : 10,
	"damage_type" : "����"
]),
([      "action" : "$Nʹһ�С�"+CYN+"������ת"+NOR+"�����ֻ�$n���ؿں�$l",
	"force" : 76,
	"attack": 42,
	"dodge" : 44,
	"parry" : 36,
	"damage": 20,
	"skill_name" : CYN"������ת"NOR,
	"lvl" : 15,
	"damage_type" : "����"
]),
([      "action" : "$Nʹһ�С�"+GRN+"���ջ���"+NOR+"����������ͬʱ�������ڿ���ͻȻ�����Ʒ��򻥱�",
	"force" : 85,
	"attack": 45,
	"dodge" : 42,
	"parry" : 41,
	"damage": 25,
	"skill_name" : GRN"���ջ���"NOR,
	"lvl" : 20,
	"damage_type" : "����"
]),
([      "action" : "$N���ֲ�ס�ζ�������һ�С�"+YEL+"������˪"+NOR+"������$n��$l��ȥ",
	"force" : 96,
	"attack": 49,
	"dodge" : 50,
	"parry" : 42,
	"damage": 20,
	"skill_name" : YEL"������˪"NOR,
	"lvl" : 25,
	"damage_type" : "����"
]),
([      "action" : "$N���ֱ���Ϊ�ģ����������絶��һ�С�"+WHT+"͡�ϰ�ɳ"+NOR+"��������$n��$l",
	"force" : 98,
	"attack": 55,
	"dodge" : 58,
	"parry" : 44,
	"damage": 15,
	"skill_name" : WHT"͡�ϰ�ɳ"NOR,
	"lvl" : 30,
	"damage_type" : "����"
]),
([      "action" : "$N����˺�벽������ʹһ�С�"+HIC+"����һɫ"+NOR+"���������$n",
	"force" : 105,
	"attack": 59,
	"dodge" : 63,
	"parry" : 48,
	"damage": 14,
	"skill_name" : HIC"����һɫ"NOR,
	"lvl" : 35,
	"damage_type" : "����"
]),
([      "action" : "$Nһ�С�"+HIW+"�����"+NOR+"���������ȷ������������ƺ󷢶�����",
	"force" : 110,
	"attack": 62,
	"dodge" : 54,
	"parry" : 49,
	"damage": 14,
	"skill_name" : HIW"�����"NOR,
	"lvl" : 40,
	"damage_type" : "����"
]),
([      "action" : "$N˫���������У�˫�����ɨ��$n��$l��ȴ��һ�С�"+HIY+"������ˮ"+NOR+"������̬����",
	"force" : 120,
	"attack": 66,
	"dodge" : 62,
	"parry" : 52,
	"damage": 12,
	"skill_name" : HIY"������ˮ"NOR,
	"lvl" : 45,
	"damage_type" : "����"
]),
([      "action" : "$N�����鰴�����ֻ�������ʹһ�С�"+WHT+"��������"+NOR+"������$n��$l��ȥ",
	"force" : 130,
	"attack": 75,
	"dodge" : 60,
	"parry" : 54,
	"damage": 16,
	"skill_name" : WHT"��������"NOR,
	"lvl" : 50,
	"damage_type" : "����"
]),
([      "action" : "$N˫�ֱ�����ȭ����ǰ��󻮻���һ�С�"+BLU+"�������"+NOR+"������$n��$l",
	"force" : 150,
	"attack": 81,
	"dodge" : 68,
	"parry" : 55,
	"damage": 12,
	"skill_name" : BLU"�������"NOR,
	"lvl" : 55,
	"damage_type" : "����"
]),
([      "action" : "$N�����黮�����ֱ���Ϊ��һ�ǡ�"+RED+"¥�����"+NOR+"������$n��$l",
	"force" : 170,
	"attack": 85,
	"dodge" : 76,
	"parry" : 58,
	"damage": 28,
	"skill_name" : RED"¥�����"NOR,
	"lvl" : 60,
	"damage_type" : "����"
]),
([      "action" : "$Nʩ����"+HIG+"������"+NOR+"������������ӳ�������ͬʱ����$n",
	"force" : 200,
	"attack": 88,
	"dodge" : 54,
	"parry" : 61,
	"damage": 24,
	"skill_name" : HIG"������"NOR,
	"lvl" : 80,
	"damage_type" : "����"
]),
([      "action" : "$N�ɱ۴��֣�����ǰ����������ʹһ�С�"+HIB+"���㳤��"+NOR+"��������$n��$l",
	"force" : 220,
	"attack": 92,
	"dodge" : 72,
	"parry" : 62,
	"damage": 15,
	"skill_name" : HIB"���㳤��"NOR,
	"lvl" : 100,
	"damage_type" : "����"
]),
([      "action" : "$N����͵أ�����ʹһ�С�"+HIR+"����ǱԾ"+NOR+"�������¶�����$n��$l��ȥ",
	"force" : 250,
	"attack": 94,
	"dodge" : 67,
	"parry" : 64,
	"damage": 18,
	"skill_name" : HIR"����ǱԾ"NOR,
	"lvl" : 110,
	"damage_type" : "����"
]),
([      "action" : "$N�����ɹ����ƣ�˫���������ϣ�������ǰ�Ƴ�һ�С�"+HIM+"�»�����"+NOR+"��",
	"force" : 280,
	"attack": 96,
	"dodge" : 81,
	"parry" : 66,
	"damage": 28,
	"skill_name" : HIM"�»�����"NOR,
	"lvl" : 120,
	"damage_type" : "����"
]),
([      "action" : "$N���Ʋ�ס����ɨ������һʽ��"+CYN+"��̶�仨"+NOR+"����������ת����$n��ȥ",
	"force" : 310,
	"attack": 99,
	"dodge" : 66,
	"parry" : 69,
	"damage": 21,
	"skill_name" : CYN"��̶�仨"NOR,
	"lvl" : 130,
	"damage_type" : "����"
]),
([      "action" : "$N���־���ǰ��������ǰƲ����ʹһ�С�"+HIC+"��ˮ����"+NOR+"������$n��$l��ȥ",
	"force" : 330,
	"attack": 100,
	"dodge" : 64,
	"parry" : 74,
	"damage": 32,
	"skill_name" : HIC"��ˮ����"NOR,
	"lvl" : 140,
	"damage_type" : "����"
]),
([      "action" : "$Nʹһ�С�"+GRN+"б�³���"+NOR+"������������������Ȧ�����ƴ�Ȧ�д�������$n",
	"force" : 370,
	"attack": 102,
	"dodge" : 72,
	"parry" : 73,
	"damage": 35,
	"skill_name" : GRN"б�³���"NOR,
	"lvl" : 150,
	"damage_type" : "����"
]),
([      "action" : "$N�������ϻ�������������ʹһ�С�"+HIY+"��ʯ����"+NOR+"�������Ʋ�ס�ζ�����"
		   "��$nͷ������֮��",
	"force" : 400,
	"attack": 105,
	"dodge" : 65,
	"parry" : 79,
	"damage": 50,
	"skill_name" : HIY"��ʯ����"NOR,
	"lvl" : 160,
	"damage_type" : "����"
])
});

int valid_enable(string usage) { return usage=="strike" || usage=="parry" ; }

int valid_combine(string combo)
{
	return combo == "sun-finger" ||
	       combo == "zhongnan-zhi";
}

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("������Ʊ�����֡�\n");

	if ((int)me->query("neili") < 900)
		return notify_fail("��������������޷�ѧ����ơ�\n");

	if ((int)me->query_skill("force") < 110)
		return notify_fail("����ڹ���򲻹����޷�ѧ����ơ�\n");
	if (me->query_skill("strike",1) <= me->query_skill("haotian-zhang",1) )
	      return notify_fail("��Ļ����Ʒ������������޷��������������ơ�\n");

	return 1;
}

mapping query_action(object me, object weapon)
{
	int i, level;
	level = (int) me->query_skill("haotian-zhang",1);
	for(i = sizeof(action); i > 0; i--)
		if(level > action[i-1]["lvl"])
			return action[NewRandom(i, 5, level/5)];

}

int practice_skill(object me)
{
	if ((int)me->query("qi") < 80)
		return notify_fail("�������̫���ˡ�\n");

	if ((int)me->query("neili") < 80)
		return notify_fail("�����������������ơ�\n");

	me->receive_damage("qi", 68);
	me->add("neili", -66);
	return 1;
}
string query_skill_name(int level)
{
	int i;
	for(i = sizeof(action)-1; i >= 0; i--)
		if(level >= action[i]["lvl"])
			return action[i]["skill_name"];
}
//�ȼ��������Ƿ�ѧ���µ���ʽ
string query_skill_up(int level)
{
	int i;
	for(i = sizeof(action)-1; i >= 0; i--)
	 {
		if(level == action[i]["lvl"])
		 {
		     return action[i]["skill_name"];
		 }
	 }
	  return "no";
}

string perform_action_file(string action)
{
	return __DIR__"haotian-zhang/" + action;
}
