// tiyunzong.c ������
// modified by Venus Oct.1997
// written by Xiang

inherit SKILL;

string *dodge_msg = ({
    "ֻ��$nһ�С��׺׳��졹���������ϱ�ֱ���������࣬�����$N��һ�С�\n",
    "$nһ�������ӷ���������ݳ�����֮Զ���ܿ���$N���������ơ�\n",
    "$nʹ��������չ�᡹����һ��ƮȻ�ݳ��������ŵء�\n"
    "����$n����Ʈ��������һ�ݣ����ѱܿ���\n",
    "$n������ת��ٿ����һ��Ų�������ߣ��ܹ�����һ�С�\n",
    "����$n����һ�ã�$N��һ�����˸��ա�\n",
    "ȴ��$n�㲻��أ����Դܿ����ߣ����˿�ȥ��\n",
    "$n����΢�Σ��о����յرܿ���$N��һ�С�\n"
});

int valid_enable(string usage)
{
	return usage == "dodge";
}

int valid_learn(object me) { return 1; }

string query_dodge_msg(string limb)
{
	return dodge_msg[random(sizeof(dodge_msg))];
}

int query_effect_dodge(object attacker, object me)
{
	int lvl;

	lvl = me->query_skill("tiyunzong", 1);
	if (lvl < 50)  return 0;
	if (lvl < 100) return 20;
	if (lvl < 150) return 30;
	if (lvl < 200) return 40;
	if (lvl < 250) return 50;
	if (lvl < 300) return 60;
	if (lvl < 350) return 70;
	return 80;
}

int practice_skill(object me)
{
	if( (int)me->query("qi") < 50 )
		return notify_fail("�������̫���ˣ������������ݡ�\n");

	me->receive_damage("qi", 40);
	return 1;
}
