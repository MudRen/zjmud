// yujiashu.c �����

inherit FORCE;

string *dodge_msg = ({
	"$nǰ��Žż�Ÿ��࿿��������������ˮ�㻬�����ࡣ\n",
	"$n˫��ǰ�죬ȫ������ƽ�ɣ���ʱ������$N���������ơ�\n",
	"$n�㲻�����ֲ�̧��һת�ۼ���Ƶ���$N�����\n",
	"$nһת��䣬����˷�Ʈ����������$n����Ӱ����$N������롣\n",
	"$nȫ���ֱ���εض����ڰ����һת�����䵽����Զ�ĵط���\n",
	"$n�����������������ݷ����У���$Nͷ����Ծ������\n",
	"$n˫�ŵ�أ�ȫ��Ϊһ����Ӱ����������$N���˼�ת��\n",
	"$n���������ݰ㼱ת�������γ�һ�������У���$N������䣬�������á�\n",
});

int valid_enable(string usage)
{
	return usage == "force" || usage == "dodge";
}

int valid_force(string force)
{
	return force == "hunyuan-yiqi" ||
	       force == "shaolin-xinfa";
}

int query_neili_improve(object me)
{
    int lvl;

    lvl = (int)me->query_skill("yujiashu", 1);
    return lvl * lvl * 15 * 18 / 100 / 200;
}

int valid_learn(object me)
{
    	if (me->query_skill("force", 1) < 100)
		return notify_fail("��Ļ����ڹ���򲻹����޷�ѧϰ�������\n");

	if (me->query("gender") != "����")
		return notify_fail("�㲻�����ԣ��޷���ϰ������񹦡�\n");

	return ::valid_learn(me);
}


int practice_skill(object me)
{
	return notify_fail("�����ֻ����ѧ(learn)�������������ȡ�\n");
}

string exert_function_file(string func)
{
	return __DIR__"yujiashu/" + func;
}
