// renshu ��������

inherit SKILL;

string *dodge_msg = ({
	"$n����һŤ��������Ϊ���죬�����$N��һ�С�\n",
	"����$nͻȻ��ͷ���ض��ߣ������$N��һ�С�\n",
	"$nͻȻ���������һ�Ű�����$Nʧȥ�˷���\n",
	"$n��Ȼ���μӿ죬ʹ$Nʧȥ��$n���ټ���\n",
	"$nͻȻ�����ڵأ�ʹ$N����ȫȻ��ա�\n",
});

int valid_enable(string usage) { return (usage == "dodge") || (usage == "move"); }

int valid_learn(object me) { return 1; }

string query_dodge_msg(string limb)
{
	return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
	if( (int)me->query("qi") < 50 )
		return notify_fail("�������̫���ˣ��޷���ϰ����������\n");

	me->receive_damage("qi", 40);
	return 1;
}
