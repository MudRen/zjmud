// weight.c
// created by doing

#include <ansi.h>

inherit F_CLEAN_UP;

int help(object me);

int main(object me, string arg)
{
	object env;
	int origin;
	string msg;
	string to;

	if (! SECURITY_D->valid_grant(me, "(wizard)"))
		return 0;

	switch (arg)
	{
	case "light":
		if (me->query_weight() < 2)
			return notify_fail("���Ѿ���Ĳ��������ˡ�\n");
		me->set_weight(me->query_weight() / 2);
		to = "��";
		break;

	case "heavy":
		if (me->query_weight() >= 128 * 1024)
			return notify_fail("���޷���ø����ˡ�\n");
		if (! me->query_weight())
			me->set_weight(1);
		else
			me->set_weight(me->query_weight() * 2);
		to = "��";
		break;

	case "origin":
		origin = 40000 + (me->query("str") - 10) * 2000;
		if (origin > me->query_weight())
			to = "��"; else
		if (origin < me->query_weight())
			to = "��"; else
			return notify_fail("�������û���κα仯��\n");

		me->set_weight(origin);
		break;

	default:
		help(me);
		return 1;
	}

	tell_object(me, HIM "�������������" + to + "��һЩ��"NOR"\n");

	if (objectp(env = environment(me)))
	{
		message("vision", me->name() + "���������дʣ���֪��"
			"�ڸ�Щʲô��\n", env, ({ env, me }));

		if (userp(env) && !me->query("env/invisible"))
			tell_object(env, HIM "���Ȼ�������Ϻ���" +
					 to + "�˺ܶࡣ"NOR"\n");
	}

	return 1;
}

int help(object me)
{
	write(@HELP
ָ���ʽ : miagic <light | heavy | origin>
 
���ָ���ʹ��������仯��ÿ�μӱ����Ǽ��롣���ָ�� origin
�ͻָ�ԭ�������ء�
 
HELP );
    return 1;
}
