// xisuidan.c ϴ�赤

#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(YEL "ϴ�赤" NOR, ({ "xisui dan", "dan", "xisuidan" }) );
	set_weight(200);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", "һ�źڲ�����ĵ�ҩ����˵"ZJURL("cmds:eat xisui dan")ZJSIZE(20)"��"NOR"�˿�����ǿ���ʡ�\n");
		set("spectxt", "80%�ļ�������1��������ǡ�\n");
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
	if (me->query("gift/xisuidan") >= 5)
	{
		message_vision("$NͻȻ����һ������ޱȵ���ƨ��\n", me);
		tell_object(me, "����ô���ǳԻ��˶��ӡ�\n");
	} else
	if (random(10) >3 && !me->query("special_skill/lucky"))
	{
		tell_object(me, "��������ú���ûʲô���á�\n");
	      //me->add("gift/xisuidan_fail", 1);
	} else
	{
		message("vision", "���ƺ�����" + me->name() + "�Ĺ�ͷ���������졣\n",
				  environment(me), ({ me }));
		tell_object(me, HIY "�����Ĺ�����ʱ�������������ͣ���ɰ����Ż��ˣ�"
				"����һ�����ͣ���������ƺ���Ǹ�����ˡ�"NOR"\n");
		me->add("con", 1);
	      me->add("gift/xisuidan", 1);
		write("\n "+HIR+"��ϲ�㣺"+NOR+HIG+"����ϴ�赤�ɹ������������ʡ������ˣ�����"NOR"\n");
	}

	destruct(this_object());
	return 1;
}

int query_autoload() { return 1; }