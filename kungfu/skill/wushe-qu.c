// wushe-qu.c ������

#include <ansi.h>

inherit SKILL;

string type() { return "knowledge"; }

int valid_enable(string usage) { return usage == "guzheng-jifa"; }

int valid_learn(object me)
{
	if (me->query_skill("guzheng-jifa", 1) < 100)
		return notify_fail("��Ĺ��ݼ���ˮƽ������������������˵�ɣ�\n");

	if (me->query_skill("guzheng-jifa", 1) < me->query_skill("wushe-qu", 1))
		return notify_fail("��Ĺ��ݼ���ˮƽ���ޣ��޷������������������\n");

	return 1;
}

int practice_skill(object me)
{
	object ob;

	if (! objectp(ob = me->query_temp("handing")) ||
	    ! ob->valid_as_zheng())
		return notify_fail("���ó�����������ô��ϰ��\n");

	if ((int)me->query("jing") < 80)
		return notify_fail("��ľ��񲻹��ã�û����ϰ�ˡ�\n");

	if ((int)me->query("qi") < 30)
		return notify_fail("������ʵ����̫ƣ���ˡ�\n");

	me->receive_damage("jing", 25);
	me->receive_damage("qi", 15);

	return 1;
}

void do_effect(object me)
{
	object env;
	int lvl;
	string *sn;
	object *obs;
	object ob;

	lvl = me->query_skill("guzheng-jifa", 1) / 2 +
	      me->query_skill("wushe-qu", 1);

	if ((env = environment(me))->query("no_fight"))
		return;

	if (lvl < 50)
	{
		write("����ͷ�󺹵ĵ��˰��죬����û��ʲô���á�\n");
		return;
	}

	if (me->query("neili") < 50)
	{
		me->set("neili", 0);
		write("����������������Щ���á�\n");
		return;
	}

	me->add("neili", -20 - random(10));

	if (! arrayp(sn = env->query("resource/snake")))
	{
		write("�㵯�˰��죬����û��һ���߳�����\n");
		return;
	}

	obs = filter_array(all_inventory(env), (: $1->is_snake() :));
	if (sizeof(obs) > 12 || random(150 + lvl) < 150)
	{
		write("�㵯�˰��죬�����ƺ�û��ʲô�߳�����\n");
		return;
	}

	ob = new(sn[random(sizeof(sn))]);
	ob->add("snake_poison/level" + random(lvl / 5));
	ob->move(env);
	write("�㵯��һ����ֻ��һ���������죬һ��" + ob->name() +
	      "�Ӳݴ��д��˳�����\n");
}
