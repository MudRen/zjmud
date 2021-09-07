
#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(HIW "�޼��ɵ�" NOR, ({ "wuji xiandan", "dan" }) );
	set_weight(200);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", "һ���ɵ���ɢ�����������㣬��˵��������һ���˵İ�����\n");
		set("value", 500000);
		set("yuanbao", 300);
		set("unit", "��");
        set("no_sell",1);
        set("no_shop",1);
		set("only_do_effect", 1);
		set("suit_point",300);
	}
}

int do_effect(object me)
{
	mapping my;

	log_file("static/using", sprintf("%s(%s) eat �޼��ɵ� at %s.\n",
		 me->name(1), me->query("id"), ctime(time())));

	message_vision("$Nһ������������һ" + query("unit") + name() + "��\n", me);
	if (me->query("gift/xiandan_fail") > 0 && random(2))
	{
		write(HIM "������Լ���ͷ�Ը������ˡ�"NOR"\n");
		me->add("gift/xiandan_fail", -1);
		me->add("int", 1);
		write("\n "+HIR+"��ϲ�㣺"+NOR+HIG+"����"+name()+"�ɹ������������ԡ������ˣ�����"NOR"\n");
	}

	if (me->query("gift/unknowdan_fail") > 0 && random(2))
	{
		write(HIR "������Լ����ȽŸ�����ˡ�"NOR"\n");
		me->add("gift/unknowdan_fail", -1);
		me->add("dex", 1);
		write("\n "+HIR+"��ϲ�㣺"+NOR+HIG+"����"+name()+"�ɹ������������������ˣ�����"NOR"\n");
	}

	if (me->query("gift/xisuidan_fail") > 0 && random(2))
	{
		write(HIC "������Լ�����Ϣ��ͨ���ˡ�"NOR"\n");
		me->add("gift/xisuidan_fail", -1);
		me->add("con", 1);
		 write("\n "+HIR+"��ϲ�㣺"+NOR+HIG+"����"+name()+"�ɹ������������ʡ������ˣ�����"NOR"\n");
	}

	if (me->query("gift/shenliwan_fail") > 0 && random(2))
	{
		write(HIG "������Լ���������ǿ���ˡ�"NOR"\n");
		me->add("gift/shenliwan_fail", -1);
		me->add("str", 1);
		write("\n "+HIR+"��ϲ�㣺"+NOR+HIG+"����"+name()+"�ɹ�������������������ˣ�����"NOR"\n");
	}
	write(HIM "ڤڤ������������ֻ������̨һƬ�����������ޱȡ�"NOR"\n");
	me->add("magic_points", 600+random(1000));
	me->add("gift/xuelian", 1);
	my = me->query_entire_dbase();
	my["eff_jing"] = my["max_jing"];
	my["jing"] = my["max_jing"];
	my["eff_qi"] = my["max_qi"];
	my["qi"] = my["max_qi"];
	if (my["jingli"] < my["max_jingli"])
		my["jingli"] = my["max_jingli"];
	if (my["neili"] < my["max_neili"])
		my["neili"] = my["max_neili"];
	write(HIY "һ�󳩿�֮������û����Ǿ���"NOR"\n");
	destruct(this_object());
	return 1;
}

int query_autoload() { return 1; }