// miss ׷Ѱ��Ʒ

#include <ansi.h>
#include <command.h>

inherit F_CLEAN_UP;

int main(object me, string str)
{
	object ob;

	if (! str)
		return notify_fail("��Ҫ׷Ѱʲô��Ʒ��\n");

	if (! stringp(str = me->query("can_summon/" + str)))
		return notify_fail("�㲻֪�����׷Ѱ�����Ʒ��\n");

	if (me->is_ghost())
		return notify_fail("���㻹������׷Ѱ�ɡ�\n");

	if (me->query("doing"))
		return notify_fail("����ƻ�������˵�ɣ�\n");

	if (me->is_busy())
		return notify_fail("����æ������˵�ɡ�\n");

	if (! objectp(ob = find_object(str)) || ! environment(ob))
		return notify_fail("���������Ҳ�޷���Ӧ�������Ʒ��\n");

	ob->receive_miss(me);
	return 1;
}

int help(object me)
{
write(@HELP
ָ���ʽ : miss <������Ʒ��ID>

��ָ�������׷Ѱ�����Ƶ���Ʒ��������һ���ľ�������������
HELP
    );
    return 1;
}
