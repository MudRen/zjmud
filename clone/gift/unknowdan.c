// unknow.c ����ɵ�

#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(HIR "����ɵ�" NOR, ({ "huohong xiandan", "dan", "xiandan" }));
	set_weight(200);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", "һ��ԲԲ�Ļ���ɵ�����˵"ZJURL("cmds:eat huohong xiandan")ZJSIZE(20)"��"NOR"����������������\n");
		set("spectxt", "80%�ļ�������1����������\n");
		set("value", 500000);
		set("yuanbao", 100);
		set("no_give",1);
		set("no_drop",1);
		set("no_get",1);
            set("no_sell",1);
		set("unit", "��");
		set("only_do_effect", 1);
		set("suit_point",300);
	}
}

int do_effect(object me)
{
	message_vision("$Nһ������������һ��" + this_object()->name() +
		       "��\n", me);
	if (me->query("gift/unknowdan") >= 5)
	{
		message_vision("$Nҡҡ�λεģ�ͻȻ��žડ�һ����ˤ�˸���ͷ��\n", me);
		tell_object(me, "����ó����Ժ�ͷ�ؽ���ġ�\n");
	} else
	if (random(10) >3 && !me->query("special_skill/lucky"))
	{
		tell_object(me, "��������ú���ûʲô���á�\n");
	      //me->add("gift/unknowdan_fail", 1);
	} else
	{
		tell_object(me, HIM "��ʱ��������ȹ����ѣ�һʱ��ʹ���̣����˹�ȥ��"NOR"\n");
		me->add("dex", 1);
	      me->add("gift/unknowdan", 1);
		write("\n "+HIR+"��ϲ�㣺"+NOR+HIG+"���û���ɵ��ɹ������������������ˣ�����"NOR"\n");
		me->unconcious();
	}

	destruct(this_object());
	return 1;
}

int query_autoload() { return 1; }