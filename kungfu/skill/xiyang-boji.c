// xiyang-boji.c ���󲫻���

inherit SKILL;

string *dodge_msg = ({
	"$n����һŤ��ǡ�ö����$N��һ�С�\n",
	"����$nͻȻ������ˣ����ݵĶ����$N��һ�С�\n",
	"$n�������ƣ�������$N��׷����\n",
	"$n����$Nת���������������$N�޷���׽��$n����Ӱ��\n",
	"$n��Ŀ��ȣ����������ֺ룬$N��һ������ȫȻ��ա�\n",
});

int valid_enable(string usage) { return usage == "dodge"; }

int valid_learn(object me) { return 1; }

string query_dodge_msg(string limb)
{
	return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
	if( (int)me->query("qi") < 50 )
		return notify_fail("�������̫���ˣ��޷���ϰ���󲫻�����\n");

	me->receive_damage("qi", 40);
	return 1;
}
