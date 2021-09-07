// summon. ȡ�ر���

#include <ansi.h>
#include <command.h>

inherit F_CLEAN_UP;

int main(object me, string str)
{
	object ob;
	string file;

	if (! str)
		return notify_fail("��Ҫ�ٻ�ʲô��Ʒ��\n");

	if (me->is_busy())
		return notify_fail("��������æ�������п�����˵�ɡ�\n");

	sscanf(str, ".%s", str);

	if (! stringp(file = me->query("can_summon/" + str)))
		return notify_fail("�㲻֪������ٻ������Ʒ��\n");

	if (file_size(file + ".c") < 0 && file_size(file) < 0)
		return notify_fail("�㲻֪������ٻ������Ʒ��\n");

	if (me->is_ghost())
		return notify_fail("���㻹�������ٻ��ɡ�\n");

	call_other(file, "???");
	ob = find_object(file);
	if (! ob || ! ob->receive_summon(me))
	{
		message_vision(HIM "$N" HIM "��������������������"
			       "�ʡ�\nȻ��ʲôҲû�з��� :)\n", me);
	}

	if (me->is_fighting())
		me->start_busy(2 + random(3));

	return 1;
}

int help(object me)
{
	write(@HELP
ָ���ʽ : summon <��Ʒ��ID>

��ָ��������ĳЩ��Ʒ����������װ���ϣ���Ȼ�����һ����
����ʩչ�������С�
HELP );
	return 1;
}
