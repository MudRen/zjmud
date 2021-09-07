// jingxiu.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	mapping fam;
	object where = environment(me);

	seteuid(getuid());

	if (me->query("family/family_name") != "������")
		return notify_fail("ֻ�������ɵ��ӲŻ���ܾ��ޣ�\n");

	if (environment(me)->query("no_fight"))
		return notify_fail("����̫���ӣ���û�����ľ��ޡ�\n");

	if (me->query("jing") < 50)
		return notify_fail("�㾫�񲻼ã��޷����ľ��ޡ�\n");

	if (me->is_busy())
		return notify_fail("����æ���أ�\n");

	if (me->is_fighting())
		return notify_fail("ս������ô���ޣ�\n");

	if (me->query_skill("buddhism", 1) < 200)
		return notify_fail("��ķ�ѧ�������������ͨ�����޲�������\n");

	switch (random(3))
	{
	case 0:
		message_vision("$N��ϥ���£�ڤ˼�붨��\n", me);
		break;

	case 1:
		message_vision("$N�������£��������⡣\n", me);
		break;

	default:
		message_vision("$N�����������������������ѡ�\n", me);
	}

	me->receive_damage("jing", 40 + random(10));
	me->improve_skill("buddhism", 5 + random(me->query_int()));
	me->start_busy(1 + random(3));
	write(HIC "��������ķ������ĵá�"NOR"\n");
	return 1;
}

int help(object me)
{
	write(@HELP
ָ���ʽ : jingxiu

���ָ���������ɵ������Ծ��޲���������.

HELP );
	return 1;
}
