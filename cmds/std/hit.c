// hit.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object obj, old_target;

	if (me->is_chatter())
		return 0;

	if (environment(me)->query("no_fight"))
		return notify_fail("�����ֹս����\n");

	if (! arg || ! objectp(obj = present(arg, environment(me))))
		return notify_fail("���빥��˭��\n");

	if (! obj->is_character())
		return notify_fail("�����һ�㣬�ǲ����������к��Ķ���\n");

	if (! living(obj))
		return notify_fail("�㻹Ҫ�򣿲���ɱ�����ˡ�\n");
	if (obj->query("owner") == me->query("id")) return notify_fail("�㾹Ȼ�����Լ��ĳ��̫���˵��˰ɣ�����\n");
	if (obj->is_fighting(me))
		return notify_fail("���ͣ����ͣ����ͣ�\n");

	if (obj==me)
		return notify_fail("���Լ�������ô�벻����\n");

	if (me->query("qi") < me->query("max_qi") * 3 / 10)
		return notify_fail("������û������ս���ˡ�\n");

	if ((me->query("age")<18 || me->query("combat_exp",1)<200000) && userp(obj))
		return notify_fail("СС��;���ɱ�˷Ż𣿻�������ȥ�ɡ�\n");

	if ((obj->query("age")<18 || obj->query("combat_exp",1)<200000) && userp(obj))
		return notify_fail("��С���Ѷ�Ҫɱ���㻹����ȱ��ѽ��\n");

	if (! wizardp(me) && wizardp(obj))
		return notify_fail("��Ҳ�����ͼɱ������Ա��\n");

	if (obj->query("can_speak"))
		message_vision("\n$N����$n���һ�������У�\n\n", me, obj);
	else
		message_vision("\n$N���һ������ʼ��$n����������\n\n", me, obj);

	notify_fail("���޴����֡�\n");
	switch (obj->accept_hit(me))
	{
	case 0:
		return 0;
	case -1:
		return 1;
	default:
	}

	me->fight_ob(obj);
	if (obj->query("can_speak"))
	{
		me->want_kill(obj);
		obj->fight_ob(me);
	} else
		obj->kill_ob(me);

	return 1;
}

int help(object me)
{
	write(@HELP
ָ���ʽ : hit <����>
 
���ָ������ֱ����һ��������С���������ʽ��ս���Ǽ�ʱ�ģ�ֻҪ���һ
��������ս���ͻῪʼ��ֱ��ĳһ������50% ����Ϊֹ�����ָ�����Щ��
ϲ��fight��NPC�����ã���Ϊ�ܶ�ʱ����ı���Ҫ��ᱻ�ܾ�������ʹ�������
���п����⵽NPC ��ǿ�ҷ�Ӧ������ҪС��ʹ�á�
 
�������ָ��: fight, kill

HELP );
	return 1;
}

