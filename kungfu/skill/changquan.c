//̫�泤ȭ changquan.c

inherit SKILL;

mapping *action = ({
([      "action": "ֻ��$N����һ�����������һ����"+HIC+"������"+NOR+"����׼$n�ı��Ӻ��������˹�ȥ",
	"dodge": 5,
	"parry": 5,
	"force": 90,
	"skill_name" : HIC"������"NOR,
	"damage_type":  "����"
]),
([      "action": "$N����һ�֣���ȭ������һ�С�"+GRN+"�β�Ѱ��"+NOR+"������$n��$l�к���ȥ",
	"dodge": 5,
	"parry": 5,
	"force": 60,
	"skill_name" : GRN"�β�Ѱ��"NOR,
	"damage_type":  "����"
]),
([      "action": "$N��ȭ��$n����һ�Σ�����ʹ�˸���"+RED+"Ҷ��͵��"+NOR+"����$n��$l����һץ",
	"dodge": 5,
	"parry": 5,
	"force": 60,
	"skill_name" : RED"Ҷ��͵��"NOR,
	"damage_type":  "ץ��"
]),
([      "action": "$N����һ������ȭ��������ȭ���磬һ�С�"+HIR+"�ڻ�����"+NOR+"���Ʋ��ɵ��ػ���$n$l",
	"dodge": 5,
	"parry": 5,
	"force": 80,
	"skill_name" : HIR"�ڻ�����"NOR,
	"damage_type":  "����"
]),
([      "action": "ֻ��$N������ʽ��һ�С�"+HIB+"˫����"+NOR+"��ʹ�û����з硣����ȴ����һ������$n$l",
	"dodge": 5,
	"parry": 5,
	"force": 70,
	"skill_name" : HIB"˫����"NOR,
	"damage_type":  "����"
]),
([      "action": "$N������𣬴��һ�����������С�"+HIM+"�����ཻ"+NOR+"����������$n���һ������ȭ����$n�������˹�ȥ",
	"dodge": 5,
	"parry": 5,
	"force": 120,
	"skill_name" : HIM"�����ཻ"NOR,
	"damage_type":  "����"
]),
([      "action": "$N�����󹭲���˫��ʹ�˸���"+HIR+"����Ʊ�"+NOR+"����$n��$lһ��",
	"dodge": 5,
	"parry": 5,
	"force": 50,
	"skill_name" : HIR"����Ʊ�"NOR,
	"damage_type":  "����"
]),
([      "action": "ֻ��$N����������һ����ȭ����$n$l������һȭ�߹�һȭ����������"+HIY+"��������"+NOR+"��",
	"dodge": 5,
	"parry": 5,
	"force": 80,
	"skill_name" : HIY"��������"NOR,
	"damage_type":  "����"
]),
([      "action": "$N����һ�ݣ�����ʹ�˸���"+MAG+"�����̸�"+NOR+"��������ɨ��$n��$l",
	"dodge": 5,
	"parry": 5,
	"force": 50,
	"skill_name" : MAG"�����̸�"NOR,
	"damage_type":  "����"
]),
([      "action": "$Nһ��ת�����ƻ��أ����Ʒ���ʹ�˸���"+HIR+"������ɽ"+NOR+"����$n��ͷһ��",
	"dodge": 5,
	"parry": 5,
	"force": 90,
	"skill_name" : HIR"������ɽ"NOR,
	"damage_type":  "����"
]),
([      "action": "$N����Ծ������һ�С�"+RED+"��ӥ����"+NOR+"���������һ������$n���ţ�ֻ��$Nһ��������˫���ѵ���$n��$l",
	"dodge": 5,
	"parry": 5,
	"force": 100,
	"skill_name" : RED"��ӥ����"NOR,
	"damage_type":  "����"
]),
});

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("����ȭ������֡�\n");
	if (me->query_skill("cuff",1) <= me->query_skill("changquan",1)&&me->query_skill("unarmed",1) <= me->query_skill("changquan",1))
		return notify_fail("��Ļ���ȭ���������޷����������̫�泤ȭ��\n");

	return 1;
}

int valid_enable(string usage)
{
	return usage == "cuff" || usage == "parry";
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

mapping query_action(object me, object weapon)
{
	return action[random(sizeof(action))];
}

int practice_skill(object me)
{
	if ((int)me->query("qi") < 40)
		return notify_fail("����������������Ϣһ�������ɡ�\n");

	if ((int)me->query("neili") < 10)
		return notify_fail("������������ˡ�\n");

	me->receive_damage("qi", 35);
	me->add("neili", -1);

	return 1;
}
