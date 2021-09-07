// burning.c

#include <ansi.h>

inherit F_CLEAN_UP;

void create()
{
	seteuid(ROOT_UID);
}

int main(object me, string arg)
{
	int count;

	if (me->query_temp("burning"))
		return notify_fail("����������ŭ���У�û�б�Ҫ�ٷ���һ�Ρ�\n");

	if (me->query_craze() < 1000)
		return notify_fail("�����ڻ�������ŭ���޷����Լ�ŭ��ȼ�ա�\n");

	message_vision(HIR "$N" HIR "һ�������Ŀ��ʱ�������䣬���ͱ��ˣ��Ʋ��ɵ���"NOR"\n", me);

	me->cost_craze(500 + random(300));
	count = me->query_skill("force") / 5;
	me->add_temp("apply/attack", count);
	me->set_temp("burning", 1);
	me->start_call_out(bind((: call_other, __FILE__, "remove_effect", me, count :), me),
			   1 + me->query_skill("force", 1) + random(100));

	return 1;
}

void remove_effect(object me, int count)
{
	if (me->query_temp("burning"))
	{
		me->delete_temp("burning");
		me->add_temp("apply/attack", -count);
		tell_object(me, "�����еķ�ŭ������ƽϢ�ˡ�\n");
	}
}

int help (object me)
{
	write(@HELP
ָ���ʽ: burning|fenu
 
���ָ�����㽫���ڽ�����ķ�ŭ��й�������������Գ�ֵ�������
�Ĺ����������ڷ�йʱ������������ķ�ŭ��

see also : berserk
HELP );
	return 1;
}
