//heifeng1.c

#include <ansi.h>
inherit ITEM;

void create()
{
	set_name(HIY "�ر�ͼ" NOR, ({ "cangbao tu" }));
	set("long", "һ�źڷ�կ�ر�ͼ��\n");
	set("unit", "��");
	set("value", 10);
	set("fuben_type", "heifeng");
	set("only_do_effect", 1);
	set("weight", 10);

	setup();
}

int do_effect(object me)
{
	if (me->is_busy())
		return notify_fail("����æ���ء�\n");

	//if (!wizardp(me))
	//	return notify_fail("��ʱ�رղر�ͼ���������޸������¿��š�\n");
	
	message_vision(CYN "$N" CYN "����һ��" + name() + CYN "����ʼ�Ա��Ź۲����ܡ�"NOR"\n", me);
	
	if (!query("where")) {
		tell_object(me,"�����Ųر�ͼ���ҿ����������Ųر�ͼԭ���Ǽٵġ�\n");
		return 1;
	}
	if(base_name(environment(me))!=query("where"))
	{
		tell_object(me,"����ղر�ͼ��������ϸ������һ�󣬽��ȴ�����ջ�\n");
		return 1;
	}

	if(FUBEN_D->create_fuben(me, query("fuben_type")))
	{
		message_vision(CYN "$N" CYN "������һ�����ص���ڣ���֪ͨ�����"NOR"\n", me);
            //me->command("fuben");
            tell_object(me,ZJFORCECMD("fuben"));
		destruct(this_object());
	}

	return 1;
}
#include "roombao.h"
void init()
{	
	do_copy();
}

int query_autoload() { return 1; }