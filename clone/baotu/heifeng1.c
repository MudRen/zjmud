// jinsha.c

#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(HIY "�ر�ͼ" NOR, ({ "cang baotu" }));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "һ�źڷ�ɽ�ر�ͼ��\n");
		set("unit", "��");
		set("value", 10);
		set("where", "/d/city/jiaowai7");
		set("fuben_type", "heifeng");
		set("only_do_effect", 1);
		set("weight", 10);
	}
	setup();
}

int do_effect(object me)
{
	string family,*skills;
	int i;

	message_vision(CYN "$N" CYN "����һ��" + name() + CYN "����ʼ�Ա��Ź۲����ܡ�"NOR"\n", me);
	if(base_name(environment(me))!=query("where"))
	{
		tell_object(me,"����ղر�ͼ��������ϸ������һ�󣬽��ȴ�����ջ�\n");
		return 1;
	}

	if(FUBEN_D->create_fuben(me,query("fuben_type")))
	{
		message_vision(CYN "$N" CYN "������һ�����صĶ��ڣ���֪ͨ�����"NOR"\n", me);
		destruct(this_object());
	}

	return 1;
}
