// shenliwan.c ������

#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(HIG "������" NOR, ({ "shenli wan", "wan"}) );
	set_weight(200);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", "һ��ԲԲ�������裬��˵"ZJURL("cmds:eat shenli wan")ZJSIZE(20)"��"NOR"�˿�����ǿ������\n");
		set("value", 500000);
		set("yuanbao", 100);
            set("no_sell",1);
            set("no_give",1);
            set("no_drop",1);
            set("no_get",1);
            //set("no_put",1);
            set("no_shop",1);
		set("unit", "��");
		set("only_do_effect", 1);
		set("suit_point", 300);
	}
}

int do_effect(object me)
{
	message_vision("$Nһ������������һ��" + this_object()->name() +
		       "��\n", me);
	if (me->query("gift/shenliwan") >= 5)
	{
		message_vision("$Nգգ�ۡ�\n", me);
		tell_object(me, "�������ҩûɶζ���������绨���óԡ�\n");
	} else
	if (random(10) >3 && !me->query("special_skill/lucky"))
	{
		tell_object(me, "��������ú���ûʲô���á�\n");
	        //me->add("gift/shenliwan_fail", 1);
	} else
	{
		tell_object(me, HIR "�����˫�ۼ������ѣ�������������"NOR"\n");
		me->add("str", 1);
	      me->add("gift/shenliwan", 1);
		write("\n "+HIR+"��ϲ�㣺"+NOR+HIG+"����������ɹ�������������������ˣ�����"NOR"\n");
	}

	destruct(this_object());
	return 1;
}

int query_autoload() { return 1; }