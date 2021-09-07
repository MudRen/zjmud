// luoying-zhang.c ��Ӣ����
// modified by Venus Oct.1997
inherit SKILL;

mapping *action = ({
([      "action" : "$N˫��ƽ�죬�����ӳ���һʽ��"+GRN+"����էչ"+NOR+"����ָ����ӯƯ����"
		   "���ᷴ��$n��$l",
	"force" : 40,
	"dodge" : 15,
	"lvl"   : 0,
	"damage_type" : "����",
	"skill_name" : GRN"����էչ"NOR
]),
([      "action" : "$N������ָ����һ�գ�һʽ��"+BLU+"�ط����"+NOR+"������ָ��Ȼңң����$n��"
		   "$nֻ������ɼ���Ϯ���Լ��崦��Ѩ",
	"force" : 60,
	"dodge" : 20,
	"lvl"   : 10,
	"damage_type" : "����",
	"skill_name" : BLU"�ط����"NOR
]),
([      "action" : "$NͻȻ����Ծ���գ��������䣬һʽ��"+HIM+"���Ƿɻ�"+NOR+"��������$n��ͷ��",
	"force" : 80,
	"dodge" : 25,
	"lvl"   : 20,
	"damage_type" : "����",
	"skill_name" : HIM"���Ƿɻ�"NOR
]),
([      "action" : "$NͻȻԾ��˫�������������罣�����缲�������һʽ��"+HIR+"�꼱��"
		   "��"+NOR+"��������$n��ȫ��",
	"force" : 100,
	"dodge" : 25,
	"lvl"   : 30,
	"damage_type" : "����",
	"skill_name" : HIR"�꼱���"NOR
]),
([      "action" : "$N���ֻ������ĳ��죬������ֲ�£ʳָ��ָ�����������һʽ"
		   "��"+HIB+"�Ǻ�����"+NOR+"����ֱָ$n������",
	"force" : 130,
	"dodge" : 20,
	"lvl"   : 40,
	"damage_type" : "����",
	"skill_name" : HIB"�Ǻ�����"NOR
]),
([      "action" : "$NͻȻ������ˣ�����һʽ��"+HIC+"�����׷�"+NOR+"����ƽ�����˫����$n"
		   "�ĺ�����������",
	"force" : 150,
	"dodge" : 35,
	"lvl"   : 60,
	"damage_type" : "����",
	"skill_name" : HIC"�����׷�"NOR
]),
([      "action" : "$NͻȻ����Ծ������Ю�ž�����ӿ�ĳ����������������ƺ�ͻ��"
		   "�����һʽ��"+HIB+"����׷��"+NOR+"����������ǰ��$n��$l��ȥ",
	"force" : 170,
	"dodge" : 45,
	"lvl"   : 70,
	"damage_type" : "����",
	"skill_name" : HIB"����׷��"NOR
]),
([      "action" : "$Nʹһʽ��"+YEL+"�����®"+NOR+"����ȫ��ͻȻ������ת��˫�ƺ�ǰ������"
		   "������$n���ؿ�",
	"force" : 200,
	"dodge" : 35,
	"lvl"   : 80,
	"damage_type" : "����",
	"skill_name" : YEL"�����®"NOR
]),
([      "action" : "$Nǰ��һ�࣬һʽ��"+HIG+"���ƺ��"+NOR+"���������罣��һ����������Ϯ��$n"
		   "������",
	"force" : 240,
	"dodge" : 45,
	"lvl"   : 90,
	"damage_type" : "����",
	"skill_name" : HIG"���ƺ��"NOR
]),
([      "action" : "$Nʹһʽ��"+BLU+"�׺羭��"+NOR+"����˫���������Ȧ������һ������$n��$l"
		   "�ȥ",
	"force" : 270,
	"parry" : 25,
	"dodge" : 50,
	"lvl"   : 100,
	"damage_type" : "����",
	"skill_name" : BLU"�׺羭��"NOR
]),
([      "action" : "$N˫��ʳָ����ָһ�ͣ�һʽ��"+HIR+"��������"+NOR+"����һ��ǿ�ҵ�����ӿ��"
		   "$n��ȫ��",
	"force" : 290,
	"parry" : 25,
	"dodge" : 55,
	"lvl"   : 120,
	"damage_type" : "����",
	"skill_name" : HIR"��������"NOR
]),
([      "action" : "$Nһʽ��"+HIY+"��Ӣ����"+NOR+"����˫������ǰ��ת���ƻ����裬����ǵ�ֱָ"
		   "��$n��$nֻ�������ƻ����ۻ����ҡ�",
	"force" : 320,
	"parry" : 30,
	"dodge" : 65,
	"damage_type" : "����",
	"lvl" : 140,
	"skill_name" : HIY"��Ӣ����"NOR
])
});

int valid_enable(string usage) { return usage=="strike" ||  usage=="parry"; } 

int valid_combine(string combo) { return combo=="xuanfeng-leg"; }

int valid_learn(object me)
{
    	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("����Ӣ���Ʊ�����֡�\n");

    	if ((int)me->query_skill("force") < 80)
		return notify_fail("����ڹ���򲻹����޷�ѧ��Ӣ���ơ�\n");

    	if ((int)me->query("max_neili") < 400)
		return notify_fail("�������̫�����޷�����Ӣ���ơ�\n");

    	if ((int)me->query_skill("strike", 1) < (int)me->query_skill("luoying-shenzhang", 1))
		return notify_fail("��Ļ����Ʒ�ˮƽ���ޣ��޷������������Ӣ���ơ�\n");

    	return 1;
}

string query_skill_name(int level)
{
    	int i;
    	for (i = sizeof(action)-1; i >= 0; i--)
		if (level >= action[i]["lvl"])
	    		return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
    	int i, level;
    	level = (int)me->query_skill("luoying-shenzhang", 1);
    	for (i = sizeof(action); i > 0; i--)
		if (level > action[i-1]["lvl"])
	    		return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
    	if ((int)me->query("qi") < 60)
		return notify_fail("�������̫���ˡ�\n");

    	if ((int)me->query("neili") < 50)
		return notify_fail("���������������Ӣ���ơ�\n");

    	me->receive_damage("qi", 45);
    	me->add("neili", -40);
    	return 1;
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
    	return __DIR__"luoying-shenzhang/" + action;
}
