// pigpart.h

#include <ansi.h>

void setup()
{
	if (clonep()) set("only_do_effect", 1);
	::setup();
}

int do_effect()
{
	return notify_fail("�������" + name() + "��\n");
}

int broil(object me, object ob)
{
	object fob;

	me = this_player();
	if (me->is_busy())
	{
		write("������æ���أ�������ٿ��ɡ�\n");
		return 1;
	}

	if (! query("food_remaining"))
	{
		write("�������û��ʲô��Ҫ�ٿ��˰ɣ�\n");
		return 1;
	}

	if (! query("only_do_effect"))
	{
		write("���˰ɣ��������ÿ����飬̫���ˡ�\n");
		return 1;
	}

	message_vision("$N��" + name() + "����" + ob->name() +
		       "��ϸϸ�Ŀ��ţ�ֻ����ࣱ�ࣵ�������һ"
		       "�����˵���ζɢ�˳�����\n", me);

	write(HIY "���" + name() + HIY "�����ˣ�"NOR"\n");
	set("long", "һ" + query("unit") + "�����������Ұ��" + name() + "��\n");
	set_name("��" + name(), 0);
	delete("only_do_effect");
	me->start_busy(1);
	return 1;
}
