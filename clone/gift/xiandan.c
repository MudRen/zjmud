// xiandan.c �����ɵ�

#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(HIY "�����ɵ�" NOR, ({ "xian dan", "dan", "xiandan" }) );
	set_weight(200);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", "һ��ԲԲ���ɵ�����˵"ZJURL("cmds:eat xian dan")ZJSIZE(20)"��"NOR"�˿�����ǿ������\n");
		set("spectxt", "80%�ļ�������1���������ԡ�\n");
		set("value", 500000);
		set("yuanbao", 100);
		set("no_give",1);
		set("no_drop",1);
		set("no_get",1);
            set("no_sell",1);
		set("unit", "��");
		set("only_do_effect", 1);
	       set("suit_point", 350);
	}
}

int do_effect(object me)
{
	message_vision("$Nһ������������һ��" + this_object()->name() +
		       "��\n", me);
	if (me->query("gift/xiandan") >= 5)
	{
		message_vision("$N��Ȼ�����ۡ�������һ�ء�\n", me);
		tell_object(me, "���������ǳ��Ŀࡣ\n");
	} else
	if (random(10) >3 && !me->query("special_skill/lucky"))
	{
		tell_object(me, "��������ú���ûʲô���á�\n");
	      //me->add("gift/xiandan_fail", 1);
	} else
	{
		tell_object(me, HIG "һ�ɻ�����Ȼ����������"
			    "��ͷʹ���ѣ�ǡ�ڴ�ʱһ������֮��"
			    "��Ȼ���𣬶ٸ���̩�ޱȡ�\n");
		me->add("int", 1);
	      me->add("gift/xiandan", 1);
	     write("\n "+HIR+"��ϲ�㣺"+NOR+HIG+"�����ɵ��ɹ������������ԡ������ˣ�����"NOR"\n");
	}

	destruct(this_object());
	return 1;
}

int query_autoload() { return 1; }