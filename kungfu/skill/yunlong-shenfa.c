// yunlong-shenfa ������
// written by That

inherit SKILL;

string *dodge_msg = ({
	"$nһʽ�����ڻ�Ծ��������һת���͵�����һ��,�����$N�Ĺ��ơ�\n",
	"$nһʽ��ɳ���������˫��������󣬲������������״�$N��ǰ�����\n",
	"$nһʽ������ͬ�ۡ������˷�����һ�����Ƶ���$N�����\n",
	"$nһʽ���������񡹣����������һ�ˣ������ù���$N���������ơ�\n",
	"$nһʽ�����Ĳ�����������һ�����һ�Σ�������Ʈ����Զ��\n",
	"$nһʽ����ӥ���á���������һֻ��ӥ������һ����$N����ǰ�ɹ���\n",
	"$nһʽ���������졹�����İεض����ڰ����һת�����䵽����Զ�ĵط���\n",
	"$nһʽ��������졹��ȫ��Ϊһ����Ӱ������һ���շ��������Ʈ���ұߡ�\n",
	"$nһʽ���������̡������ζ��ر��Ʈ����������$N�޷����塣\n",
	"$nһʽ���������¡�������һ����ʸ������ٿ�İεض�����$N�������ӡ�\n",
});

int valid_enable(string usage) { return (usage == "dodge") || (usage == "move");
 }

int valid_learn(object me) { return 1; }

string query_dodge_msg(string limb)
{
	return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
	if((int)me->query("qi") < 50 )
		return notify_fail("�������̫���ˣ���������������\n");

	me->receive_damage("qi", 40);
	return 1;
}
