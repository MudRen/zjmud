// chanchu_bufa.c ��ܲ���

inherit SKILL;

string *dodge_msg = ({
	"ֻ��$nһ�С��ɾ��졹���������ϱ�ֱ���������࣬�����$N��һ�С�\n",
	"����$nһ��ʹ�����������졹������Ʈ��������һ�ݣ����ѱܿ���\n",
	 "$nһ�С����뵾�����������ת��ٿ����һ��Ų�������ߣ��ܹ�����һ�С�\n",
	"����$nһ��������˳桹������һ�ã�$N��һ�����˸��ա�\n",
	"ȴ��$n��󸷭�׶ǡ����㲻��أ����Դܿ����ߣ����˿�ȥ��\n",
	"$n����һ�С������¡�������΢�Σ��о����յرܿ���$N��һ�С�\n"
});

int valid_enable(string usage) { return usage == "dodge"; }

int valid_learn(object me) { return 1; }

string query_dodge_msg(string limb)
{
	return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
	if( (int)me->query("qi") < 45 )
		return notify_fail("�������̫���ˣ���������ܲ�����\n");

	me->receive_damage("qi", 40);
	return 1;
}

